/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSSLAcceptor.cpp
 * \brief   SSL network server acceptor class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altSSLAcceptor.h"
#include "altSSLServerConnection.h"
#include "altSSLConnection.h"
#include "altNETConnectionManager.h"
#include "altNetUtil.h"
#include "altBase/altUtil.h"
#include "openssl/ssl.h"

#include <fcntl.h>

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
/// \param  pReceiveCallBack    [I ] receive call back function
/// \param  nThreadCount        [I ] Reqeust Thread Count
/// \param  nAcceptThreadCount  [I ] Accept Thread Count
/// \param  nSSLVersion         [I ] SSL Version (ALT_SSL_V2 or ALT_SSL_V3 or ALT_TSL_V1)
///
LIBALT_API altSSLAcceptor::altSSLAcceptor(const altNETReceiveCallBack pReceiveCallBack, const altUInt nThreadCount, const altUInt nAcceptThreadCount, const altByte nSSLVersion) :
m_pReceiveCallBack (pReceiveCallBack),
m_oReceiverBroker (pReceiveCallBack, nThreadCount),
m_pAcceptCallBack (NULL),
m_nPort (0),
m_nListenSocket (0),
m_nAcceptThreadCount (nAcceptThreadCount),
m_oAcceptThreadContainer(),
m_oSenderBroker(),
m_nSSLVersion (nSSLVersion)
{
}

///
/// \brief  Destructor
///
LIBALT_API altSSLAcceptor::~altSSLAcceptor()
{
  alt_t status = ClosePort();
  ALT_LOG (status);
}


