#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef ALTFONTMANAGER_H
#define ALTFONTMANAGER_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altFontManager.h
 * \brief   DirectX 2D Font Manager class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN
#include <altDX/altFont.h>
#include <altBase/altStr.h>

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
#define aiFontManager altFontManager::GetInstance()   ///< Get font manager instance

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef std::map<altStr, altFont *> altFontMap;   ///< Font Container

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  DirectX 2D Font Manager
///
class altFontManager : public altSingleton<altFontManager>
{
friend class altSingleton<altFontManager>;
private:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altFontManager();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altFontManager();

public:
  ///
  /// \brief  Create new font
  ///
  /// \param  h         [I ] Font Height
  /// \param  w         [I ] Font Width
  /// \param  nWeight   [I ] Font weight
  /// \param  bItalic   [I ] Italic or not
  /// \param  nCharSet  [I ] Charcter set
  /// \param  sFaceName [I ] Font face name
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t CreateFont(const altStr & sFontName, const altInt h, const altInt w = 0, const altUInt nWeight = FW_NORMAL, const altBool bItalic = false, const BYTE nCharSet = SHIFTJIS_CHARSET, const altWStr & sFaceName = (wchar_t *)_T("‚l‚r‚o ƒSƒVƒbƒN"));

  ///
  /// \brief  Get font
  ///
  /// \param  sFontName [I ] Font name
  ///
  /// \return Pointer of font
  ///
  LIBALT_API altFont * GetFont(const altStr & sFontName);

  ///
  /// \brief  Get altFontManager Instance
  ///
  /// \return altDX Instance
  ///
  LIBALT_API static altFontManager & GetInstance();

  ///
  /// \brief  Delete Instance
  ///
  LIBALT_API static void DeleteInstance();

private:
  altFontMap  m_oFontMap;
};

#endif
#endif

#endif // ALT_USE_DX