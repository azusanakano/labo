#ifndef TESTSTR_H
#define TESTSTR_H
/*--------------------------------------------------------------------------*

   Alternative Library Test

  $Id: testStr.h 36 2007-05-08 22:17:24Z nekosys $

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
 * \file    testStr.h
 * \brief   Alternative Library Test Header
 * \date    2007
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "../test.h"

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  altStr test class
///
class testStr : public testBase
{
public:
  ///
  /// \brief  Constructor
  ///
  testStr();

  ///
  /// \brief  Destructor
  ///
  virtual ~testStr();
};

#endif  //TESTSTR_H
