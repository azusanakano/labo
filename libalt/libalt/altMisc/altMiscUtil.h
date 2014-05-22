#ifndef ALTMISCUTIL_H
#define ALTMISCUTIL_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMiscUtil.h
 * \brief   Utility functions class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#include <altBase/altLog.h>

/*----------------------------------------------------------------*
 * Function Declare
 *----------------------------------------------------------------*/
///
/// \brief  Hex to DWORD
///
/// \param  szHex   [I ] Hex string
///
/// \return DWORD value
///
LIBALT_API DWORD altHexToDWORD(const altChar * szHex);

///
/// \brief  fputs
///
/// \param  szStr [I ] String
/// \param  pFile [I ] FILE pointer
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_WRITE   write error
/// \return ALT_E_INVAL   invalid paramter
///
LIBALT_API alt_t altFPuts(const altChar * szData, FILE * pFile);

#endif
