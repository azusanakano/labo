#ifndef ALTMEM_H
#define ALTMEM_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMem.h
 * \brief   Memory function
 * \date    2007
 * \author  Azusa Nakano
 */

/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altBaseMem.h>
#include <altBase/altLog.h>

/*--------------------------------------------------------------------*
 * Enumration
 *--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*
 * Define
 *--------------------------------------------------------------------*/
#define ALT_MALLOC(p, size) \
  altMalloc ((altChar * &)(p), (size), __FILE__, __LINE__)

#define ALT_DUPALLOC(d, s, size) \
  altDupAlloc ((altChar * &)(d), (altChar *)(s), (size), __FILE__, __LINE__)

#define ALT_EXALLOC(d, nowsize, newsize) \
  altExAlloc ((altChar * &)(d), (nowsize), (newsize), __FILE__, __LINE__)

#define ALT_STRALLOC(d, s) \
  altStrAlloc ((altChar * &)(d), (altChar *)(s), __FILE__, __LINE__)

#define ALT_STRNALLOC(d, s, size) \
  altStrnAlloc ((altChar * &)(d), (altChar *)(s), (size), __FILE__, __LINE__)

#define ALT_STRALLOC_CAT(d, s) \
  altStrAllocCat ((altChar * &)(d), (altChar *)(s), __FILE__, __LINE__)

#define ALT_BINALLOC_CAT(d, sr, sz) \
  altStrAllocCat ((altByte * &)(d), (altByte *)(sr), (sz), __FILE__, __LINE__)

#define ALT_FREE(p) \
  altFree ((void * &)(p), __FILE__, __LINE__)

/*----------------------------------------------------------------*
 * Structure Definition
 *----------------------------------------------------------------*/


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
);


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
);


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
);


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
);

#endif  // ALTBASEMEM_H
