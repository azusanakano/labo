/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDataStream.cpp
 * \brief   Data stream class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altDataStream.h"
#include "altBase/altMem.h"

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
#define ALT_WRITE(data, size) Write ((altChar *)& (data), (size))
#define ALT_PWRITE(data)      ALT_WRITE ((data), sizeof (data))
#define ALT_PREAD(data)       Read ((altChar *)& (data), sizeof (data))

/*----------------------------------------------------------------*
 * Class Variable
 *----------------------------------------------------------------*/
const altByte altDataStream::TYPE_EOF = 0x00;
const altByte altDataStream::TYPE_CHAR = 0x01;
const altByte altDataStream::TYPE_UCHAR = 0x02;
const altByte altDataStream::TYPE_BOOL = 0x03;
const altByte altDataStream::TYPE_SHORT = 0x04;
const altByte altDataStream::TYPE_USHORT = 0x05;
const altByte altDataStream::TYPE_INT = 0x06;
const altByte altDataStream::TYPE_UINT = 0x07;
const altByte altDataStream::TYPE_LONG = 0x08;
const altByte altDataStream::TYPE_ULONG = 0x09;
const altByte altDataStream::TYPE_LONGLONG = 0x0A;
const altByte altDataStream::TYPE_ULONGLONG = 0x0B;
const altByte altDataStream::TYPE_FLOAT = 0x0C;
const altByte altDataStream::TYPE_DOUBLE = 0x0D;
const altByte altDataStream::TYPE_STR = 0x0E;
const altByte altDataStream::TYPE_WSTR = 0x0F;

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altDataStream::altDataStream() :
m_pData (NULL),
m_nDataSize (0),
m_nBufferSize (0),
m_nIndex (0)
{
}

///
/// \brief  Destructor
///
LIBALT_API altDataStream::~altDataStream()
{
  ALT_FREE (m_pData);
}

