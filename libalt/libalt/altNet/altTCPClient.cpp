/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTCPClient.cpp
 * \brief   TCP network client class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altTCPClient.h"
#include "altNetUtil.h"

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
///
LIBALT_API altTCPClient::altTCPClient(altNetClientCallBack pCallBackFunc, altNetClientDisconnectCallBack pDisconnectCallBack) ALT_THROWS (alt_t) :
m_pCallBackFunc (pCallBackFunc),
m_pDisconnectCallBack (pDisconnectCallBack),
m_oSocket (0),
m_oSendThread(),
m_oRecvThread(),
m_oRequestThread(),
m_oSendQue(),
m_oRecvQue(),
m_oInetAddr()
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
LIBALT_API altTCPClient::~altTCPClient()
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
///
LIBALT_API alt_t altTCPClient::Connect(const altStr & sIP, const altUInt nPort)
{
  alt_t status;

  status = m_oInetAddr.Init (sIP.GetCStr(), nPort);
  ALT_ERR_RET (status);
  status = m_oSocket.Connect (m_oInetAddr);
  ALT_ERR_RET (status);

  m_oSendThread.Start (altTCPClient::SendThread, this);
  m_oRecvThread.Start (altTCPClient::RecvThread, this);
  m_oRequestThread.Start (altTCPClient::RequestThread, this);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Disconnect
///
/// \return ALT_S_SUCCESS       success
///
LIBALT_API alt_t altTCPClient::Disconnect()
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
LIBALT_API alt_t altTCPClient::Send(const altChar * pData, const altUInt nSize)
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
LIBALT_API alt_t altTCPClient::Send(const altCharPtr pData, const altUInt nSize)
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
LIBALT_API altStr altTCPClient::GetIP() const
{
  return (m_oInetAddr.GetIP());
}

///
/// \brief Get Port NO
///
/// \return Port NO
///
LIBALT_API altInt altTCPClient::GetPort() const
{
  return (m_oInetAddr.GetPort());
}

///
/// \brief  Disconnected
///
/// \return ALT_S_SUCCESS       success
///
LIBALT_API alt_t altTCPClient::Disconnected()
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
LIBALT_API alt_t altTCPClient::SendThread(void * pParam)
{
  altTCPClient * pClient = (altTCPClient *)pParam;
  alt_t status;

  altClientPacket * pPacket = NULL;
  status = pClient->m_oSendQue.Pop (pPacket);
  if (pPacket != NULL) {
    altInt nSendByte = 0;
    status = altNetUtil::Send (pClient->m_oSocket.GetSocket(), pPacket->GetData(), pPacket->GetSize(), nSendByte);
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
LIBALT_API alt_t altTCPClient::RecvThread(void * pParam)
{
  altTCPClient * pClient = (altTCPClient *)pParam;
  alt_t status;

  altClientPacket * pPacket = NULL;
  altChar *         pBuf = NULL;
  altInt            nRecvSize = 0;

  status = ALT_MALLOC (pBuf, ALT_BUFSIZ);
  ALT_ERR_RET (status);

  status = altNetUtil::Recv (pClient->m_oSocket.GetSocket(), pBuf, ALT_BUFSIZ, nRecvSize);
  if (status == ALT_S_SUCCESS) {
    pPacket = ALT_NEW altClientPacket ();
    status = pPacket->Set (pBuf, static_cast<altUInt>(nRecvSize));
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
  else {
    ALT_LOG (status);
    // Disconnect
    status = pClient->Disconnected();
    ALT_ERR_RET (status);
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Request Thread
///
/// \param  pParam  [I ] this Client Object
///
LIBALT_API alt_t altTCPClient::RequestThread(void * pParam)
{
  altTCPClient * pClient = (altTCPClient *)pParam;
  alt_t status;
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

