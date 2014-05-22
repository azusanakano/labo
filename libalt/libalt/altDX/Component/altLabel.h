#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef ALTLABEL_H
#define ALTLABEL_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altLabel.h
 * \brief   Label component class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN
#include <altDX/alt2DQuad.h>
#include <altDX/altFont.h>
#include <altDX/altDX.h>
#include <altBase/altStr.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  DirectX 2D Label
///
class altLabel : public altComponent
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  x [I ] X
  /// \param  y [I ] Y
  /// \param  h [I ] Height
  /// \param  w [I ] Width
  ///
  LIBALT_API altLabel(const altLong x, const altLong y, const altLong h, const altLong w);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altLabel();

  ///
  /// \brief  Set font
  ///
  /// \param  sFontName [I ] Font name
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t SetFont(const altStr & sFontName);

  ///
  /// \brief  Set text
  ///
  /// \param  sText [I ] Text
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetText(const altWStr & sText);

  ///
  /// \brief  Set text color
  ///
  /// \param  dwColor [I ] Text color
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetTextColor(const DWORD dwColor);

  ///
  /// \brief  Set text format
  ///
  /// \param  dwFormat  [I ] format
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetTextFormat(const DWORD dwFormat);

  ///
  /// \brief  Set background color
  ///
  /// \param  dwColor [I ] Background color
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetBackColor(const DWORD dwColor);

  ///
  /// \brief  Render
  ///
  /// \param  pDevice  [I ] D3D Device
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API virtual alt_t Render(IDirect3DDevice9 * pDevice);

protected:
  altWStr       m_sText;        ///< Text
  altFont *     m_pFont;        ///< Font
  DWORD         m_dwFormat;     ///< Text format
  DWORD         m_dwTextColor;  ///< Text color
  altLong       m_x;
  altLong       m_y;
  altLong       m_h;
  altLong       m_w;
  alt2DQuad     m_oBackGround;  ///< BackGround

private:
  DWORD         m_dwBackColor;  ///< Background color
};

#endif
#endif

#endif // ALT_USE_DX