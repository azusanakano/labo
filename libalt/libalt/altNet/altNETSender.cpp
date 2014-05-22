/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETSender.cpp
 * \brief   Network data sender calss
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altNETConnectionManager.h"
#include "altNETSender.h"
#include "altNetUtil.h"
#include "altBase/altUtil.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altNETSender::altNETSender()
{
}

///
/// \brief  Destructor
///
LIBALT_API altNETSender::~altNETSender()
{
  alt_t status = Stop();
  ALT_LOG (status);
}

///
/// \brief  Send
///
/// \param  pConnection [I ] Connection
/// \param  pData       [I ] Data
/// \param  nSize       [I ] Data Size
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altNETSender::Send(const altCNETConnectionPtr & pConnection, const altCharPtr & pData, const altInt nSize) const
{
  alt_t status;
  altNETPacket * pPacket = ALT_NEW altNETPacket();
  
  if (pPacket == NULL) {
    ALT_RET (ALT_E_NOMEM);
  }

  status = pPacket->Set (pConnection, pData, nSize);
  ALT_ERR_RET (status);

  m_oPacketQue.Push (pPacket);
#ifdef ALT_WIN
  m_oPacketQue.SetSignal();
#endif

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Queue Size
///
/// \return Queue Size
///
LIBALT_API altUInt altNETSender::GetQueSize() const
{
  return m_oPacketQue.Size();
}

///
/// \brief  Start Send Thread
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altNETSender::Start()
{
  m_oSendThread.Start (altNETSender::SendThread, this);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Stop Send Thread
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altNETSender::Stop()
{
  m_oSendThread.Stop();
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send Thread
///
/// \param  pParam  [I ] altNETSender object
///
LIBALT_API alt_t altNETSender::SendThread(void * pParam)
{
  altNETSender *            pSender = (altNETSender *)pParam;
  altQue<altNETPacket *> &  oQue = pSender->m_oPacketQue;
  alt_t                     status;

#ifdef ALT_WIN
  oQue.WaitSignal(100);
#endif
#ifdef ALT_LINUX
  altSleep (1);
#endif
  if (oQue.Empty()) {
    ALT_RET (ALT_S_SUCCESS);
  }

  altNETPacket * pPacket = NULL;
  status = oQue.Pop (pPacket);
  if (status == ALT_S_SUCCESS) {
    altCNETConnectionPtr  pConnection = NULL;
    altCharPtr            pData;
    altUInt               nSize = 0;

    status = pPacket->Get (pConnection, pData, nSize);
    if (ALT_IS_ERR (status)) {
      delete pPacket;
      ALT_RET (status);
    }

    if (! pConnection->Connected()) {
      delete pPacket;
      ALT_RET (ALT_S_SUCCESS);
    }

    pConnection->BeginLock();
    status = pConnection->RealSend (pData, nSize);
    pConnection->EndLock();
    if (ALT_IS_ERR (status)) {
      delete pPacket;
      aiNETConnectionManager.Del (pConnection);
      ALT_RET (status);
    }

    delete pPacket;
  }

  ALT_RET (ALT_S_SUCCESS);
}
