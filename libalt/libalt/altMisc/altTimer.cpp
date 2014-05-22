/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTimer.cpp
 * \brief   Timer class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altTimer.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altTimer::altTimer() :
#ifdef ALT_WIN
m_nTimerID (0),
#endif
#ifdef ALT_LINUX
m_oAct(),
m_oOldAct(),
m_oValue(),
m_oOldValue(),
m_pTimerCallBack(NULL),
#endif
m_bStarted (false)
{
}

///
/// \brief  Destructor
///
LIBALT_API altTimer::~altTimer()
{
  Stop();
}

///
/// \brief  Start Timer
///
/// \param  nDelay    [I ] Timer Interval
/// \return pCallBack [I ] Call Back Function
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altTimer::Start(const altUInt nDelay, altTimerCallBack pCallBack)
{
  if (pCallBack == NULL) {
    ALT_RET (ALT_E_ERROR);
  }
  if (m_bStarted) {
    ALT_RET (ALT_E_ERROR);
  }
#ifdef ALT_WIN
  m_nTimerID = timeSetEvent (nDelay, 5, (LPTIMECALLBACK)pCallBack, NULL, TIME_PERIODIC);
#endif

#ifdef ALT_LINUX
  memset (& m_oAct, 0x00, sizeof (m_oAct));
  m_oAct.sa_handler = pCallBack;
  sigaction (SIGALRM, & m_oAct, & m_oOldAct);

  m_oValue.it_value.tv_usec = (nDelay % 1000) * 100000;
  m_oValue.it_value.tv_sec = nDelay / 1000;
  m_oValue.it_interval.tv_usec = (nDelay % 1000) * 100000;
  m_oValue.it_interval.tv_sec = nDelay / 1000;
  setitimer (ITIMER_REAL, & m_oValue, & m_oOldValue);
#endif
  m_bStarted = true;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Stop Timer
///
/// \return ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altTimer::Stop()
{
  if (! m_bStarted) {
    ALT_RET (ALT_S_SUCCESS);
  }
#ifdef ALT_WIN
  timeKillEvent (m_nTimerID);
#endif

#ifdef ALT_LINUX
  setitimer (ITIMER_REAL, & m_oOldValue, & m_oValue);
  sigaction (SIGALRM, & m_oOldAct, NULL);
#endif
  m_bStarted = false;
  ALT_RET (ALT_S_SUCCESS);
}


