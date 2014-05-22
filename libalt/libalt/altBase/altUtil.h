#ifndef ALTUTIL_H
#define ALTUTIL_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altUtil.h
 * \brief   Utility functions
 * \date    2013
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <alt_wrapper/alt_string.h>
#include <alt_wrapper/alt_io.h>
#include <altBase/altStr.h>

#ifdef ALT_WIN
  #include <share.h>  // for _SH_DENYNO
#endif

#ifdef ALT_WIN
  #include <direct.h>
  #include <share.h>  // for _SH_DENYNO
#endif

#include <stdarg.h>

/*----------------------------------------------------------------*
 * Function Declare
 *----------------------------------------------------------------*/

/**
 * \brief sleep
 *
 * \param msec  [I ] sleep miliseconds
 */
LIBALT_API void altSleep (
  const DWORD msec
);


/**
 * \brief create directory
 *
 * \param sDirName  [I ] directory name
 * \param mode      [I ] directory permission
 *
 * \return true   success
 * \return false  error
 */
LIBALT_API inline const altBool altMkDir (
  const altStr &  sDirName,
  const mode_t    mode = 0777
)
{
  return (alt_mkdir (sDirName.GetCStr(), mode));
}


/**
 * \brief create directory recursive
 *
 * \param szDirName  [I ] directory name
 *
 * \return true   success
 * \return false  error
 */
LIBALT_API const altBool altMkDirR (
  const altChar * szDirPath
);

///
/// \brief	open file
///
/// \param	szFileName	[I ] file name
/// \param	szMode		  [I ] open mode
/// \param	pFile		    [ O] pointer of file stream
///
LIBALT_API inline void altFOpen (
  const altChar * szFileName,
  const altChar * szMode,
  FILE * &        pFile
)
{
#ifdef ALT_WIN
	pFile = _fsopen (szFileName, szMode, _SH_DENYNO);
#endif

#ifdef ALT_LINUX
	pFile = fopen (szFileName, szMode);
#endif
}

#ifdef ALT_WIN

/**
 * \brief format string
 *
 * \param pBuf      [IO] buffer
 * \param nBufSize  [I ] buffer size
 * \param szFormat  [I ] format
 * \param oArgs     [I ] arguments
 *
 * \return  string length
 */
LIBALT_API inline const altInt altVswnprintf (
  altWChar *        pBuf,
  const altUInt     nBufSize,
  const wchar_t *   szFormat,
  va_list &         oArgs
)
{
  return vswprintf_s ((wchar_t *)pBuf, nBufSize, szFormat, oArgs);
}
#endif

///
/// \brief  Get wide string length
///
/// \param  szWStr  [I ] Wide string
///
/// \return Wide string length
///
altUInt altWStrLen (
  const altWChar *  szWStr
);


/**
 * \brief Copy wide string
 *
 * \param pDst  [ O] output
 * \param pSrc  [I ] source string
 * \param nSize [I ] string size
 */
LIBALT_API void altWStrncpy (
  altWChar *        pDst,
  const altWChar *  pSrc,
  const altUInt     nSize
);

#endif

