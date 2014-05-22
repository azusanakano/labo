/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETRequestInvoker.cpp
 * \brief   Network request invoker class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altNETRequestInvoker.h"
#include "altNETServerConnection.h"
#include "altBase/altThread.h"


/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
/// \param  oPacketQue [I ] Packet Que
///
LIBALT_API altNETRequestInvoker::altNETRequestInvoker(altNETPacketQue & oPacketQue, const altNETReceiveCallBack pReceiveCallBackFunc, const altUInt nThreadCount) :
m_oRequestQue(),
m_oRequestThreadContainer(),
m_oPacketQue (oPacketQue),
m_oRequestInvoker(10),
m_pReceiveCallBackFunc (pReceiveCallBackFunc)
{
  m_oRequestInvoker.Start (altNETRequestInvoker::RequestInvokerThread, this);

  for (altUInt i = 0; i < nThreadCount; i++) {
    altLoopThread * pRequestThread = ALT_NEW altLoopThread();
    pRequestThread->Start (altNETRequestInvoker::RequestThread, this);
    m_oRequestThreadContainer.push_back (pRequestThread);
  }
}

///
/// \brief  Destructor
///
LIBALT_API altNETRequestInvoker::~altNETRequestInvoker()
{
  for (altNETRequestThreadContainer::iterator i = m_oRequestThreadContainer.begin(); i != m_oRequestThreadContainer.end(); i++) {
    (* i)->Stop();
    delete (* i);
  }
  m_oRequestThreadContainer.clear();
  m_oRequestInvoker.Stop();
}

///
/// \brief  Restart threads
///
/// \\return  ALT_S_SUCCESS success
///
LIBALT_API alt_t altNETRequestInvoker::ReStart()
{
  for (altUInt i = 0; i < m_oRequestThreadContainer.size(); i++) {
    m_oRequestThreadContainer[i]->StopNoWait();
  }
  m_oRequestInvoker.StopNoWait();
  m_oRequestQue.EndLock();
  m_oRequestInvoker.Start (altNETRequestInvoker::RequestInvokerThread, this);
  for (altUInt i = 0; i < m_oRequestThreadContainer.size(); i++) {
    m_oRequestThreadContainer[i]->Start(altNETRequestInvoker::RequestThread, this);
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Request Invoker Thread
///
/// \param  pParam  [IO] altNETRequestInvoker object
///
LIBALT_API alt_t altNETRequestInvoker::RequestInvokerThread(void * pParam)
{
  altNETRequestInvoker *  pInvoker = (altNETRequestInvoker *)pParam;
  altNETReceiveCallBack   pCallBackFunc = pInvoker->m_pReceiveCallBackFunc;
  alt_t                   status;
  altNETPacketQue &       oPacketQue = pInvoker->m_oPacketQue;
  altNETPacket *          pPacket = NULL;

  status = oPacketQue.Pop (pPacket);
  if (status == ALT_S_SUCCESS) {
    altNETRequest *   pRequest = ALT_NEW altNETRequest();
    pRequest->m_pReceiveCallBackFunc = pCallBackFunc;
    pPacket->Get (pRequest->m_pConnection, pRequest->m_pData, pRequest->m_nSize);
    delete pPacket;
    pInvoker->m_oRequestQue.Push (pRequest);
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Request Thread
///
/// \param  pParam  [I ] Request Infomation
///
LIBALT_API alt_t altNETRequestInvoker::RequestThread(void * pParam)
{
  altNETRequestInvoker *    pInvoker = (altNETRequestInvoker *)pParam;
  altNETRequest *           pRequest = NULL;

  pInvoker->m_oRequestQue.Pop (pRequest);

  if (pRequest != NULL) {
    if (pRequest->m_pConnection->IsServerConnection()) {
      altCNETServerConnectionPtr pServerConnection = (altCNETServerConnection *)pRequest->m_pConnection.get_ptr(); 
      alt_t status = pServerConnection->CallReceiveCallBack (pRequest->m_pData, pRequest->m_nSize);
      ALT_LOG (status);
    }
    else {
      pRequest->m_pReceiveCallBackFunc (pRequest->m_pConnection, pRequest->m_pData, pRequest->m_nSize);
    }
    delete pRequest;
  }

  ALT_RET (ALT_S_SUCCESS);
}