///
/// \brief  write
///
/// \param  v [i ] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::Write(const altChar v)
{
  alt_t status;

  status = ALT_PWRITE (TYPE_CHAR);
  ALT_ERR_RET (status);

  status = ALT_PWRITE (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  write
///
/// \param  v [i ] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::Write(const altUChar v)
{
  alt_t status;

  status = ALT_PWRITE (TYPE_UCHAR);
  ALT_ERR_RET (status);

  status = ALT_PWRITE (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  write
///
/// \param  v [i ] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::Write(const altBool v)
{
  alt_t status;

  status = ALT_PWRITE (TYPE_BOOL);
  ALT_ERR_RET (status);

  status = ALT_PWRITE (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  write
///
/// \param  v [i ] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::Write(const altShort v)
{
  alt_t status;

  status = ALT_PWRITE (TYPE_SHORT);
  ALT_ERR_RET (status);

  status = ALT_PWRITE (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  write
///
/// \param  v [i ] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::Write(const altUShort v)
{
  alt_t status;

  status = ALT_PWRITE (TYPE_USHORT);
  ALT_ERR_RET (status);

  status = ALT_PWRITE (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  write
///
/// \param  v [i ] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::Write(const altInt v)
{
  alt_t status;

  status = ALT_PWRITE (TYPE_INT);
  ALT_ERR_RET (status);

  status = ALT_PWRITE (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  write
///
/// \param  v [i ] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::Write(const altUInt v)
{
  alt_t status;

  status = ALT_PWRITE (TYPE_UINT);
  ALT_ERR_RET (status);

  status = ALT_PWRITE (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  write
///
/// \param  v [i ] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::Write(const altLong v)
{
  alt_t status;

  status = ALT_PWRITE (TYPE_LONG);
  ALT_ERR_RET (status);

  status = ALT_PWRITE (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  write
///
/// \param  v [i ] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::Write(const altULong v)
{
  alt_t status;

  status = ALT_PWRITE (TYPE_ULONG);
  ALT_ERR_RET (status);

  status = ALT_PWRITE (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  write
///
/// \param  v [i ] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::Write(const altLongLong v)
{
  alt_t status;

  status = ALT_PWRITE (TYPE_LONGLONG);
  ALT_ERR_RET (status);

  status = ALT_PWRITE (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  write
///
/// \param  v [i ] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::Write(const altULongLong v)
{
  alt_t status;

  status = ALT_PWRITE (TYPE_ULONGLONG);
  ALT_ERR_RET (status);

  status = ALT_PWRITE (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  write
///
/// \param  v [i ] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::Write(const altFloat v)
{
  alt_t status;

  status = ALT_PWRITE (TYPE_FLOAT);
  ALT_ERR_RET (status);

  status = ALT_PWRITE (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  write
///
/// \param  v [i ] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::Write(const altDouble v)
{
  alt_t status;

  status = ALT_PWRITE (TYPE_DOUBLE);
  ALT_ERR_RET (status);

  status = ALT_PWRITE (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  write
///
/// \param  v [i ] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::Write(const altStr & v)
{
  alt_t status;

  status = ALT_PWRITE (TYPE_STR);
  ALT_ERR_RET (status);

  altUInt nLen = v.GetLen();

  status = ALT_PWRITE (nLen);
  ALT_ERR_RET (status);

  status = Write (v.GetCStr(), nLen);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  write
///
/// \param  v [i ] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::Write(const altWStr & v)
{
  alt_t status;

  status = ALT_PWRITE (TYPE_WSTR);
  ALT_ERR_RET (status);

  altUInt nSize = v.GetLen() * sizeof (altWChar);

  status = ALT_PWRITE (nSize);
  ALT_ERR_RET (status);

  status = Write ((const altChar *)v.GetCStr(), nSize);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  read
///
/// \param  v [ O] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::Read(altChar & v)
{
  alt_t   status;

  status = ReadType (TYPE_CHAR);
  ALT_ERR_RET (status);

  status = Read (& v, sizeof (v));
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  read
///
/// \param  v [ O] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::Read(altUChar & v)
{
  alt_t   status;

  status = ReadType (TYPE_UCHAR);
  ALT_ERR_RET (status);

  status = ALT_PREAD (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  read
///
/// \param  v [ O] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::Read(altBool & v)
{
  alt_t   status;

  status = ReadType (TYPE_BOOL);
  ALT_ERR_RET (status);

  status = ALT_PREAD (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  read
///
/// \param  v [ O] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::Read(altShort & v)
{
  alt_t   status;

  status = ReadType (TYPE_SHORT);
  ALT_ERR_RET (status);

  status = ALT_PREAD (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  read
///
/// \param  v [ O] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::Read(altUShort & v)
{
  alt_t   status;

  status = ReadType (TYPE_USHORT);
  ALT_ERR_RET (status);

  status = ALT_PREAD (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  read
///
/// \param  v [ O] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::Read(altInt & v)
{
  alt_t   status;

  status = ReadType (TYPE_INT);
  ALT_ERR_RET (status);

  status = ALT_PREAD (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  read
///
/// \param  v [ O] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::Read(altUInt & v)
{
  alt_t   status;

  status = ReadType (TYPE_UINT);
  ALT_ERR_RET (status);

  status = ALT_PREAD (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  read
///
/// \param  v [ O] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::Read(altLong & v)
{
  alt_t   status;

  status = ReadType (TYPE_LONG);
  ALT_ERR_RET (status);

  status = ALT_PREAD (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  read
///
/// \param  v [ O] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::Read(altULong & v)
{
  alt_t   status;

  status = ReadType (TYPE_ULONG);
  ALT_ERR_RET (status);

  status = ALT_PREAD (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  read
///
/// \param  v [ O] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::Read(altLongLong & v)
{
  alt_t   status;

  status = ReadType (TYPE_LONGLONG);
  ALT_ERR_RET (status);

  status = ALT_PREAD (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  read
///
/// \param  v [ O] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::Read(altULongLong & v)
{
  alt_t   status;

  status = ReadType (TYPE_ULONGLONG);
  ALT_ERR_RET (status);

  status = ALT_PREAD (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  read
///
/// \param  v [ O] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::Read(altFloat & v)
{
  alt_t   status;

  status = ReadType (TYPE_FLOAT);
  ALT_ERR_RET (status);

  status = ALT_PREAD (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  read
///
/// \param  v [ O] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::Read(altDouble & v)
{
  alt_t   status;

  status = ReadType (TYPE_DOUBLE);
  ALT_ERR_RET (status);

  status = ALT_PREAD (v);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  read
///
/// \param  v [ O] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::Read(altStr & v)
{
  alt_t   status;

  status = ReadType (TYPE_STR);
  ALT_ERR_RET (status);

  altUInt nLen = 0;
  status = ALT_PREAD (nLen);
  ALT_ERR_RET (status);

  altChar * szValue = NULL;
  status = ALT_MALLOC (szValue, nLen + 1);
  ALT_ERR_RET (status);

  status = Read (szValue, nLen);
  ALT_ERR_RET (status);

  v = szValue;
  ALT_FREE (szValue);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  read
///
/// \param  v [ O] value
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::Read(altWStr & v)
{
  alt_t   status;

  status = ReadType (TYPE_WSTR);
  ALT_ERR_RET (status);

  altUInt nSize = 0;
  status = ALT_PREAD (nSize);
  ALT_ERR_RET (status);

  altWChar * szValue = NULL;
  status = ALT_MALLOC (szValue, nSize + sizeof (altWChar));
  ALT_ERR_RET (status);

  status = Read ((altChar *)szValue, nSize);
  ALT_ERR_RET (status);

  v = szValue;
  ALT_FREE (szValue);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get next type
///
/// \return Next type
///
LIBALT_API altByte altDataStream::GetNextType()
{
  altByte nType;
  memcpy (& nType, & m_pData[m_nIndex], sizeof (nType));
  return (nType);
}

///
/// \brief  Get data
///
/// \param  pData [ O] Data
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::GetData(altCharPtr & pData) const
{
  alt_t     status;
  altChar * pBuf = NULL;

  status = ALT_MALLOC (pBuf, m_nDataSize);
  ALT_ERR_RET (status);

  pData = pBuf;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get data size
///
/// \return Data size
///
LIBALT_API altUInt altDataStream::GetDataSize() const
{
  return (m_nDataSize);
}

///
/// \brief  Set data
///
/// \param  pData [I ] Data
/// \param  nSize [I ] Data size
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::SetData(const altCharPtr & pData, const altUInt nSize)
{
  alt_t     status;

  ALT_FREE (m_pData);

  status = ALT_DUPALLOC (m_pData, pData, nSize);
  ALT_ERR_RET (status);

  m_nBufferSize = nSize;
  m_nDataSize = nSize;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Extend buffer
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::ExtendBuffer()
{
  if (m_nDataSize > m_nBufferSize) {
    alt_t status;
    if (m_nBufferSize == 0) {
      status = ALT_EXALLOC (m_pData, m_nBufferSize, 512);
      ALT_ERR_RET (status);
      m_nBufferSize = BUFSIZ;
    }
    else {
      status = ALT_EXALLOC (m_pData, m_nBufferSize, m_nBufferSize * 2);
      ALT_ERR_RET (status);
      m_nBufferSize *= 2;
    }
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Write
///
/// \param  pData [I ] Data
/// \param  nSize [I ] Data size
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altDataStream::Write(const altChar * pData, const altUInt nSize)
{
  alt_t status;
  m_nDataSize += nSize;

  status = ExtendBuffer();
  ALT_ERR_RET (status);

  memcpy (& m_pData[m_nIndex], pData, nSize);
  m_nIndex += nSize;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Read type
///
/// \param  _nType  [I ] Type
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::ReadType(const altByte _nType)
{
  if (m_nIndex >= m_nDataSize) {
    ALT_RET (ALT_E_ERROR);
  }

  altByte nType;

  memcpy (& nType, & m_pData[m_nIndex], sizeof (nType));
  if (nType != _nType) {
    ALT_RET (ALT_E_ERROR);
  }
  m_nIndex += sizeof (nType);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Read
///
/// \param  pData [ O] Data
/// \param  nSize [I ] Size
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altDataStream::Read(altChar * pData, const altUInt nSize)
{
  if (m_nIndex >= m_nDataSize) {
    ALT_RET (ALT_E_ERROR);
  }
  memcpy (pData, & m_pData[m_nIndex], nSize);
  m_nIndex += nSize;
  ALT_RET (ALT_S_SUCCESS);
}
