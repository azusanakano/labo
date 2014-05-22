#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef TEST5_1_B_H
#define TEST5_1_B_H
/*--------------------------------------------------------------------------*

   Alternative Llibrary

  $Id: Test5_1_b.h 757 2007-12-13 03:08:30Z nekosys $

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
 * \file    Test5_1_b.h
 * \brief   DirectX Test 5-1-b
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
/// \brief  DirectX Test 5-1-b
///
class Test5_1_b : public altComponent
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  sXFile  [I ] X file
  ///
  Test5_1_b(const altStr & sXFile);

  ///
  /// \brief  Destructor
  ///
  ~Test5_1_b();

  ///
  /// \brief  Render
  ///
  /// \param  pd3dDevice  [I ] D3D Device
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  alt_t Render(IDirect3DDevice9 * pDevice);

private:
  altXFile  m_oXFile;
};

///
/// \brief  DirectX Test 5-1
///
class Test5_1_b_Panel : public altComponent
{
public:
  ///
  /// \brief  Constructor
  ///
  Test5_1_b_Panel();

  ///
  /// \brief  Destructor
  ///
  ~Test5_1_b_Panel();

  ///
  /// \brief  Render
  ///
  /// \param  pd3dDevice  [I ] D3D Device
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  alt_t Render(IDirect3DDevice9 * pDevice);

private:
  Test5_1_b m_o1;
  Test5_1_b m_o2;
  Test5_1_b m_o3;
};

#endif

#endif