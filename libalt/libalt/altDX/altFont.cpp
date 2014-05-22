#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altFont.cpp
 * \brief   DirectX 2D Font class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altFont.h"
#ifdef ALT_WIN

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
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
LIBALT_API altFont::altFont(const altInt h, const altInt w, const altUInt nWeight, const altBool bItalic, const BYTE nCharSet, const altWStr & sFaceName) :
m_hFont (NULL),
m_oFontCharMap()
{
  LOGFONT logFont;
  logFont.lfHeight = h;
  logFont.lfWidth = w;
  logFont.lfEscapement = 0;
  logFont.lfOrientation = 0;
  logFont.lfWeight = nWeight;
  logFont.lfItalic = bItalic;
  logFont.lfUnderline = 0;
  logFont.lfStrikeOut = 0;
  logFont.lfCharSet = nCharSet;
  logFont.lfOutPrecision = OUT_TT_ONLY_PRECIS;
  logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
  logFont.lfQuality = PROOF_QUALITY;
  logFont.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
  lstrcpy (logFont.lfFaceName, (LPCWSTR)sFaceName.GetCStr());
  m_hFont = CreateFontIndirect (& logFont);
}

///
/// \brief  Destructor
///
LIBALT_API altFont::~altFont()
{
  for (altFontCharMap::iterator i = m_oFontCharMap.begin(); i != m_oFontCharMap.end(); i++) {
    delete i->second;
    i->second = NULL;
  }
  m_oFontCharMap.clear();
  if (m_hFont != NULL) {
    DeleteObject (m_hFont);
    m_hFont = NULL;
  }
}

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
LIBALT_API alt_t altFont::Draw(const altWStr & sStr, const altInt x, const altInt y, const altInt z, const D3DCOLOR dwColor)
{
  alt_t         status;
  altFontSprite oSprite;
  altFontChar * pFontChar = NULL;
  altInt        dX = x;
  altInt        dY = y;

  for (altUInt i = 0; i < sStr.GetLen(); i++) {
    status = GetFontChar (sStr[i], pFontChar);
    ALT_ERR_RET (status);

    oSprite.pTexture = pFontChar->pTex;
    oSprite.oRect.bottom = (LONG)pFontChar->h;
    oSprite.oRect.left = 0;
    oSprite.oRect.right = (LONG)pFontChar->w;
    oSprite.oRect.top = 0;

    oSprite.pCenter = D3DXVECTOR3 (0, 0, 0);
    oSprite.pPosition = D3DXVECTOR3((float)dX,(float)dY, 0);
    oSprite.dwColor = dwColor;

    D3DXMATRIX pMatrix;
    aiDX.GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
    aiDX.GetSprite()->SetTransform (D3DXMatrixTransformation2D(& pMatrix, NULL, 0.0f, NULL, NULL, 0.0f, NULL));
    aiDX.GetSprite()->Draw (oSprite.pTexture, & oSprite.oRect, & oSprite.pCenter, & oSprite.pPosition, oSprite.dwColor);
    aiDX.GetSprite()->End();

    dX += (altInt)pFontChar->w;
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get text width
///
/// \param  sText [I ] Text
///
/// \return Text width
///
LIBALT_API altLong altFont::GetWidth(const altWStr & sText) const
{
  GLYPHMETRICS  oGM;
	TEXTMETRIC    oTM;

	HDC hdc = GetDC (NULL);
	SelectObject (hdc, m_hFont);

  CONST MAT2 Mat = {{0,1},{0,0},{0,0},{0,1}};

  altLong nWidth = 0;
  for (altUInt i = 0; i <= sText.GetLen(); i++) {
    altUInt nCode = sText[i];
	  GetTextMetrics (hdc, & oTM);
	  DWORD nSize = GetGlyphOutline (hdc, nCode, GGO_BEZIER, & oGM, 0, NULL, & Mat);
    if (nSize == GDI_ERROR) {
      altStr  sBuf;
      ALT_LOG_P (ALT_E_ERROR, sBuf.Format ("%lu", GetLastError()));
      continue;
    }
    nWidth += oGM.gmCellIncX;
  }
  ReleaseDC (NULL, hdc);
  return (nWidth);
}

///
/// \brief  Get font char
///
/// \param  nCode     [I ] Code
/// \param  pFontChar [ O] Character
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altFont::GetFontChar(UINT nCode, altFontChar * & pFontChar)
{
  pFontChar = m_oFontCharMap[nCode];
  if (pFontChar != NULL) {
    ALT_RET (ALT_S_SUCCESS);
  }

	LPDIRECT3DTEXTURE9  pTex = NULL;
  GLYPHMETRICS        oGM;
	TEXTMETRIC          oTM;

	HDC hdc = GetDC (NULL);
	SelectObject (hdc, m_hFont);

  CONST MAT2 Mat = {{0,1},{0,0},{0,0},{0,1}};

  GetTextMetrics (hdc, & oTM);
  DWORD nSize = GetGlyphOutline (hdc, nCode, GGO_BEZIER, & oGM, 0, NULL, & Mat);
  if (nSize == GDI_ERROR) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%lu", GetLastError()));
  }
  BYTE * ptr = new BYTE[nSize];
  GetGlyphOutline (hdc, nCode, GGO_GRAY4_BITMAP, & oGM, nSize, ptr, & Mat);
  ReleaseDC (NULL, hdc);

  if (FAILED (aiDX.GetDevice()->CreateTexture (oGM.gmCellIncX, oTM.tmHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, & pTex, NULL))) {
    ALT_RET (ALT_E_ERROR); 
  };

  D3DLOCKED_RECT oLockedRect;
  pTex->LockRect (0, & oLockedRect, NULL, D3DLOCK_DISCARD);

  int iOfs_x = oGM.gmptGlyphOrigin.x;
  int iOfs_y = oTM.tmAscent - oGM.gmptGlyphOrigin.y;
  int iBmp_w = oGM.gmBlackBoxX + (4 - (oGM.gmBlackBoxX % 4)) % 4;
  int iBmp_h = oGM.gmBlackBoxY;
  int Level = 17;
  int x, y;
  DWORD Alpha;
  DWORD Color;
  FillMemory(oLockedRect.pBits, oLockedRect.Pitch * oTM.tmHeight, 0);
  for(y = iOfs_y; y < iOfs_y+iBmp_h; y++) {
    for(x = iOfs_x; x < iOfs_x + iBmp_w; x++){
      Alpha = (255 * ptr[x-iOfs_x + iBmp_w * (y - iOfs_y)]) / (Level-1);
      // Space
      if(nCode == 0x20 || nCode == 0x8140) {
        Color = 0;
      }
      else {
        Color = D3DCOLOR_ARGB (Alpha, 255, 255, 255);
      }
      memcpy((BYTE*)oLockedRect.pBits + oLockedRect.Pitch * y + 4 * x, & Color, sizeof (DWORD));
    }
  }

  pTex->UnlockRect (0);
  delete[] ptr;

  pFontChar = new altFontChar();
  if (pFontChar == NULL) {
    ALT_RET (ALT_E_NOMEM);
  }

  pFontChar->w = oGM.gmCellIncX;
  pFontChar->h = (altFloat)oTM.tmHeight;
  pFontChar->nCode = nCode;
  pFontChar->pTex = pTex;

  m_oFontCharMap[nCode] = pFontChar;

  ALT_RET (ALT_S_SUCCESS);
}

#endif

#endif // ALT_USE_DX