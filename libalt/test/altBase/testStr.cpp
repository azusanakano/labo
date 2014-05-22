/*--------------------------------------------------------------------------*

   Alternative Library Test

  $Id: testStr.cpp 251 2007-06-04 10:15:44Z nekosys $

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
 * \file    testStr.cpp
 * \brief   Alternative Library Test
 * \date    2007
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "testStr.h"

/*----------------------------------------------------------------*
 * Static Function Declare
 *----------------------------------------------------------------*/
///
/// \brief  altStr test
///
static void Test_altStr();


/*----------------------------------------------------------------*
 * Static variables
 *----------------------------------------------------------------*/
static TestEntry st_aTestTable[] = {
  TEST_ENT (Test_altStr),
};

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
testStr::testStr()
{
  Set (st_aTestTable, ALT_ARRAY_SIZE (st_aTestTable));
}

///
/// \brief  Destructor
///
testStr::~testStr()
{
}

///
/// \brief  altStr test
///
static void Test_altStr()
{
  altStr  sStr1 = "aa";
  altStr  sStr2 = "aa";

  TEST (sStr1 == sStr2);
  TEST (sStr1 == "aa");

  sStr1 += "a";
  TEST (sStr1 == "aaa");
  TEST (sStr1 != sStr2);

  sStr1.Format ("aa%d", 1);
  TEST (sStr1 == "aa1");

  sStr1 = " aa ";
  sStr1.Trim();
  TEST (sStr1 == "aa");

  sStr1.ToUpper();
  TEST (sStr1 == "AA");

  sStr1.ToLower();
  TEST (sStr1 == "aa");
  TEST (sStr1[0] == 'a');
  TEST (sStr1[1] == 'a');
  TEST (sStr1[2] == 0x00);
  TEST (sStr1[3] == 0x00);

  sStr1 = "aa";
  sStr2 = "ab";
  TEST (sStr1 < sStr2);
  TEST (sStr2 > sStr1);
  TEST (sStr1 <= sStr2);
  TEST (sStr2 >= sStr1);

  sStr2 = "aa";
  TEST (sStr1 <= sStr2);
  TEST (sStr2 >= sStr1);

  sStr1 = "0123456789a12345678a";
  altInt nIndex = sStr1.Find ("567");
  TEST (nIndex == 5);

  nIndex = sStr1.Find ("0");
  TEST (nIndex == 0);

  nIndex = sStr1.Find ("aaaa");
  TEST (nIndex == -1);

  nIndex = sStr1.Find ("");
  TEST (nIndex == -1);

  nIndex = sStr1.FindLastOf ("a");
  TEST (nIndex == 19);

  nIndex = sStr1.FindLastOf ("0");
  TEST (nIndex == 0);

  nIndex = sStr1.FindChar("a");
  TEST (nIndex == 10);

  nIndex = sStr1.FindChar("a3");
  TEST (nIndex == 3);

  nIndex = sStr1.FindLastOfChar ("0");
  TEST (nIndex == 0);

  nIndex = sStr1.FindLastOfChar ("a0");
  TEST (nIndex == 19);

  sStr1 = "01234567890123456789";
  sStr2 = sStr1.SubStr (10);
  TEST (sStr2 == "0123456789");

  sStr2 = sStr1.SubStr(1, 9);
  TEST (sStr2 == "123456789");

  sStr2.Replace ("12345", "");
  TEST (sStr2 == "6789");

  sStr2.Replace ("6789", "1234");
  TEST (sStr2 == "1234");

  sStr2.Replace ("1234", "0123456789");
  TEST (sStr2 == "0123456789");

  altStr  s1 = "aaa";
  altStr  s2 = "bbb";

  TEST (s1 < s2);
  TEST (s1 <= s2);
  TEST (s2 <= s2);
  TEST (s1 != s2);

  TEST (s2 > s1);
  TEST (s2 >= s1);
  TEST (s2 >= s2);

  sStr1.SetByte(1);
  TEST (sStr1 == "1");
}


