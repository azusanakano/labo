#ifndef ALTTIMER_H
#define ALTTIMER_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTimer.h
 * \brief   Timer class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altStatus.h>
#include <altBase/altLog.h>

#ifdef ALT_LINUX
  #include <sys/time.h>
  #include <signal.h>
  #include <unistd.h>
#endif

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef void (* altTimerCallBack)(int);

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Timer
///
class altTimer : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altTimer();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altTimer();

  ///
  /// \brief  Start Timer
  ///
  /// \param  nDelay    [I ] Timer Interval
  /// \return pCallBack [I ] Call Back Function
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t Start(const altUInt nDelay, altTimerCallBack pCallBack);

  ///
  /// \brief  Stop Timer
  ///
  /// \return ALT_S_SUCCESS
  ///
  LIBALT_API alt_t Stop();

private:
#ifdef ALT_WIN
  altUInt m_nTimerID;   ///< Timer ID
#endif
#ifdef ALT_LINUX
  struct sigaction  m_oAct;
  struct sigaction  m_oOldAct;
  struct itimerval  m_oValue;
  struct itimerval  m_oOldValue;
  altTimerCallBack  m_pTimerCallBack;
#endif
  altBool m_bStarted;   ///< Started
};

#endif
