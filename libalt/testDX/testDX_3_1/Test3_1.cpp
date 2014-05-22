#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

   Alternative Library Test

  $Id: Test3_1.cpp 763 2007-12-18 18:07:54Z nekosys $

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
 * \file    Test3_1.cpp
 * \brief   Alternative Library Test
 * \date    2007
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "Test3_1.h"

INT WINAPI WinMain( HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR szStr,INT nCmdshow)
{
  alt_t status;

  status = aiDX.Create (hInst, _T("testDXTest3_1"), 640, 480, false, nCmdshow);
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }

  Test3_1 oTest3_1;
  status = aiDX.Add (& oTest3_1);
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
Test3_1::Test3_1() :
m_oTexture()
{
  SetPositionEx (270, 180, 100, 100);
}

///
/// \brief  Destructor
///
Test3_1::~Test3_1()
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
alt_t Test3_1::Render(IDirect3DDevice9 * pd3dDevice)
{
  alt_t status;
  
  aiDX.DeviceClear (D3DCOLOR_XRGB(100,100,100));

  RECT rect = {0,0,100,100};
  RECT oPos = GetPosition();
  D3DXVECTOR3 vec3Center (0,0,0);
  D3DXVECTOR3 vec3Position ((FLOAT)oPos.left, (FLOAT)oPos.top, 0);

  aiDX.GetSprite()->Begin (D3DXSPRITE_ALPHABLEND);
  if (m_oTexture.GetRawTexture() == NULL) {
    status = m_oTexture.Load ("../testResource/Sprite.bmp", 100, 100, 0xff000000);
    ALT_ERR_RET (status);
  }
  status = m_oTexture.Draw (& rect, & vec3Center, & vec3Position, 0xffffffff);
  ALT_ERR_RET (status);
  aiDX.GetSprite()->End();

  return (altComponent::Render (pd3dDevice));
}

///
/// \brief  Listen key down event
///
/// \param  oEvent  [I ] Event
/// \param  nKey    [I ] Key
///
/// \return ALT_S_SUCCESS success
///
alt_t Test3_1::OnKeyDown(const altEvent & oEvent, const altUInt nKey)
{
  if (oEvent.GetEventSource() != this) {
    ALT_RET (ALT_S_SUCCESS);
  }
  RECT oRect = GetPosition();

  switch (nKey) {
    case  DIK_LEFT:
      oRect.left -= 4;
      break;
    case DIK_RIGHT:
      oRect.left += 4;
      break;
    case DIK_UP:
      oRect.top -= 4;
      break;
    case DIK_DOWN:
      oRect.top += 4;
      break;
    default:
      break;
  }
  SetPosition (oRect.left, oRect.top);
  ALT_RET (ALT_S_SUCCESS);
}

#endif