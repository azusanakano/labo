/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMem.cpp
 * \brief   Memory functions
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altMem.h"
#include "altStr.h"
#include "altStatus.h"

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Structure Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Groable variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Static variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Static Function Declare
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
/**
 * \brief allocate memory
 *
 * \param p           [ O] allocated memory
 * \param nSize       [I ] size(Byte)
 * \param szFilename  [I ] file name
 * \param nLine       [I ] line number
 *
 * \return ALT_S_SUCCESS   success
 * \return ALT_E_NOMEM     not enough memory
 * \return ALT_E_INVAL     invalid arguments
 * \return ALT_E_MAXLIMIT  over max limit
 *
 * this function is required that p should be NULL.
 * When the above-mentioned conditions are not fulfilled, this function 
 * goes wrong and returns ALT_E_INVAL.
 *
 * ALT_E_MAXLIMIT is returned when there is a demand which surpasses the 
 * maximum memory size set up.
 *
 */
LIBALT_API alt_t altMalloc (
  altChar * &     p,
  const altUInt   nSize,
  const altChar * szFilename,
  const altUInt   nLine
)
{
  altStr sBuf;
  altInt nRet = altBaseMalloc (p, nSize, szFilename, nLine);
  switch (nRet) {
    case  ALT_NOMEM:
      ALT_RET_P (ALT_E_NOMEM, sBuf.Format ("%s nSize=%u", altMemErrStr (nRet), nSize));
    case ALT_INVAL:
      ALT_RET_P (ALT_E_INVAL, sBuf.Format ("%s p=0x%X", altMemErrStr (nRet), p));
    case ALT_MAXLIMIT:
      ALT_RET_P (ALT_E_MAXLIMIT, sBuf.Format ("%s nSize=%u max_size=%u", altMemErrStr (nRet), nSize, altMemGetMaxLimitSize()));
  }

  ALT_RET (ALT_S_SUCCESS);
}

/**
 * \brief allocate duplicated memory
 *
 * \param pDst        [ O] allocated memory
 * \param pSrc        [I ] source memory
 * \param nSize       [I ] size
 * \param szFilename  [I ] file name
 * \param nLine       [I ] line number
 *
 * \return ALT_S_SUCCESS   success
 * \return ALT_E_NOMEM     not enough memory
 * \return ALT_E_INVAL     invalid arguments
 * \return ALT_E_MAXLIMIT  over max limit
 */
LIBALT_API alt_t altDupAlloc (
  altChar * &       pDst,
  const altChar *   pSrc,
  const altUInt     nSize,
  const altChar *   szFilename,
  const altUInt     nLine
)
{
  altStr sBuf;
  altInt nRet = altBaseDupAlloc (pDst, pSrc, nSize, szFilename, nLine);
  switch (nRet) {
    case  ALT_NOMEM:
      ALT_RET_P (ALT_E_NOMEM, sBuf.Format ("%s nSize=%u", altMemErrStr (nRet), nSize));
    case ALT_INVAL:
      ALT_RET_P (ALT_E_INVAL, sBuf.Format ("%s p=0x%X", altMemErrStr (nRet), pDst));
    case ALT_MAXLIMIT:
      ALT_RET_P (ALT_E_MAXLIMIT, sBuf.Format ("%s nSize=%u max_size=%u", altMemErrStr (nRet), nSize, altMemGetMaxLimitSize()));
  }

  ALT_RET (ALT_S_SUCCESS);
}

/**
 * \brief free allocated memory
 *
 * \param p           [IO] allocated memory
 * \param szFilename  [I ] file name
 * \param nLine       [I ] line number
 *
 * \return ALT_S_SUCCESS   success
 * \return ALT_E_INVAL     invalid arguments
 */
