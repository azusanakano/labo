/*--------------------------------------------------------------------------*

   Alternative Library Test

  $Id: testBaseMem.cpp 16 2007-05-06 00:18:24Z nekosys $

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
 * \file    testBaseMem.cpp
 * \brief   Alternative Library Test
 * \date    2007
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "testBaseMem.h"

/*----------------------------------------------------------------*
 * Static Function Declare
 *----------------------------------------------------------------*/
///
/// \brief  ALT_BASE_MALLOC test
///
static void Test_ALT_BASE_MALLOC();

///
/// \brief  ALT_BASE_DUPALLOC test
///
static void Test_ALT_BASE_DUPALLOC();

///
/// \brief  ALT_BASE_EXALLOC test
///
static void Test_ALT_BASE_EXALLOC();

/*----------------------------------------------------------------*
 * Static variables
 *----------------------------------------------------------------*/
static TestEntry st_aTestTable[] = {
  TEST_ENT (Test_ALT_BASE_MALLOC),
  TEST_ENT (Test_ALT_BASE_DUPALLOC),
  TEST_ENT (Test_ALT_BASE_EXALLOC),
};

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
testBaseMem::testBaseMem()
{
  Set (st_aTestTable, ALT_ARRAY_SIZE (st_aTestTable));
}

///
/// \brief  Destructor
///
testBaseMem::~testBaseMem()
{
}

///
/// \brief  ALT_BASE_MALLOC test
///
static void Test_ALT_BASE_MALLOC()
{
  altInt    nRet;
  altChar * pPtr = NULL;

  // success
  nRet = ALT_BASE_MALLOC (pPtr, 100);
  TEST (nRet == ALT_SUCCESS);

  // error
  nRet = ALT_BASE_MALLOC (pPtr, 100);
  TEST (nRet == ALT_INVAL);

  // success
  nRet = ALT_BASE_FREE (pPtr);
  TEST (nRet == ALT_SUCCESS);
  TEST (pPtr == NULL);
}

///
/// \brief  ALT_BASE_DUPALLOC test
///
static void Test_ALT_BASE_DUPALLOC()
{
  altInt    nRet;
  altChar * pPtr = NULL;

  // success
  nRet = ALT_BASE_DUPALLOC (pPtr, "aaa", sizeof ("aaa"));
  TEST (nRet == ALT_SUCCESS);
  TEST (memcmp (pPtr, "aaa", sizeof ("aaa")) == 0);

  // error
  nRet = ALT_BASE_DUPALLOC (pPtr, "aaa", sizeof ("aaa"));
  TEST (nRet == ALT_INVAL);
  TEST (memcmp (pPtr, "aaa", sizeof ("aaa")) == 0);

  // success
  nRet = ALT_BASE_FREE (pPtr);
  TEST (nRet == ALT_SUCCESS);
  TEST (pPtr == NULL);
}

///
/// \brief  ALT_BASE_EXALLOC test
///
static void Test_ALT_BASE_EXALLOC()
{
  altInt    nRet;
  altChar * pPtr = NULL;

  // success
  nRet = ALT_BASE_EXALLOC (pPtr, 0, 2);
  TEST (nRet == ALT_SUCCESS);

  // error
  nRet = ALT_BASE_EXALLOC (pPtr, 0, 2);
  TEST (nRet == ALT_INVAL);

  // error
  nRet = ALT_BASE_EXALLOC (pPtr, 1, 2);
  TEST (nRet == ALT_INVAL);

  // success
  nRet = ALT_BASE_EXALLOC (pPtr, 2, 4);
  TEST (nRet == ALT_SUCCESS);

  // success
  nRet = ALT_BASE_FREE (pPtr);
  TEST (nRet == ALT_SUCCESS);
  TEST (pPtr == NULL);
}
