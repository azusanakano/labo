#ifndef ALTDATASTREAM_H
#define ALTDATASTREAM_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDataStream.h
 * \brief   Data stream class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCharPtr.h>
#include <altBase/altLog.h>
#include <altBase/altStr.h>
#include <altBase/altWStr.h>

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Data Stream
///
class altDataStream : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altDataStream();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altDataStream();

  ///
  /// \brief  write
  ///
  /// \param  v [i ] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Write(const altChar v);

  ///
  /// \brief  write
  ///
  /// \param  v [i ] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Write(const altUChar v);

  ///
  /// \brief  write
  ///
  /// \param  v [i ] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Write(const altBool v);

  ///
  /// \brief  write
  ///
  /// \param  v [i ] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Write(const altShort v);

  ///
  /// \brief  write
  ///
  /// \param  v [i ] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Write(const altUShort v);

  ///
  /// \brief  write
  ///
  /// \param  v [i ] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Write(const altInt v);

  ///
  /// \brief  write
  ///
  /// \param  v [i ] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Write(const altUInt v);

  ///
  /// \brief  write
  ///
  /// \param  v [i ] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Write(const altLong v);

  ///
  /// \brief  write
  ///
  /// \param  v [i ] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Write(const altULong v);

  ///
  /// \brief  write
  ///
  /// \param  v [i ] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Write(const altLongLong v);

  ///
  /// \brief  write
  ///
  /// \param  v [i ] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Write(const altULongLong v);

  ///
  /// \brief  write
  ///
  /// \param  v [i ] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Write(const altFloat v);

  ///
  /// \brief  write
  ///
  /// \param  v [i ] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Write(const altDouble v);

  ///
  /// \brief  write
  ///
  /// \param  v [i ] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Write(const altStr & v);

  ///
  /// \brief  write
  ///
  /// \param  v [i ] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Write(const altWStr & v);

  ///
  /// \brief  read
  ///
  /// \param  v [ O] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Read(altChar & v);

  ///
  /// \brief  read
  ///
  /// \param  v [ O] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Read(altUChar & v);

  ///
  /// \brief  read
  ///
  /// \param  v [ O] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Read(altBool & v);

  ///
  /// \brief  read
  ///
  /// \param  v [ O] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Read(altShort & v);

  ///
  /// \brief  read
  ///
  /// \param  v [ O] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Read(altUShort & v);

  ///
  /// \brief  read
  ///
  /// \param  v [ O] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Read(altInt & v);

  ///
  /// \brief  read
  ///
  /// \param  v [ O] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Read(altUInt & v);

  ///
  /// \brief  read
  ///
  /// \param  v [ O] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Read(altLong & v);

  ///
  /// \brief  read
  ///
  /// \param  v [ O] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Read(altULong & v);

  ///
  /// \brief  read
  ///
  /// \param  v [ O] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Read(altLongLong & v);

  ///
  /// \brief  read
  ///
  /// \param  v [ O] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Read(altULongLong & v);

  ///
  /// \brief  read
  ///
  /// \param  v [ O] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Read(altFloat & v);

  ///
  /// \brief  read
  ///
  /// \param  v [ O] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Read(altDouble & v);

  ///
  /// \brief  read
  ///
  /// \param  v [ O] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Read(altStr & v);

  ///
  /// \brief  read
  ///
  /// \param  v [ O] value
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Read(altWStr & v);

  ///
  /// \brief  Get next type
  ///
  /// \return Next type
  ///
  LIBALT_API altByte GetNextType();

  ///
  /// \brief  Get data
  ///
  /// \param  pData [ O] Data
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t GetData(altCharPtr & pData) const;

  ///
  /// \brief  Get data size
  ///
  /// \return Data size
  ///
  LIBALT_API altUInt GetDataSize() const;

  ///
  /// \brief  Set data
  ///
  /// \param  pData [I ] Data
  /// \param  nSize [I ] Data size
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t SetData(const altCharPtr & pData, const altUInt nSize);

  static const altByte  TYPE_EOF;
  static const altByte  TYPE_CHAR;
  static const altByte  TYPE_UCHAR;
  static const altByte  TYPE_BOOL;
  static const altByte  TYPE_SHORT;
  static const altByte  TYPE_USHORT;
  static const altByte  TYPE_INT;
  static const altByte  TYPE_UINT;
  static const altByte  TYPE_LONG;
  static const altByte  TYPE_ULONG;
  static const altByte  TYPE_LONGLONG;
  static const altByte  TYPE_ULONGLONG;
  static const altByte  TYPE_FLOAT;
  static const altByte  TYPE_DOUBLE;
  static const altByte  TYPE_STR;
  static const altByte  TYPE_WSTR;

private:
  ///
  /// \brief  Extend buffer
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t ExtendBuffer();

  ///
  /// \brief  Write
  ///
  /// \param  pData [I ] Data
  /// \param  nSize [I ] Data size
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t Write(const altChar * pData, const altUInt nSize);

  ///
  /// \brief  Read type
  ///
  /// \param  _nType  [I ] Type
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t ReadType(const altByte _nType);

  ///
  /// \brief  Read
  ///
  /// \param  pData [ O] Data
  /// \param  nSize [I ] Size
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Read(altChar * pData, const altUInt nSize);

  altChar *   m_pData;
  altUInt     m_nDataSize;
  altUInt     m_nBufferSize;
  altUInt     m_nIndex;
};

#endif
