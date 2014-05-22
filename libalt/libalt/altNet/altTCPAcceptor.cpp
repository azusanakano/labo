/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTCPAcceptor.cpp
 * \brief   Network server acceptor class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altTCPServer.h"
#include "altTCPServerConnection.h"
#include "altTCPConnection.h"
#include "altInetAddress.h"
#include "altNETConnectionManager.h"
#include "altTCPAcceptor.h"
#include "altNetUtil.h"

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
/// \param  oTCPServer          [I ] TCP server instance
/// \param  pReceiveCallBack    [I ] receive call back function
/// \param  nThreadCount        [I ] Reqeust Thread Count
///
LIBALT_API altTCPAcceptor::altTCPAcceptor(const altNETReceiveCallBack pReceiveCallBack, const altUInt nThreadCount) :
m_oReceiverBroker (pReceiveCallBack, nThreadCount),
m_oSenderBroker(),
m_nPort(0),
m_nListenSocket(0),
m_oAcceptThread(),
m_pAcceptCallBackFunc(NULL)
{
}

///
/// \brief  Destructor
///
LIBALT_API altTCPAcceptor::~altTCPAcceptor()
{
  aiNETConnectionManager.DeletePort (m_nPort);
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
LIBALT_API alt_t altTCPAcceptor::OpenPort(const altInt nPort, const altInt nListenQueSize, const altNETAcceptCallBack pAcceptCallBack)
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

  m_pAcceptCallBackFunc = pAcceptCallBack;
  m_nPort = nPort;

  // Add TCP Receiver Broker to Connection Manager
  aiNETConnectionManager.Add (nPort, & m_oReceiverBroker);

  // start accept thread
  m_oAcceptThread.Start (altTCPAcceptor::AcceptThread, this);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Close Port
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altTCPAcceptor::ClosePort()
{
  alt_t status = m_nListenSocket.Close();
  ALT_LOG (status);
  m_oAcceptThread.Stop();
  m_nPort = 0;
  m_pAcceptCallBackFunc = NULL;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Accept Thread
///
/// \param  pParam  [I ] parameter
///
LIBALT_API alt_t altTCPAcceptor::AcceptThread(void * pParam)
{
  altTCPAcceptor *    pAcceptor = static_cast<altTCPAcceptor *>(pParam);
	fd_set              oRfds;
	struct timeval      oTimeout;
  alt_t               status;
  SOCKET              nServerSocket = pAcceptor->m_nListenSocket.GetSocket();

  FD_ZERO (& oRfds);
  FD_SET (nServerSocket, & oRfds);

  oTimeout.tv_sec = 0;
  oTimeout.tv_usec = 100;

  status = altNetUtil::Select (nServerSocket, & oRfds, NULL, NULL, & oTimeout);
  ALT_LOG (status);

  if (status == ALT_S_SUCCESS) {

    SOCKADDR_IN oClientSockAddr;
    altInt      nClientSockAddrLen = sizeof (oClientSockAddr);
    SOCKET      nClientSocket;

    // accept
    status = altNetUtil::Accept (nServerSocket, & oClientSockAddr, & nClientSockAddrLen, nClientSocket);
    ALT_ERR_RET (status);

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

    altCNETConnectionPtr        pNETConnection = NULL;
    altCNETServerConnectionPtr  pServerConnection = NULL;

    if (aiNETConnectionManager.IsServerIP (oInetAddress.GetIP())) {
      pServerConnection = ALT_NEW altTCPServerConnection (nClientSocket, oClientSockAddr, pAcceptor->m_nPort, pAcceptor->m_oSenderBroker, aiNETConnectionManager.GetServerInfo (oInetAddress.GetIP()));
      pNETConnection = (altCNETConnection *)(pServerConnection.get_ptr());
      if (pNETConnection == NULL) {
        ALT_RET (ALT_E_NOMEM);
      }
    }
    else {
      // create new connection
      pNETConnection = ALT_NEW altTCPConnection (nClientSocket, oClientSockAddr, pAcceptor->m_nPort, pAcceptor->m_oSenderBroker);
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
      if (pAcceptor->m_pAcceptCallBackFunc != NULL) {
        pAcceptor->m_pAcceptCallBackFunc (pAcceptor->m_nPort, pNETConnection);
      }
    }
  }
  ALT_RET (ALT_S_SUCCESS);
}
