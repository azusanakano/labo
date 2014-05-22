/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altBzip2.cpp
 * \brief   bzip2 compress class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altBzip2.h"
#include "altBase/altMem.h"
#include "altBase/altStatus.h"

#ifdef ALT_WIN
  #include <bzip2/bzlib.h>
#endif

#ifdef ALT_LINUX
  #include <bzlib.h>
#endif

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altBzip2::altBzip2()
{
}

///
/// \brief  Destructor
///
LIBALT_API altBzip2::~altBzip2()
{
}

///
/// \brief  Compress
///
/// \param  pData   [IO] Data
/// \param  nLen    [IO] Data Length
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_NOMEM     Out of memory
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altBzip2::Compress(altChar * & pData, altUInt & nLen)
{
  alt_t     status;
  altChar * pOut = NULL;

retry:
  status = ALT_MALLOC (pOut, nLen);
  ALT_ERR_RET (status);

  status = Compress (pOut, nLen, pData, nLen);
  ALT_ERR_RET (status);

  if (status == ALT_S_OUTBUFFER_FULL) {
    ALT_FREE (pOut);
    nLen *= 2;
    goto retry;
  }

  if (status == ALT_S_SUCCESS) {
    ALT_FREE (pData);
    pData = pOut;
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Decompress
///
/// \param  pData   [IO] Data
/// \param  nLen    [IO] Data Length
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_NOMEM     Out of memory
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altBzip2::Decompress(altChar * & pData, altUInt & nLen)
{
  alt_t       status;
  altChar *   pOut = NULL;
  altUInt     nOutLen = nLen * 10;

retry:
  status = ALT_MALLOC (pOut, nOutLen);
  ALT_ERR_RET (status);

  status = Decompress (pOut, nOutLen, pData, nLen);
  ALT_ERR_RET (status);

  if (status == ALT_S_OUTBUFFER_FULL) {
    ALT_FREE (pOut);
    nOutLen *= 2;
    goto retry;
  }

  if (status == ALT_S_SUCCESS) {
    ALT_FREE (pData);
    pData = pOut;
    nLen = nOutLen;
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Compress
///
/// \param  pDst    [ O] Data
/// \param  nDstLen [ O] Data Length
/// \param  pSrc    [I ] Data
/// \param  nSrcLen [I ] Data Length
///
/// \return ALT_S_SUCCESS         Success
/// \return ALT_S_OUTBUFFER_FULL  Out Buffer Full
/// \return ALT_E_ERROR           Error
///
LIBALT_API alt_t altBzip2::Compress(altChar * pDst, altUInt nDstLen, altChar * pSrc, altUInt nSrcLen)
{
  altInt nRet = BZ2_bzBuffToBuffCompress (pDst, & nDstLen, pSrc, nSrcLen, 1, 0, 30);
  if (nRet == BZ_OUTBUFF_FULL) {
    ALT_RET (ALT_S_OUTBUFFER_FULL);
  }
  else if (nRet != BZ_OK) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("Error NO = %d", nRet));
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Decompress
///
/// \param  pDst    [ O] Data
/// \param  nDstLen [ O] Data Length
/// \param  pSrc    [I ] Data
/// \param  nSrcLen [I ] Data Length
///
/// \return ALT_S_SUCCESS         Success
/// \return ALT_S_NOCOMPRESS      No Compress
/// \return ALT_S_OUTBUFFER_FULL  Out Buffer Full
/// \return ALT_E_ERROR           Error
///
LIBALT_API alt_t altBzip2::Decompress(altChar * pDst, altUInt nDstLen, altChar * pSrc, altUInt nSrcLen)
{
  altInt nRet = BZ2_bzBuffToBuffDecompress (pDst, & nDstLen, pSrc, nSrcLen, 0, 0);
  if (nRet != BZ_OK) {
    if (nRet == BZ_OUTBUFF_FULL) {
      ALT_RET (ALT_S_OUTBUFFER_FULL);
    }

    if (nRet == BZ_DATA_ERROR_MAGIC) {
      ALT_RET (ALT_S_NOCOMPRESS);
    }

    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("Error NO = %d", nRet));
  }

  ALT_RET (ALT_S_SUCCESS);
}

