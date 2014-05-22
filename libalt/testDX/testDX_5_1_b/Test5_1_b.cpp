#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

   Alternative Library Test

  $Id: Test5_1_b.cpp 763 2007-12-18 18:07:54Z nekosys $

  Copyright (C) 2007 NEKO SYSTEM
 
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or any later version.
 
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Library General Public License for more details.
 
  You should have received a copy of the GNU Library General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *---------------------------------------------------------------------------*/
/**
 * \file    Test5_1_b.cpp
 * \brief   Alternative Library Test
 * \date    2007
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "Test5_1_b.h"

INT WINAPI WinMain( HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR szStr,INT nCmdshow)
{
  alt_t status;

  aiLog.Open ("../Log/Test5_1_b.log");

  status = aiDX.Create (hInst, _T("testDXTest5_1_b"), 640, 480, false, nCmdshow);
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }

  status = aiDXInput.SetKeyboard();
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }

  Test5_1_b_Panel oPanel;
  status = aiDX.Add (& oPanel);
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }

  status = aiDX.Run();
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }

  altDX::DeleteInstance();
  return (0);
}

///
/// \brief  Constructor
///
/// \param  sXFile  [I ] X file
///
Test5_1_b::Test5_1_b(const altStr & sXFile)
{
  m_oXFile.Load (sXFile.GetCStr());
}

///
/// \brief  Destructor
///
Test5_1_b::~Test5_1_b()
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
alt_t Test5_1_b::Render(IDirect3DDevice9 * pDevice)
{
  altCamera oCamera;
  oCamera.Translation (GetViewPosition().x, GetViewPosition().y, GetViewPosition().z);
  oCamera.SetTransformWorld();

  oCamera.SetEyePosition (0.0f, 1.0f, -3.0f);
  oCamera.SetLookAtPosition (0.0f, 0.0f, 0.0f);
  oCamera.SetUpVector (0.0f, 1.0f, 0.0f);
  oCamera.SetTransformView ();

  oCamera.SetTransformProjection (D3DX_PI/4, 1.0f, 1.0f, 100.0f);
  oCamera.SetTransform();

  m_oXFile.Draw();

  return (altComponent::Render(pDevice));
}



///
/// \brief  Constructor
///
Test5_1_b_Panel::Test5_1_b_Panel() :
m_o1 ("../testResource/Ground.x"),
m_o2 ("../testResource/Can.x"),
m_o3 ("../testResource/Bottle.x")
{
  aiDX.GetDevice()->SetRenderState (D3DRS_ZENABLE, TRUE);  
  aiDX.GetDevice()->SetRenderState (D3DRS_LIGHTING, TRUE);
  aiDX.GetDevice()->SetRenderState (D3DRS_AMBIENT, 0x00111111 );
  aiDX.GetDevice()->SetRenderState (D3DRS_SPECULARENABLE,TRUE);

  m_o1.SetViewPosition (0, -1, 0);
  m_o2.SetViewPosition (0, 0, 0);
  m_o3.SetViewPosition (1, 0, 1);

  Add (& m_o1);
  Add (& m_o2);
  Add (& m_o3);
}

///
/// \brief  Destructor
///
Test5_1_b_Panel::~Test5_1_b_Panel()
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
alt_t Test5_1_b_Panel::Render(IDirect3DDevice9 * pDevice)
{
  altLight      oLight;
  D3DXVECTOR3   vecDirection(0,0,1);
  D3DCOLORVALUE Diffuse;
  D3DCOLORVALUE Specular;

  Diffuse.r  = 1.0f;
  Diffuse.g  = 1.0f;
  Diffuse.b  = 1.0f;
  Specular.r = 1.0f;
  Specular.g = 1.0f;
  Specular.b = 1.0f;

  oLight.SetLight (vecDirection, D3DLIGHT_DIRECTIONAL, Diffuse, Specular, 200.0f);

  aiDX.GetDevice()->Clear (0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(100,100,100), 1.0f, 0);

  return (altComponent::Render (pDevice));
}

#endif