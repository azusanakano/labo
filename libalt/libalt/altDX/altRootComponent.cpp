#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altRootComponent.cpp
 * \brief   DirectX root component class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altRootComponent.h"
#ifdef ALT_WIN
#include "altMouse.h"
#include "altDX.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altRootComponent::altRootComponent()
{
}

///
/// \brief  Destructor
///
LIBALT_API altRootComponent::~altRootComponent()
{
}

///
/// \brief  Add key event listener
///
/// \param  pKeyEventListener [I ] Key event listener
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_INVAL   invalid paramter
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altRootComponent::AddKeyEventListener(altKeyEventListener * pKeyEventListener)
{
  ALT_P_ASSERT (pKeyEventListener != NULL);

  try {
    m_oKeyEventListnerCotainer.push_back (pKeyEventListener);
  }
  catch (std::exception & e) {
    ALT_RET_P (ALT_E_ERROR, e.what());
  }
  catch (...) {
    ALT_RET (ALT_E_ERROR);
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Remove key event listener
///
/// \param  pKeyEventListener [I ] Key event listener
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_INVAL   invalid paramter
///
LIBALT_API alt_t altRootComponent::RemoveKeyEventListener (altKeyEventListener * pKeyEventListener)
{
  ALT_P_ASSERT (pKeyEventListener != NULL);

  for (altKeyEventListenerConatiner::iterator i = m_oKeyEventListnerCotainer.begin(); i != m_oKeyEventListnerCotainer.end(); i++) {
    if ((* i) == pKeyEventListener) {
      m_oKeyEventListnerCotainer.erase (i);
      break;
    }
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Listen key event
///
/// \param  oEvent  [I ] Event
/// \param  oKey    [I ] Key
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altRootComponent::OnKeyEvent(const altEvent & oEvent, altKeyContainer oKey)
{
  alt_t status;
  for (altUInt i = 0; i < m_oKeyEventListnerCotainer.size(); i++) {
    switch (oEvent.GetType()) {
    case WM_KEYDOWN:
      for (altUInt j = 0; j < oKey.size(); j++) {
        status = m_oKeyEventListnerCotainer[i]->OnKeyDown (oEvent, oKey[j]);
        ALT_LOG (status);
      }
      break;
    }
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set focus
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altRootComponent::SetFocus()
{
  altInt  x;
  altInt  y;
  altInt  f;
  alt_t   status;
  
  status = aiMouse.GetLastCurPos (x, y, f);
  ALT_ERR_RET (status);

  if (f & altMouse::LBTN_DOWN) {
    status = aiDX.SetFocus (NULL);
    ALT_ERR_RET (status);
  }

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
/// \brief  Off focus
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altRootComponent::OffFocus()
{
  for (altUInt i = 0; i < m_oComponentContainer.size(); i++) {
    if (aiDX.GetFocus() == m_oComponentContainer[i]) {
      continue;
    }
    alt_t status = m_oComponentContainer[i]->OffFocus();
    ALT_ERR_RET (status);
  }
  ALT_RET (ALT_S_SUCCESS);
}

#endif

#endif // ALT_USE_DX
