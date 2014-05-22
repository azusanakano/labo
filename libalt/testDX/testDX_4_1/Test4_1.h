#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef TEST4_1_H
#define TEST4_1_H
/*--------------------------------------------------------------------------*

   Alternative Llibrary

  $Id: Test4_1.h 740 2007-12-05 19:37:58Z nekosys $

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
 * \file    Test4_1.h
 * \brief   DirectX Test 4-1
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
class Test4_1 : public altComponent
{
public:
  ///
  /// \brief  Constructor
  ///
  Test4_1();

  ///
  /// \brief  Destructor
  ///
  ~Test4_1();

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
  altPolygon  m_oPolygon;
};

#endif

#endif