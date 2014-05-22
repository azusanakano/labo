#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMouse.cpp
 * \brief   Mouse class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altMouse.h"
#ifdef ALT_WIN
#include "altDX.h"
#include "altBase/altStr.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altMouse::altMouse() :
m_nFlags (0),
m_oLastCurPos(),
m_oDragStCPos(),
m_nWheelRotation (0)
{
}

///
/// \brief  Destructor
///
LIBALT_API altMouse::~altMouse()
{
}

///
/// \brief  Move
///
/// \param  x   [I ] X
/// \param  y   [I ] Y
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altMouse::Move(altInt x, altInt y)
{
  HWND  hwnd = aiDX.GetHWnd();
  POINT oCurPos;

  if (! GetCursorPos (& oCurPos)) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u", GetLastError()));
  }

  if (! ScreenToClient (hwnd, & oCurPos)) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u", GetLastError()));
  }

  m_oLastCurPos = oCurPos;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Left Button Down
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altMouse::LButtonDown()
{
  HWND  hwnd = aiDX.GetHWnd();

  if (SetFocus (hwnd) == NULL) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u", GetLastError()));
  }

  if (! m_nFlags) {
    SetCapture (hwnd);
  }
  m_nFlags |= LBTN_DOWN;

  if (! GetCursorPos (& m_oDragStCPos)) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u", GetLastError()));
  }

  if (! ScreenToClient (hwnd, & m_oDragStCPos)) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u", GetLastError()));
  }
  m_oLastCurPos = m_oDragStCPos;
  
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Left Button Up
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altMouse::LButtonUp()
{
  m_nFlags &= ~LBTN_DOWN;
  if (! m_nFlags) {
    ReleaseCapture();
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Right Button Down
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altMouse::RButtonDown()
{
  HWND  hwnd = aiDX.GetHWnd();

  if (! m_nFlags) {
    SetCapture (hwnd);
  }
  m_nFlags |= RBTN_DOWN;

  if (! GetCursorPos (& m_oDragStCPos)) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u", GetLastError()));
  }

  if (! ScreenToClient (hwnd, & m_oDragStCPos)) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u", GetLastError()));
  }
  m_oLastCurPos = m_oDragStCPos;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Right Button Up
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altMouse::RButtonUp()
{
  m_nFlags &= ~RBTN_DOWN;
  if (! m_nFlags) {
    ReleaseCapture();
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Wheel rotation
///
/// \param  nRotation [I ] rotation
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altMouse::Wheel(altInt nRotation)
{
  m_nWheelRotation += nRotation;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get wheel rotation
///
/// \param  bReset  [I ] Reset
///
/// \return rotation distance
///
LIBALT_API altInt altMouse::GetWheelRotation(altBool bReset)
{
  altInt nRotation = m_nWheelRotation;
  if (bReset) {
    m_nWheelRotation = 0;
  }
  return (nRotation);
}

///
/// \brief  Get drag distance
///
/// \param  x       [ O] X
/// \param  y       [ O] Y
/// \param  nFlags  [ O] Button flag
/// \param  bReset  [I ] Reset
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altMouse::GetDragDistance(altInt & x, altInt & y, altInt & nFlags, altBool bReset)
{
  if (m_nFlags == 0) {
    x = 0;
    y = 0;
    nFlags = 0;
    ALT_RET (ALT_S_SUCCESS);
  }

  x = m_oLastCurPos.x - m_oDragStCPos.x;
  y = m_oLastCurPos.y - m_oDragStCPos.y;
  nFlags = m_nFlags;

  if (bReset) {
    m_oDragStCPos = m_oLastCurPos;
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get cursor position
///
/// \param  x       [ O] X
/// \param  y       [ O] Y
/// \param  nFlags  [ O] Button flag
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altMouse::GetCurPos(altInt & x, altInt & y, altInt & nFlags)
{
  HWND  hwnd = aiDX.GetHWnd();
  POINT oCurPos;

  if (! GetCursorPos (& oCurPos)) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u", GetLastError()));
  }

  if (! ScreenToClient (hwnd, & oCurPos)) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u", GetLastError()));
  }

  x = oCurPos.x;
  y = oCurPos.y;
  nFlags = m_nFlags;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get last cursor position
///
/// \param  x       [ O] X
/// \param  y       [ O] Y
/// \param  nFlags  [ O] Button flag
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altMouse::GetLastCurPos(altInt & x, altInt & y, altInt & nFlags)
{
  x = m_oLastCurPos.x;
  y = m_oLastCurPos.y;
  nFlags = m_nFlags;
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
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altMouse::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  alt_t status;
	switch (msg) {
  case WM_MOUSEMOVE:
    status = aiMouse.Move (LOWORD (lParam), HIWORD (lParam));
    ALT_ERR_RET (status);
    break;
  case WM_LBUTTONDOWN:
    status = aiMouse.LButtonDown();
    ALT_ERR_RET (status);
    break;
  case WM_LBUTTONUP:
    status = aiMouse.LButtonUp();
    ALT_ERR_RET (status);
    break;
  case WM_RBUTTONDOWN:
    status = aiMouse.RButtonDown();
    ALT_ERR_RET (status);
    break;
  case WM_RBUTTONUP:
    status = aiMouse.RButtonUp();
    ALT_ERR_RET (status);
    break;
  case WM_MOUSEWHEEL:
    status = aiMouse.Wheel (HIWORD (wParam));
    ALT_ERR_RET (status);
    break;
	}
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get altMouse Instance
///
/// \return altMouse Instance
///
LIBALT_API altMouse & altMouse::GetInstance()
{
  return (altSingleton<altMouse>::GetInstance());
}

#endif

#endif // ALT_USE_DX