#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef ALTLIGHT_H
#define ALTLIGHT_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altLight.h
 * \brief   Light class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN
#include <altDX/altDX.h>
#include <altBase/altLog.h>

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Light
///
class altLight : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altLight();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altLight();

  ///
  /// \brief  Set light
  ///
  /// \param  vecDirection  [I ] Direction
  /// \param  nType         [I ] Type
  /// \param  oDiffuse      [I ] Diffuse Color
  /// \param  oSpecular     [I ] Specular Color
  /// \param  fRange        [I ] Range
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetLight(const D3DXVECTOR3 & vecDirection, const D3DLIGHTTYPE nType, const D3DCOLORVALUE & oDiffuse, const D3DCOLORVALUE & oSpecular, const FLOAT fRange);

private:
  D3DLIGHT9 m_oLight;
};

#endif
#endif

#endif // ALT_USE_DX