#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef ALTIMECOMPONENT_H
#define ALTIMECOMPONENT_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altIMEComponent.h
 * \brief   IME control component class
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
#include <altBase/altStatus.h>

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  IME Control Component
///
class altIMEComponent : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altIMEComponent();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altIMEComponent();

  ///
  /// \brief  Input IME word
  ///
  /// \param  sData [I ] IME word
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API virtual alt_t InputIMEWord(const altWStr & sData) = 0;

  ///
  /// \brief  Send IME word
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API virtual alt_t SendIMEWord(const altWStr & sData) = 0;
};

#endif
#endif

#endif // ALT_USE_DX