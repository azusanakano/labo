#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

   Alternative Library Test

  $Id: Test4_2.cpp 763 2007-12-18 18:07:54Z nekosys $

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
 * \file    Test4_2.cpp
 * \brief   Alternative Library Test
 * \date    2007
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "Test4_2.h"

INT WINAPI WinMain( HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR szStr,INT nCmdshow)
{
  alt_t status;

  aiLog.Open ("../Log/Test4_2.log");

  status = aiDX.Create (hInst, _T("testDXTest4_2"), 640, 480, false, nCmdshow);
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }

  status = aiDXInput.SetKeyboard();
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }

  Test4_2 oTest4_2;
  status = aiDX.Add (& oTest4_2);
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
Test4_2::Test4_2()
{
  m_oXFile.Load ("../testResource/Chips.x");
  aiDX.GetDevice()->SetRenderState (D3DRS_ZENABLE, TRUE);  
  aiDX.GetDevice()->SetRenderState (D3DRS_LIGHTING, TRUE);
  aiDX.GetDevice()->SetRenderState (D3DRS_AMBIENT, 0x00111111 );
  aiDX.GetDevice()->SetRenderState (D3DRS_SPECULARENABLE,TRUE);
}

///
/// \brief  Destructor
///
Test4_2::~Test4_2()
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
  alt_t Test4_2::Render(IDirect3DDevice9 * pDevice)
{
  altCamera oCamera;
  oCamera.SetRotationWorld (0.0f, timeGetTime()/3000.0f, 0.0f);

  oCamera.SetEyePosition (0.0f, 1.0f, -3.0f);
  oCamera.SetLookAtPosition (0.0f, 0.0f, 0.0f);
  oCamera.SetUpVector (0.0f, 1.0f, 0.0f);
  oCamera.SetTransformView ();

  oCamera.SetTransformProjection (D3DX_PI/4, 1.0f, 1.0f, 100.0f);
  oCamera.SetTransform();

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
  m_oXFile.Draw();

  return (altComponent::Render(pDevice));
}

#endif