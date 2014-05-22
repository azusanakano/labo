#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef ALTPOLYGON_H
#define ALTPOLYGON_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altPolygon.h
 * \brief   Polygon class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN
#include <altDX/altTexture.h>
#include <altDX/altComponent.h>
#include <altDX/altDX.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
struct altVertex
{
  FLOAT x;
  FLOAT y;
  FLOAT z;
  DWORD dwColor;
};

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Polygon
///
class altPolygon : public altComponent
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altPolygon();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altPolygon();

  ///
  /// \brief  Create vertex buffer
  ///
  /// \param  pVertex         [I ] Vertex array
  /// \param  nSize           [I ] Vertex array size
  /// \param  dwFVFFormat     [I ] FVF Format
  /// \param  nPrimitiveCount [I ] Primitive count
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t CreateVertexBuffer(const altVertex * pVertex, const altUInt nSize, const DWORD dwFVFFormat, const altUInt nPrimitiveCount);

  ///
  /// \brief  Set primitive type
  ///
  /// \param  nPrimitiveType  [I ] Primitive type
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API alt_t SetPrimitiveType(const D3DPRIMITIVETYPE nPrimitiveType);

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
  LIBALT_API virtual alt_t Render(IDirect3DDevice9 * pDevice);

private:
  ///
  /// \brief  Clean up
  ///
  LIBALT_API void Cleanup();

  LPDIRECT3DVERTEXBUFFER9 m_pVB;              ///< Vertex Buffer
  DWORD                   m_dwFVFFormat;      ///< FVF Format
  altUInt                 m_nPrimitiveCount;  ///< Primitive Count
  D3DPRIMITIVETYPE        m_nPrimitiveType;   ///< Primitive Type
  altTexture              m_oTex;             ///< Texture
};

#endif
#endif

#endif // ALT_USE_DX