///
/// \brief  Open Port
///
/// \param  nPort               [I ] Port NO
/// \param  nListenQueSize      [I ] Listen Queue Size
/// \param  pAcceptCallBack     [I ] Accept Call Back Function
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_INVAL     parameter error
/// \return ALT_E_SOCKET    create socket error
/// \return ALT_E_BIND      bind error
/// \return ALT_E_LISTEN    listen error
///
LIBALT_API alt_t altSSLAcceptor::OpenPort(const altInt nPort, const altInt nListenQueSize, const altNETAcceptCallBack pAcceptCallBack)
{
  alt_t   status;
  altStr  sBuf;

  // create listen socket
  if (m_nListenSocket.GetSocket() == 0) {
    status = m_nListenSocket.Init (AF_INET, SOCK_STREAM, 0);
    ALT_ERR_RET_P (status, sBuf.Format ("nPort=%d nListenQueSize=%d", nPort, nListenQueSize));
  }

  // listen
  status = m_nListenSocket.Listen (nPort, nListenQueSize);
  ALT_ERR_RET_P (status, sBuf.Format ("nPort=%d nListenQueSize=%d", nPort, nListenQueSize));

  m_pAcceptCallBack = pAcceptCallBack;
  m_nPort = nPort;

  // Add TCP Receiver Broker to Connection Manager
  aiNETConnectionManager.Add (nPort, & m_oReceiverBroker);

  // start accept thread
  for (altUInt i = 0; i < m_nAcceptThreadCount; i++) {
    altLoopThread * pLoopThread = ALT_NEW altLoopThread();
    if (pLoopThread == NULL) {
      ALT_RET (ALT_E_NOMEM);
    }
    pLoopThread->Start (altSSLAcceptor::AcceptThread, this);
    m_oAcceptThreadContainer.push_back (pLoopThread);
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Close Port
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altSSLAcceptor::ClosePort()
{
  alt_t status = m_nListenSocket.Close();
  ALT_LOG (status);
  for (altUInt i = 0; i < m_oAcceptThreadContainer.size(); i++) {
    m_oAcceptThreadContainer[i]->Stop();
    m_oAcceptThreadContainer[i] = NULL;
  }
  m_oAcceptThreadContainer.clear();
  m_nPort = 0;
  m_pAcceptCallBack = NULL;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Accept Thread
///
/// \param  pParam  [I ] parameter
///
LIBALT_API alt_t altSSLAcceptor::AcceptThread(void * pParam)
{
  altSSLAcceptor *  pAcceptor = static_cast<altSSLAcceptor *>(pParam);
  fd_set            oRfds;
  struct timeval    oTimeout;
  alt_t             status;
  SOCKET            nServerSocket = pAcceptor->m_nListenSocket.GetSocket();

  FD_ZERO (& oRfds);
  FD_SET (nServerSocket, & oRfds);

  oTimeout.tv_sec = 0;
  oTimeout.tv_usec = 100;

  status = altNetUtil::Select (nServerSocket, & oRfds, NULL, NULL, & oTimeout);
  ALT_ERR_RET (status);

  if (status == ALT_S_SUCCESS) {
    SOCKADDR_IN oClientSockAddr;
    altInt      nClientSockAddrLen = sizeof (oClientSockAddr);
    SOCKET      nClientSocket;

    // accept
    status = altNetUtil::Accept (nServerSocket, & oClientSockAddr, & nClientSockAddrLen, nClientSocket);
    ALT_ERR_RET (status);

    SSL_CTX * pSSLContext = NULL;
    
    if (pAcceptor->m_nSSLVersion == ALT_SSL_V23) {
      ALT_LOG_P (ALT_D_DEBUG, "use SSLv23_server_method()");
      pSSLContext = SSL_CTX_new (SSLv23_server_method ());
    }
    else if (pAcceptor->m_nSSLVersion == ALT_SSL_V2) {
      ALT_LOG_P (ALT_D_DEBUG, "use SSLv2_server_method()");
      pSSLContext = SSL_CTX_new (SSLv2_server_method ());
    }
    else if (pAcceptor->m_nSSLVersion == ALT_SSL_V3) {
      ALT_LOG_P (ALT_D_DEBUG, "use SSLv3_server_method()");
      pSSLContext = SSL_CTX_new (SSLv3_server_method ());
    }
    else if (pAcceptor->m_nSSLVersion == ALT_TSL_V1) {
      ALT_LOG_P (ALT_D_DEBUG, "use TLSv1_server_method()");
      pSSLContext = SSL_CTX_new (TLSv1_server_method ());
    }

    if (pSSLContext == NULL) {
      altNetUtil::CloseSocket (nClientSocket);
      ALT_RET_P (ALT_E_ERROR, "SSL_CTX_new error");
    }

    SSL * pSSL = SSL_new (pSSLContext);
    if (pSSL == NULL) {
      altNetUtil::CloseSocket (nClientSocket);
      ALT_RET_P (ALT_E_ERROR, "SSL_new error");
    }

    altInt nRet = SSL_set_fd (pSSL, (int)nClientSocket);
    if (nRet == 0) {
      altNetUtil::CloseSocket (nClientSocket);
      ALT_RET_P (ALT_E_ERROR, "SSL_set_fd error");
    }

    nRet = SSL_use_certificate_file (pSSL, "public.key", SSL_FILETYPE_PEM);
    if (nRet != 1) {
      altInt  nErrNo = errno;
      altInt  nSSLErrNo = SSL_get_error (pSSL, nRet);
      DWORD   dwSSLErrNo = ERR_get_error();
      altStr  sBuf;
      
      altNetUtil::CloseSocket (nClientSocket);

#ifdef ALT_WIN
      altChar szBuf[BUFSIZ];
      strerror_s (szBuf, sizeof (szBuf), nErrNo);
      ALT_RET_P (ALT_E_ERROR, sBuf.Format ("SSL_use_certificate_file error (%d:%s) SSL_ERR_NO=%d(%lu:%s)", nErrNo, szBuf, nSSLErrNo, dwSSLErrNo, ERR_reason_error_string (dwSSLErrNo)));
#endif
#ifdef ALT_LINUX
      ALT_RET_P (ALT_E_ERROR, sBuf.Format ("SSL_use_certificate_file error (%d:%s) SSL_ERR_NO=%d(%lu:%s)", nErrNo, strerror (nErrNo), nSSLErrNo, dwSSLErrNo, ERR_reason_error_string (dwSSLErrNo)));
#endif
    }

    nRet = SSL_use_PrivateKey_file (pSSL, "private.key", SSL_FILETYPE_PEM);
    if (nRet != 1) {
      altInt  nErrNo = errno;
      altInt  nSSLErrNo = SSL_get_error (pSSL, nRet);
      DWORD   dwSSLErrNo = ERR_get_error();
      altStr  sBuf;
      
      altNetUtil::CloseSocket (nClientSocket);

#ifdef ALT_WIN
      altChar szBuf[BUFSIZ];
      strerror_s (szBuf, sizeof (szBuf), nErrNo);
      ALT_RET_P (ALT_E_ERROR, sBuf.Format ("SSL_use_certificate_file error (%d:%s) SSL_ERR_NO=%d(%lu:%s)", nErrNo, szBuf, nSSLErrNo, dwSSLErrNo, ERR_reason_error_string (dwSSLErrNo)));
#endif
#ifdef ALT_LINUX
      ALT_RET_P (ALT_E_ERROR, sBuf.Format ("SSL_use_PrivateKey_file error (%d:%s) SSL_ERR_NO=%d(%lu:%s)", nErrNo, strerror (nErrNo), nSSLErrNo, dwSSLErrNo, ERR_reason_error_string (dwSSLErrNo)));
#endif
    }

retry_ssl_accept:
    nRet = SSL_accept (pSSL);
    if (nRet != 1) {
      altInt nErrNo = SSL_get_error (pSSL, nRet);
      if (nErrNo == SSL_ERROR_WANT_ACCEPT) {
        goto retry_ssl_accept;
      }
      else if (nErrNo == SSL_ERROR_SYSCALL) {
#ifdef ALT_WIN
        altInt nErrorNo = WSAGetLastError();
        altStr sBuf;
        ALT_LOG_P (ALT_E_ERROR, sBuf.Format ("SSL_accept error (%d) %d", nErrNo, nErrorNo));
#endif
#ifdef ALT_LINUX
        altInt nErrorNo = errno;
        altStr sBuf;
        ALT_LOG_P (ALT_E_ERROR, sBuf.Format ("SSL_accept error (%d) %d:%s", nErrNo, nErrorNo, strerror (nErrorNo)));
#endif
        altNetUtil::CloseSocket (nClientSocket);
        ALT_RET (ALT_E_ERROR);
      }
      else {
        DWORD   dwSSLErrNo = ERR_get_error();
        altStr  sBuf;
        altNetUtil::CloseSocket (nClientSocket);
        ALT_RET_P (ALT_E_ERROR, sBuf.Format ("SSL_accept error (%d) (%lu:%s)", nErrNo, dwSSLErrNo, ERR_reason_error_string (dwSSLErrNo)));
      }
    }

    // Set non block
#ifdef ALT_LINUX
    altInt nFlag = fcntl (nClientSocket, F_GETFL, 0);
    fcntl (nClientSocket, F_SETFL, nFlag | O_NONBLOCK);
#endif
#ifdef ALT_WIN
    u_long nFlag = 1;
    ioctlsocket (nClientSocket, FIONBIO, & nFlag);
#endif

    altInetAddress oInetAddress(oClientSockAddr);

    altCNETConnectionPtr       pNETConnection;
    altCNETServerConnectionPtr pServerConnection;

    // create new connection
    if (aiNETConnectionManager.IsServerIP (oInetAddress.GetIP())) {
      pServerConnection = ALT_NEW altSSLServerConnection (pSSL, pSSLContext, nClientSocket, oClientSockAddr, pAcceptor->m_nPort, pAcceptor->m_oSenderBroker, aiNETConnectionManager.GetServerInfo (oInetAddress.GetIP()));
      pNETConnection = (altCNETConnection *)pServerConnection.get_ptr();
      if (pNETConnection == NULL) {
        ALT_RET (ALT_E_NOMEM);
      }
    }
    else {
      pNETConnection = ALT_NEW altSSLConnection (pSSL, pSSLContext, nClientSocket, oClientSockAddr, pAcceptor->m_nPort, pAcceptor->m_oSenderBroker);
      if (pNETConnection == NULL) {
        ALT_RET (ALT_E_NOMEM);
      }
    }

    // add to connection manager
    status = aiNETConnectionManager.Add (pNETConnection);
    if (ALT_IS_ERR (status)) {
      SOCKET nClientSocket = pNETConnection->GetSocket();
      altNetUtil::CloseSocket (nClientSocket);
      ALT_RET (status);
    }

    // add to receive broker
    status = pAcceptor->m_oReceiverBroker.Add (pNETConnection);
    if (ALT_IS_ERR (status)) {
      aiNETConnectionManager.Del (pNETConnection);
      ALT_RET (status);
    }

    // Call Accept call back function
    if (aiNETConnectionManager.IsServerIP (pNETConnection->GetIP())) {
      ALT_ASSERT (pServerConnection != NULL);
      pServerConnection->CallAcceptCallBack (pAcceptor->m_nPort);
    }
    else {
      if (pAcceptor->m_pAcceptCallBack != NULL) {
        pAcceptor->m_pAcceptCallBack (pAcceptor->m_nPort, pNETConnection);
      }
    }
  }

  ALT_RET (ALT_S_SUCCESS);
}
