#ifndef ALTBASE_H
#define ALTBASE_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altBase.h
 * \brief   Base Class
 * \date    2007
 * \author  Azusa Nakano
 */

/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altBaseMem.h>
#include <altBase/altCommon.h>

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
#define ALT_NEW new (__FILE__, __LINE__)

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  base class
///
class altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altBase();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altBase();

  ///
  /// \brief  new operator
  ///
  /// \param  nSize [I ] memory size
  ///
  /// \return pointer of memory
  ///
  LIBALT_API void * operator new(size_t nSize)
  {
    altChar * pPtr = NULL;
    ALT_BASE_MALLOC (pPtr, nSize);
    return ((void *)pPtr);
  }

  ///
  /// \brief  delete operator
  ///
  /// \param  pPtr  [I ] pointer of memory
  ///
  LIBALT_API void operator delete(void * p)
  {
    ALT_BASE_FREE (p);
  }

  ///
  /// \brief  new operator
  ///
  /// \param  nSize       [I ] memory size
  /// \param  szFileName  [I ] file name
  /// \param  nLine       [I ] line numnber
  ///
  /// \return pointer of memory
  ///
  LIBALT_API void * operator new(size_t nSize, const altChar * szFileName, const altUInt nLine)
  {
    altChar * p = NULL;
    altBaseMalloc (p, nSize, szFileName, nLine);
    return ((void *)p);
  }

  ///
  /// \brief  delete operator
  ///
  /// \param  pPtr        [I ] pointer of memory
  /// \param  szFileName  [I ] file name
  /// \param  nLine       [I ] line numnber
  ///
  LIBALT_API void operator delete(void * p, const altChar * szFileName, const altUInt nLine)
  {
    altBaseFree (p, szFileName, nLine);
  }

};

#endif

