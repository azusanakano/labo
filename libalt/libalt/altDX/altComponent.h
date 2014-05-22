#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.

#ifndef ALTCOMPONENT_H
#define ALTCOMPONENT_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altComponent.h
 * \brief   DirectX component class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN

#include <altBase/altLog.h>
#include <d3d9.h>
#include <d3dx9.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
class altComponent;
typedef std::vector<altComponent *> altComponentContainer;

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  DirectX Component
///
class altComponent : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altComponent();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altComponent();

  ///
  /// \brief  Render
  ///
  /// \param  pDevice  [I ] D3D Device
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API virtual alt_t Render(IDirect3DDevice9 * pDevice);

  ///
  /// \brief  Add Component
  ///
  /// \param  pComponent  [I ] Component
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t Add(altComponent * pComponent);

  ///
  /// \brief  Set position
  ///
  /// \param  nLeft   [I ] Left
  /// \param  nTop    [I ] Top
  /// \param  nRight  [I ] Right
  /// \param  nBottom [I ] Bottom
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetPosition(const altLong nLeft, const altLong nTop, const altLong nRight, const altLong nBottom);

  ///
  /// \brief  Set position
  ///
  /// \param  x [I ] X
  /// \param  y [I ] Y
  /// \param  w [I ] Width
  /// \param  h [I ] Height
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetPositionEx(const altLong x, const altLong y, const altULong w, const altULong h);

  ///
  /// \brief  Set position
  ///
  /// \param  x [I ] X
  /// \param  y [I ] Y
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetPosition(const altLong x, const altLong y);

  ///
  /// \brief  Set position
  ///
  /// \param  oRect [I ] Position
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetPosition(const RECT & oRect);

  ///
  /// \brief  Set view position
  ///
  /// \param  x [I ] X
  /// \param  y [I ] Y
  /// \param  z [I ] Z
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetViewPosition(const altFloat x, const altFloat y, const altFloat z);

  ///
  /// \brief  Set view position
  ///
  /// \param  oPosition [I ] Position
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetViewPosition(const D3DXVECTOR3 & oPosition);

  ///
  /// \brief  Get view position
  ///
  /// \return View position
  ///
  LIBALT_API D3DXVECTOR3 GetViewPosition();

  ///
  /// \brief  Set view rotation
  ///
  /// \param  oRotation [I ] Rotation
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetViewRotation(const D3DXVECTOR3 & oRotation);

  ///
  /// \brief  Get view rotation
  ///
  /// \return View position
  ///
  LIBALT_API D3DXVECTOR3 GetViewRotation();

  ///
  /// \brief  Set scale
  ///
  /// \param  oScale  [I ] Scale
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetScale(const D3DXVECTOR3 & oScale);

  ///
  /// \brief  Get scale
  ///
  /// \return Scale
  ///
  LIBALT_API D3DXVECTOR3 GetScale();

  ///
  /// \brief  Get position
  ///
  /// \return Position
  ///
  LIBALT_API RECT GetPosition();

  ///
  /// \brief  Set focus
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API virtual alt_t SetFocus();

  ///
  /// \brief  Get on focus
  ///
  /// \return true  On focus
  /// \return false Not on focus
  ///
  LIBALT_API altBool IsOnFocus();

  ///
  /// \brief  On focus
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API virtual alt_t OnFocus();

  ///
  /// \brief  Off focus
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API virtual alt_t OffFocus();
  
  ///
  /// \brief  Window Procedure
  ///
  /// \param  hwnd    [I ] Window handle
  /// \param  msg     [I ] message
  /// \param  wParam  [I ] parameter
  /// \param  lParam  [I ] parameter
  ///
  LIBALT_API virtual LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
  RECT                    m_oPosition;            ///< Position
  D3DXVECTOR3             m_oViewPosition;        ///< View position
  D3DXVECTOR3             m_oViewRotation;        ///< View rotation
  D3DXVECTOR3             m_oScale;               ///< Scale
  altComponentContainer   m_oComponentContainer;  ///< Component Container

private:
  altComponent *          m_pParent;              ///< Parent Component
};

#endif
#endif

#endif // ALT_USE_DX