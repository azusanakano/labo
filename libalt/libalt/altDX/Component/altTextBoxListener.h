#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef ALTTEXTBOXLISTENER_H
#define ALTTEXTBOXLISTENER_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTextBoxListener.h
 * \brief   Text box listener class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN
#include <altBase/altWStr.h>
#include <altBase/altLog.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Text Box Listener
///
class altTextBoxListener
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altTextBoxListener();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altTextBoxListener();

  ///
  /// \brief  On input call back
  ///
  /// \param  sMessage  [I ] Message
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API virtual alt_t OnInput(const altWStr & sMessage) = 0;
};

#endif
#endif

#endif // ALT_USE_DX