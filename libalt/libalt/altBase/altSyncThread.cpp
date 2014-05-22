/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSyncThread.cpp
 * \brief   Synchronize threads object class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altSyncThread.h"

#ifdef ALT_LINUX
  #include <sys/time.h>
  #include <errno.h>
#endif

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altSyncThread::altSyncThread() :
m_bLock (false)
{
#ifdef ALT_WIN
  InitializeCriticalSection (& m_oCriticalSection);
  m_oEvent = CreateEvent (NULL, false, true, NULL);
#else
  pthread_mutex_init (& m_oMutex, NULL);
  pthread_cond_init (& m_oCond, NULL);
#endif
}

///
/// \brief  Destructor
///
LIBALT_API altSyncThread::~altSyncThread()
{
#ifdef ALT_WIN
  CloseHandle (m_oEvent);
  DeleteCriticalSection (& m_oCriticalSection);
#else
  altInt nRet = pthread_cond_destroy (& m_oCond);
  if (nRet == EBUSY) {
    SetSignal();
    pthread_cond_destroy (& m_oCond);
  }
  pthread_mutex_destroy (& m_oMutex);
#endif
}

///
/// \brief  Begin Lock
///
LIBALT_API void altSyncThread::BeginLock() const
{
#ifdef ALT_WIN
  EnterCriticalSection (& m_oCriticalSection);
#endif
#ifdef ALT_LINUX
  pthread_mutex_lock (& m_oMutex);
#endif
  m_bLock = true;
}

///
/// \brief  End Lock
///
LIBALT_API void altSyncThread::EndLock() const
{
  if (m_bLock) {
    m_bLock = false;
#ifdef ALT_WIN
    LeaveCriticalSection (& m_oCriticalSection);
#endif
#ifdef ALT_LINUX
    pthread_mutex_unlock (& m_oMutex);
#endif
  }
}

///
/// \brief  Wait Signal
///
/// \param  dwTimeout   [I ] timeout(msec) (default value is no timeout)
///
void altSyncThread::WaitSignal(DWORD dwTimeout) const
{
#ifdef ALT_WIN
  WaitForSingleObject (m_oEvent, dwTimeout);
#else
  if (dwTimeout == INFINITE) {
    pthread_mutex_lock (& m_oMutex);
    pthread_cond_wait (& m_oCond, & m_oMutex);
    pthread_mutex_unlock (& m_oMutex);
  }
  else {
    struct timeval  oNow;
    struct timespec oTimeout;

    gettimeofday (& oNow, NULL);
    
    time_t  nSec = oNow.tv_sec + (dwTimeout / 1000);
    altLong nNanoSec = (oNow.tv_usec * 1000) + ((dwTimeout % 1000) * 1000000);

    if (nNanoSec >= 1000000000) {
      nNanoSec -= 1000000000;
      nSec += 1;
    }

    oTimeout.tv_sec = nSec;
    oTimeout.tv_nsec = nNanoSec;

    pthread_mutex_lock (& m_oMutex);
    pthread_cond_timedwait (& m_oCond, & m_oMutex, & oTimeout);
    pthread_mutex_unlock (& m_oMutex);
  }
#endif
}

///
/// \brief	Set Signal
///
void altSyncThread::SetSignal() const
{
#ifdef ALT_WIN
  SetEvent (m_oEvent);
#else
  pthread_cond_signal (& m_oCond);
#endif
}
