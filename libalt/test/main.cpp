/*--------------------------------------------------------------------------*

   Alternative Library Test

  $Id: main.cpp 664 2007-11-16 22:29:26Z nekosys $

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
#include "altBase/testCommon.h"
#include "altBase/testBaseMem.h"
#include "altBase/testStr.h"
#include "test.h"

/*----------------------------------------------------------------*
 * Structure Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Static variables
 *----------------------------------------------------------------*/
static testBase * st_oTest[] = {
  ALT_NEW testCommon(),
  ALT_NEW testBaseMem(),
  ALT_NEW testStr(),
};

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  main
///
/// \param  argc  [I ] arguments count
/// \param  argv  [I ] arguments
///
/// \return 0
///
int main(int argc, char * argv[])
{
  for (altUInt i = 0; i < ALT_ARRAY_SIZE (st_oTest); i++) {
    st_oTest[i]->ExecuteTest();
  }
  return (0);
}
