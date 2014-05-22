/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSSLClient.cpp
 * \brief   SSL network client class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altSSLClient.h"
#include "altNetUtil.h"
#include "altBase/altMem.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
/// \param  pCallBackFunc       [I ] Recv Call Back Function
/// \param  pDisconnectCallBack [I ] Disconnect Call Back Function
/// \param  nSSLVersion         [I ] SSL Version (ALT_SSL_V2 or ALT_SSL_V3 or ALT_TSL_V1)
///
LIBALT_API altSSLClient::altSSLClient(altSSLClientCallBack pCallBackFunc, altSSLClientDisconnectCallBack pDisconnectCallBack, const altByte nSSLVersion) ALT_THROWS (alt_t) :
m_pCallBackFunc (pCallBackFunc),
m_pDisconnectCallBack (pDisconnectCallBack),
m_oSocket (0),
m_oSendThread(),
m_oRecvThread(),
m_oRequestThread(),
m_oSendQue(),
m_oRecvQue(),
m_oInetAddr(),
m_nSSLVersion (nSSLVersion)
{
  alt_t status;
  status = m_oSocket.Init (AF_INET, SOCK_STREAM, 0);
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    throw status;
  }
}

///
/// \brief  Destructor
///
LIBALT_API altSSLClient::~altSSLClient()
{
  alt_t status = Disconnect();
  ALT_LOG (status);
}

///
/// \brief  Connect
///
/// \param  sIP   [I ] IP Address
/// \param  nPort [I ] Port NO
///
/// \return ALT_S_SUCCESS       success
/// \return ALT_E_UNKNOWN_HOST  unknown host error
/// \return ALT_E_CONNECT       connect error
/// \return ALT_E_ERROR         error
///
LIBALT_API alt_t altSSLClient::Connect(const altStr & sIP, const altUInt nPort)
{
  alt_t status;

  status = m_oInetAddr.Init (sIP.GetCStr(), nPort);
  ALT_ERR_RET (status);
  status = m_oSocket.Connect (m_oInetAddr, m_nSSLVersion);
  ALT_ERR_RET (status);

  m_oSendThread.Start (altSSLClient::SendThread, this);
  m_oRecvThread.Start (altSSLClient::RecvThread, this);
  m_oRequestThread.Start (altSSLClient::RequestThread, this);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Disconnect
///
/// \return ALT_S_SUCCESS       success
///
LIBALT_API alt_t altSSLClient::Disconnect()
{
  alt_t status;

  status = m_oSocket.Close();
  ALT_ERR_RET (status);

  m_oRecvThread.Stop();
  m_oSendThread.Stop();
  m_oRequestThread.Stop();

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send
///
/// \param  pData [I ] Send Data
/// \param  nSize [I ] Send Data Size
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_NOMEM     out of memory error
///
LIBALT_API alt_t altSSLClient::Send(const altChar * pData, const altUInt nSize)
{
  alt_t status;

  altClientPacket * pPacket = ALT_NEW altClientPacket();
  if (pPacket == NULL) {
    ALT_RET (ALT_E_NOMEM);
  }

  altCharPtr  pSendData;
  altChar *   pTmp = NULL;

  status = ALT_DUPALLOC (pTmp, pData, nSize);
  ALT_ERR_RET (status);

  pSendData = pTmp;

  status = pPacket->Set (pSendData, nSize);
  ALT_ERR_RET (status);

  status = m_oSendQue.Push (pPacket);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send
///
/// \param  pData [I ] Send Data
/// \param  nSize [I ] Send Data Size
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_NOMEM     out of memory error
///
LIBALT_API alt_t altSSLClient::Send(const altCharPtr & pData, const altUInt nSize)
{
  alt_t status;

  altClientPacket * pPacket = ALT_NEW altClientPacket();
  if (pPacket == NULL) {
    ALT_RET (ALT_E_NOMEM);
  }

  status = pPacket->Set (pData, nSize);
  ALT_ERR_RET (status);

  status = m_oSendQue.Push (pPacket);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get IP
///
/// \return IP Address
///
LIBALT_API altStr altSSLClient::GetIP() const
{
  return (m_oInetAddr.GetIP());
}

///
/// \brief Get Port NO
///
/// \return Port NO
///
LIBALT_API altInt altSSLClient::GetPort() const
{
  return (m_oInetAddr.GetPort());
}

///
/// \brief  Disconnected
///
/// \return ALT_S_SUCCESS       success
///
LIBALT_API alt_t altSSLClient::Disconnected()
{
  alt_t status;

  status = m_oSocket.Close();
  ALT_ERR_RET (status);

  m_oRecvThread.StopNoWait();
  m_oSendThread.StopNoWait();
  m_oRequestThread.StopNoWait();

  if (m_pDisconnectCallBack != NULL) {
    (m_pDisconnectCallBack) (* this);
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send Thread
///
/// \param  pParam  [I ] this Client Object
///
LIBALT_API alt_t altSSLClient::SendThread(void * pParam)
{
  altSSLClient * pClient = (altSSLClient *)pParam;
  alt_t status;

  altClientPacket * pPacket = NULL;
  status = pClient->m_oSendQue.Pop (pPacket);
  if (pPacket != NULL) {
    status = pClient->m_oSocket.Send (pPacket->GetData(), pPacket->GetSize());
    delete pPacket;
    if (ALT_IS_ERR (status)) {
      ALT_LOG (status);
      // Disconnect
      status = pClient->Disconnected();
      ALT_RET (status);
    }
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Recv Thread
///
/// \param  pParam  [I ] this Client Object
///
LIBALT_API alt_t altSSLClient::RecvThread(void * pParam)
{
  altSSLClient *    pClient = (altSSLClient *)pParam;
  alt_t             status;
  altClientPacket * pPacket = NULL;
  altCharPtr        pBuf;
  altUInt           nRecvSize = ALT_BUFSIZ;

  status = pClient->m_oSocket.Recv (pBuf, nRecvSize);
  if (status == ALT_S_SUCCESS) {
    pPacket = ALT_NEW altClientPacket ();
    status = pPacket->Set (pBuf, nRecvSize);
    if (ALT_IS_ERR (status)) {
      delete pPacket;
      ALT_RET (status);
    }
    status = pClient->m_oRecvQue.Push (pPacket);
    if (ALT_IS_ERR (status)) {
      delete pPacket;
      ALT_RET (status);
    }
  }
  // If error caused, print log and disconnect.
  else {
    // print log
    ALT_LOG (status);

    // disconnect
    status = pClient->Disconnected();
    ALT_RET (status);
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Request Thread
///
/// \param  pParam  [I ] this Client Object
///
LIBALT_API alt_t altSSLClient::RequestThread(void * pParam)
{
  altSSLClient *    pClient = (altSSLClient *)pParam;
  alt_t             status;
  altClientPacket * pPacket = NULL;

  status = pClient->m_oRecvQue.Pop (pPacket);
  ALT_ERR_RET (status);

  if (pPacket != NULL) {
    if (pClient->m_pCallBackFunc != NULL) {
      pClient->m_pCallBackFunc (* pClient, pPacket->GetData(), pPacket->GetSize());
    }
    delete pPacket;
  }

  ALT_RET (ALT_S_SUCCESS);
}

