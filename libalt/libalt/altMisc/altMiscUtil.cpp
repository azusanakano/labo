/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMiscUtil.cpp
 * \brief   Utility functions class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altMiscUtil.h"
#include <errno.h>

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Hex to DWORD
///
/// \param  szHex   [I ] Hex string
///
/// \return DWORD value
///
LIBALT_API DWORD altHexToDWORD(const altChar * szHex)
{
  if (szHex == NULL) {
    return (0);
  }
  DWORD   dwVal = 0;
  DWORD   dwAdd = 1;
  altInt  nLen = (altInt)strlen (szHex);

  for (altInt i = nLen - 1; i >= 0; i--) {
    switch (szHex[i]) {
      case '0':
        dwVal += dwAdd * 0;
        break;
      case '1':
        dwVal += dwAdd * 1;
        break;
      case '2':
        dwVal += dwAdd * 2;
        break;
      case '3':
        dwVal += dwAdd * 3;
        break;
      case '4':
        dwVal += dwAdd * 4;
        break;
      case '5':
        dwVal += dwAdd * 5;
        break;
      case '6':
        dwVal += dwAdd * 6;
        break;
      case '7':
        dwVal += dwAdd * 7;
        break;
      case '8':
        dwVal += dwAdd * 8;
        break;
      case '9':
        dwVal += dwAdd * 9;
        break;
      case 'a':
      case 'A':
        dwVal += dwAdd * 10;
        break;
      case 'b':
      case 'B':
        dwVal += dwAdd * 11;
        break;
      case 'c':
      case 'C':
        dwVal += dwAdd * 12;
        break;
      case 'd':
      case 'D':
        dwVal += dwAdd * 13;
        break;
      case 'e':
      case 'E':
        dwVal += dwAdd * 14;
        break;
      case 'f':
      case 'F':
        dwVal += dwAdd * 15;
        break;
    }
    dwAdd *= 16;
  }
  return (dwVal);
}

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
LIBALT_API alt_t altFPuts(const altChar * szStr, FILE * pFile)
{
  ALT_P_ASSERT (szStr != NULL);
  ALT_P_ASSERT (pFile != NULL);

  altInt nRet = fputs (szStr, pFile);
  if (nRet == EOF) {
    altInt  nErrNo = errno;
    altStr  sBuf;
#ifdef ALT_WIN
    altChar szBuf[BUFSIZ];
    strerror_s (szBuf, sizeof (szBuf), nErrNo);
    ALT_RET_P (ALT_E_WRITE, sBuf.Format ("errno=%d (%s)", nErrNo, szBuf));
#endif
#ifdef ALT_LINUX
    ALT_RET_P (ALT_E_WRITE, sBuf.Format ("errno=%d (%s)", nErrNo, strerror (nErrNo)));
#endif
  }
  ALT_RET (ALT_S_SUCCESS);
}
