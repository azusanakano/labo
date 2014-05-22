#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef ALTKEYEVENTLISTENER_H
#define ALTKEYEVENTLISTENER_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altKeyEventListener.h
 * \brief   Key event listener class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN
#include <altDX/altEvent.h>
#include <altBase/altLog.h>

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Key Event Listener
///
class altKeyEventListener : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altKeyEventListener();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altKeyEventListener();

  ///
  /// \brief  Listen key down event
  ///
  /// \param  oEvent  [I ] Event
  /// \param  nKey    [I ] Key
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API virtual alt_t OnKeyDown(const altEvent & oEvent, const altUInt nKey) = 0;
};

#endif
#endif

#endif // ALT_USE_DX