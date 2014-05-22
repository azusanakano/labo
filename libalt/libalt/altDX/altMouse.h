#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef ALTMOUSE_H
#define ALTMOUSE_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMouse.h
 * \brief   Mouse
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN

#include <altBase/altLog.h>
#include <altBase/altSingleton.h>

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
///
/// \brief  Get Instance
///
#define aiMouse altMouse::GetInstance()

#ifndef WM_MOUSEWHEEL
  #define WM_MOUSEWHEEL 0x020A
#endif

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Mouse
///
class altMouse : public altSingleton<altMouse>
{
friend class altSingleton<altMouse>;
public:
  enum{
    LBTN_DOWN = 0x1,
    RBTN_DOWN = 0x2,
  };
private:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altMouse();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altMouse();

public:
  ///
  /// \brief  Move
  ///
  /// \param  x   [I ] X
  /// \param  y   [I ] Y
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t Move(altInt x, altInt y);

  ///
  /// \brief  Left Button Down
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t LButtonDown();

  ///
  /// \brief  Left Button Up
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API alt_t LButtonUp();

  ///
  /// \brief  Right Button Down
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t RButtonDown();

  ///
  /// \brief  Right Button Up
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API alt_t RButtonUp();

  ///
  /// \brief  Wheel rotation
  ///
  /// \param  nRotation [I ] rotation
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API alt_t Wheel(altInt nRotation);

  ///
  /// \brief  Get wheel rotation
  ///
  /// \param  bReset  [I ] Reset
  ///
  /// \return rotation distance
  ///
  LIBALT_API altInt GetWheelRotation(altBool bReset = true);

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
  LIBALT_API alt_t GetDragDistance(altInt & x, altInt & y, altInt & nFlags, altBool bReset = true);

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
  LIBALT_API alt_t GetCurPos(altInt & x, altInt & y, altInt & nFlags);

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
  LIBALT_API alt_t GetLastCurPos(altInt & x, altInt & y, altInt & nFlags);

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
  LIBALT_API alt_t WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  ///
  /// \brief  Get altMouse Instance
  ///
  /// \return altMouse Instance
  ///
  LIBALT_API static altMouse & GetInstance();

private:
  altInt    m_nFlags;
  POINT     m_oLastCurPos;
  POINT     m_oDragStCPos;
  altInt    m_nWheelRotation;
};

#endif
#endif

#endif // ALT_USE_DX
