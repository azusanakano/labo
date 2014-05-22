#ifndef ALTNETUTIL_H
#define ALTNETUTIL_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNetUtil.h
 * \brief   Network utility functions
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altInetAddress.h>
#include <altBase/altLog.h>
#include <altBase/altStatus.h>

#ifdef ALT_WIN
  #include <altNet/openssl/ssl.h>
  #include <altNet/openssl/err.h>
  #include <altNet/openssl/rand.h>
#endif

#ifdef ALT_LINUX
  #include <openssl/ssl.h>
  #include <openssl/err.h>
  #include <openssl/rand.h>
  #include <sys/types.h>
  #include <sys/socket.h>
#endif

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/


/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
class altNetUtil
{
public:
  ///
  /// \brief  Windows Sockets DLL Start up
  ///
  /// \return ALT_S_SUCCESS     success
  /// \return ALT_E_WSASTARTUP  start up error
  /// \return ALT_E_WSAVERSION  WinSock version error
  ///
  LIBALT_API static alt_t WSAStartup();

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
  LIBALT_API static alt_t CreateSocket(const altInt nAf, const altInt nType, const altInt nProtocol, SOCKET & nSocket);

  ///
  /// \brief  close socket
  ///
  /// \param  nSocket [IO] socket
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API static alt_t CloseSocket(SOCKET & nSocket);

  ///
  /// \brief  connect
  ///
  /// \param  nSocket   [I ] socket
  /// \param  oInetAddr [I ] socket address
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_CONNECT   connect error
  ///
  LIBALT_API static alt_t Connect(const SOCKET nSocket, const altInetAddress & oInetAddr);

  ///
  /// \brief	bind
  ///
  /// \param	nSocket   [I ] Socket
  /// \param  oInetAddr [I ] Internet Socket Addresss
  ///
  /// \return ALT_S_SUCCESS  success
  /// \return ALT_E_BIND     error
  ///
  LIBALT_API static alt_t Bind(const SOCKET nSocket, const altInetAddress & oInetAddr);

  ///
  /// \brief listen
  ///
  /// \param  nSocket         [I ] socket
  /// \param  nListenQueSize  [I ] listen que size
  ///
  /// \return ALT_S_SUCCESS  success
  /// \return ALT_E_LISTEN   error
  ///
  LIBALT_API static alt_t Listen(const SOCKET nSocket, const altInt nListenQueSize);

  ///
  /// \brief  select
  ///
  /// \param  nMaxSocket  [I ] max socket number
  /// \param  pRfds       [IO] read file descriptors
  /// \param  pWfds       [IO] write file descriptors
  /// \param  pEfds       [IO] error file descriptors
  /// \param  pTimeout    [I ] タイムアウト
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_S_TIMEOUT   timeout
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API static alt_t Select(const SOCKET nMaxSocket, fd_set * pRfds, fd_set * pWfds, fd_set * pEfds, struct timeval * pTimeout);

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
  LIBALT_API static alt_t Accept(const SOCKET nSocket, SOCKADDR_IN * pAddrIn, altInt * pAddrSize, SOCKET & nAcceptedSocket);

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
  LIBALT_API static alt_t Recv(const SOCKET nSocket, altChar * pBuf, const altUInt nBufSize, altInt & nRecvSize);

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
  LIBALT_API static alt_t Send(const SOCKET nSocket, const altChar * pData, const altInt nSize, altInt & nSendByte);

  ///
  /// \brief  Initialize SSL Library
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API static alt_t SSLLibraryInit();

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
  LIBALT_API static alt_t RecvSSL(SSL * pSSL, altChar * pBuf, const altUInt nBufSize, altInt & nRecvSize);

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
  LIBALT_API static alt_t SendSSL(SSL * pSSL, const altChar * pData, const altInt nSize, altInt & nSendSize);

  ///
  /// \brief  Get Local IP Addr
  ///
  /// \param  sIPAddr [ O] Local IP Address
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API static alt_t GetLocalIPAddr(altStr & sIPAddr);

  ///
  /// \brief  Get local host name
  ///
  /// \param  sHostname [ O] Local host name
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API static alt_t GetLocalHostName(altStr & sHostname);

#if 0
  ///
  /// \brief  Signal Hander
  ///
  /// \param  nSignal [I ] Signal Number
  ///
  LIBALT_API static void SignalHandler(altInt nSignal);
#endif
};
#endif  //ALTNETUTIL_H

