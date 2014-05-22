/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETReceiver.cpp
 * \brief   Network data receiver class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altNETConnectionManager.h"
#include "altNETReceiverBroker.h"
#include "altNet/altNetUtil.h"
#include "altBase/altMem.h"
#include "altBase/altUtil.h"

#include <vector>

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
/// \param  pReceiveCallBackFunc  [I ] Receive Call Back Function
/// \param  nThreadCount          [I ] Request Thread Count
///
LIBALT_API altNETReceiver::altNETReceiver(const altNETReceiveCallBack pReceiveCallBackFunc, const altUInt nThreadCount, const altUInt nRecvBufferSize) :
m_oConnectionMap(),
m_oReceiveThreaed (10),
m_oPacketQue(),
m_oRequestInvoker (m_oPacketQue, pReceiveCallBackFunc, nThreadCount),
m_nRecvBufferSize (nRecvBufferSize)
{
}

///
/// \brief  Destructor
///
LIBALT_API altNETReceiver::~altNETReceiver()
{
  alt_t status;
  status = Stop();
  ALT_LOG (status);
}

///
/// \brief  Add Connection
///
/// \param  pConnection [I ] NET Connection
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_I_MAX       max
///
LIBALT_API alt_t altNETReceiver::Add(const altCNETConnectionPtr & pConnection)
{
  BeginLock();
  if (Size() >= FD_SETSIZE) {
    EndLock();
    ALT_RET (ALT_I_MAX);
  }
  m_oConnectionMap[pConnection->GetSocket()] = pConnection;
  EndLock();
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Del Connection
///
/// \param  pConnection [I ] NET Connection
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_S_NOT_FOUND not found
///
LIBALT_API alt_t altNETReceiver::Del(const altCNETConnectionPtr & pConnection)
{
  BeginLock();
  altNETConnectionMap::iterator i = m_oConnectionMap.find (pConnection->GetSocket());
  if (i != m_oConnectionMap.end()) {
    m_oConnectionMap.erase (i);
  }
  else {
    EndLock();
    ALT_RET (ALT_S_NOT_FOUND);
  }
  EndLock();
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Size
///
/// \return content size
///
LIBALT_API altUInt altNETReceiver::Size() const
{
  return (static_cast<altUInt>(m_oConnectionMap.size()));
}

///
/// \brief  Start Receive Thread
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altNETReceiver::Start()
{
  m_oReceiveThreaed.Start (altNETReceiver::ReceiveThread, this);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Stop Receiver Thread
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altNETReceiver::Stop()
{
  m_oReceiveThreaed.Stop();
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Pop received packet
///
/// \param  pPacket [ O] pointer of packet
///
/// \return ALT_S_SUCCESS     success
/// \return ALT_S_NOT_FOUND   not data
///
LIBALT_API alt_t altNETReceiver::Pop (altNETPacket * & pPacket)
{
  alt_t status;
  status = m_oPacketQue.Pop (pPacket);
  ALT_RET (status);
}

///
/// \brief  Delete all client connection
///
LIBALT_API void altNETReceiver::DelAllClient()
{
  BeginLock();
  for (altNETConnectionMap::iterator i = m_oConnectionMap.begin(); i != m_oConnectionMap.end(); i++) {
    if (! aiNETConnectionManager.IsServerIP ((* i).second->GetIP())) {
      m_oConnectionMap.erase (i);
    }
  }
  EndLock();
}

///
/// \brief  Set receive buffer size
///
/// \param  nSize [I ] receive buffer size
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_INVAL   invalid paramter
///
LIBALT_API alt_t altNETReceiver::SetRecvBufferSize(const altUInt nSize)
{
  ALT_P_ASSERT (nSize != 0);
  m_nRecvBufferSize = nSize;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  receive thread
///
/// \param  pParam  [I ] altNETReceiver object
///
LIBALT_API alt_t altNETReceiver::ReceiveThread(void * pParam)
{
  altNETReceiver *        pReceiver = static_cast<altNETReceiver *>(pParam);
  altNETPacketQue &       oPacketQue = pReceiver->m_oPacketQue;
  altNETConnectionMap     oConnectionMap;
  alt_t                   status;
  fd_set                  oRfds;
  fd_set                  oEfds;
  altUInt                 nConnectionCount = 0;
  struct timeval          oTimeout;
  
  pReceiver->BeginLock();
  oConnectionMap = pReceiver->m_oConnectionMap;
  pReceiver->EndLock();

  nConnectionCount = static_cast<altUInt>(oConnectionMap.size());
  if (nConnectionCount == 0) {
    ALT_RET (ALT_S_SUCCESS);
  }

  std::vector<altCNETConnectionPtr> oDisconnectList;
  SOCKET  nMaxSocket = 0;
  oTimeout.tv_sec = 0;
  oTimeout.tv_usec = 10;
  FD_ZERO (& oRfds);
  FD_ZERO (& oEfds);

  for (altNETConnectionMap::iterator i = oConnectionMap.begin(); i != oConnectionMap.end(); i++) {
    altPtr<const altNETConnection> pNETConnection = i->second;
    SOCKET nSocket = pNETConnection->GetSocket();

    FD_SET (nSocket, & oRfds);
    FD_SET (nSocket, & oEfds);

    if (nSocket > nMaxSocket) {
      nMaxSocket = nSocket;
    }
  }

  status = altNetUtil::Select (nMaxSocket + 1, & oRfds, NULL, & oEfds, & oTimeout);
  ALT_LOG (status);
  if (status == ALT_S_SUCCESS) {
    for (altNETConnectionMap::iterator i = oConnectionMap.begin(); i != oConnectionMap.end(); i++) {
      
      altCNETConnectionPtr  pNETConnection = i->second;
      SOCKET                nSocket = pNETConnection->GetSocket();
      altCharPtr            pData;
      altUInt               nSize = pReceiver->m_nRecvBufferSize;

      if (FD_ISSET (nSocket, & oRfds)) {
        status = pNETConnection->Recv (pData, nSize);
        if (status == ALT_S_SUCCESS) {
          altNETPacket * pPacket = ALT_NEW altNETPacket();
          pPacket->Set (pNETConnection, pData, nSize);
          oPacketQue.Push (pPacket);
        }
        else if (status == ALT_S_NET_EOF) {
          oDisconnectList.push_back (pNETConnection);
        }
        else if (ALT_IS_ERR (status)) {
          ALT_LOG (status);
          oDisconnectList.push_back (pNETConnection);
        }
      }
      else if (FD_ISSET (pNETConnection->GetSocket(), & oEfds)) {
        oDisconnectList.push_back (pNETConnection);
      }
    }
  }

  // remove diconnected connection
  for (altUInt i = 0; i < oDisconnectList.size(); i++) {
    pReceiver->Del (oDisconnectList[i]);
    aiNETConnectionManager.Del (oDisconnectList[i]);
  }

  ALT_RET (ALT_S_SUCCESS);
}

