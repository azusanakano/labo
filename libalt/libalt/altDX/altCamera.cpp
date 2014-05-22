#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altCamera.cpp
 * \brief   Camera class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altCamera.h"
#ifdef ALT_WIN

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altCamera::altCamera() :
m_matTrans(),
m_matRotation(),
m_matRotation2(),
m_matWorld(),
m_vecEyePosition (0.0f, 0.0f, 0.0f),
m_vecLookAtPosition (0.0f, 0.0f, 0.0f),
m_vecUpVector (0.0f, 0.0f, 0.0f),
m_matView(),
m_matProjection(),
m_bRotation (false)
{
  D3DXMatrixIdentity (& m_matWorld);
  D3DXMatrixIdentity (& m_matRotation);
  D3DXMatrixIdentity (& m_matRotation2);
}

///
/// \brief  Destructor
///
LIBALT_API altCamera::~altCamera()
{
}

///
/// \brief  Translation
///
/// \param  x [I ] X
/// \param  y [I ] Y
/// \param  z [I ] Z
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altCamera::Translation(const FLOAT x, const FLOAT y, const FLOAT z)
{
  D3DXMatrixTranslation (& m_matTrans, x, y, z);
  D3DXMatrixMultiply (& m_matWorld, & m_matWorld, & m_matTrans);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Translation
///
/// \param  x [I ] X
/// \param  y [I ] Y
/// \param  z [I ] Z
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altCamera::Scaling(const altFloat x, const altFloat y, const altFloat z)
{
  D3DXMatrixScaling (& m_matScale, x, y, z);
  D3DXMatrixMultiply (& m_matWorld, & m_matWorld, & m_matScale);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set transform world
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altCamera::SetTransformWorld()
{
  aiDX.GetDevice()->SetTransform (D3DTS_WORLD, & m_matWorld);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set rotation world
///
/// \param  x [I ] X
/// \param  y [I ] Y
/// \param  z [I ] Z
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altCamera::SetRotationWorld(const FLOAT x, const FLOAT y, const FLOAT z)
{
  D3DXMatrixRotationX (& m_matRotation2, x);
  D3DXMatrixMultiply (& m_matRotation, & m_matRotation, & m_matRotation2);
  D3DXMatrixRotationY (& m_matRotation2, y);
  D3DXMatrixMultiply (& m_matRotation, & m_matRotation, & m_matRotation2);
  D3DXMatrixRotationZ (& m_matRotation2, z);
  D3DXMatrixMultiply (& m_matRotation, & m_matRotation, & m_matRotation2);
  D3DXMatrixMultiply (& m_matWorld, & m_matWorld, & m_matRotation);
  aiDX.GetDevice()->SetTransform (D3DTS_WORLD, & m_matWorld);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set eye position
///
/// \param  x [I ] X
/// \param  y [I ] Y
/// \param  z [I ] Z
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altCamera::SetEyePosition(const FLOAT x, const FLOAT y, const FLOAT z)
{
  m_vecEyePosition.x = x;
  m_vecEyePosition.y = y;
  m_vecEyePosition.z = z;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set look at position
///
/// \param  x [I ] X
/// \param  y [I ] Y
/// \param  z [I ] Z
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altCamera::SetLookAtPosition(const FLOAT x, const FLOAT y, const FLOAT z)
{
  m_vecLookAtPosition.x = x;
  m_vecLookAtPosition.y = y;
  m_vecLookAtPosition.z = z;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set up vector
///
/// \param  x [I ] X
/// \param  y [I ] Y
/// \param  z [I ] Z
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altCamera::SetUpVector(const FLOAT x, const FLOAT y, const FLOAT z)
{
  m_vecUpVector.x = x;
  m_vecUpVector.y = y;
  m_vecUpVector.z = z;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set transform view
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altCamera::SetTransformView()
{
  D3DXMatrixLookAtLH (& m_matView, & m_vecEyePosition, & m_vecLookAtPosition, & m_vecUpVector);
  aiDX.GetDevice()->SetTransform (D3DTS_VIEW, & m_matView);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set transfrom projection
///
/// \param  fFovy   [I ] Field of view in the y direction, in radians.
/// \param  fAspect [I ] Aspect ratio, defined as view space width divided by height. 
/// \param  fZn     [I ] Z-value of the near view-plane.
/// \param  fZf     [I ] Z-value of the far view-plane.
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altCamera::SetTransformProjection(const FLOAT fFovy, const FLOAT fAspect, const FLOAT fZn, const FLOAT fZf)
{
  D3DXMatrixPerspectiveFovLH (& m_matProjection, fFovy, fAspect, fZn, fZf);
  aiDX.GetDevice()->SetTransform (D3DTS_PROJECTION, & m_matProjection);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set transform default
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altCamera::SetTransform()
{
  alt_t status;

  status = SetTransformWorld();
  ALT_ERR_RET (status);

  status = SetTransformView();
  ALT_ERR_RET (status);

  status = SetTransformProjection();
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

#endif

#endif // ALT_USE_DX