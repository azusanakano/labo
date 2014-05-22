#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef ALTFONT_H
#define ALTFONT_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altFont.h
 * \brief   DirectX 2D Font class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN
#include <altDX/altDX.h>
#include <altBase/altStr.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef struct altFontSprite
{
	LPDIRECT3DTEXTURE9  pTexture;
	RECT                oRect;
	D3DXVECTOR3         pCenter;
	D3DXVECTOR3         pPosition;
	D3DCOLOR            dwColor;
}altFontSprite;

typedef struct altFontChar
{
  altFloat            w;
  altFloat            h;
  UINT                nCode;
  LPDIRECT3DTEXTURE9  pTex;
} altFontChar;

typedef std::map<UINT, altFontChar *> altFontCharMap;

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  DirectX 2D Font
///
class altFont : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  h         [I ] Font Height
  /// \param  w         [I ] Font Width
  /// \param  nWeight   [I ] Font weight
  /// \param  bItalic   [I ] Italic or not
  /// \param  nCharSet  [I ] Charcter set
  /// \param  sFaceName [I ] Font face name
  ///
  LIBALT_API altFont(const altInt h, const altInt w, const altUInt nWeight, const altBool bItalic, const BYTE nCharSet, const altWStr & sFaceName);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altFont();

  ///
  /// \brief Draw string
  ///
  /// \param  sStr    [I ] String
  /// \param  x       [I ] X
  /// \param  y       [I ] Y
  /// \param  z       [I ] Z
  /// \param  dwColor [I ] Color
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t Draw(const altWStr & sStr, const altInt x, const altInt y, const altInt z, const D3DCOLOR dwColor = D3DCOLOR_XRGB (0, 0, 0));

  ///
  /// \brief  Get text width
  ///
  /// \param  sText [I ] Text
  ///
  /// \return Text width
  ///
  LIBALT_API altLong GetWidth(const altWStr & sText) const;

protected:
  ///
  /// \brief  Get font char
  ///
  /// \param  nCode     [I ] Code
  /// \param  pFontChar [ O] Character
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t GetFontChar(UINT nCode, altFontChar * & pFontChar);

  HFONT           m_hFont;          ///< Font data
  altFontCharMap  m_oFontCharMap;   ///< Font character map
};

#endif
#endif

#endif // ALT_USE_DX