#ifndef ALTLOOPTHREAD_H
#define ALTLOOPTHREAD_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altLoopThread.h
 * \brief   loop thread
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altThread.h>
#include <altBase/altStatus.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef alt_t (* altLoopThreadFunc)(void *);

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Thread
///
class altLoopThread : public altThread
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  nInterval [I ] thread interval(msec)
  ///
  LIBALT_API altLoopThread(DWORD nInterval = 20);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altLoopThread();

  ///
  /// \brief  Set thread interval
  ///
  /// \param  nInterval [I ] Interval (msec)
  ///
  LIBALT_API void SetInterval(DWORD nInterval);

  ///
  /// \brief  Start thread
  ///
  /// \param  pFunc   [I ] thread funciton
  /// \param  pParam  [I ] thread function parameter
  ///
  LIBALT_API void Start(altLoopThreadFunc pFunc, void * pParam);

  ///
  /// \brief  Stop thread
  ///
  LIBALT_API void Stop();

  ///
  /// \brief  Stop thread no wait
  ///
  LIBALT_API void StopNoWait();

private:
  ///
  /// \brief  Loop thread function
  ///
  /// \param  pParam  [I ] thread function parameter
  ///
  LIBALT_API static ALT_THREAD Run(void * pParam);

  altBool   m_bThreadContinue;    ///< continue loop flag
  altBool   m_bThreadDone;        ///< thread done flag
  DWORD     m_nInterval;          ///< thread interval
};

#endif  // ALTLOOPTHREAD_H

