#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDX.cpp
 * \brief   DirectX class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altDX.h"
#ifdef ALT_WIN
#include "altFontManager.h"
#include "altMouse.h"
#include "altIME.h"
#include "altDXInput.h"
#include "altBase/altUtil.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altDX::altDX() :
m_lpD3D (NULL),
m_lpD3DDevice (NULL),
m_d3dpp (),
m_bAppLoop (true),
m_sTitle(),
m_oWC(),
m_nMaxFrameCount (60),
m_pSprite (NULL),
m_oRootComponent(),
m_pFocus (NULL)
{
}

///
/// \brief  Destructor
///
LIBALT_API altDX::~altDX()
{
  Cleanup();
}

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
/// 
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDX::Create(HINSTANCE hInst, const altWStr & sTitle, const altInt nWidth, const altInt nHeight, const altBool bFullScreen, const altInt nCmdshow, const DWORD dwStyle, WNDPROC lpWndProc)
{
  alt_t status;

  m_sTitle = sTitle;

  status = CreateMainWindow (hInst, sTitle, nWidth, nHeight, bFullScreen, nCmdshow, dwStyle, lpWndProc, m_oWC);
  ALT_ERR_RET (status);

  status = InitMainWindow();
  ALT_ERR_RET (status);

  status = aiDXInput.SetKeyboard();
  ALT_ERR_RET (status);

  ALT_RET (status);
}

///
/// \brief  Run Application
/// 
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDX::Run()
{
  alt_t     status;

  status = AppLoop();

  UnregisterClass ((LPCWSTR)m_sTitle.GetCStr(), m_oWC.hInstance);
  ALT_RET (status);
}

