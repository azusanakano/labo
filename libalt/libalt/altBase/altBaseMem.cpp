/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altBaseMem.cpp
 * \brief   Memory functions
 * \date    2013
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altBaseMem.h"
#include "altMemManager.h"
#include "altUtil.h"
#include "alt_wrapper/alt_cast.h"
#include <malloc.h>
#include <map>

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
static altAllocHandleFunc                 st_pAllocHandler = NULL;              ///< memory allocation handler
static altAllocFailedHandleFunc           st_pAllocFailedHander = NULL;         ///< memory allocation failed handler
static altFreeHandleFunc                  st_pFreeHandler = NULL;               ///< memory free handler
static altMemOverWriteDetectedHandleFunc  st_pOverWriteDetectedHandler = NULL;  ///< memory over write detected handler

/*----------------------------------------------------------------*
 * Static Function Declare
 *----------------------------------------------------------------*/
/**
 * Find the length of a length-limited string
 *
 * \param szStr [I ] string
 * \param nSize [I ] size
 *
 * \return length
 */
static altInt altMemStrnLen (
  const altChar *   szStr,
  const altUInt     nSize
);

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
 * \return ALT_SUCCESS   success
 * \return ALT_NOMEM     not enough memory
 * \return ALT_INVAL     invalid arguments
 * \return ALT_MAXLIMIT  over max limit
 *
 * this function is required that p should be NULL.
 * When the above-mentioned conditions are not fulfilled, this function 
 * goes wrong and returns AM_INVAL.
 *
 * AM_MAXLIMIT is returned when there is a demand which surpasses the 
 * maximum memory size set up.
 *
 */
LIBALT_API altInt altBaseMalloc (
  altChar * &     p,
  const altUInt   nSize,
  const altChar * szFilename,
  const altUInt   nLine
)
{
  altChar *     pNewPtr;

  // check paramter
  if (p != NULL) {
    return (ALT_INVAL);
  }
  if (nSize == 0) {
    return (ALT_SUCCESS);
  }

  altUInt       nRealSize;
  altMemInfo    oMemInfo;

  // check max limit
  if (aiMemManager.OverLimitSize (nSize)) {
    if (st_pAllocFailedHander != NULL) {
      (st_pAllocFailedHander) (szFilename, nLine, nSize, ALT_MAXLIMIT);
    }
    return (ALT_MAXLIMIT);
  }

  // Init memory infomation
  oMemInfo.Init (nSize, szFilename, nLine);

  // allocate memory
  nRealSize = oMemInfo.GetRealSize();
  pNewPtr = (altChar *)malloc (nRealSize);
  if (pNewPtr == NULL) {
    if (st_pAllocFailedHander != NULL) {
      (st_pAllocFailedHander) (szFilename, nLine, nSize, ALT_NOMEM);
    }
    return (ALT_NOMEM);
  }
  oMemInfo.m_pAddr = pNewPtr + oMemInfo.GetInfoSize();
  oMemInfo.Write (pNewPtr);
  p = alt_cast2_char_p (oMemInfo.m_pAddr);

  // Add memory infomation
  aiMemManager.Add (pNewPtr, alt_cast2_c_char_p (p));

  if (st_pAllocHandler != NULL) {
    (st_pAllocHandler) (oMemInfo);
  }

  return (ALT_SUCCESS);
}

/**
 * \brief free allocated memory
 *
 * \param p           [IO] allocated memory
 * \param szFilename  [I ] file name
 * \param nLine       [I ] line number
 *
 * \return ALT_SUCCESS   success
 * \return ALT_INVAL     invalid arguments
 */
