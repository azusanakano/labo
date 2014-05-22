/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altLoopThread.cpp
 * \brief   loop thread
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altLoopThread.h"
#include "altUtil.h"
#include "altStatus.h"
#include "altLog.h"

#include <exception>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
///
/// \brief  loop thread paramter
///
typedef struct {
  altLoopThread *     pLoopThread;  ///< loop thread object
  altLoopThreadFunc   pFunc;        ///< thread function
  void *              pParam;       ///< thread function paramter
} altLoopThreadParam;

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
/// \param  nInterval [I ] thread interval(msec)
///
LIBALT_API altLoopThread::altLoopThread(DWORD nInterval) :
m_bThreadContinue(false),
m_bThreadDone(false),
m_nInterval(nInterval)
{
}

///
/// \brief  Destructor
///
LIBALT_API altLoopThread::~altLoopThread()
{
  if (m_bThreadContinue) {
    Stop();
  }
}

///
/// \brief  Set thread interval
///
/// \param  nInterval [I ] Interval (msec)
///
LIBALT_API void altLoopThread::SetInterval(DWORD nInterval)
{
  m_nInterval = nInterval;
}

///
/// \brief  Start thread
///
/// \param  pFunc   [I ] thread funciton
/// \param  pParam  [I ] thread function parameter
///
LIBALT_API void altLoopThread::Start(altLoopThreadFunc pFunc, void * pParam)
{
  altLoopThreadParam oParam;
  
  oParam.pLoopThread = this;
  oParam.pFunc = pFunc;
  oParam.pParam = pParam;

  m_bThreadContinue = false;
  altThread::Start (altLoopThread::Run, (void *)& oParam);
  while (! m_bThreadContinue) {
    altSleep (10);
  }
}

///
/// \brief  Stop thread
///
LIBALT_API void altLoopThread::Stop()
{
  m_bThreadContinue = false;
  while (! m_bThreadDone) {
    altSleep (10);
  }
}

///
/// \brief  Stop thread no wait
///
LIBALT_API void altLoopThread::StopNoWait()
{
  m_bThreadContinue = false;
}

///
/// \brief  Loop thread function
///
/// \param  pParam  [I ] thread function parameter
///
LIBALT_API ALT_THREAD altLoopThread::Run(void * pParam)
{
  altLoopThreadParam oLoopParam = *(altLoopThreadParam *)pParam;
  altLoopThread * pThread = oLoopParam.pLoopThread;

  pThread->m_bThreadContinue = true;
  pThread->m_bThreadDone = false;
  while (pThread->m_bThreadContinue) {
    try {
      altSleep (pThread->m_nInterval);
      alt_t status = oLoopParam.pFunc (oLoopParam.pParam);
      ALT_LOG (status);
    }
    catch (alt_t exception) {
      ALT_LOG (exception);
    }
    catch (std::exception & oException) {
      ALT_LOG_P (ALT_E_ERROR, oException.what());
    }
    catch (...) {
      ALT_LOG (ALT_E_ERROR);
    }
  }
  pThread->m_bThreadDone = true;
  ALT_THREAD_END (NULL);
}
