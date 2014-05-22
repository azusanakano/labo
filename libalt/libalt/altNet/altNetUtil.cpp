/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNetUtil.cpp
 * \brief   Network utility functions
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altNetUtil.h"
#include "altSSLSyncThread.h"
#include "altBase/altSignal.h"
#include "altBase/altStr.h"
#include "altBase/altSyncThread.h"

#include "openssl/ssl.h"

#ifdef ALT_LINUX
  #include <errno.h>
  #include <arpa/inet.h>
  #include <netdb.h>
  #include <signal.h>
#endif

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
#ifdef ALT_LINUX
  typedef unsigned char BYTE;
#endif

/*----------------------------------------------------------------*
 * Static variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Windows Sockets DLL Start up
///
/// \return ALT_S_SUCCESS     success
/// \return ALT_E_WSASTARTUP  start up error
/// \return ALT_E_WSAVERSION  WinSock version error
///
LIBALT_API alt_t altNetUtil::WSAStartup()
{
#ifdef ALT_WIN
  static altBool  st_bWSAStartupDone = false; ///< WSAStartup done or not
	if (! st_bWSAStartupDone) {
    static altSyncThread  st_oSyncWSAStartup; ///< WSAStartup sync thread object
    st_oSyncWSAStartup.BeginLock();
    if (! st_bWSAStartupDone) {
		  altInt  nRet;
		  WSADATA	oWsaData;
      altStr  sBuf;

		  WORD wVersionRequired = MAKEWORD(2, 2);

		  // Windows Sockets DLL start up
      nRet = ::WSAStartup (wVersionRequired, & oWsaData);
		  if (nRet != 0) {
        altInt nErrCode = WSAGetLastError ();
			  WSACleanup ();
        ALT_RET_P (ALT_E_WSASTARTUP, sBuf.Format ("Error Code=%d", nErrCode));
		  }

		  altInt nMajorVersion = LOBYTE (oWsaData.wVersion);
		  altInt nMinorVersion = HIBYTE (oWsaData.wVersion);
		  altInt nHiMajorVersion = LOBYTE (oWsaData.wHighVersion);
		  altInt nHiMinorVersion = HIBYTE (oWsaData.wHighVersion);

      ALT_LOG_P (ALT_D_DEBUG, sBuf.Format ("Version          : %d.%d", nMajorVersion, nMinorVersion));
		  ALT_LOG_P (ALT_D_DEBUG, sBuf.Format ("Hi Version       : %d.%d", nHiMajorVersion, nHiMinorVersion));
		  ALT_LOG_P (ALT_D_DEBUG, sBuf.Format ("Description      : %s", oWsaData.szDescription));
		  ALT_LOG_P (ALT_D_DEBUG, sBuf.Format ("System Status    : %s", oWsaData.szSystemStatus));
		  ALT_LOG_P (ALT_D_DEBUG, sBuf.Format ("Max Sockets      : %d", oWsaData.iMaxSockets));
		  ALT_LOG_P (ALT_D_DEBUG, sBuf.Format ("Max UDP DataGram : %d", oWsaData.iMaxUdpDg));

		  // check version
		  if (oWsaData.wVersion != wVersionRequired) {
			  WSACleanup ();
        ALT_RET_P (ALT_E_WSAVERSION, sBuf.Format ("WinSock API Version(%d.%d)", LOBYTE (oWsaData.wVersion), HIBYTE (oWsaData.wVersion)));
		  }
		  st_bWSAStartupDone = true;
    }
    st_oSyncWSAStartup.EndLock();
	}
#endif //ALT_WIN
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief	create socket
///
/// \param  nAf       [I ] AF_INET etc
/// \param  nType     [I ] SOCK_STREAM etc
/// \param  nProtocol [I ] 0 etc
/// \param  nSocket   [ O] new socket
///
/// \return	ALT_S_SUCCESS success
/// \return	ALT_E_SOCKET  error
///
LIBALT_API alt_t altNetUtil::CreateSocket(const altInt nAf, const altInt nType, const altInt nProtocol, SOCKET & nSocket)
{
  WSAStartup();
	nSocket = socket (nAf, nType, nProtocol);

#ifdef ALT_WIN
	if (nSocket == INVALID_SOCKET) {
		nSocket = 0;
    altStr sBuf;
    ALT_RET_P (ALT_E_SOCKET, sBuf.Format ("Error Code=%d", WSAGetLastError()));
	}
#endif

#ifdef ALT_LINUX
	if (nSocket < 0) {
		int nErrCode = errno;
		nSocket = 0;
    altStr sBuf;
    ALT_RET_P (ALT_E_SOCKET, sBuf.Format ("Error Code=%d (%s)", nErrCode, strerror (nErrCode)));
	}
#endif

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  close socket
///
/// \param  nSocket [IO] socket
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altNetUtil::CloseSocket(SOCKET & nSocket)
{
  altInt nRet;
  altStr sBuf;

#ifdef ALT_WIN
  nRet = ::shutdown (nSocket, SD_SEND);
  if (nRet != 0) {
    ALT_LOG_P (ALT_E_ERROR, sBuf.Format ("nSocket=%d Error Code=%d", nSocket, WSAGetLastError()));
  }

  nRet = ::closesocket (nSocket);
  if (nRet != 0) {
    ALT_LOG_P (ALT_E_ERROR, sBuf.Format ("nSocket=%d Error Code=%d", nSocket, WSAGetLastError()));
  }
#endif

#ifdef ALT_LINUX
  nRet = ::shutdown (nSocket, SHUT_RD);
  if (nRet != 0) {
    ALT_LOG_P (ALT_E_ERROR, sBuf.Format ("Error Code=%d (%s)", errno, strerror (errno)));
  }

  nRet = ::close (nSocket);
  if (nRet != 0) {
    ALT_LOG_P (ALT_E_ERROR, sBuf.Format ("Error Code=%d (%s)", errno, strerror (errno)));
  }
#endif

  nSocket = 0;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  connect
///
/// \param  nSocket   [I ] socket
/// \param  oInetAddr [I ] socket address
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_CONNECT   connect error
///
LIBALT_API alt_t altNetUtil::Connect(const SOCKET nSocket, const altInetAddress & oInetAddr)
{
  altInt    nRet;
  altStr    sBuf;
  nRet = ::connect (nSocket, (const sockaddr *)oInetAddr.GetAddrInPtr(), oInetAddr.GetAddrLen());
#ifdef ALT_WIN
  if (nRet == SOCKET_ERROR) {
    ALT_RET_P (ALT_E_CONNECT, sBuf.Format ("Error Code=%d %s:%d", WSAGetLastError(), oInetAddr.GetIP().GetCStr(), oInetAddr.GetPort()));
  }
#endif
#ifdef ALT_LINUX
  if (nRet != 0) {
    altInt nErrNo = errno;
    ALT_RET_P (ALT_E_CONNECT, sBuf.Format ("Error Code=%d (%s) %s:%d", nErrNo, strerror (nErrNo), oInetAddr.GetIP().GetCStr(), oInetAddr.GetPort()));
  }
#endif
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief	bind
///
/// \param	nSocket   [I ] Socket
/// \param  oInetAddr [I ] Internet Socket Addresss
///
/// \return ALT_S_SUCCESS  success
/// \return ALT_E_BIND     error
///
LIBALT_API alt_t altNetUtil::Bind(const SOCKET nSocket, const altInetAddress & oInetAddr)
{
	altInt  nRet;
  altStr  sBuf;
	nRet = ::bind (nSocket, (const sockaddr *)oInetAddr.GetAddrInPtr(), oInetAddr.GetAddrLen());

#ifdef ALT_WIN
	if (nRet == SOCKET_ERROR) {
		ALT_RET_P (ALT_E_BIND, sBuf.Format ("Error Code=%d", WSAGetLastError()));
	}
#endif

#ifdef ALT_LINUX
	if (nRet < 0) {
		ALT_RET_P (ALT_E_BIND, sBuf.Format ("Error Code=%d (%s)", errno, strerror (errno)));
	}
#endif

	ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief listen
///
/// \param  nSocket         [I ] socket
/// \param  nListenQueSize  [I ] listen que size
///
/// \return ALT_S_SUCCESS  success
/// \return ALT_E_LISTEN   error
///
LIBALT_API alt_t altNetUtil::Listen(const SOCKET nSocket, const altInt nListenQueSize)
{
	altInt  nRet;
  altStr  sBuf;

	nRet = ::listen (nSocket, nListenQueSize);
#ifdef ALT_WIN
	if (nRet == SOCKET_ERROR) {
		ALT_RET_P (ALT_E_LISTEN, sBuf.Format ("Error Code=%d", WSAGetLastError()));
	}
#endif
#ifdef ALT_LINUX
	if (nRet < 0) {
		ALT_RET_P (ALT_E_LISTEN, sBuf.Format ("Error Code=%d (%s)", errno, strerror (errno)));
	}
#endif

	ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  select
///
/// \param  nMaxSocket  [I ] max socket number
/// \param  pRfds       [IO] read file descriptors
/// \param  pWfds       [IO] write file descriptors
/// \param  pEfds       [IO] error file descriptors
/// \param  pTimeout    [I ] timeout
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_S_TIMEOUT   timeout
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altNetUtil::Select(const SOCKET nMaxSocket, fd_set * pRfds, fd_set * pWfds, fd_set * pEfds, struct timeval * pTimeout)
{
  altInt nRet = select ((altInt)nMaxSocket + 1, pRfds, pWfds, pEfds, pTimeout);
#ifdef ALT_WIN
  if (nRet == SOCKET_ERROR) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("Error Code=%d", WSAGetLastError()));
  }
#endif

#ifdef ALT_LINUX
  if (nRet < 0) {
    altInt nErrNo = errno;
    altStr sBuf;
    if (nErrNo != EINTR) {
      ALT_RET_P (ALT_E_ERROR, sBuf.Format ("Error Code=%d (%s)", nErrNo, strerror (nErrNo)));
    }
  }
#endif

  if (nRet == 0) {
    ALT_RET (ALT_S_TIMEOUT);
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief	Accept
///
/// \param	nSocket         [I ] socket number
/// \param	pAddrIn         [IO] pointer of address structure
/// \param	pAddrSize       [IO] pointer size of address structure
/// \param	nAcceptedSocket [ O] accepted socket number
///
/// \return ED_S_SUCCESS  success
/// \return ED_E_ERROR    error
///
LIBALT_API alt_t altNetUtil::Accept(const SOCKET nSocket, SOCKADDR_IN * pAddrIn, altInt * pAddrSize, SOCKET & nAcceptedSocket)
{

#ifdef ALT_WIN
	nAcceptedSocket = accept (nSocket, (sockaddr *)pAddrIn, pAddrSize);
	if (nAcceptedSocket == INVALID_SOCKET) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("Error Code=%d", WSAGetLastError()));
  }
#endif

#ifdef ALT_LINUX
	nAcceptedSocket = accept (nSocket, (sockaddr *)pAddrIn, (socklen_t *)pAddrSize);
	if (nAcceptedSocket < 0) {
    altStr  sBuf;
		ALT_RET_P (ALT_E_ERROR, sBuf.Format ("SOCKET=%d Error Code=%d (%s)", nSocket, errno, strerror (errno)));
	}
#endif
	ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Receive
///
/// \param  nSocket   [I ] socket
/// \param  pBuf      [IO] receive buffer
/// \param  nBufSize  [I ] receive buffer size
/// \param  nRecvSize [ O] receive size
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_S_NET_EOF   connection closed
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altNetUtil::Recv(const SOCKET nSocket, altChar * pBuf, const altUInt nBufSize, altInt & nRecvSize)
{
  altStr sBuf;
retry:
  nRecvSize = ::recv (nSocket, pBuf, nBufSize, 0);
  if (nRecvSize == 0) {
    ALT_RET (ALT_S_NET_EOF);
  }

#ifdef ALT_WIN
  if (nRecvSize == SOCKET_ERROR) {
    altInt nErrNo = WSAGetLastError();
    if (nErrNo == WSAEWOULDBLOCK) {
      goto retry;
    }
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("nSocket=%d nErrorNO=%d", nSocket, nErrNo));
  }
#endif

#ifdef ALT_LINUX
  if (nRecvSize < 0) {
    altInt nErrNo = errno;
    if (nErrNo == EINTR || nErrNo == EAGAIN) {
      goto retry;
    }
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("nSocket=%d nErrorNO=%d (%s)", nSocket, nErrNo, strerror (nErrNo)));
  }
#endif

  ALT_LOG_P (ALT_D_RECV, sBuf.Format ("nRecvSize=%d", nRecvSize));

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send
///
/// \param  nSocket   [I ] socket
/// \param  pData     [I ] data
/// \param  nSize     [I ] data size
/// \param  nSendByte [I ] send byte
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_INVAL     invalid parameter
/// \return ALT_E_SEND      send error
///
LIBALT_API alt_t altNetUtil::Send(const SOCKET nSocket, const altChar * pData, const altInt nSize, altInt & nSendByte)
{
  if (pData == NULL) {
    ALT_RET_P (ALT_E_INVAL, "pData is NULL");
  }
  nSendByte = 0;
  altStr  sBuf;

  while (nSize != nSendByte) {
    altInt nRet;

#ifdef ALT_WIN
    nRet = ::send (nSocket, & pData[nSendByte], nSize - nSendByte, 0);
    if (nRet == SOCKET_ERROR) {
      ALT_RET_P (ALT_E_SEND, sBuf.Format ("Error Code=%d", WSAGetLastError()));
    }
#endif

#ifdef ALT_LINUX
    alt_t status = altSignal::Block (SIGPIPE);
    ALT_LOG (status);
    nRet = ::send (nSocket, & pData[nSendByte], nSize - nSendByte, MSG_DONTWAIT);
    if (nRet < 0) {
      ALT_RET_P (ALT_E_SEND, sBuf.Format ("Error Code=%d (%s)", errno, strerror (errno)));
    }
#endif

    nSendByte += nRet;
  }

  ALT_LOG_P (ALT_D_SEND, sBuf.Format ("nSendByte=%d", nSendByte));

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Initialize SSL Library
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altNetUtil::SSLLibraryInit()
{
  alt_t status;
  
  static altBool bSSLInitDone = false;
  if (! bSSLInitDone) {
    static altSyncThread oSyncThread;
    oSyncThread.BeginLock();
    if (! bSSLInitDone) {
      SSL_load_error_strings();
		  SSL_library_init();
      status = altSSLSyncThread::InitLock();
      if (ALT_IS_ERR (status)) {
        oSyncThread.EndLock();
        ALT_RET (status);
      }
    }
    oSyncThread.EndLock();
  }

  ALT_RET (ALT_S_SUCCESS);
}


///
/// \brief SSL Read
///
/// \param  pSSL      [IO] Pointer of SSL Object
/// \param  pBuf      [IO] Recv Buffer
/// \param  nBufSize  [I ] Recv Buffer Size
/// \param  nRecvSize [I ] Recv Size
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_S_NET_EOF   connection closed
/// \return ALT_E_RECV      recv error
///
LIBALT_API alt_t altNetUtil::RecvSSL(SSL * pSSL, altChar * pBuf, const altUInt nBufSize, altInt & nRecvSize)
{
retry:
  if (pSSL == NULL) {
    ALT_RET_P (ALT_E_RECV, "pSSL is NULL");
  }
  nRecvSize = SSL_read (pSSL, pBuf, nBufSize);
  if (nRecvSize < 0) {
    altInt nErrorCode = SSL_get_error (pSSL, nRecvSize);
    if (nErrorCode == SSL_ERROR_WANT_READ) {
      goto retry;
    }
    else if (nErrorCode == SSL_ERROR_SYSCALL) {
      altStr sBuf;
#ifdef ALT_WIN
      altInt nLastError = WSAGetLastError ();
      altInt nErrNo = errno;
      if (nErrNo == EAGAIN) {
        goto retry;
      }
      ALT_RET_P (ALT_E_RECV, sBuf.Format ("SSL_read error (%d) LastError=%d errno=%d", nErrorCode, nLastError, nErrNo));
#endif
#ifdef ALT_LINUX
      altInt	nErrNo = errno;
      if (nErrNo == EAGAIN) {
        goto retry;
      }
      ALT_RET_P (ALT_E_RECV, sBuf.Format ("SSL_read error (%d) errno=%d (%s)", nErrorCode, nErrNo, strerror (nErrNo)));
#endif
    }
    else {
      altStr sBuf;
      ALT_RET_P (ALT_E_RECV, sBuf.Format ("SSL_read error (%d) (%s)", nErrorCode, ERR_reason_error_string (ERR_get_error())));
    }
  }
  else if (nRecvSize == 0) {
    ALT_RET (ALT_S_NET_EOF);
  }

  altStr sBuf;
  ALT_LOG_P (ALT_D_RECV, sBuf.Format ("nRecvSize=%d", nRecvSize));
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send SSL
///
/// \param  pSSL      [IO] Pointer of SSL Object
/// \param  pData     [I ] Send Data
/// \param  nSize     [I ] Send Data Size
/// \param  nSendSize [ O] Send Bytes 
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_SEND    send error
///
LIBALT_API alt_t altNetUtil::SendSSL(SSL * pSSL, const altChar * pData, const altInt nSize, altInt & nSendSize)
{
  retry:
  if (pSSL == NULL) {
    ALT_RET_P (ALT_E_SEND, "pSSL is NULL");
  }

  nSendSize = SSL_write (pSSL, pData, nSize);
  if (nSendSize < 0) {
    altInt nErrorCode = SSL_get_error (pSSL, nSendSize);
    if (nErrorCode == SSL_ERROR_WANT_WRITE) {
      goto retry;
    }
    else if (nErrorCode == SSL_ERROR_SSL) {
      altStr sBuf;
      ALT_RET_P (ALT_E_SEND, sBuf.Format ("SSL_read error (%d) (%s)", nErrorCode, ERR_reason_error_string (ERR_get_error())));
    }
    else if (nErrorCode == SSL_ERROR_SYSCALL) {
#ifdef ALT_WIN
      altInt  nErrNo = WSAGetLastError ();
      altStr  sBuf;
      ALT_RET_P (ALT_E_SEND, sBuf.Format ("SSL_write error (%d) %d", nErrorCode, nErrNo));
#endif
#ifdef ALT_LINUX
      altInt  nErrNo = errno;
      altStr  sBuf;
      ALT_RET_P (ALT_E_SEND, sBuf.Format ("SSL_write error (%d) %d (%s)", nErrorCode, nErrNo, strerror (nErrNo)));
#endif
    }
    else {
      altStr  sBuf;
      ALT_RET_P (ALT_E_SEND, sBuf.Format ("SSL_write error (%d) (%s)", nErrorCode, ERR_reason_error_string (ERR_get_error())));
    }
  }

  altStr sBuf;
  ALT_LOG_P (ALT_D_SEND, sBuf.Format ("nSendByte=%d", nSendSize));
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Local IP Addr
///
/// \param  sIPAddr [ O] Local IP Address
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altNetUtil::GetLocalIPAddr(altStr & sIPAddr)
{
  alt_t status = altNetUtil::WSAStartup();
  if (ALT_IS_ERR (status)) {
    ALT_RET (ALT_E_ERROR);
  }
  
  altChar buf[BUFSIZ];
  altInt nRet = gethostname (buf, sizeof (buf));
  if (nRet != 0) {
    ALT_RET (ALT_E_ERROR);
  }

  LPHOSTENT pHostEnt = gethostbyname (buf);
  if (pHostEnt->h_addr_list[0] == NULL) {
    ALT_RET (ALT_E_ERROR);
  }

  sIPAddr.Format("%d.%d.%d.%d", 
    (BYTE)*((pHostEnt->h_addr_list[0])),
    (BYTE)*((pHostEnt->h_addr_list[0])+1),
    (BYTE)*((pHostEnt->h_addr_list[0])+2),
    (BYTE)*((pHostEnt->h_addr_list[0])+3));

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get local host name
///
/// \param  sHostname [ O] Local host name
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altNetUtil::GetLocalHostName(altStr & sHostname)
{
  alt_t status = altNetUtil::WSAStartup();
  if (ALT_IS_ERR (status)) {
    ALT_RET (ALT_E_ERROR);
  }
  
  altChar buf[BUFSIZ];
  memset (buf, 0x00, sizeof (buf));
  altInt nRet = gethostname (buf, sizeof (buf) - 1);
  if (nRet != 0) {
    ALT_RET (ALT_E_ERROR);
  }

  sHostname = buf;

  ALT_RET (ALT_S_SUCCESS);
}

#if 0
///
/// \brief  Signal Hander
///
/// \param  nSignal [I ] Signal Number
///
LIBALT_API void altNetUtil::SignalHandler(altInt nSignal)
{
  altStr sBuf;
  ALT_LOG_P (ALT_I_INFO, sBuf.Format ("nSignal=%d", nSignal));
  return;
}
#endif


