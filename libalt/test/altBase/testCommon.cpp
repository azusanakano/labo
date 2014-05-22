/*--------------------------------------------------------------------------*

   Alternative Library Test

  $Id: testCommon.cpp 56 2007-05-11 20:28:50Z nekosys $

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
 * \file    testCommon.cpp
 * \brief   Alternative Library Test
 * \date    2007
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "testCommon.h"

/*----------------------------------------------------------------*
 * Static Function Declare
 *----------------------------------------------------------------*/
///
/// \brief  altCommon test
///
static void Test_altCommon();


/*----------------------------------------------------------------*
 * Static variables
 *----------------------------------------------------------------*/
static TestEntry st_aTestTable[] = {
  TEST_ENT (Test_altCommon),
};

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
testCommon::testCommon()
{
  Set (st_aTestTable, ALT_ARRAY_SIZE (st_aTestTable));
}

///
/// \brief  Destructor
///
testCommon::~testCommon()
{
}

///
/// \brief  altCommon test
///
static void Test_altCommon()
{
  TEST (sizeof (altChar) == 1);
  TEST (sizeof (altUChar) == 1);
  TEST (sizeof (altByte) == 1);
  TEST (sizeof (altShort) == 2);
  TEST (sizeof (altUShort) == 2);
  TEST (sizeof (WORD) == 2);
  TEST (sizeof (altInt) == 4);
  TEST (sizeof (altUInt) == 4);
  TEST (sizeof (altLong) == 8);
  TEST (sizeof (altULong) == 8);
  TEST (sizeof (DWORD) == 8);
  TEST (sizeof (altLongLong) == 8);
  TEST (sizeof (altULongLong) == 8);
}


