#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDXInput.cpp
 * \brief   DirectX Input class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altDXInput.h"
#ifdef ALT_WIN
#include "altDX.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altDXInput::altDXInput() :
m_pDinput (NULL),
m_pInputDevice (NULL)
{
}

///
/// \brief  Destructor
///
LIBALT_API altDXInput::~altDXInput()
{
  Cleanup();
}

///
/// \brief  Clean up
///
LIBALT_API void altDXInput::Cleanup()
{
  if (m_pInputDevice != NULL) {
    m_pInputDevice->Unacquire();
    m_pInputDevice->Release();
    m_pInputDevice = NULL;
  }
  if (m_pDinput != NULL) {
    m_pDinput->Release();
    m_pDinput = NULL; 
  }
}

///
/// \brief  Set keyboard
///
/// \param  dwCooperativeLevel  [I ] Cooperative level
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDXInput::SetKeyboard(DWORD dwCooperativeLevel)
{
  HWND    hWnd = aiDX.GetHWnd();
  HRESULT hr;
  
  Cleanup();

  hr = DirectInput8Create (GetModuleHandle (NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID **)& m_pDinput, NULL);
  if (FAILED (hr)) {
    ALT_RET_P (ALT_E_ERROR, DXGetErrorDescription9A (hr));
  }

  hr = m_pDinput->CreateDevice (GUID_SysKeyboard, & m_pInputDevice, NULL);
  if (FAILED (hr)) {
    ALT_RET_P (ALT_E_ERROR, DXGetErrorDescription9A (hr));
  }

  hr = m_pInputDevice->SetDataFormat (& c_dfDIKeyboard);
  if (FAILED (hr)) {
    ALT_RET_P (ALT_E_ERROR, DXGetErrorDescription9A (hr));
  }

  hr = m_pInputDevice->SetCooperativeLevel (hWnd, dwCooperativeLevel);
  if (FAILED (hr)) {
    ALT_RET_P (ALT_E_ERROR, DXGetErrorDescription9A (hr));
  }

  m_pInputDevice->Acquire();

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get down key or not
///
/// \param  nKey  [I ] Key
///
/// \return true  down
/// \return false not down
///
LIBALT_API altBool altDXInput::DownKey(const altByte nKey)
{
  HRESULT hr = m_pInputDevice->Acquire();
  if (hr == DI_OK || hr == S_FALSE) {
    BYTE aDiks[256];
    if (nKey >= sizeof (aDiks)) {
      return (false);
    }
    m_pInputDevice->GetDeviceState (sizeof (aDiks), & aDiks);
    return (aDiks [nKey] && 0x80);
  }
  return (false);
}

///
/// \brief  Get down key or not
///
/// \return true  down
/// \return false not down
///
LIBALT_API altBool altDXInput::DownAnyKey()
{
  HRESULT hr = m_pInputDevice->Acquire();
  if (hr == DI_OK || hr == S_FALSE) {
    BYTE aDiks[256];
    m_pInputDevice->GetDeviceState (sizeof (aDiks), & aDiks);
    for (altUInt i = 0; i < sizeof (aDiks); i++) {
      if (aDiks [i] && 0x80) {
        return (true);
      }
    }
  }
  return (false);
}

///
/// \brief  Get down keys
///
/// \return Down keys
///
LIBALT_API altKeyContainer altDXInput::GetDownKey()
{
  altKeyContainer oKeyContainer;
  HRESULT hr = m_pInputDevice->Acquire();
  if (hr == DI_OK || hr == S_FALSE) {
    BYTE aDiks[256];
    m_pInputDevice->GetDeviceState (sizeof (aDiks), & aDiks);
    for (altUInt i = 0; i < sizeof (aDiks); i++) {
      if (aDiks[i] && 0x80) {
        oKeyContainer.push_back (i);
      }
    }
  }
  return (oKeyContainer);
}

///
/// \brief  Get altDXInput Instance
///
/// \return altDX Instance
///
LIBALT_API altDXInput & altDXInput::GetInstance()
{
  return (altSingleton<altDXInput>::GetInstance());
}

///
/// \brief  Delete Instance
///
LIBALT_API void altDXInput::DeleteInstance()
{
  altSingleton<altDXInput>::DeleteInstance();
}

#endif

#endif // ALT_USE_DX