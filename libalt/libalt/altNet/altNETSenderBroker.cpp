/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNetNETSendBroker.cpp
 * \brief   Network data sender broker class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altNETSenderBroker.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altNETSenderBroker::altNETSenderBroker()
{
  alt_t status = CreateNewSender();
  ALT_LOG (status);
  m_oDeleterThread.Start (altNETSenderBroker::DeleterThread, this);
}

///
/// \brief  Destructor
///
LIBALT_API altNETSenderBroker::~altNETSenderBroker()
{
  m_oDeleterThread.Stop();
  for (altNetNETSenderContainer::iterator i = m_oNETSenderContainer.begin(); i != m_oNETSenderContainer.end(); i++) {
    delete (* i);
  }
  m_oNETSenderContainer.clear();
}

///
/// \brief  Send
///
/// \param  pConnection [I ] connection
/// \param  pData       [I ] data
/// \param  nSize       [I ] data size
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_NOMEM     out of memory
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altNETSenderBroker::Send(const altCNETConnectionPtr & pConnection, const altCharPtr & pData, const altInt nSize) const
{
  altUInt nMinSize = 0;
  altNETSender * pSender = NULL;

  if (m_oNETSenderContainer.size() == 0) {
    CreateNewSender();
  }

  BeginLock();
  for (altUInt i = 0; i < m_oNETSenderContainer.size(); i++) {
    if (i == 0) {
      nMinSize = m_oNETSenderContainer[i]->GetQueSize();
      pSender = m_oNETSenderContainer[i];
      continue;
    }
    if (nMinSize > m_oNETSenderContainer[i]->GetQueSize()) {
      nMinSize = m_oNETSenderContainer[i]->GetQueSize();
      pSender = m_oNETSenderContainer[i];
    }
  }

  if (pSender == NULL) {
    EndLock();
    ALT_RET_P (ALT_E_ERROR, "no sender object");
  }

  alt_t status;
  status = pSender->Send (pConnection, pData, nSize);
  ALT_ERR_RET (status);
  EndLock();

  if (nMinSize > 128) {
    CreateNewSender();
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Create New Sender
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altNETSenderBroker::CreateNewSender() const
{
  altNETSender * pNETSender = ALT_NEW altNETSender();
  if (pNETSender == NULL) {
    ALT_RET (ALT_E_NOMEM);
  }
  alt_t status = pNETSender->Start();
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    delete pNETSender;
    ALT_RET (status);
  }
  BeginLock();
  m_oNETSenderContainer.push_back (pNETSender);
  EndLock();
  ALT_LOG_P (ALT_D_DEBUG, "create new Sender");
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Deleter Thread
///
/// \param  pParam  [IO] this object
///
LIBALT_API alt_t altNETSenderBroker::DeleterThread(void * pParam)
{
  altNETSenderBroker *        pSenderBroker = (altNETSenderBroker *)pParam;
  altNetNETSenderContainer *  pSenderContainer = & pSenderBroker->m_oNETSenderContainer;
  altNetNETSenderContainer    oDelete;

  if (pSenderContainer->size() <= 1) {
    ALT_RET (ALT_S_SUCCESS);
  }

  pSenderBroker->BeginLock();
  for (altNetNETSenderContainer::iterator i = pSenderContainer->begin(); i != pSenderContainer->end();) {
    if ((* i)->GetQueSize() == 0) {
      oDelete.push_back ((* i));
      pSenderContainer->erase (i);
      i = pSenderContainer->begin();
    }
    else {
      i++;
    }
  }
  pSenderBroker->EndLock();

  for (altNetNETSenderContainer::iterator i = oDelete.begin(); i != oDelete.end(); i++) {
    delete (* i);
    ALT_LOG_P (ALT_D_DEBUG, "delete Sender");
  }

  ALT_RET (ALT_S_SUCCESS);
}
