#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef TEST5_3_H
#define TEST5_3_H
/*--------------------------------------------------------------------------*

   Alternative Llibrary

  $Id: Test5_3.h 760 2007-12-13 20:55:02Z nekosys $

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
 * \file    Test5_3.h
 * \brief   DirectX Test 5-3
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
/// \brief  DirectX Test 5-3
///
class Test5_3 : public altComponent, public altKeyEventListener
{
public:
  ///
  /// \brief  Constructor
  ///
  Test5_3();

  ///
  /// \brief  Destructor
  ///
  ~Test5_3();

  ///
  /// \brief  Render
  ///
  /// \param  pd3dDevice  [I ] D3D Device
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  alt_t Render(IDirect3DDevice9 * pDevice);

  ///
  /// \brief  Listen key down event
  ///
  /// \param  oEvent  [I ] Event
  /// \param  nKey    [I ] Key
  ///
  /// \return ALT_S_SUCCESS success
  ///
  alt_t OnKeyDown(const altEvent & oEvent, const altUInt nKey);

private:
  altXFile  m_oXFile;
};

#endif

#endif