LIBALT_API alt_t altFree (
  void * &        p,
  const altChar * szFilename,
  const altUInt   nLine
)
{
  altStr sBuf;
  altInt nRet = altBaseFree (p, szFilename, nLine);
  switch (nRet) {
    case ALT_INVAL:
      ALT_RET_P (ALT_E_INVAL, sBuf.Format ("%s p=0x%X", altMemErrStr (nRet), p));
  }

  ALT_RET (ALT_S_SUCCESS);
}

/**
 * \brief extend allocate memory
 *
 * \param p           [ O] allocated memory
 * \param nNowSize    [I ] now size
 * \param nNewSize    [I ] new size
 * \param szFilename  [I ] file name
 * \param nLine       [I ] line number
 *
 * \return ALT_S_SUCCESS   success
 * \return ALT_E_NOMEM     not enough memory
 * \return ALT_E_INVAL     invalid arguments
 * \return ALT_E_MAXLIMIT  over max limit
 */
LIBALT_API alt_t altExAlloc (
  altChar * &       p,
  const altUInt     nNowSize,
  const altUInt     nNewSize,
  const altChar *   szFilename,
  const altUInt     nLine
)
{
  altStr sBuf;
  altInt nRet = altBaseExAlloc (p, nNowSize, nNewSize, szFilename, nLine);
  switch (nRet) {
    case  ALT_NOMEM:
      ALT_RET_P (ALT_E_NOMEM, sBuf.Format ("%s nNowSize=%u nNewSize=%u", altMemErrStr (nRet), nNowSize, nNewSize));
    case ALT_INVAL:
      ALT_RET_P (ALT_E_INVAL, sBuf.Format ("%s p=0x%X", altMemErrStr (nRet), p));
    case ALT_MAXLIMIT:
      ALT_RET_P (ALT_E_MAXLIMIT, sBuf.Format ("%s nNowSize=%u nNewSize=%u max_size=%u", altMemErrStr (nRet), nNowSize, nNewSize, altMemGetMaxLimitSize()));
  }

  ALT_RET (ALT_S_SUCCESS);
}

/**
 * \brief allocate string memory
 *
 * \param pDst        [ O] allocated string
 * \param pSrc        [I ] source string
 * \param szFilename  [I ] file name
 * \param nLine       [I ] line number
 *
 * \return ALT_S_SUCCESS    success
 * \return ALT_E_NOMEM      not enough memory
 * \return ALT_E_INVAL      invalid arguments
 * \return ALT_E_MAXLIMIT   over max limit
 */
LIBALT_API alt_t altStrAlloc (
  altChar * &       pDst,
  const altChar *   pSrc,
  const altChar *   szFilename,
  const altUInt     nLine
)
{
  altStr sBuf;
  altInt nRet = altBaseStrAlloc (pDst, pSrc, szFilename, nLine);
  switch (nRet) {
    case  ALT_NOMEM:
      ALT_RET_P (ALT_E_NOMEM, sBuf.Format ("%s", altMemErrStr (nRet)));
    case ALT_INVAL:
      ALT_RET_P (ALT_E_INVAL, sBuf.Format ("%s pDst=0x%X", altMemErrStr (nRet), pDst));
    case ALT_MAXLIMIT:
      ALT_RET_P (ALT_E_MAXLIMIT, sBuf.Format ("%s MaxLimitSize=%u", altMemErrStr (nRet), altMemGetMaxLimitSize()));
  }

  ALT_RET (ALT_S_SUCCESS);
}

/**
 * \brief allocate string memory
 *
 * \param pDst        [ O] allocated string
 * \param pSrc        [I ] source string
 * \param nSize       [I ] size
 * \param szFilename  [I ] file name
 * \param nLine       [I ] line number
 *
 * \return ALT_S_SUCCESS    success
 * \return ALT_E_NOMEM      not enough memory
 * \return ALT_E_INVAL      invalid arguments
 * \return ALT_E_MAXLIMIT   over max limit
 */
