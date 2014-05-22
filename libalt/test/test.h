#ifndef TEST_H
#define TEST_H
/*--------------------------------------------------------------------------*

   Alternative Library Test

  $Id: test.h 15 2007-05-06 00:11:04Z nekosys $

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
 * \file    test.h
 * \brief   Alternative Library Test Header
 * \date    2007
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "libalt.h"

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
///
/// \brief  Test
///
/// \param  cond  [I ] condition
///
#define TEST(cond) \
  if (cond) { printf ("[OK] (%s:%d) %s\n", __FILE__, __LINE__, #cond); } \
  else      { printf ("[NG] (%s:%d) %s\n", __FILE__, __LINE__, #cond); }

///
/// \brief  Entry Test Function
///
/// \param  pFunc [I ] pointer of test function
///
#define TEST_ENT(pFunc) \
  {pFunc, #pFunc}

/*----------------------------------------------------------------*
 * Structure Definition
 *----------------------------------------------------------------*/
///
/// \brief  Test Function
///
typedef void (* testFunc)();

///
/// \brief  Test Function Entry
///
typedef struct test_entry {
  testFunc          pTestFunc;        ///< pointer of test function
  const altChar *   szTestFuncName;   ///< name of test function
} TestEntry;

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  test base class
///
class testBase : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  testBase();

  ///
  /// \brief  Destructor
  ///
  virtual ~testBase();

  ///
  /// \brief  execute test
  ///
  /// \param  aTable  [I ] test function table
  /// \param  nCount  [I ] test function table size
  ///
  void ExecuteTest();

protected:
  ///
  /// \brief  set test function table
  ///
  /// \param  aTable  [I ] test function table
  /// \param  nCount  [I ] test function table count
  ///
  void Set(const TestEntry aTable[], const altUInt nCount);

private:
  const TestEntry * m_pTable; ///< test function table
  altUInt           m_nCount; ///< test function table size
};

#endif // TEST_H
