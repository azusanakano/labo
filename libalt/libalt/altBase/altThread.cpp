/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altThread.cpp
 * \brief   Thread class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altThread.h"

#ifdef ALT_WIN
  #include <process.h>
#else
  #include <pthread.h>
#endif

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altThread::altThread()
{
}

///
/// \brief  Destructor
///
LIBALT_API altThread::~altThread()
{
}

///
/// \brief  Start thread
///
LIBALT_API void altThread::Start(altThreadFunc pFunc, void * pParam)
{
#ifdef ALT_WIN
  _beginthread (pFunc, 0, pParam);
#else
  pthread_t oThread;
  altInt nRet = pthread_create (& oThread, NULL, pFunc, pParam);
  if (nRet != 0) {
    // error
  }
#endif
}

