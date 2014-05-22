#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altIME.cpp
 * \brief   IME control class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altIME.h"
#ifdef ALT_WIN
#include "altDX.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altIME::altIME() :
m_bIMEMode (false),
m_sIMEData(),
m_sIMEDataBack(),
m_pIMEComponent (NULL)
{
}

///
/// \brief  Destructor
///
LIBALT_API altIME::~altIME()
{
}

///
/// \brief  Initialize
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altIME::Init()
{
  HWND hWndIME;

  hWndIME = ImmGetDefaultIMEWnd (aiDX.GetHWnd());
  if (hWndIME == NULL) {
    ALT_RET (ALT_E_ERROR);
  }

  SendMessage (hWndIME, WM_IME_CONTROL, IMC_CLOSESTATUSWINDOW, 0);
  alt_t status = SetIMEMode (false, FALSE);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set IME Mode
///
/// \param  bIMEMode      [I ] IME mode
/// \param  bImEOpenMode  [I ] IME open mode
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altIME::SetIMEMode(const altBool bIMEMode, const BOOL bIMEOpenMode)
{
  m_bIMEMode = bIMEMode;

  HIMC hIMC = ImmGetContext (aiDX.GetHWnd());
  if (hIMC == NULL) {
    ALT_RET (ALT_E_ERROR);
  }

  BOOL bFOpen = ImmGetOpenStatus (hIMC);

  if (bIMEMode == false) {
    if (bFOpen) {
      ImmSetOpenStatus (hIMC, false);
    }
  }
  else {
    if (bFOpen != bIMEOpenMode) {
      ImmSetOpenStatus (hIMC, bIMEOpenMode);
    }
  }

  ImmReleaseContext (aiDX.GetHWnd(), hIMC);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get IME Mode
///
/// \return true    ON
/// \return false   OFF
///
LIBALT_API altBool altIME::GetIMEMode()
{
  return (m_bIMEMode);
}

///
/// \brief  Set IME data
///
/// \param  sData [I ] IME Data
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altIME::SetIMEData(const altWStr & sData)
{
  m_sIMEData = sData;
  m_sIMEDataBack = sData;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get IME Data
///
/// \return IME Data
///
LIBALT_API altWStr altIME::GetIMEData()
{
  return (m_sIMEData);
}

///
/// \brief  Get IME Back Data
///
/// \return IME Back Data
///
LIBALT_API altWStr altIME::GetIMEDataBack()
{
  return (m_sIMEDataBack);
}

///
/// \brief  Clear IME Data
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altIME::ClearIMEData()
{
  m_sIMEData = _T("");
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set IME component
///
/// \param  pIMEComponent [I ] Pointer of IME component
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altIME::SetIMEComponent(altIMEComponent * pIMEComponent)
{
  m_pIMEComponent = pIMEComponent;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Window Procedure
///
/// \param  hwnd    [I ] Window handle
/// \param  msg     [I ] message
/// \param  wParam  [I ] parameter
/// \param  lParam  [I ] parameter
///
LIBALT_API LRESULT altIME::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg) {
    case WM_ACTIVATEAPP:
      if (wParam) {
        UINT nKL = GetKeyboardLayoutList (0, NULL);
        HKL * phKL = new HKL[nKL];
        if (phKL != NULL) {
          GetKeyboardLayoutList (nKL, phKL);
          for (UINT i = 0; i < nKL; i++) {
            if (IsEastAsianLanguages (phKL[i])) {
              continue;
            }
          }
          delete[] phKL;
        }
      }
      break;
    case WM_INPUTLANGCHANGE:
      return (true);
    case WM_IME_SETCONTEXT:
      //lParam &= ~ISC_SHOWUIALL;
      lParam = 0;
      return (false);
    case WM_IME_STARTCOMPOSITION:
      return (false);
    case WM_IME_ENDCOMPOSITION:
      if (m_pIMEComponent != NULL) {
          m_pIMEComponent->SendIMEWord (aiIME.GetIMEDataBack());
      }
      return (false);
    case WM_IME_COMPOSITION:
      if (aiIME.GetIMEMode() == true) {
        altWChar  szBuf[ALT_BUFSIZ];
        memset (szBuf, 0x00, sizeof (szBuf));
        HIMC hIMC = ImmGetContext (aiDX.GetHWnd());
        LONG nRetSize = ImmGetCompositionStringW (hIMC, GCS_COMPSTR, (LPVOID)szBuf, sizeof (szBuf));

        if (nRetSize != IMM_ERROR_NODATA && nRetSize != IMM_ERROR_GENERAL) {
          szBuf[nRetSize] = 0x0000;
          if (nRetSize > 0) {
            aiIME.SetIMEData (szBuf);
          }
        }

        aiIME.m_nCursorPosition = ImmGetCompositionStringW (hIMC, GCS_CURSORPOS, NULL, 0);

        ImmReleaseContext (aiDX.GetHWnd(), hIMC);
        if (m_pIMEComponent != NULL) {
          m_pIMEComponent->InputIMEWord (szBuf);
        }
        return (false);
      }
      break;
    case WM_IME_NOTIFY:
      switch (wParam) {
      case IMN_OPENSTATUSWINDOW:
      case IMN_CLOSESTATUSWINDOW:
      case IMN_CLOSECANDIDATE:
        return (false);
      case IMN_OPENCANDIDATE:
      case IMN_CHANGECANDIDATE:
        return (true);
      default:
        if (aiIME.GetIMEMode() == true) {
          return (true);
        }
        else {
          BOOL bFOpen;
          HIMC hIMC = ImmGetContext (aiDX.GetHWnd());
          if (hIMC != NULL) {
            bFOpen = ImmGetOpenStatus (hIMC);
            if (bFOpen != FALSE) {
              ImmSetOpenStatus (hIMC, FALSE);
            }
            ImmReleaseContext (aiDX.GetHWnd(), hIMC);
          }
          aiIME.ClearIMEData();
          return (false);
        }
        break;
      }
    default:
      return (true);
  }
  return (true);
}

///
/// \brief  Check East Asian languages that are not
///
/// \param  HKL [I ] Keyboard layout handle
///
/// \return true  East Asian languages
/// \return false Not East Asian languages
///
LIBALT_API altBool altIME::IsEastAsianLanguages(HKL hKL)
{
  if (PRIMARYLANGID (LOWORD (hKL)) == LANG_CHINESE) {
    return (true);
  }
  if (PRIMARYLANGID (LOWORD (hKL)) == LANG_JAPANESE) {
    return (true);
  }
  if (PRIMARYLANGID (LOWORD (hKL)) == LANG_KOREAN) {
    return (true);
  }
  return (false);
}

///
/// \brief  Get altIME Instance
///
/// \return altIME Instance
///
LIBALT_API altIME & altIME::GetInstance()
{
  return (altSingleton<altIME>::GetInstance());
}

///
/// \brief  Delte Instance
///
LIBALT_API void altIME::DeleteInstance()
{
  altSingleton<altIME>::DeleteInstance();
}

#endif

#endif // ALT_USE_DX