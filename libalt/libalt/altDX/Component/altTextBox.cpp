#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTextBox.cpp
 * \brief   Text box component class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altTextBox.h"
#ifdef ALT_WIN
#include "../altIME.h"

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
#define ALT_CURSOR_WAIT 1

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
/// \param  x [I ] X
/// \param  y [I ] Y
/// \param  h [I ] Height
/// \param  w [I ] Width
///
LIBALT_API altTextBox::altTextBox(const altLong x, const altLong y, const altLong h, const altLong w) :
altLabel (x, y, h, w),
m_sInputBuffer(),
m_sInput (),
m_oInputListener(),
m_nLastTime (0)
{
}

///
/// \brief  Destructor
///
LIBALT_API altTextBox::~altTextBox()
{
  m_oInputListener.clear();
}

///
/// \brief  Render
///
/// \param  pDevice  [I ] D3D Device
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altTextBox::Render(IDirect3DDevice9 * pDevice)
{
  alt_t status;

  status = m_oBackGround.Render (pDevice);
  ALT_LOG (status);

  altLong nOutX = m_x; 
  m_pFont->Draw (m_sInputBuffer, nOutX, m_y, 0, m_dwTextColor);
  nOutX += m_pFont->GetWidth (m_sInputBuffer);

  m_pFont->Draw (m_sInput, nOutX, m_y, 0, D3DCOLOR_ARGB(255,255,255,0));
  nOutX += m_pFont->GetWidth (m_sInput);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  On focus
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altTextBox::OnFocus()
{
  altLabel::SetBackColor (D3DCOLOR_RGBA (0, 0, 0, 80));
  aiIME.Init();
  aiIME.SetIMEComponent (this);
  aiIME.SetIMEMode (true, false);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Off focus
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altTextBox::OffFocus()
{
  altLabel::SetBackColor (D3DCOLOR_RGBA (0, 0, 0, 0));
  aiIME.SetIMEComponent (NULL);
  aiIME.SetIMEMode (false, false);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Input IME word
///
/// \param  sData [I ] IME word
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altTextBox::InputIMEWord(const altWStr & sData)
{
  if (sData.GetLen() > 0) {
    m_sInput = sData;
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send IME word
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altTextBox::SendIMEWord(const altWStr & sData)
{
  altStr  sBuf;
  m_sInputBuffer += sData;
  m_sInput = L"";
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Listen key down event
///
/// \param  oEvent  [I ] Event
/// \param  nKey    [I ] Key
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altTextBox::OnKeyDown(const altEvent & oEvent, const altUInt nKey)
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
LIBALT_API LRESULT altTextBox::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  if (aiDX.GetFocus() != this) {
    return (altComponent::WndProc (hwnd, msg, wParam, lParam));
  }
  switch (msg) {
  case WM_CHAR:
    {
      switch ((altWChar)wParam) {
        // Junk characters we don't want in the string
        case 26:  // Ctrl Z
        case 2:   // Ctrl B
        case 14:  // Ctrl N
        case 19:  // Ctrl S
        case 4:   // Ctrl D
        case 6:   // Ctrl F
        case 7:   // Ctrl G
        case 10:  // Ctrl J
        case 11:  // Ctrl K
        case 12:  // Ctrl L
        case 17:  // Ctrl Q
        case 23:  // Ctrl W
        case 5:   // Ctrl E
        case 18:  // Ctrl R
        case 20:  // Ctrl T
        case 25:  // Ctrl Y
        case 21:  // Ctrl U
        case 9:   // Ctrl I
        case 15:  // Ctrl O
        case 16:  // Ctrl P
        case 27:  // Ctrl [
        case 29:  // Ctrl ]
        case 28:  // Ctrl \ 
            break;  
        case  VK_BACK:// Backspace
          if (aiIME.GetIMEMode() == false && m_sInput.GetLen() > 0) {
            m_sInput.DeleteLastChar();
          }
          if (m_sInput.GetLen() == 0 && m_sInputBuffer.GetLen() > 0) {
            m_sInputBuffer.DeleteLastChar();
          }
          break;
        case  VK_RETURN:
          if (m_sInput.GetLen() == 0) {
            for (altTextInputListenerList::iterator i = m_oInputListener.begin(); i != m_oInputListener.end(); i++) {
              (* i)->OnInput (m_sInputBuffer + m_sInput);
            }
            m_sInputBuffer = L"";
          }
          m_sInput = L"";
          break;
        default:
          altWStr  sBuf((altWChar)wParam);
          m_sInputBuffer += sBuf;
      }
    }
  }
  return (altComponent::WndProc (hwnd, msg, wParam, lParam));
}

///
/// \brief  Add input listener
///
/// \param  pListener [I ] Input listener
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
/// \return ALT_E_INVAL   invalid paramter
///
LIBALT_API alt_t altTextBox::AddListener(altTextBoxListener * pListener)
{
  ALT_P_ASSERT (pListener != NULL);
  try {
    m_oInputListener.push_back (pListener);
  }
  catch (std::exception & e) {
    ALT_RET_P (ALT_E_ERROR, e.what());
  }
  catch (...) {
    ALT_RET (ALT_E_ERROR);
  }
  ALT_RET (ALT_S_SUCCESS);
}

#endif

#endif // ALT_USE_DX