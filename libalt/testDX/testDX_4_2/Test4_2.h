#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef TEST4_2_H
#define TEST4_2_H
/*--------------------------------------------------------------------------*

   Alternative Llibrary

  $Id: Test4_2.h 746 2007-12-07 03:47:13Z nekosys $

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
 * \file    Test4_2.h
 * \brief   DirectX Test 4-2
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
/// \brief  DirectX Test 4-2
///
class Test4_2 : public altComponent
{
public:
  ///
  /// \brief  Constructor
  ///
  Test4_2();

  ///
  /// \brief  Destructor
  ///
  ~Test4_2();

  ///
  /// \brief  Render
  ///
  /// \param  pd3dDevice  [I ] D3D Device
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  alt_t Render(IDirect3DDevice9 * pd3dDevice);

private:
  altXFile  m_oXFile;
};

#endif

#endif