#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.

#ifndef ALT2DQUAD_H
#define ALT2DQUAD_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    alt2DQuad.h
 * \brief   DirectX 2D Quad class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN

#include <altDX/altCamera.h>
#include <altDX/altPolygon.h>
#include <altDX/altTexture.h>
#include <altDX/altComponent.h>
#include <altBase/altStatus.h>


/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
struct TLVERTEX
{
  D3DXVECTOR3   vPos;
  FLOAT         rhw;
  DWORD         color;
  FLOAT         tu;
  FLOAT         tv;

  static const DWORD  FVF_FORMAT;
};

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  DirectX 2D Quad
///
class alt2DQuad : public altComponent
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API alt2DQuad();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~alt2DQuad();

  ///
  /// \brief  Set Position
  ///
  /// \param  x       [I ] X
  /// \param  y       [I ] Y
  /// \param  w       [I ] Width
  /// \param  h       [I ] Height
  /// \param  dwColor [I ] Color
  ///
  LIBALT_API alt_t SetPosition(const FLOAT x, const FLOAT y, const FLOAT w, const FLOAT h, const DWORD dwColor);

  ///
  /// \brief  Set Position
  ///
  /// \param  x [I ] X
  /// \param  y [I ] Y
  /// \param  w [I ] Width
  /// \param  h [I ] Height
  ///
  LIBALT_API alt_t SetPosition(const FLOAT x, const FLOAT y, const FLOAT w, const FLOAT h);

  ///
  /// \brief  Set color
  ///
  /// \param  dwColor [I ] Color
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetColor(const DWORD dwColor);

  ///
  /// \brief  Set Texture
  ///
  /// \param  sFileName [I ] File Name
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t SetTexture(const altStr & sFileName);

  ///
  /// \brief  Render
  ///
  /// \param  pd3dDevice  [I ] D3D Device
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t Render(IDirect3DDevice9 * pd3dDevice);

  ///
  /// \brief  Release Memory
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API alt_t Cleanup();

private:
  ///
  /// \brief  Set Position
  ///
  /// \param  vPos    [I ] Position
  /// \param  vRect   [I ] Rectangle
  /// \param  dwColor [I ] Color
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t SetPosition(const D3DXVECTOR3 * vPos, const D3DXVECTOR2 * vRect, const DWORD dwColor);

  IDirect3DVertexBuffer9 *    m_pVB;      ///< Pointer of Vertex Buffer
  altTexture                  m_oTex;     ///< Texture
  FLOAT                       m_x;        ///< X
  FLOAT                       m_y;        ///< Y
  FLOAT                       m_w;        ///< Width
  FLOAT                       m_h;        ///< Height
  DWORD                       m_dwColor;  ///< Color
};

#endif
#endif

#endif // ALT_USE_DX