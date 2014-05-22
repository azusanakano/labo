#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.

#ifndef ALTCAMERA_H
#define ALTCAMERA_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altCamera.h
 * \brief   Camera class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN
#include <altDX/altDX.h>

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Camera
///
class altCamera : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altCamera();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altCamera();

  ///
  /// \brief  Translation
  ///
  /// \param  x [I ] X
  /// \param  y [I ] Y
  /// \param  z [I ] Z
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t Translation(const FLOAT x = 0, const FLOAT y = 0, const FLOAT z = 0);

  ///
  /// \brief  Translation
  ///
  /// \param  x [I ] X
  /// \param  y [I ] Y
  /// \param  z [I ] Z
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t Scaling(const altFloat x, const altFloat y, const altFloat z);

  ///
  /// \brief  Set transform world
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetTransformWorld();

  ///
  /// \brief  Set rotation world
  ///
  /// \param  x [I ] X
  /// \param  y [I ] Y
  /// \param  z [I ] Z
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetRotationWorld(const FLOAT x, const FLOAT y, const FLOAT z);

  ///
  /// \brief  Set eye position
  ///
  /// \param  x [I ] X
  /// \param  y [I ] Y
  /// \param  z [I ] Z
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetEyePosition(const FLOAT x = 0.0f, const FLOAT y = 1.0f, const FLOAT z = -3.0f);

  ///
  /// \brief  Set look at position
  ///
  /// \param  x [I ] X
  /// \param  y [I ] Y
  /// \param  z [I ] Z
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetLookAtPosition(const FLOAT x = 0.0f, const FLOAT y = 0.0f, const FLOAT z = 0.0f);

  ///
  /// \brief  Set up vector
  ///
  /// \param  x [I ] X
  /// \param  y [I ] Y
  /// \param  z [I ] Z
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetUpVector(const FLOAT x = 0.0f, const FLOAT y = 1.0f, const FLOAT z = 0.0f);

  ///
  /// \brief  Set transform view
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetTransformView();

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
  LIBALT_API alt_t SetTransformProjection(const FLOAT fFovy = D3DX_PI/4, const FLOAT fAspect = 1.0f, const FLOAT fZn = 1.0f, const FLOAT fZf = 100.0f);

  ///
  /// \brief  Set transform default
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetTransform();

private:
  D3DXMATRIXA16   m_matTrans;
  D3DXMATRIXA16   m_matScale;
  D3DXMATRIXA16   m_matRotation;
  D3DXMATRIXA16   m_matRotation2;
  D3DXMATRIXA16   m_matWorld;

  D3DXVECTOR3     m_vecEyePosition;
  D3DXVECTOR3     m_vecLookAtPosition;
  D3DXVECTOR3     m_vecUpVector;
  D3DXMATRIXA16   m_matView;
  D3DXMATRIXA16   m_matProjection;

  altBool         m_bRotation;
};

#endif
#endif

#endif // ALT_USE_DX