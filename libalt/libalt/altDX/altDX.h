#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.

#ifndef ALTDX_H
#define ALTDX_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDX.h
 * \brief   DirectX class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN

#include <altDX/altKeyEventListener.h>
#include <altDX/altRootComponent.h>
#include <altBase/altWStr.h>
#include <altBase/altSingleton.h>
#include <altBase/altStatus.h>
#include <altBase/altLog.h>

#include <map>
#include <vector>

#include <d3dx9.h>
#include <dxerr9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
///
/// \brief  Get Instance
///
#define aiDX altDX::GetInstance()

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef std::vector<altKeyEventListener *>  altKeyEventListenerConatiner;

enum altAlphaBlendTypes {
  ALT_ALPHA_BLEND_0 = 0,  ///< üŒ`‡¬
  ALT_ALPHA_BLEND_1,      ///< ‰ÁŽZ‡¬
  ALT_ALPHA_BLEND_2,      ///< Œ¸ŽZ‡¬
  ALT_ALPHA_BLEND_3,      ///< æŽZ‡¬
  ALT_ALPHA_BLEND_4,      ///< Ä‚«ž‚Ý
  ALT_ALPHA_BLEND_5,      ///< ƒlƒKƒ|ƒW”½“]
  ALT_ALPHA_BLEND_6,      ///< •s“§–¾
};

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  DirectX
///
class altDX : public altSingleton<altDX>
{
friend class altSingleton<altDX>;
private:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altDX();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altDX();

public:
  ///
  /// \brief  Create Main Window
  ///
  /// \param  hInst       [I ] Instance Handle
  /// \param  sTitle      [I ] Title Name
  /// \param  nWidth      [I ] Window Width
  /// \param  nHeight     [I ] Widnow Heignt
  /// \param  bFullScreen [I ] FullScreen or not
  /// \param  nCmdshow    [I ] Command show
  /// \param  dwStyle     [I ] Window style
  /// \param  lpWndProc   [I ] Pointer to the window procedure
  /// 
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Create(HINSTANCE hInst, const altWStr & sTitle, const altInt nWidth, const altInt nHeight, const altBool bFullScreen, const altInt nCmdshow, const DWORD dwStyle = WS_OVERLAPPEDWINDOW, WNDPROC lpWndProc = NULL);

  ///
  /// \brief  Run Application
  /// 
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Run();

  ///
  /// \brief  Add Component
  ///
  /// \param  pComponent  [I ] Pointer of Component
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t Add(altComponent * pComponent);

  ///
  /// \brief  Set max frame count in 1 second
  ///
  /// \param  nMaxFrameCount  [I ] Max frame count
  ///
  /// \return ALT_S_SUCCESS
  ///
  LIBALT_API alt_t SetMaxFrameCount(const altUInt nMaxFrameCount);

  ///
  /// \brief  Get D3D Device
  ///
  /// \return D3D Device
  ///
  LIBALT_API LPDIRECT3DDEVICE9 GetDevice();

  ///
  /// \brief  Get Sprite
  ///
  /// \return Sprite
  ///
  LIBALT_API LPD3DXSPRITE GetSprite();

  ///
  /// \brief  Get Window Handle
  ///
  /// \return Window Handle
  ///
  LIBALT_API HWND GetHWnd();

  ///
  /// \brief  Set focus component
  ///
  /// \param  pComponent  [I ] Component
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetFocus(altComponent * pComponent);

  ///
  /// \brief  Get focus component
  ///
  /// \return Focus component
  ///
  LIBALT_API altComponent * GetFocus() const;

  ///
  /// \brief  Add key event listener
  ///
  /// \param  pKeyEventListener [I ] Key event listener
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_INVAL   invalid paramter
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t AddKeyEventListener(altKeyEventListener * pKeyEventListener);

  ///
  /// \brief  Remove key event listener
  ///
  /// \param  pKeyEventListener [I ] Key event listener
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_INVAL   invalid paramter
  ///
  LIBALT_API alt_t RemoveKeyEventListener(altKeyEventListener * pKeyEventListener);

  ///
  /// \brief  Clear device
  ///
  /// \param  dwColor [I ] Color
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t DeviceClear(D3DCOLOR dwColor);

  ///
  /// \brief  Set alpha blend type
  ///
  /// \param  nType [I ] alpha blend type
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetAlphaBlend(const altAlphaBlendTypes nType);

  ///
  /// \brief  Set alpha blend enable
  ///
  /// \param  bEnable [I ] true or false
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetAlphaBlendEnable(const altBool bEnable);

  ///
  /// \brief  Window Function
  ///
  /// \param  hwnd    [I ] Window Handle
  /// \param  msg     [I ] message
  /// \param  wParam  [I ] parameter
  /// \param  lParam  [I ] parameter
  ///
  LIBALT_API static LRESULT APIENTRY WndFunc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  ///
  /// \brief  Get altDX Instance
  ///
  /// \return altDX Instance
  ///
  LIBALT_API static altDX & GetInstance();

  ///
  /// \brief  Delete Instance
  ///
  LIBALT_API static void DeleteInstance();

protected:
  ///
  /// \brief  Create Main Window
  ///
  /// \param  hInst       [I ] Instance Handle
  /// \param  sTitle      [I ] Title Name
  /// \param  nWidth      [I ] Window Width
  /// \param  nHeight     [I ] Widnow Heignt
  /// \param  bFullScreen [I ] FullScreen or not
  /// \param  nCmdshow    [I ] Command show
  /// \param  dwStyle     [I ] Window Style
  /// \param  lpWndProc   [I ] Pointer to the window procedure
  /// \param  wc          [ O] Window Class
  /// 
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t CreateMainWindow(HINSTANCE hInst, const altWStr & sTitle, const altInt nWidth, const altInt nHeight, const altBool bFullScreen, const altInt nCmdshow, const DWORD dwStyle, WNDPROC lpWndProc, WNDCLASSEX & wc);

  ///
  /// \brief Initialize Main Window
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t InitMainWindow();

  ///
  /// \brief  Application Loop
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API alt_t AppLoop();

  ///
  /// \brief  Render
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API alt_t Render();

  ///
  /// \brief  Get root component
  ///
  /// \return Root component
  ///
  LIBALT_API altRootComponent & GetRootComponent();

  ///
  /// \brief  Release Memory
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API alt_t Cleanup();

private:
  LPDIRECT3D9           m_lpD3D;                    ///< Direct3D interface
  LPDIRECT3DDEVICE9     m_lpD3DDevice;              ///< Direct3DDevice interface
  D3DPRESENT_PARAMETERS m_d3dpp;                    ///< Direct3D Parameters
  altBool               m_bAppLoop;                 ///< Application Loop
  altWStr               m_sTitle;                   ///< Application Title
  WNDCLASSEX            m_oWC;                      ///< Window Class
  HWND                  m_oHwnd;                    ///< Window Handle
  altUInt               m_nMaxFrameCount;           ///< Max frame count in 1 second
  LPD3DXSPRITE          m_pSprite;                  ///< Sprite
  altRootComponent      m_oRootComponent;           ///< Root component
  altComponent *        m_pFocus;                   ///< Focus component
};
#endif  // ALT_WIN
#endif  // ALTDX_H

#endif // ALT_USE_DX