LIBALT_API alt_t altStrnAlloc (
  altChar * &       pDst,
  const altChar *   pSrc,
  const altUInt     nSize,
  const altChar *   szFilename,
  const altUInt     nLine
)
{
  altStr sBuf;
  altInt nRet = altBaseStrnAlloc (pDst, pSrc, nSize, szFilename, nLine);
  switch (nRet) {
    case  ALT_NOMEM:
      ALT_RET_P (ALT_E_NOMEM, sBuf.Format ("%s", altMemErrStr (nRet)));
    case ALT_INVAL:
      ALT_RET_P (ALT_E_INVAL, sBuf.Format ("%s pDst=0x%X", altMemErrStr (nRet), pDst));
    case ALT_MAXLIMIT:
      ALT_RET_P (ALT_E_MAXLIMIT, sBuf.Format ("%s max_size=%u", altMemErrStr (nRet), altMemGetMaxLimitSize()));
  }

  ALT_RET (ALT_S_SUCCESS);
}

/**
 * \brief concatenate allocate strings
 *
 * \param pDst        [IO] allocated string
 * \param pSrc        [I ] concatenate string
 * \param szFilename  [I ] file name
 * \param nLine       [I ] line number
 *
 * \return ALT_S_SUCCESS    success
 * \return ALT_E_NOMEM      not enough memory
 * \return ALT_E_INVAL      invalid arguments
 * \return ALT_E_MAXLIMIT   over max limit
 */
LIBALT_API alt_t altStrAllocCat (
  altChar * &       pDst,
  const altChar *   pSrc,
  const altChar *   szFilename,
  const altUInt     nLine
)
{
  altStr sBuf;
  altInt nRet = altBaseStrAllocCat (pDst, pSrc, szFilename, nLine);
  switch (nRet) {
    case  ALT_NOMEM:
      ALT_RET_P (ALT_E_NOMEM, sBuf.Format ("%s", altMemErrStr (nRet)));
    case ALT_INVAL:
      ALT_RET_P (ALT_E_INVAL, sBuf.Format ("%s pDst=0x%X", altMemErrStr (nRet), pDst));
    case ALT_MAXLIMIT:
      ALT_RET_P (ALT_E_MAXLIMIT, sBuf.Format ("%s max_size=%u", altMemErrStr (nRet), altMemGetMaxLimitSize()));
  }

  ALT_RET (ALT_S_SUCCESS);
}


/**
 * \brief concatenate allocate binary data
 *
 * \param pDst        [IO] allocated binary data
 * \param pSrc        [I ] concatenate binary data
 * \param nSrcSize    [I ] concatenate binary data size
 * \param szFilename  [I ] file name
 * \param nLine       [I ] line number
 *
 * \return ALT_S_SUCCESS    success
 * \return ALT_E_NOMEM      not enough memory
 * \return ALT_E_INVAL      invalid arguments
 * \return ALT_E_MAXLIMIT   over max limit
 */
LIBALT_API alt_t altBinAllocCat (
  altByte * &       pDst,
  const altByte *   pSrc,
  const altUInt     nSrcSize,
  const altChar *   szFilename,
  const altUInt     nLine
)
{
  altStr sBuf;
  altInt nRet = altBaseBinAllocCat (pDst, pSrc, nSrcSize, szFilename, nLine);
  switch (nRet) {
    case  ALT_NOMEM:
      ALT_RET_P (ALT_E_NOMEM, sBuf.Format ("%s", altMemErrStr (nRet)));
    case ALT_INVAL:
      ALT_RET_P (ALT_E_INVAL, sBuf.Format ("%s pDst=0x%X", altMemErrStr (nRet), pDst));
    case ALT_MAXLIMIT:
      ALT_RET_P (ALT_E_MAXLIMIT, sBuf.Format ("%s max_size=%u", altMemErrStr (nRet), altMemGetMaxLimitSize()));
  }

  ALT_RET (ALT_S_SUCCESS);
}
