/*--------------------------------------------------------------------------*

   Alternative Library Test

  $Id: test.cpp 15 2007-05-06 00:11:04Z nekosys $

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
 * \file    test.cpp
 * \brief   Alternative Library Test
 * \date    2007
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "test.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
testBase::testBase()
{
  m_pTable = NULL;
  m_nCount = 0;
}

///
/// \brief  Destructor
///
testBase::~testBase()
{
  m_pTable = NULL;
  m_nCount = 0;
}

///
/// \brief  set test function table
///
/// \param  aTable  [I ] test function table
/// \param  nCount  [I ] test function table count
///
void testBase::Set(const TestEntry aTable[], const altUInt nCount)
{
  m_pTable = aTable;
  m_nCount = nCount;
}

///
/// \brief  execute test
///
void testBase::ExecuteTest()
{
  for (altUInt i = 0; i < m_nCount; i++) {
    printf ("-------------------------------------------------------------------------------\n");
    printf ("%s\n", m_pTable[i].szTestFuncName);
    printf ("-------------------------------------------------------------------------------\n");
    (m_pTable[i].pTestFunc)();
  }
}
