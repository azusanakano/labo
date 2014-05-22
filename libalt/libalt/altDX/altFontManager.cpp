#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altFontManager.cpp
 * \brief   DirectX 2D Font Manager class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altFontManager.h"
#ifdef ALT_WIN

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altFontManager::altFontManager() :
m_oFontMap()
{
  CreateFont ("Default", 12);
}

///
/// \brief  Destructor
///
LIBALT_API altFontManager::~altFontManager()
{
  for (altFontMap::iterator i = m_oFontMap.begin(); i != m_oFontMap.end(); i++) {
    delete i->second;
  }
  m_oFontMap.clear();
}

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
LIBALT_API alt_t altFontManager::CreateFont(const altStr & sFontName, const altInt h, const altInt w, const altUInt nWeight, const altBool bItalic, const BYTE nCharSet, const altWStr & sFaceName)
{
  try {
    altFont * pFont = ALT_NEW altFont (h, w, nWeight, bItalic, nCharSet, sFaceName);
    if (pFont == NULL) {
      ALT_RET (ALT_E_NOMEM);
    }
    m_oFontMap[sFontName] = pFont;
  }
  catch (alt_t e) {
    ALT_RET (e);
  }
  catch (std::exception & e) {
    ALT_LOG_P (ALT_E_ERROR, e.what());
    ALT_RET (ALT_E_ERROR);
  }
  catch (...) {
    ALT_RET (ALT_E_ERROR);
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get font
///
/// \param  sFontName [I ] Font name
///
/// \return Pointer of font
///
LIBALT_API altFont * altFontManager::GetFont(const altStr & sFontName)
{
  return (m_oFontMap[sFontName]);
}

///
/// \brief  Get altFontManager Instance
///
/// \return altDX Instance
///
LIBALT_API altFontManager & altFontManager::GetInstance()
{
  return (altSingleton<altFontManager>::GetInstance());
}

///
/// \brief  Delete Instance
///
LIBALT_API void altFontManager::DeleteInstance()
{
  altSingleton<altFontManager>::DeleteInstance();
}

#endif

#endif // ALT_USE_DX