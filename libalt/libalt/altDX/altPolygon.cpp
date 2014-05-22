#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altPolygon.cpp
 * \brief   Polygon class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altPolygon.h"
#ifdef ALT_WIN

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altPolygon::altPolygon() :
m_pVB (NULL),
m_dwFVFFormat (0),
m_nPrimitiveCount (0),
m_nPrimitiveType (D3DPT_TRIANGLELIST)
{
}

///
/// \brief  Destructor
///
LIBALT_API altPolygon::~altPolygon()
{
  Cleanup();
}

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
LIBALT_API alt_t altPolygon::CreateVertexBuffer(const altVertex * pVertex, const altUInt nSize, const DWORD dwFVFFormat, const altUInt nPrimitiveCount)
{
  HRESULT hr;
  if (m_pVB != NULL) {
    Cleanup();
  }

  m_nPrimitiveCount = nPrimitiveCount;
  m_dwFVFFormat = dwFVFFormat;

  Cleanup();
  hr = aiDX.GetDevice()->CreateVertexBuffer (nSize, 0, m_dwFVFFormat, D3DPOOL_DEFAULT, & m_pVB, NULL); 
  if (FAILED (hr)) {
    ALT_RET_P (ALT_E_ERROR, DXGetErrorDescription9A (hr));
  }
  
  if (pVertex == NULL) {
    ALT_RET (ALT_E_ERROR);
  }

  VOID * pVertices = NULL;
  hr = m_pVB->Lock (0, nSize, (void **)& pVertices, 0);
  if (FAILED (hr)) {
    ALT_RET_P (ALT_E_ERROR, DXGetErrorDescription9A (hr));
  }
  memcpy (pVertices, pVertex, nSize);
  m_pVB->Unlock();

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set primitive type
///
/// \param  nPrimitiveType  [I ] Primitive type
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altPolygon::SetPrimitiveType(const D3DPRIMITIVETYPE nPrimitiveType)
{
  m_nPrimitiveType = nPrimitiveType;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set Texture
///
/// \param  sFileName [I ] File Name
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altPolygon::SetTexture(const altStr & sFileName)
{
  alt_t status = m_oTex.Load (sFileName);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Render
///
/// \param  pd3dDevice  [I ] D3D Device
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altPolygon::Render(IDirect3DDevice9 * pDevice)
{
  HRESULT hr;

  m_oTex.SetTexture();

  hr = pDevice->SetStreamSource (0, m_pVB, 0, sizeof (altVertex));
  if (FAILED (hr)) {
    ALT_RET_P (ALT_E_ERROR, DXGetErrorDescription9A (hr));
  }

  hr = pDevice->SetFVF (m_dwFVFFormat);
  if (FAILED (hr)) {
    ALT_RET_P (ALT_E_ERROR, DXGetErrorDescription9A (hr));
  }

  hr = pDevice->DrawPrimitive (m_nPrimitiveType, 0, m_nPrimitiveCount);
  if (FAILED (hr)) {
    ALT_RET_P (ALT_E_ERROR, DXGetErrorDescription9A (hr));
  }

  ALT_RET (altComponent::Render (pDevice));
}

///
/// \brief  Clean up
///
LIBALT_API void altPolygon::Cleanup()
{
  if (m_pVB != NULL) {
    m_pVB->Release();
    m_pVB = NULL;
  }
}

#endif

#endif // ALT_USE_DX