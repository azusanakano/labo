#ifndef ALTBASEMEM_H
#define ALTBASEMEM_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altBaseMem.h
 * \brief   Memory function
 * \date    2007
 * \author  Azusa Nakano
 */

/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altMemInfo.h>

/*--------------------------------------------------------------------*
 * Enumration
 *--------------------------------------------------------------------*/
enum
{
  ALT_SUCCESS = 0,       ///< success
  ALT_INVAL,             ///< invalid parameter error
  ALT_NOMEM,             ///< memory allocation error
  ALT_MAXLIMIT,          ///< over max limit error
  ALT_MANAGER_UNENABLE,  ///< memory manager unenable error
  ALT_INTERNAL,          ///< library internal error
};

/*--------------------------------------------------------------------*
 * Define
 *--------------------------------------------------------------------*/
#define ALT_BASE_MALLOC(p, size) \
  altBaseMalloc ((altChar * &)(p), (size), __FILE__, __LINE__)

#define ALT_BASE_DUPALLOC(d, s, size) \
  altBaseDupAlloc ((altChar * &)(d), (altChar *)(s), (size), __FILE__, __LINE__)

#define ALT_BASE_EXALLOC(d, nowsize, newsize) \
  altBaseExAlloc ((altChar * &)(d), (nowsize), (newsize), __FILE__, __LINE__)

#define ALT_BASE_STRALLOC(d, s) \
  altBaseStrAlloc ((altChar * &)(d), (altChar *)(s), __FILE__, __LINE__)

#define ALT_BASE_STRNALLOC(d, s, size) \
  altBaseStrnAlloc ((altChar * &)(d), (altChar *)(s), (size), __FILE__, __LINE__)

#define ALT_BASE_STRALLOC_CAT(d, s) \
  altBaseStrAllocCat ((altChar * &)(d), (altChar *)(s), __FILE__, __LINE__)

#define ALT_BASE_BINALLOC_CAT(d, sr, sz) \
  altBaseBinAllocCat ((altByte * &)(d), (const altByte *)(sr), (sz), __FILE__, __LINE__)

#define ALT_BASE_WSTRALLOC(d, s) \
  altBaseWStrAlloc ((altWChar * &)(d), (const altWChar *)(s), __FILE__, __LINE__)

#define ALT_BASE_FREE(p) \
  altBaseFree ((void * &)(p), __FILE__, __LINE__)

#define ALT_VALID_PTR(p) \
  (altMemValidate (p))

/*----------------------------------------------------------------*
 * Structure Definition
 *----------------------------------------------------------------*/
/**
 * \brief memory allocation handler
 *
 * [parameter]
 * 	const altMemInfo &	...	allocated address's memory management infomation
 */
typedef void (* altAllocHandleFunc) (const altMemInfo &);

/**
 * \brief memory allocation failed handler
 *
 * [parameter]
 *  const altChar * ... alloc called source file name
 *  const altUInt ... alloc called source file line number
 *  const altUInt ... alloc size
 *  const altInt  ... alloc failed reason number(ALT_NOMEM or ALT_MAXLIMIT)
 */
typedef void (* altAllocFailedHandleFunc) (const altChar *, const altUInt, const altUInt, const altInt);

/**
 * \brief memory free handler
 *
 * [parameter]
 * 	const altMemInfo &	...	freed address's memory management infomation
 * 	const altChar *	...	free called source file name
 * 	const altUInt	...	free called source file's line number
 */
typedef void (* altFreeHandleFunc) (const altMemInfo &, const altChar *, const altUInt);

/**
 * \brief memory end signature broken detected handler
 *
 * [parameter]
 * 	const altMemInfo &	...	freed address's memory management infomation
 * 	const altChar *	...	free called source file name
 * 	const altUInt	...	free called source file's line number
 */
typedef void (* altMemOverWriteDetectedHandleFunc) (const altMemInfo &, const altChar *, const altUInt);

/*----------------------------------------------------------------*
 * Function Declare
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
 * ALT_MAXLIMIT is returned when there is a demand which surpasses the 
 * maximum memory size set up.
 *
 */
LIBALT_API altInt altBaseMalloc (
  altChar * &     p,
  const altUInt   nSize,
  const altChar * szFilename,
  const altUInt   nLine
);


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
  void * &        p,
  const altChar * szFilename,
  const altUInt   nLine
);


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
);


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
);


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
);


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
);


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
);


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
);


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
);


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
);


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
);


/**
 * \brief Get error string
 *
 * \param nErrCode    [I ] error code
 *
 * \return error string
 */
LIBALT_API const altChar * altMemErrStr (
  const altInt nErrCode
);


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
  altAllocHandleFunc *  ppPrevHandleFunc = NULL
);


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
  altAllocFailedHandleFunc *  ppPrevHandleFunc = NULL
);


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
  altFreeHandleFunc *  ppPrevHandleFunc = NULL
);


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
  altMemOverWriteDetectedHandleFunc *  ppPrevHandleFunc = NULL
);

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
LIBALT_API altUInt altMemGetTotalSize();


/**
 * \brief get allocating total real memory size
 *
 * \return allocating real memory size(Byte)
 *
 * this function return allocating memory size included manage infomation area
 *
 * - Depend on memory manager
 */
LIBALT_API altUInt altMemGetTotalRealSize();


/**
 * \brief get max allocate memory size
 *
 * \return max allocate limit size(byte)
 *
 * - Depend on memory manager
 */
LIBALT_API altUInt altMemGetMaxLimitSize();


/**
 * \brief Get allocated block count
 *
 * \return allocated block count
 *
 * - Depend on memory manager
 */
LIBALT_API altUInt altMemGetBlockCount();

#endif  // ALTBASEMEM_H
