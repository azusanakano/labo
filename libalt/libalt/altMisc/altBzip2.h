#ifndef ALTBZIP2_H
#define ALTBZIP2_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altBzip2.h
 * \brief   bzip2 compress class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altLog.h>

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  bzip2
///
class altBzip2 : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altBzip2();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altBzip2();

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
  LIBALT_API alt_t Compress(altChar * & pData, altUInt & nLen);

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
  LIBALT_API alt_t Decompress(altChar * & pData, altUInt & nLen);

private:
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
  LIBALT_API alt_t Compress(altChar * pDst, altUInt nDstLen, altChar * pSrc, altUInt nSrcLen);

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
  LIBALT_API alt_t Decompress(altChar * pDst, altUInt nDstLen, altChar * pSrc, altUInt nSrcLen);
};

#endif
