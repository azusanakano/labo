#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef ALTIME_H
#define ALTIME_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altIME.h
 * \brief   IME control class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN
#include <altDX/altIMEComponent.h>
#include <altBase/altStr.h>
#include <altBase/altWStr.h>
#include <altBase/altLog.h>
#include <altBase/altSingleton.h>

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
///
/// \brief  Get Instance
///
#define aiIME altIME::GetInstance()

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  IME Control
///
class altIME : public altSingleton<altIME>
{
friend class altSingleton<altIME>;
private:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altIME();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altIME();

public:
  ///
  /// \brief  Initialize
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t Init();

  ///
  /// \brief  Set IME Mode
  ///
  /// \param  bIMEMode      [I ] IME mode
  /// \param  bImEOpenMode  [I ] IME open mode
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t SetIMEMode(const altBool bIMEMode, const BOOL bIMEOpenMode);

  ///
  /// \brief  Get IME Mode
  ///
  /// \return true    ON
  /// \return false   OFF
  ///
  LIBALT_API altBool GetIMEMode();

  ///
  /// \brief  Set IME data
  ///
  /// \param  sData [I ] IME Data
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API alt_t SetIMEData(const altWStr & sData);

  ///
  /// \brief  Get IME Data
  ///
  /// \return IME Data
  ///
  LIBALT_API altWStr GetIMEData();

  ///
  /// \brief  Get IME Back Data
  ///
  /// \return IME Back Data
  ///
  LIBALT_API altWStr GetIMEDataBack();

  ///
  /// \brief  Clear IME Data
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API alt_t ClearIMEData();

  ///
  /// \brief  Set IME component
  ///
  /// \param  pIMEComponent [I ] Pointer of IME component
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API alt_t SetIMEComponent(altIMEComponent * pIMEComponent);

  ///
  /// \brief  Window Procedure
  ///
  /// \param  hwnd    [I ] Window handle
  /// \param  msg     [I ] message
  /// \param  wParam  [I ] parameter
  /// \param  lParam  [I ] parameter
  ///
  LIBALT_API LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  ///
  /// \brief  Check East Asian languages that are not
  ///
  /// \param  HKL [I ] Keyboard layout handle
  ///
  /// \return true  East Asian languages
  /// \return false Not East Asian languages
  ///
  LIBALT_API altBool IsEastAsianLanguages(HKL hKL);

  ///
  /// \brief  Get altIME Instance
  ///
  /// \return altIME Instance
  ///
  LIBALT_API static altIME & GetInstance();

  ///
  /// \brief  Delte Instance
  ///
  LIBALT_API static void DeleteInstance();

  altLong             m_nCursorPosition;  ///< Cursor position

private:
  altBool             m_bIMEMode;         ///< IME mode(on/off) flag
  altWStr             m_sIMEData;         ///< IME data buffer
  altWStr             m_sIMEDataBack;
  altIMEComponent *   m_pIMEComponent;    ///< IME Component
};

#endif
#endif

#endif // ALT_USE_DX