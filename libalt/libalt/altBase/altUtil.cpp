/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altUtil.cpp
 * \brief   Utility functions
 * \date    2013
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altUtil.h"
#include "altStr.h"

#ifdef ALT_WIN
#endif

#ifdef ALT_LINUX
  #include <time.h>
  #include <sys/stat.h>   // for mkdir
  #include <sys/types.h>  // for mkdir
  #include <fcntl.h>      // for O_RDWR
#endif

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
/**
 * \brief sleep
 *
 * \param msec  [I ] sleep milliseconds
 */
LIBALT_API void altSleep (
  const DWORD dwMilliseconds
)
{
#ifdef ALT_WIN
  Sleep (dwMilliseconds);
#endif

#ifdef ALT_LINUX
  struct timespec oReq;
  struct timespec oRem;

  oReq.tv_sec = dwMilliseconds / 1000;
  oReq.tv_nsec = (dwMilliseconds % 1000) * 100000;

  altInt nRet = nanosleep (& oReq, & oRem);
  while (nRet != 0) {
    nRet = nanosleep (& oRem, & oRem);
  }
#endif
}


/**
 * \brief create directory recursive
 *
 * \param szDirName  [I ] directory name
 *
 * \return 0  success
 * \return -1 error
 */
LIBALT_API const altBool altMkDirR (
  const altChar * szDirName
)
{
  altStr  sDir;
  altStr  sDirName = szDirName;
  altInt  nIndex = sDirName.FindChar ("\\/");

  while (nIndex > 0) {
    // create directory
    sDir = sDirName.SubStr (0, nIndex - 1);
    altMkDir (sDir.GetCStr());
    nIndex = sDirName.FindChar (nIndex + 1, "\\/");
  }

  // create directory
  if (! altMkDir (szDirName)) {
    return (false);
  }
 
  return (true);
}

///
/// \brief  Get wide string length
///
/// \param  szWStr  [I ] Wide string
///
/// \return Wide string length
///
altUInt altWStrLen (
  const altWChar *  szWStr
)
{
  if (szWStr == NULL) {
    return (0);
  }
  altUInt nLen = 0;
  while (szWStr[nLen] != 0x0000) {
    nLen++;
  }
  return (nLen);
}


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
)
{
  if (pDst == NULL) {
    return;
  }
  if (pSrc == NULL) {
    return;
  }
  if (nSize == 0) {
    return;
  }
  for (altUInt i = 0; i < nSize; i++) {
    if (pSrc[i] == 0x0000) {
      pDst[i] = 0x0000;
      break;
    }
    pDst[i] = pSrc[i];
  }
  pDst[nSize - 1] = 0x0000;
}
