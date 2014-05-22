#ifndef ALT_STRING_H
#define ALT_STRING_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    alt_string.h
 * \brief   String wrapper functions
 * \date    2013
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#include <stdarg.h>
#include <string.h>

/*----------------------------------------------------------------*
 * Function Declare
 *----------------------------------------------------------------*/

/**
 * \brief copy string
 *
 * \param pSrc  [I ] source string
 * \param nSize [I ] string size
 * \param pDst  [ O] output
 */
LIBALT_API inline void alt_strncpy (
  const altChar * pSrc,
  const altUInt   nSize,
  altChar *       pDst
)
{
#ifdef ALT_WIN
  strncpy_s (pDst, nSize, pSrc, nSize);
#else
  strncpy (pDst, pSrc, nSize);
#endif
}



/**
 * \brief add string
 *
 * \param pDst      [ O] output
 * \param nDstSize  [I ] output buffer size
 * \param pSrc      [I ] source string
 * \param nSize     [I ] string size
 */
LIBALT_API inline void alt_strncat (
  altChar *       pDst,
  const altUInt   nDstSize,
  const altChar * pSrc,
  const altUInt   nSize
)
{
#ifdef ALT_WIN
  strncat_s (pDst, nDstSize, pSrc, nSize);
#else
  strncat (pDst, pSrc, nSize);
#endif
}


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
LIBALT_API inline const altInt alt_vsnprintf (
  altChar *       pBuf,
  const altUInt   nBufSize,
  const altChar * szFormat,
  va_list &       oArgs
)
{
#ifdef ALT_WIN
  return vsnprintf_s (pBuf, nBufSize, _TRUNCATE, szFormat, oArgs);
#else
  return vsnprintf (pBuf, nBufSize, szFormat, oArgs);
#endif
}


#endif


