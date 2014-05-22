/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETReceiverBroker.cpp
 * \brief   Network receiver broker class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altNETReceiverBroker.h"
#include "altNETConnectionManager.h"

/*----------------------------------------------------------------*
 * Static variables
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
/// \param  pReceiveCallBack      [I ] NET Data Receive Call Back Function
/// \param  nThreadCount          [I ] Request Thread Count
///
LIBALT_API altNETReceiverBroker::altNETReceiverBroker(const altNETReceiveCallBack pCallBackFunc, const altUInt nThreadCount) : 
m_oNETReceiverContainer(),
m_pReceiveCallBackFunc (pCallBackFunc),
m_nRequestThreadCount (nThreadCount),
m_oDeleterThread (100)
{
  CreateNewNETReceiver();
  m_oDeleterThread.Start (altNETReceiverBroker::DeleterThread, this);
}

///
/// \brief  Destructor
///
LIBALT_API altNETReceiverBroker::~altNETReceiverBroker()
{
  m_oDeleterThread.Stop();
  for (altUInt i = 0; i < m_oNETReceiverContainer.size(); i++) {
    delete m_oNETReceiverContainer[i];
    m_oNETReceiverContainer[i] = NULL;
  }
  m_oNETReceiverContainer.clear();
}

///
/// \brief  Add NET Connection
///
/// \param  pNETConnection  [I ] NET Connection
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altNETReceiverBroker::Add(const altCNETConnectionPtr & pNETConnection)
{
  altUInt nMinSize = 0;
  altNETReceiver * pReceiver = NULL;

  BeginLock();
  // select min count container
  for (altUInt i = 0; i < m_oNETReceiverContainer.size(); i++) {
    if (i == 0) {
      pReceiver = m_oNETReceiverContainer[i];
      nMinSize = m_oNETReceiverContainer[i]->Size();
      continue;
    }

    if (nMinSize >= m_oNETReceiverContainer[i]->Size()) {
      pReceiver = m_oNETReceiverContainer[i];
      nMinSize = m_oNETReceiverContainer[i]->Size();
    }
  }

  // add to min count container
  alt_t status = pReceiver->Add (pNETConnection);
  EndLock();

  if (status == ALT_I_MAX) {
    CreateNewNETReceiver();
    status = Add (pNETConnection);
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Delete NET Connection
///
/// \param  pNETConnection  [I ] NET Connection
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altNETReceiverBroker::Del(const altCNETConnectionPtr & pNETConnection)
{
  BeginLock();
  for (altUInt i = 0; i < m_oNETReceiverContainer.size(); i++) {
    alt_t status = m_oNETReceiverContainer[i]->Del (pNETConnection);
    if (status == ALT_S_SUCCESS) {
      break;
    }
  }
  EndLock();
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Delete all client connection
///
LIBALT_API void altNETReceiverBroker::DelAllClient()
{
  BeginLock();
  for (altUInt i = 0; i < m_oNETReceiverContainer.size(); i++) {
    m_oNETReceiverContainer[i]->DelAllClient();
  }
  EndLock();
}

///
/// \brief  Set receive buffer size
///
/// \param  nSize [I ] receive buffer size
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_INVAL     invalid paramter
///
LIBALT_API alt_t altNETReceiverBroker::SetRecvBufferSize(const altUInt nSize)
{
  ALT_P_ASSERT (nSize != 0);
  BeginLock();
  for (altUInt i = 0; i < m_oNETReceiverContainer.size(); i++) {
    alt_t status = m_oNETReceiverContainer[i]->SetRecvBufferSize (nSize);
    if (ALT_IS_ERR (status)) {
      EndLock();
      ALT_RET (status);
    }
  }
  EndLock();
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  New NET Receiver
///
LIBALT_API void altNETReceiverBroker::CreateNewNETReceiver()
{
  altNETReceiver * pNETReceiver = ALT_NEW altNETReceiver (m_pReceiveCallBackFunc, m_nRequestThreadCount, aiNETConnectionManager.GetRecvBufferSize());
  if (pNETReceiver != NULL) {
    alt_t status = pNETReceiver->Start();
    if (ALT_IS_ERR (status)) {
      ALT_LOG (status);
      delete pNETReceiver;
      return;
    }
    BeginLock();
    m_oNETReceiverContainer.push_back (pNETReceiver);
    EndLock();
  }
}

///
/// \brief  Deleter Thread
///
/// \param  pParam  [IO] this object
///
LIBALT_API alt_t altNETReceiverBroker::DeleterThread(void * pParam)
{
  altNETReceiverBroker *     pBroker = (altNETReceiverBroker *)pParam;
  altNETReceiverContainer *  pReceiverContainer = & pBroker->m_oNETReceiverContainer;
  altNETReceiverContainer    oDelete;

  if (pReceiverContainer->size() > 1) {
    pBroker->BeginLock();
    for (altNETReceiverContainer::iterator i = pReceiverContainer->begin(); pReceiverContainer->size() > 1 && i != pReceiverContainer->end();) {
      if ((* i)->Size() == 0) {
        oDelete.push_back ((* i));
        pReceiverContainer->erase (i);
        i = pReceiverContainer->begin();
      }
      else {
        i++;
      }
    }
    pBroker->EndLock();
  }

  for (altNETReceiverContainer::iterator i = oDelete.begin(); i != oDelete.end(); i++) {
    delete (* i);
  }
  ALT_RET (ALT_S_SUCCESS);
}
