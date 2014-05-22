#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altLabel.cpp
 * \brief   Label component class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altLabel.h"
#ifdef ALT_WIN
#include "../altFontManager.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
/// \param  x [I ] X
/// \param  y [I ] Y
/// \param  h [I ] Height
/// \param  w [I ] Width
///
LIBALT_API altLabel::altLabel(const altLong x, const altLong y, const altLong h, const altLong w) :
m_oBackGround(),
m_pFont (NULL),
m_dwFormat (DT_LEFT | DT_NOCLIP),
m_sText(),
m_dwTextColor (D3DCOLOR_RGBA (0, 0, 0, 255)),
m_dwBackColor (D3DCOLOR_RGBA (255, 255, 255, 0)),
m_x (x),
m_y (y),
m_h (h),
m_w (w)
{
  SetBackColor (m_dwBackColor);
  SetFont ("Default");
  altComponent::SetPositionEx(x, y, w, h);
}

///
/// \brief  Destructor
///
LIBALT_API altLabel::~altLabel()
{
}

///
/// \brief  Set font
///
/// \param  sFontName [I ] Font name
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altLabel::SetFont(const altStr & sFontName)
{
  altFont * pFont = aiFontManager.GetFont (sFontName);
  if (pFont == NULL) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("font [%s] not found", sFontName.GetCStr()));
  }

  m_pFont = pFont;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set text
///
/// \param  sText [I ] Text
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altLabel::SetText(const altWStr & sText)
{
  m_sText = sText;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set text color
///
/// \param  dwColor [I ] Text color
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altLabel::SetTextColor(const DWORD dwColor)
{
  m_dwTextColor = dwColor;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set format
///
/// \param  dwFormat  [I ] format
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altLabel::SetTextFormat(const DWORD dwFormat)
{
  m_dwFormat = dwFormat;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set background color
///
/// \param  dwColor [I ] Background color
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altLabel::SetBackColor(const DWORD dwColor)
{
  m_dwBackColor = dwColor;
  m_oBackGround.SetPosition ((altFloat)m_x, (altFloat)m_y, (altFloat)m_w, (altFloat)m_h, m_dwBackColor);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Render
///
/// \param  pDevice  [I ] D3D Device
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altLabel::Render(IDirect3DDevice9 * pDevice)
{
  alt_t status;

  status = m_oBackGround.Render (pDevice);
  ALT_LOG (status);

  if (m_pFont != NULL) {
    //m_pFont->Draw (m_sText, m_x, m_y, m_w, m_h, m_dwFormat, m_dwTextColor);
    m_pFont->Draw (m_sText, m_x, m_y, 0, m_dwTextColor);
  }

  return (altComponent::Render(pDevice));
}

#endif

#endif // ALT_USE_DX
