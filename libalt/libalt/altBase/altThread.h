#ifndef ALTTHREAD_H
#define ALTTHREAD_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altThread.h
 * \brief   Thread class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altBase.h>
#include <altBase/altUncopyable.h>

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
#ifdef ALT_WIN
  #define ALT_THREAD  void
#else
  #define ALT_THREAD  void *
#endif

#ifdef ALT_WIN
  #define ALT_THREAD_END(p) return
#else
  #define ALT_THREAD_END(p) return (p)
#endif

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef ALT_THREAD (* altThreadFunc)(void *);

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Thread
///
class altThread : public altBase, private altUncopyable
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altThread();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altThread();

  ///
  /// \brief  Start thread
  ///
  /// \param  pFunc   [I ] thread funciton
  /// \param  pParam  [I ] thread function parameter
  ///
  LIBALT_API virtual void Start(altThreadFunc pFunc, void * pParam);
};

#endif  // ALTTHREAD_H

