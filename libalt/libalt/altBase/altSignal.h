#ifndef ALTSIGNAL_H
#define ALTSIGNAL_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSignal.h
 * \brief   Signal class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_LINUX
#include <altBase/altLog.h>
#include <signal.h>

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Signal
///
class altSignal : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altSignal();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altSignal();

  ///
  /// \brief  Signal block
  ///
  /// \param  nSignal [I ] Signal Number
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API static alt_t Block(altInt nSignal);

  ///
  /// \brief  Signal block handler
  ///
  /// \param  nSignal [I ] Signal number
  ///
  LIBALT_API static void BlockHandler(int nSignal);
};

#endif
#endif
