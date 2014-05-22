#ifndef ALTCLASS_H
#define ALTCLASS_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altRuntime.h
 * \brief   Runtime class
 * \date    2013
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altBase.h>
#include <altBase/altStr.h>
#include <typeinfo>

#ifdef ALT_WIN
#pragma comment(lib, "imagehlp.lib")
#include <imagehlp.h>
#endif

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
///
/// \brief  Get typeid
///
/// \param  o [I ] paramter
///
#define ALT_GET_TYPE(o)           typeid (o)

///
/// \brief  Get type name
///
/// \param  o [I ] paramter
///
/// \return Type name
///
#define ALT_GET_TYPE_NAME(o)      ALT_GET_TYPE (o).name()

///
/// \brief  Get class name
///
/// \return Class name
///
#define ALT_GET_CLASS_NAME()      ALT_GET_TYPE_NAME (* this)

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Runtime Class
///
class altRuntime
{
private:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altRuntime();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altRuntime();

public:
  ///
  /// \brief  Get stack trace
  ///
  /// \return  Stack trace
  ///
  LIBALT_API static altStr GetStackTrace();

#ifdef ALT_WIN
  ///
  /// \brief  Convert address
  ///
  /// \param  hProcess  [I ] Proccess handle
  /// \param  dwAddr    [I ] Address
  /// \param  sOutBuf   [ O] Out buffer
  ///
  /// \return System size
  ///
  LIBALT_API static void ConvertAddress(HANDLE hProcess, DWORD dwAddr, altStr & sOutBuf);
#endif
};

#endif
