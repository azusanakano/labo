#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.

/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    alt2DQuad.cpp
 * \brief   DirectX 2D Quad class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "alt2DQuad.h"
#include "altDX.h"
#ifdef ALT_WIN

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/
const DWORD TLVERTEX::FVF_FORMAT = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API alt2DQuad::alt2DQuad() :
m_pVB (NULL),
m_oTex(),
m_x(0),
m_y(0),
m_w(0),
m_h(0),
m_dwColor (D3DCOLOR_RGBA (255, 255, 255, 255))
{
  aiDX.GetDevice()->CreateVertexBuffer (sizeof (TLVERTEX) * 4, 0, TLVERTEX::FVF_FORMAT, D3DPOOL_MANAGED, & m_pVB, NULL);
}

///
/// \brief  Destructor
///
LIBALT_API alt2DQuad::~alt2DQuad()
{
  Cleanup();
}

///
/// \brief  Set Position
///
/// \param  x       [I ] X
/// \param  y       [I ] Y
/// \param  w       [I ] Width
/// \param  h       [I ] Height
/// \param  dwColor [I ] Color
///
LIBALT_API alt_t alt2DQuad::SetPosition(const FLOAT x, const FLOAT y, const FLOAT w, const FLOAT h, const DWORD dwColor)
{
  alt_t status;
  m_x = x;
  m_y = y;
  m_w = w;
  m_h = h;
  m_dwColor = dwColor;
  status = SetPosition (& D3DXVECTOR3(x, y, 0), & D3DXVECTOR2(w, h), dwColor);
  ALT_RET (status);
}

///
/// \brief  Set Position
///
/// \param  x [I ] X
/// \param  y [I ] Y
/// \param  w [I ] Width
/// \param  h [I ] Height
///
LIBALT_API alt_t alt2DQuad::SetPosition(const FLOAT x, const FLOAT y, const FLOAT w, const FLOAT h)
{
  alt_t status;
  status = SetPosition (x, y, w, h, m_dwColor);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set color
///
/// \param  dwColor [I ] Color
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t alt2DQuad::SetColor(const DWORD dwColor)
{
  alt_t status;
  status = SetPosition (m_x, m_y, m_w, m_h, dwColor);
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
LIBALT_API alt_t alt2DQuad::SetTexture(const altStr & sFileName)
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
LIBALT_API alt_t alt2DQuad::Render(IDirect3DDevice9 * pd3dDevice)
{
  if (m_pVB == NULL) {
    ALT_RET_P (ALT_E_ERROR, "Not Initialized");
  }

  if (pd3dDevice == NULL) {
    ALT_RET_P (ALT_E_ERROR, "pd3dDevice is NULL");
  }

  m_oTex.SetTexture();

  HRESULT hr = pd3dDevice->SetFVF (TLVERTEX::FVF_FORMAT);
  if (FAILED (hr)) {
    ALT_RET (ALT_E_ERROR);
  }

  hr = pd3dDevice->SetStreamSource (0, m_pVB, 0, sizeof (TLVERTEX));
  if (FAILED (hr)) {
    ALT_RET (ALT_E_ERROR);
  }

  aiDX.SetAlphaBlendEnable (true);

  hr = pd3dDevice->DrawPrimitive (D3DPT_TRIANGLESTRIP, 0, 2);
  if (FAILED (hr)) {
    ALT_RET (ALT_E_ERROR);
  }

  alt_t status = altComponent::Render(pd3dDevice);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Release Memory
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t alt2DQuad::Cleanup()
{
  if (m_pVB != NULL) {
    m_pVB->Release();
    m_pVB = NULL;
  }
  ALT_RET (ALT_S_SUCCESS);
}

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
LIBALT_API alt_t alt2DQuad::SetPosition(const D3DXVECTOR3 * vPos, const D3DXVECTOR2 * vRect, const DWORD dwColor)
{
  if (m_pVB == NULL) {
    ALT_RET_P (ALT_E_ERROR, "Not Initialized");
  }

  TLVERTEX v[] = { * vPos, 1.0f, dwColor, 0.0f, 0.0f, 
                   * vPos + D3DXVECTOR3 (vRect->x, 0, 0), 1.0f, dwColor, 1.0f, 0.0f,
                   * vPos + D3DXVECTOR3 (0, vRect->y, 0), 1.0f, dwColor, 0.0f, 1.0f,
                   * vPos + D3DXVECTOR3 (vRect->x, vRect->y, 0), 1.0f, dwColor, 1.0f, 1.0f,};

  TLVERTEX * pV = NULL;

  HRESULT hr = m_pVB->Lock (0, 0, (VOID **)& pV, 0);
  if (FAILED (hr)) {
    ALT_RET (ALT_E_ERROR);
  }

  memcpy (pV, v, sizeof (v));
  m_pVB->Unlock();

  ALT_RET (ALT_S_SUCCESS);
}

#endif

#endif // ALT_USE_DX