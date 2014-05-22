#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

   Alternative Library Test

  $Id: main.cpp 773 2007-12-19 22:00:50Z nekosys $

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
 * \file    main.cpp
 * \brief   Alternative Library Test
 * \date    2007
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <libalt.h>

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev, LPSTR lpszCmdParam,int nCmdshow)
{
  alt_t     status;

  aiLog.Open ("../Log/TestDX.log");

  status = aiDX.Create (hInst, _T("testDX"), 480, 680, false, nCmdshow, WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX);
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }

  alt2DQuad * p2DQuad = new alt2DQuad();
  if (p2DQuad == NULL) {
    return (1);
  }

  status = p2DQuad->SetTexture ("../testResource/1.jpg");
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }

  status = p2DQuad->SetPosition (0, 0, 480, 640, D3DCOLOR_RGBA (255, 255, 255, 255));
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }

  status = aiDX.Add (p2DQuad);
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }

  altLabel oLabel(0, 640, 20, 640);
  oLabel.SetTextFormat (DT_VCENTER);
  oLabel.SetText (_T ("Ç±ÇÃîLÇÕÇ´Ç´ÇÂÇ§ÇøÇ·ÇÒÇ≈Ç∑ÅB(ÅGÅEÅ~ÅE)"));

  status = aiDX.Add (& oLabel);
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }

  altTextBox oTextBox(0, 660, 20, 640);
  status = aiDX.Add (& oTextBox);
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }

  status = aiDX.Run ();
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }

  delete p2DQuad;
  altDX::DeleteInstance();
  
  return (0);
}

#endif