///
/// \brief  Add Component
///
/// \param  pComponent  [I ] Pointer of Component
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altDX::Add(altComponent * pComponent)
{
  ALT_P_ASSERT (pComponent != NULL);

  alt_t status;

  status = m_oRootComponent.Add (pComponent);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set max frame count in 1 second
///
/// \param  nMaxFrameCount  [I ] Max frame count
///
/// \return ALT_S_SUCCESS
///
LIBALT_API alt_t altDX::SetMaxFrameCount(const altUInt nMaxFrameCount)
{
  m_nMaxFrameCount = nMaxFrameCount;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get D3D Device
///
/// \return D3D Device
///
LIBALT_API LPDIRECT3DDEVICE9 altDX::GetDevice()
{
  return (m_lpD3DDevice);
}

///
/// \brief  Get Sprite
///
/// \return Sprite
///
LIBALT_API LPD3DXSPRITE altDX::GetSprite()
{
  return (m_pSprite);
}

///
/// \brief  Get Window Handle
///
/// \return Window Handle
///
LIBALT_API HWND altDX::GetHWnd()
{
  return (m_oHwnd);
}

///
/// \brief  Set focus component
///
/// \param  pComponent  [I ] Component
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altDX::SetFocus(altComponent * pComponent)
{
  m_pFocus = pComponent;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get focus component
///
/// \return Focus component
///
LIBALT_API altComponent * altDX::GetFocus() const
{
  return (m_pFocus);
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
LIBALT_API alt_t altDX::AddKeyEventListener(altKeyEventListener * pKeyEventListener)
{
  alt_t status;
  status = m_oRootComponent.AddKeyEventListener (pKeyEventListener);
  ALT_ERR_RET (status);

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
LIBALT_API alt_t altDX::RemoveKeyEventListener (altKeyEventListener * pKeyEventListener)
{
  alt_t status;

  status = m_oRootComponent.RemoveKeyEventListener (pKeyEventListener);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Clear device
///
/// \param  dwColor [I ] Color
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altDX::DeviceClear(D3DCOLOR dwColor)
{
  HRESULT hr = m_lpD3DDevice->Clear (0, NULL, D3DCLEAR_TARGET, dwColor, 1.0f, 0);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set alpha blend type
///
/// \param  nType [I ] alpha blend type
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altDX::SetAlphaBlend(const altAlphaBlendTypes nType)
{
  switch (nType) {
    case ALT_ALPHA_BLEND_0:
      m_lpD3DDevice->SetRenderState (D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
      m_lpD3DDevice->SetRenderState (D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
      break;
    case ALT_ALPHA_BLEND_1:
      m_lpD3DDevice->SetRenderState (D3DRS_DESTBLEND, D3DBLEND_ONE);
      m_lpD3DDevice->SetRenderState (D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
      break;
    case ALT_ALPHA_BLEND_2:
      m_lpD3DDevice->SetRenderState (D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
      m_lpD3DDevice->SetRenderState (D3DRS_DESTBLEND, D3DBLEND_ONE);
      m_lpD3DDevice->SetRenderState (D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
      break;
    case ALT_ALPHA_BLEND_3:
      m_lpD3DDevice->SetRenderState (D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
      m_lpD3DDevice->SetRenderState (D3DRS_SRCBLEND, D3DBLEND_ZERO);
      break;
    case ALT_ALPHA_BLEND_4:
      m_lpD3DDevice->SetRenderState (D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
      m_lpD3DDevice->SetRenderState (D3DRS_SRCBLEND, D3DBLEND_ZERO);
      break;
    case ALT_ALPHA_BLEND_5:
      m_lpD3DDevice->SetRenderState (D3DRS_DESTBLEND, D3DBLEND_ZERO);
      m_lpD3DDevice->SetRenderState (D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
      break;
    case ALT_ALPHA_BLEND_6:
      m_lpD3DDevice->SetRenderState (D3DRS_DESTBLEND, D3DBLEND_ZERO);
      m_lpD3DDevice->SetRenderState (D3DRS_SRCBLEND, D3DBLEND_ONE);
      break;
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set alpha blend enable
///
/// \param  bEnable [I ] true or false
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altDX::SetAlphaBlendEnable(const altBool bEnable)
{
  m_lpD3DDevice->SetRenderState (D3DRS_ALPHABLENDENABLE, bEnable);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Window Function
///
/// \param  hwnd    [I ] Window Handle
/// \param  msg     [I ] message
/// \param  wParam  [I ] parameter
/// \param  lParam  [I ] parameter
///
LIBALT_API LRESULT APIENTRY altDX::WndFunc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  alt_t status;
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage (0);
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
      break;
		}
    break;
  case WM_LBUTTONDOWN:
  case WM_RBUTTONDOWN:
    {
      status = aiMouse.WndProc (hwnd, msg, wParam, lParam);
      ALT_LOG (status);
      status = aiDX.m_oRootComponent.SetFocus();
      ALT_LOG (status);
      altComponent * pComponent = aiDX.GetFocus();
      if (pComponent != NULL) {
        pComponent->OnFocus();
      }
      status = aiDX.GetRootComponent().OffFocus();
      ALT_LOG (status);
    }
    break;
  case WM_MOUSEMOVE:
  case WM_LBUTTONUP:
  case WM_RBUTTONUP:
  case WM_MOUSEWHEEL:
    status = aiMouse.WndProc (hwnd, msg, wParam, lParam);
    ALT_LOG (status);
    break;
	}

  aiDX.GetRootComponent().WndProc (hwnd, msg, wParam, lParam);

  if (aiIME.WndProc (hwnd, msg, wParam, lParam)) {
    return (DefWindowProc(hwnd, msg, wParam, lParam));
  }
  else {
    return (0);
  }

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

///
/// \brief  Get altDX Instance
///
/// \return altDX Instance
///
LIBALT_API altDX & altDX::GetInstance()
{
  return (altSingleton<altDX>::GetInstance());
}

///
/// \brief  Delete Instance
///
LIBALT_API void altDX::DeleteInstance()
{
  aiIME.DeleteInstance();
  aiFontManager.DeleteInstance();
  altSingleton<altDX>::DeleteInstance();
}

///
/// \brief  Create Main Window
///
/// \param  hInst       [I ] Instance Handle
/// \param  sTitle      [I ] Title Name
/// \param  nWidth      [I ] Window Width
/// \param  nHeight     [I ] Widnow Heignt
/// \param  bFullScreen [I ] FullScreen or not
/// \param  nCmdshow    [I ] command show
/// \param  dwStyle     [I ] Window Style
/// \param  lpWndProc   [I ] Pointer to the window procedure
/// \param  wc          [ O] Window Class
/// 
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDX::CreateMainWindow(HINSTANCE hInst, const altWStr & sTitle, const altInt nWidth, const altInt nHeight, const altBool bFullScreen, const altInt nCmdshow, const DWORD dwStyle, WNDPROC lpWndProc, WNDCLASSEX & wc)
{
	wc.style = CS_DBLCLKS;
  if (lpWndProc == NULL) {
    wc.lpfnWndProc = altDX::WndFunc;
  }
  else {
    wc.lpfnWndProc = lpWndProc;
  }
  wc.cbSize = sizeof (wc);
  wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
	wc.lpszMenuName = NULL;
  wc.lpszClassName = (LPCWSTR)(sTitle.GetCStr());
  wc.hIconSm = LoadIcon (NULL, IDI_APPLICATION);

	RegisterClassEx (& wc);

	m_oHwnd = CreateWindowEx (
		WS_EX_TOPMOST,
		(LPCWSTR)sTitle.GetCStr(),
    (LPCWSTR)sTitle.GetCStr(),
		dwStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nWidth,
    nHeight,
		NULL,
    NULL,
    hInst,
		NULL);
  if (m_oHwnd == NULL) {
    ALT_RET (ALT_E_ERROR);
  }

  ShowWindow (m_oHwnd, nCmdshow);
  UpdateWindow (m_oHwnd);
  ::SetFocus (m_oHwnd);
  if (bFullScreen) {
    ShowCursor (FALSE);
  }
  else{
    RECT rc={ 0, 0, nWidth, nHeight};
    AdjustWindowRect (& rc, WS_OVERLAPPEDWINDOW, FALSE);
    SetWindowPos (m_oHwnd, NULL, 0, 0, rc.right-rc.left, rc.bottom-rc.top, SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOZORDER);
  }

  // Create Direct3D Object
  m_lpD3D = Direct3DCreate9 (D3D_SDK_VERSION);
  if (! m_lpD3D) {
    ALT_RET_P (ALT_E_ERROR, "Create Direct3D Failed.");
  }

	int adapter;

  // Adapter Number
  adapter = D3DADAPTER_DEFAULT;

  // Because making of a window was completed, I initialize Direct3D
  ZeroMemory (& m_d3dpp ,sizeof (D3DPRESENT_PARAMETERS));
  // Setting of a Direct3D initialization parameter
  if (bFullScreen) {
    D3DDISPLAYMODE disp;
    m_lpD3D->GetAdapterDisplayMode (adapter, & disp);
    m_d3dpp.BackBufferFormat = disp.Format;
	}
  else {
    m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
  }
  // Setting of view area size
  m_d3dpp.BackBufferCount = 1;
  m_d3dpp.BackBufferWidth = nWidth;
  m_d3dpp.BackBufferHeight = nHeight;
  m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

  if (!bFullScreen) {
		// A window mode
		m_d3dpp.Windowed = 1;
	}

  // Automatic making of a Z buffer
  m_d3dpp.EnableAutoDepthStencil = 1;
  m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

  //I can lock back buffer and do it(GetDC is enabled, too)
  m_d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

  // Making of a device - T&L HAL
  if (FAILED(m_lpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, m_oHwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, & m_d3dpp, & m_lpD3DDevice))) {
    // Because I failed, I try it in HAL
    if (FAILED(m_lpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, m_oHwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, & m_d3dpp, & m_lpD3DDevice))) {
      // Because I failed, I try it in REF
      if (FAILED(m_lpD3D->CreateDevice(adapter, D3DDEVTYPE_REF, m_oHwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, & m_d3dpp, & m_lpD3DDevice))) {
        // I failed after all
        MessageBox (NULL, _T("I cannot initialize DirectX9. I seem to be a PC of non-correspondence."), _T("ERROR"), MB_OK | MB_ICONSTOP);
        m_lpD3D->Release();
        ALT_RET (ALT_E_ERROR);
      }
    }
  }

  if (FAILED (D3DXCreateSprite (m_lpD3DDevice, & m_pSprite))) {
    ALT_RET (ALT_E_ERROR);
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief Initialize Main Window
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altDX::InitMainWindow()
{
	// I set a rendering state
	// I do a calculation of Z buffer validation - context precisely
	m_lpD3DDevice->SetRenderState (D3DRS_ZENABLE, D3DZB_TRUE);
	m_lpD3DDevice->SetRenderState (D3DRS_ZWRITEENABLE, TRUE);

	// An alpha blending validation
	m_lpD3DDevice->SetRenderState (D3DRS_ALPHABLENDENABLE,TRUE);

	// I set an alpha blending method
	m_lpD3DDevice->SetRenderState (D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_lpD3DDevice->SetRenderState (D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Setting of a calculation method of alpha value at the time of rendering
	m_lpD3DDevice->SetTextureStageState (0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	// I use a color of texture
	m_lpD3DDevice->SetTextureStageState (0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	// I use a color of a top
	m_lpD3DDevice->SetTextureStageState (0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	// Setting of a calculation method of a color at the time of rendering
	m_lpD3DDevice->SetTextureStageState (0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	//Back side carrying
	m_lpD3DDevice->SetRenderState (D3DRS_CULLMODE, D3DCULL_CCW);

  SetAlphaBlend (ALT_ALPHA_BLEND_0);

	// Filter setting
	m_lpD3DDevice->SetSamplerState (0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	m_lpD3DDevice->SetSamplerState (0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_lpD3DDevice->SetSamplerState (0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

#if 0
	//Do you perform a calculation about light?
	m_lpD3DDevice->SetRenderState (D3DRS_LIGHTING, TRUE);

	//The establishment of a light
	D3DLIGHT9 Light;
  ZeroMemory (& Light, sizeof (D3DLIGHT9));
  Light.Type       = D3DLIGHT_DIRECTIONAL;             // A kind of a source of light
  Light.Diffuse.r  = 1.0f;                             // Diffuse ‚q
  Light.Diffuse.g  = 1.0f;                             // Diffuse ‚f
  Light.Diffuse.b  = 1.0f;                             // Diffuse ‚a
  Light.Diffuse.a  = 0.0f;                             // Diffuse ‚`
  Light.Direction  = D3DXVECTOR3 (1.0f, -1.0f, 1.0f);  // A course to advance of light

  m_lpD3DDevice->SetLight (0, & Light);
  m_lpD3DDevice->LightEnable (0, TRUE);
#endif
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Application Loop
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altDX::AppLoop()
{
  MSG msg;
  ZeroMemory (& msg, sizeof (msg));

	while (m_bAppLoop) {
    if (PeekMessage (& msg, NULL, 0, 0, PM_NOREMOVE)) {
      if (msg.message == WM_QUIT) {
        break;
      }
      if (!GetMessage (& msg, NULL, 0, 0)) {
        break;
      }
      TranslateMessage (& msg);
      DispatchMessage (& msg);
      
      if (aiDXInput.DownAnyKey()) {
        altEvent oEvent (WM_KEYDOWN, aiDX.GetFocus());
        aiDX.m_oRootComponent.OnKeyEvent (oEvent, aiDXInput.GetDownKey());
      }
    }
    else {
      Render();
    }
    altSleep (1);
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Render
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altDX::Render()
{
  HRESULT hr = S_OK;
  static DWORD dwNowTime;
  static DWORD dwPrevTime;
  dwNowTime = timeGetTime();
  if ((dwNowTime - dwPrevTime) < 1000 / m_nMaxFrameCount) {
    ALT_RET (ALT_S_SUCCESS);
  }
  dwPrevTime = dwNowTime;

  DeviceClear (D3DCOLOR_XRGB (255, 255, 255));

  if (SUCCEEDED (hr = m_lpD3DDevice->BeginScene())) {
    alt_t status = m_oRootComponent.Render (m_lpD3DDevice);
    ALT_LOG (status);
    hr = m_lpD3DDevice->EndScene();
  }

  if (FAILED (hr = m_lpD3DDevice->Present (NULL, NULL, NULL, NULL))) {
    m_lpD3DDevice->Reset (& m_d3dpp);
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get root component
///
/// \return Root component
///
LIBALT_API altRootComponent & altDX::GetRootComponent()
{
  return (m_oRootComponent);
}

///
/// \brief  Release Memory
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altDX::Cleanup()
{
  if (m_pSprite != NULL) {
    m_pSprite->Release();
    m_pSprite = NULL;
  }

  if (m_lpD3DDevice != NULL) {
    m_lpD3DDevice->Release();
    m_lpD3DDevice = NULL;
  }

  if (m_lpD3D != NULL) {
    m_lpD3D->Release();
    m_lpD3D = NULL;
  }

  ALT_RET (ALT_S_SUCCESS);
}

#endif // ALT_WIN

#endif // ALT_USE_DX