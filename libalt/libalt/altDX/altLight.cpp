#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altLight.cpp
 * \brief   Light class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altLight.h"
#ifdef ALT_WIN

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altLight::altLight() :
m_oLight()
{
}

///
/// \brief  Destructor
///
LIBALT_API altLight::~altLight()
{
}

///
/// \brief  Set light
///
/// \param  vecDirection  [I ] Direction
/// \param  oDiffuse      [I ] Diffuse Color
/// \param  oSpecular     [I ] Specular Color
/// \param  fRange        [I ] Range
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altLight::SetLight(const D3DXVECTOR3 & vecDirection, const D3DLIGHTTYPE nType, const D3DCOLORVALUE & oDiffuse, const D3DCOLORVALUE & oSpecular, const FLOAT fRange)
{
  ZeroMemory(& m_oLight, sizeof (m_oLight));
  m_oLight.Type = nType;
  m_oLight.Diffuse = oDiffuse;
  m_oLight.Specular = oSpecular;
  D3DXVec3Normalize ((D3DXVECTOR3 *)& m_oLight.Direction, & vecDirection);
  m_oLight.Range = fRange;
  aiDX.GetDevice()->SetLight (0, & m_oLight);
  aiDX.GetDevice()->LightEnable (0, TRUE);

  ALT_RET (ALT_S_SUCCESS);
}

#endif

#endif // ALT_USE_DX