#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef ALTTEXTBOX_H
#define ALTTEXTBOX_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTextBox.h
 * \brief   Text box component class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN
#include <altDX/Component/altTextBoxListener.h>
#include <altDX/Component/altLabel.h>
#include <altDX/altIMEComponent.h>
#include <time.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef std::vector<altTextBoxListener *> altTextInputListenerList;

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Text Box
///
class altTextBox : public altLabel, public altIMEComponent, public altKeyEventListener
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  x [I ] X
  /// \param  y [I ] Y
  /// \param  h [I ] Height
  /// \param  w [I ] Width
  ///
  LIBALT_API altTextBox(const altLong x, const altLong y, const altLong h, const altLong w);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altTextBox();

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
  /// \brief  Input IME word
  ///
  /// \param  sData [I ] IME word
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API virtual alt_t InputIMEWord(const altWStr & sData);

  ///
  /// \brief  Send IME word
  ///
  /// \param  sData [I ] IME word
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API virtual alt_t SendIMEWord(const altWStr & sData);

  ///
  /// \brief  Listen key down event
  ///
  /// \param  oEvent  [I ] Event
  /// \param  nKey    [I ] Key
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API virtual alt_t OnKeyDown(const altEvent & oEvent, const altUInt nKey);
  
  ///
  /// \brief  Window Procedure
  ///
  /// \param  hwnd    [I ] Window handle
  /// \param  msg     [I ] message
  /// \param  wParam  [I ] parameter
  /// \param  lParam  [I ] parameter
  ///
  LIBALT_API virtual LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  ///
  /// \brief  Add input listener
  ///
  /// \param  pListener [I ] Input listener
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  /// \return ALT_E_INVAL   invalid paramter
  ///
  LIBALT_API alt_t AddListener(altTextBoxListener * pListener);

protected:
  altWStr                   m_sInputBuffer;     ///< Input string buffer
  altWStr                   m_sInput;           ///< Input string

private:
  altTextInputListenerList  m_oInputListener;   ///< Text input listener list
  clock_t                   m_nLastTime;        ///< Cursor last time
};

#endif
#endif

#endif