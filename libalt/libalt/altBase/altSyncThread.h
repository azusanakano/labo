#ifndef ALTSYNCTHREAD_H
#define ALTSYNCTHREAD_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSyncThread.h
 * \brief   Synchronize threads object class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>

#ifdef ALT_LINUX
  #include <pthread.h>
#endif

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Thread Sync
///
class altSyncThread
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altSyncThread();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altSyncThread();

  ///
  /// \brief  Begin Lock
  ///
  LIBALT_API void BeginLock() const;

  ///
  /// \brief  End Lock
  ///
  LIBALT_API void EndLock() const;

  ///
  /// \brief  Wait Signal
  ///
  /// \param  dwTimeout   [I ] timeout(msec) (default value is no timeout)
  ///
  void WaitSignal(DWORD dwTimeout = INFINITE) const;

	///
	/// \brief	Set Signal
	///
	void SetSignal() const;

private:
#ifdef ALT_WIN
  mutable CRITICAL_SECTION  m_oCriticalSection;
  mutable HANDLE            m_oEvent;
#else
  mutable pthread_mutex_t   m_oMutex;
  mutable pthread_cond_t    m_oCond;
#endif
  mutable altBool           m_bLock;
};

#endif  // ALTSYNCTHREAD_H

