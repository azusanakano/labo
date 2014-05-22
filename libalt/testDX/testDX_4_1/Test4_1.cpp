#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

   Alternative Library Test

  $Id: Test4_1.cpp 763 2007-12-18 18:07:54Z nekosys $

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
 * \file    Test4_1.cpp
 * \brief   Alternative Library Test
 * \date    2007
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "Test4_1.h"

INT WINAPI WinMain( HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR szStr,INT nCmdshow)
{
  alt_t status;

  aiLog.Open ("../Log/Test4_1.log");

  status = aiDX.Create (hInst, _T("testDXTest4_1"), 640, 480, false, nCmdshow);
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }

  status = aiDXInput.SetKeyboard();
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }

  Test4_1 oTest4_1;
  status = aiDX.Add (& oTest4_1);
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
Test4_1::Test4_1()
{
  altVertex aVertex[] = {
	  {	-0.8f,-0.8f, 0.0f, 0xffff0000,},
	  {	 0.8f,-0.8f, 0.0f, 0xff00ff00,},
	  {	 0.0f, 0.8f, 0.0f, 0xff0000ff,},
  };
  m_oPolygon.CreateVertexBuffer (aVertex, sizeof (aVertex), D3DFVF_XYZ | D3DFVF_DIFFUSE, 1);

  aiDX.GetDevice()->SetRenderState (D3DRS_CULLMODE, D3DCULL_NONE);
  aiDX.GetDevice()->SetRenderState (D3DRS_LIGHTING, FALSE);
}

///
/// \brief  Destructor
///
Test4_1::~Test4_1()
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
alt_t Test4_1::Render(IDirect3DDevice9 * pDevice)
{	
  aiDX.DeviceClear (D3DCOLOR_XRGB (100,100,100));
  m_oPolygon.Render(pDevice);

  return (altComponent::Render(pDevice));
}

#endif