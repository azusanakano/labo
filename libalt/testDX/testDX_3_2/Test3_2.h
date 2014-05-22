#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef TEST3_2_H
#define TEST3_2_H
/*--------------------------------------------------------------------------*

   Alternative Llibrary

  $Id: Test3_2.h 735 2007-12-01 10:17:32Z nekosys $

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
 * \file    Test3_2.h
 * \brief   DirectX Test 3-2
 * \date    2007
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <libalt.h>

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  DirectX Test 3-2
///
class Test3_2 : public altComponent
{
public:
  ///
  /// \brief  Constructor
  ///
  Test3_2();

  ///
  /// \brief  Destructor
  ///
  ~Test3_2();

  ///
  /// \brief  Render
  ///
  /// \param  pd3dDevice  [I ] D3D Device
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  alt_t Render(IDirect3DDevice9 * pd3dDevice);

  ///
  /// \brief  Move
  ///
  /// \return ALT_S_SUCCESS success
  ///
  alt_t Move();

  ///
  /// \brief  On focus
  ///
  /// \return ALT_S_SUCCESS success
  ///
  alt_t OnFocus();

  ///
  /// \brief  Off focus
  ///
  /// \return ALT_S_SUCCESS success
  ///
  alt_t OffFocus();

private:
  altTexture  m_oTexture;
  DWORD       m_dwColor;
};

#endif

#endif