LIBALT_API altInt altBaseFree (
  void * &          p,
  const altChar *   szFilename,
  const altUInt     nLine
)
{
  altMemInfo  oMemInfo;

  // check paramter
  if (p == NULL) {
    return (ALT_SUCCESS);
  }

  const void * pRealPtr = NULL;
  pRealPtr = aiMemManager.GetRealPtr ((const altChar *)p);
  oMemInfo.Read (pRealPtr);

  // check magic number
  if (oMemInfo.m_cMagic != altMemInfo::ALT_MEM_MAGIC) {
    return (ALT_INVAL);
  }

  // check memory end signature
  if (oMemInfo.OverWriteDetected()) {

    // If over write detecter function was setting, call handler function.
    if (st_pOverWriteDetectedHandler != NULL) {
      (st_pOverWriteDetectedHandler) (oMemInfo, szFilename, nLine);
    }
  }

  aiMemManager.Del (alt_cast2_c_char_p (p));
  // clear memory
  altUInt nRealSize = oMemInfo.GetRealSize();
  memset ((void *)pRealPtr, ALT_MEM_GARBEGE, nRealSize);

  // free memory
  free (alt_cast2_void_p (pRealPtr));
  p = NULL;

  if (st_pFreeHandler != NULL) {
    (st_pFreeHandler) (oMemInfo, szFilename, nLine);
  }

  return (ALT_SUCCESS);
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
 * \return ALT_SUCCESS   success
 * \return ALT_NOMEM     not enough memory
 * \return ALT_INVAL     invalid arguments
 * \return ALT_MAXLIMIT  over max limit
 */
LIBALT_API altInt altBaseDupAlloc (
  altChar * &       pDst,
  const altChar *   pSrc,
  const altUInt     nSize,
  const altChar *   szFilename,
  const altUInt     nLine
)
{
  altInt status;

  if ((status = altBaseMalloc (pDst, nSize, szFilename, nLine)) != ALT_SUCCESS) {
    return (status);
  }

  memcpy (pDst, pSrc, nSize);
  return (ALT_SUCCESS);
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
 * \return ALT_SUCCESS   success
 * \return ALT_NOMEM     not enough memory
 * \return ALT_INVAL     invalid arguments
 * \return ALT_MAXLIMIT  over max limit
 */
LIBALT_API altInt altBaseExAlloc (
  altChar * &       p,
  const altUInt     nNowSize,
  const altUInt     nNewSize,
  const altChar *   szFilename,
  const altUInt     nLine
)
{
  altInt    status = ALT_SUCCESS;
  altChar * pNew = NULL;

  // check paramter(size)
  if (nNowSize > nNewSize) {
    return (ALT_INVAL);
  }

  // check validation signiture
  if (p != NULL && (! altMemValidate (p))) {
      return (ALT_INVAL);
  }

  // check memory size
  if (nNowSize != aiMemManager.GetUserSize (alt_cast2_c_char_p (p))) {
      return (ALT_INVAL);
  }

  try {
    // allocate new memory
    if ((status = altBaseMalloc (pNew, nNewSize, szFilename, nLine)) != ALT_SUCCESS) {
      throw new std::exception();
    }

    if (p != NULL) {
      // copy data to new memory
      memcpy (pNew, p, nNowSize);

      // free old memory
      if ((status = altBaseFree (alt_cast2_void_p_ref (p), szFilename, nLine)) != ALT_SUCCESS) {
        throw new std::exception();
      }
    }
    p = pNew;
  }
  catch (...) {
    // If new memory allocated, free it.
    if (pNew != NULL) {
      altBaseFree (alt_cast2_void_p_ref (pNew), szFilename, nLine);
    }
    return (status);
  }

  return (ALT_SUCCESS);
}

/**
 * \brief allocate string memory
 *
 * \param pDst        [ O] allocated string
 * \param pSrc        [I ] source string
 * \param szFilename  [I ] file name
 * \param nLine       [I ] line number
 *
 * \return ALT_SUCCESS    success
 * \return ALT_NOMEM      not enough memory
 * \return ALT_INVAL      invalid arguments
 * \return ALT_MAXLIMIT   over max limit
 */
LIBALT_API altInt altBaseStrAlloc (
  altChar * &       pDst,
  const altChar *   pSrc,
  const altChar *   szFilename,
  const altUInt     nLine
)
{
  altInt  status;
  altUInt nLen;

  // check paramter
  if (pSrc == NULL) {
    return (ALT_INVAL);
  }

  nLen = (altUInt)strlen (pSrc) + 1;
  if ((status = altBaseMalloc (pDst, nLen, szFilename, nLine)) != ALT_SUCCESS) {
    return (status);
  }

  alt_strncpy (pSrc, nLen, pDst);
  return (ALT_SUCCESS);
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
 * \return ALT_SUCCESS    success
 * \return ALT_NOMEM      not enough memory
 * \return ALT_INVAL      invalid arguments
 * \return ALT_MAXLIMIT   over max limit
 */
LIBALT_API altInt altBaseStrnAlloc (
  altChar * &       pDst,
  const altChar *   pSrc,
  const altUInt     nSize,
  const altChar *   szFilename,
  const altUInt     nLine
)
{
  altInt  status;
  altUInt nLen;

  /* check paramter */
  if (pSrc == NULL) {
    return (ALT_INVAL);
  }

  nLen = (altMemStrnLen (pSrc, nSize) + 1);
  if ((status = altBaseMalloc (pDst, nLen, szFilename, nLine)) != ALT_SUCCESS) {
    return (status);
  }

  alt_strncpy (pSrc, nLen, pDst);
  return (ALT_SUCCESS);
}

/**
 * \brief concatenate allocate strings
 *
 * \param pDst        [IO] allocated string
 * \param pSrc        [I ] concatenate string
 * \param szFilename  [I ] file name
 * \param nLine       [I ] line number
 *
 * \return ALT_SUCCESS    success
 * \return ALT_NOMEM      not enough memory
 * \return ALT_INVAL      invalid arguments
 * \return ALT_MAXLIMIT   over max limit
 */
LIBALT_API altInt altBaseStrAllocCat (
  altChar * &       pDst,
  const altChar *   pSrc,
  const altChar *   szFilename,
  const altUInt     nLine
)
{
  altInt  status;
  altUInt nDstLen;

  // check paramter
  if (pSrc == NULL) {
    return (ALT_INVAL);
  }

  if (pDst == NULL) {
    nDstLen = 0;
  }
  else {
    nDstLen = (altUInt)strlen (pDst);
  }

  altUInt nSrcLen = (altUInt)strlen (pSrc);
  altUInt nNowSize = nDstLen + 1;
  altUInt nNewSize = nDstLen + nSrcLen + 1;

  status = altBaseExAlloc (pDst, nNowSize, nNewSize, szFilename, nLine);
  if (status != ALT_SUCCESS) {
    return (status);
  }

  alt_strncat (pDst, nNewSize, pSrc, nSrcLen);
  return (ALT_SUCCESS);
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
 * \return ALT_SUCCESS    success
 * \return ALT_NOMEM      not enough memory
 * \return ALT_INVAL      invalid arguments
 * \return ALT_MAXLIMIT   over max limit
 */
LIBALT_API altInt altBaseBinAllocCat (
  altByte * &       pDst,
  const altByte *   pSrc,
  const altUInt     nSrcSize,
  const altChar *   szFilename,
  const altUInt     nLine
)
{
  altInt  status;
  altUInt nDstLen;

  // check paramter
  if (pSrc == NULL) {
    return (ALT_INVAL);
  }

  if (pDst == NULL) {
    nDstLen = 0;
  }
  else {
    altMemSize ((const altChar *)pDst, nDstLen);
  }

  altUInt nNowSize = nDstLen;
  altUInt nNewSize = nDstLen + nSrcSize;

  status = altBaseExAlloc ((altChar * &)pDst, nNowSize, nNewSize, szFilename, nLine);
  if (status != ALT_SUCCESS) {
    return (status);
  }

  memcpy (& pDst[nDstLen], pSrc, nSrcSize);
  return (ALT_SUCCESS);
}


/**
 * \brief allocate wide string memory
 *
 * \param pDst        [ O] allocated string
 * \param pSrc        [I ] source string
 * \param szFilename  [I ] file name
 * \param nLine       [I ] line number
 *
 * \return ALT_SUCCESS    success
 * \return ALT_NOMEM      not enough memory
 * \return ALT_INVAL      invalid arguments
 * \return ALT_MAXLIMIT   over max limit
 */
LIBALT_API altInt altBaseWStrAlloc (
  altWChar * &      pDst,
  const altWChar *  pSrc,
  const altChar *   szFilename,
  const altUInt     nLine
)
{
  altInt  status;
  altUInt nSize;

  // check paramter
  if (pSrc == NULL) {
    return (ALT_INVAL);
  }

  nSize = (altWStrLen (pSrc) + 1) * sizeof (altWChar);
  if ((status = altBaseDupAlloc ((altChar * &)pDst, (const altChar *)pSrc, nSize, szFilename, nLine)) != ALT_SUCCESS) {
    return (status);
  }

  return (ALT_SUCCESS);
}

/**
 * \brief get memory size
 *
 * \param pAddr [I ] pointer of memory
 * \param nSize [ O] allocated size
 *
 * \return ALT_SUCCESS  success
 * \return ALT_INVAL    invalid arguments
 */
LIBALT_API altInt altMemSize (
  const altChar *   pAddr,
  altUInt &         nSize
)
{
  // check paramter
  if (pAddr == NULL) {
    return (ALT_INVAL);
  }

  const altChar * pRealPtr = aiMemManager.GetRealPtr ((const altChar *)pAddr);
  altMemInfo oMemInfo;
  oMemInfo.Read (pRealPtr);

  // check magic number
  if (oMemInfo.m_cMagic != altMemInfo::ALT_MEM_MAGIC) {
    return (ALT_INVAL);
  }

  nSize = oMemInfo.m_nSize;

  return (ALT_SUCCESS);
}

/**
 * \brief validate memory 
 *
 * \param pAddr    [I ] pointer of memory
 *
 * \return success  true
 * \return error    false
 */
LIBALT_API altBool altMemValidate (
  const altChar *  pAddr
)
{
  if (pAddr == NULL) {
    return (false);
  }
  
  const altChar * pRealPtr = aiMemManager.GetRealPtr ((const altChar *)pAddr);
  if (pRealPtr == NULL) {
    return (false);
  }

  altMemInfo oMemInfo;
  oMemInfo.Read (pRealPtr);

  if (oMemInfo.m_cMagic != altMemInfo::ALT_MEM_MAGIC) {
    return (false);
  }

  return (true);
}

/**
 * \brief Get error string
 *
 * \param nErrCode    [I ] error code
 *
 * \return error string
 */
LIBALT_API const altChar * altMemErrStr (
  const altInt nErrCode
)
{
  static const altChar * st_aStringTable[] = {
#define ENT(_c_, _m_) _m_
    ENT (AM_SUCCESS,          "success"),
    ENT (AM_INVAL,            "invalid paramter error"),
    ENT (AM_NOMEM,            "no enough memory"),
    ENT (AM_MAXLIMIT,         "over max limit"),
    ENT (AM_MANAGER_UNENABLE, "memory manager is unenable"),
    ENT (AM_INTERNAL,         "internal error"),
#undef ENT
  };
  static const altChar * szNone = "";

  if ((altUInt)nErrCode > ALT_ARRAY_SIZE (st_aStringTable)) {
    return (szNone);
  }
  return (st_aStringTable[nErrCode]);
}

/**
 * \brief Set allocation handler
 *
 * \param pHandleFunc       [I ] new handler address
 * \param ppPrevHandleFunc  [ O] previous handler address
 *
 * \return  ALT_SUCCESS  success
 *
 * p_handle ... A NULL value is permitted.
 * pp_prev_handle ... A NULL value is permitted.
 *
 */
LIBALT_API altInt altSetAllocHandler (
  altAllocHandleFunc    pHandleFunc,
  altAllocHandleFunc *  ppPrevHandleFunc
)
{
  if (ppPrevHandleFunc != NULL) {
    (* ppPrevHandleFunc) = st_pAllocHandler;
  }
  st_pAllocHandler = pHandleFunc;
  return (ALT_SUCCESS);
}

/**
 * \brief Set allocation failed handler
 *
 * \param pHandleFunc       [I ] new handler address
 * \param ppPrevHandleFunc  [ O] previous handler address
 *
 * \return  ALT_SUCCESS  success
 *
 * p_handle ... A NULL value is permitted.
 * pp_prev_handle ... A NULL value is permitted.
 *
 */
LIBALT_API altInt altSetAllocFailedHandler (
  altAllocFailedHandleFunc    pHandleFunc,
  altAllocFailedHandleFunc *  ppPrevHandleFunc
)
{
  if (ppPrevHandleFunc != NULL) {
    (* ppPrevHandleFunc) = st_pAllocFailedHander;
  }
  st_pAllocFailedHander = pHandleFunc;
  return (ALT_SUCCESS);
}

/**
 * \brief Set free handler
 *
 * \param pHandleFunc       [I ] new handler address
 * \param ppPrevHandleFunc  [ O] previous handler address
 *
 * \return  ALT_SUCCESS  success
 *
 * pHandleFunc ... A NULL value is permitted.
 * ppPrevHandleFunc ... A NULL value is permitted.
 *
 */
LIBALT_API altInt altSetFreeHandler (
  altFreeHandleFunc    pHandleFunc,
  altFreeHandleFunc *  ppPrevHandleFunc
)
{
  if (ppPrevHandleFunc != NULL) {
    (* ppPrevHandleFunc) = st_pFreeHandler;
  }
  st_pFreeHandler = pHandleFunc;
  return (ALT_SUCCESS);
}

/**
 * \brief Set memory over write detected handler
 *
 * \param pHandleFunc       [I ] new handler address
 * \param ppPrevHandleFunc  [ O] previous handler address
 *
 * \return  ALT_SUCCESS  success
 *
 * pHandleFunc ... A NULL value is permitted.
 * ppPrevHandleFunc ... A NULL value is permitted.
 *
 */
LIBALT_API altInt altSetMemOverWriteDetectedHandler (
  altMemOverWriteDetectedHandleFunc    pHandleFunc,
  altMemOverWriteDetectedHandleFunc *  ppPrevHandleFunc
)
{
  if (ppPrevHandleFunc != NULL) {
    (* ppPrevHandleFunc) = st_pOverWriteDetectedHandler;
  }
  st_pOverWriteDetectedHandler = pHandleFunc;
  return (ALT_SUCCESS);
}

/*----------------------------------------------------------------*
 * Depend Memory Manager Functions
 *----------------------------------------------------------------*/
/**
 * \brief get allocating total memory size
 *
 * \return allocating memory size(Byte)
 *
 * - Depend on memory manager
 */
LIBALT_API altUInt altMemGetTotalSize()
{
  return (aiMemManager.GetTotalSize());
}

/**
 * \brief get allocating total real memory size
 *
 * \return allocating real memory size(Byte)
 *
 * this function return allocating memory size included manage infomation area
 *
 * - Depend on memory manager
 */
LIBALT_API altUInt altMemGetTotalRealSize ()
{
  return (aiMemManager.GetTotalRealSize());
}

/**
 * \brief get max allocate memory size
 *
 * \return max allocate limit size(byte)
 *
 * - Depend on memory manager
 */
LIBALT_API altUInt altMemGetMaxLimitSize ()
{
  return (aiMemManager.GetMaxAllocateLimitSize());
}

/**
 * \brief Get allocated block count
 *
 * \return allocated block count
 *
 * - Depend on memory manager
 */
LIBALT_API altUInt altMemGetBlockCount()
{
  return (aiMemManager.GetBlockCount());
}

/*----------------------------------------------------------------*
 * Static Function Implements
 *----------------------------------------------------------------*/
/**
 * Find the length of a length-limited string
 *
 * \param szStr [I ] string
 * \param nSize [I ] size
 *
 * \return length
 */
static altInt altMemStrnLen (
  const altChar *   szStr,
  const altUInt     nSize
)
{
  altUInt i;

  if (szStr == NULL) {
    return (0);
  }

  for (i = 0; i < nSize; i++) {
    if ((* szStr) == 0x00) {
      break;
    }
    szStr++;
  }
  return (i);
}

