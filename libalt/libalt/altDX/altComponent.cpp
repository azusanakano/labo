#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altComponent.cpp
 * \brief   DirectX component class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altComponent.h"
#ifdef ALT_WIN
#include "altCamera.h"
#include "altMouse.h"
#include "altDX.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altComponent::altComponent() :
m_oPosition(),
m_oViewPosition (0.0f, 0.0f, 0.0f),
m_oViewRotation (0.0f, 0.0f, 0.0f),
m_oScale (1.0f, 1.0f, 1.0f),
m_oComponentContainer(),
m_pParent (NULL)
{
}

///
/// \brief  Destructor
///
LIBALT_API altComponent::~altComponent()
{
}

///
/// \brief  Render
///
/// \param  pd3dDevice  [I ] D3D Device
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altComponent::Render(IDirect3DDevice9 * pDevice)
{
  for (altComponentContainer::iterator i = m_oComponentContainer.begin(); i != m_oComponentContainer.end(); i++) {
    (* i)->Render(pDevice);
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Add Component
///
/// \param  pComponent  [I ] Component
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altComponent::Add(altComponent * pComponent)
{
  if (pComponent == NULL) {
    ALT_RET (ALT_E_ERROR);
  }
  try {
    m_oComponentContainer.push_back (pComponent);
  }
  catch (std::exception & e) {
    ALT_RET_P (ALT_E_ERROR, e.what());
  }
  catch (...) {
    ALT_RET (ALT_E_ERROR);
  }
  pComponent->m_pParent = this;

  ALT_RET (ALT_S_SUCCESS);
}

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
LIBALT_API alt_t altComponent::SetPosition(const altLong nLeft, const altLong nTop, const altLong nRight, const altLong nBottom)
{
  m_oPosition.left = nLeft;
  m_oPosition.top = nTop;
  m_oPosition.right = nRight;
  m_oPosition.bottom = nBottom;
  ALT_RET (ALT_S_SUCCESS);
}

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
LIBALT_API alt_t altComponent::SetPositionEx(const altLong x, const altLong y, const altULong w, const altULong h)
{
  m_oPosition.left = x;
  m_oPosition.top = y;
  m_oPosition.right = w + x;
  m_oPosition.bottom = h + y;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set position
///
/// \param  x [I ] X
/// \param  y [I ] Y
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altComponent::SetPosition(const altLong x, const altLong y)
{
  m_oPosition.right += (x - m_oPosition.left);
  m_oPosition.bottom += (y - m_oPosition.top);
  m_oPosition.left = x;
  m_oPosition.top = y;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set position
///
/// \param  oRect [I ] Position
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altComponent::SetPosition(const RECT & oRect)
{
  m_oPosition = oRect;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set view position
///
/// \param  x [I ] X
/// \param  y [I ] Y
/// \param  z [I ] Z
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altComponent::SetViewPosition(const altFloat x, const altFloat y, const altFloat z)
{
  m_oViewPosition.x = x;
  m_oViewPosition.y = y;
  m_oViewPosition.z = z;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set view position
///
/// \param  oPosition [I ] Position
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altComponent::SetViewPosition(const D3DXVECTOR3 & oPosition)
{
  m_oViewPosition = oPosition;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get view position
///
/// \return View position
///
LIBALT_API D3DXVECTOR3 altComponent::GetViewPosition()
{
  return (m_oViewPosition);
}

///
/// \brief  Set view rotation
///
/// \param  oRotation [I ] Rotation
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altComponent::SetViewRotation(const D3DXVECTOR3 & oRotation)
{
  m_oViewRotation = oRotation;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get view rotation
///
/// \return View position
///
LIBALT_API D3DXVECTOR3 altComponent::GetViewRotation()
{
  return (m_oViewRotation);
}

///
/// \brief  Set scale
///
/// \param  oScale  [I ] Scale
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altComponent::SetScale(const D3DXVECTOR3 & oScale)
{
  m_oScale = oScale;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get scale
///
/// \return Scale
///
LIBALT_API D3DXVECTOR3 altComponent::GetScale()
{
  return (m_oScale);
}

///
/// \brief  Get position
///
/// \return Position
///
LIBALT_API RECT altComponent::GetPosition()
{
  return (m_oPosition);
}

///
/// \brief  Set focus
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altComponent::SetFocus()
{
  altInt  x;
  altInt  y;
  altInt  f;
  alt_t   status;
  
  status = aiMouse.GetLastCurPos (x, y, f);
  ALT_ERR_RET (status);

  if (x >= m_oPosition.left
    && x <= m_oPosition.right
    && y <= m_oPosition.bottom
    && y >= m_oPosition.top
    && f & altMouse::LBTN_DOWN) {
      status = aiDX.SetFocus (this);
      ALT_ERR_RET (status);
  }

  for (altUInt i = 0; i < m_oComponentContainer.size(); i++) {
    status = m_oComponentContainer[i]->SetFocus();
    ALT_ERR_RET (status);
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get on focus
///
/// \return true  On focus
/// \return false Not on focus
///
LIBALT_API altBool altComponent::IsOnFocus()
{
  return (aiDX.GetFocus() == this);
}

///
/// \brief  On focus
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altComponent::OnFocus()
{
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Off focus
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altComponent::OffFocus()
{
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
LIBALT_API LRESULT altComponent::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  LRESULT hr = true;
  for (altUInt i = 0; i < m_oComponentContainer.size(); i++) {
    hr = m_oComponentContainer[i]->WndProc (hwnd, msg, wParam, lParam);
  }
  return (hr);
}

#endif

#endif // ALT_USE_DX