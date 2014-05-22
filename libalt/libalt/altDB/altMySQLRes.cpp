/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMySQLRes.cpp
 * \brief   MySQL results class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altMySQLRes.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altMySQLRes::altMySQLRes() :
m_pMySQLRes (NULL)
{
}

///
/// \brief  Constructor
///
/// \param  pMySQLRes [I ] Pointer of MySQL Response
///
LIBALT_API altMySQLRes::altMySQLRes(MYSQL_RES * pMySQLRes) :
m_pMySQLRes (pMySQLRes)
{
}

///
/// \brief  Destructor
///
LIBALT_API altMySQLRes::~altMySQLRes()
{
  FreeResult();
}

///
/// \brief  Data Seek
///
/// \param  nOffset [I ] Offset
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQLRes::Seek(altULongLong nOffset)
{
  if (m_pMySQLRes == NULL) {
    ALT_RET_P (ALT_E_ERROR, "m_pMySQLRes is NULL");
  }
  mysql_data_seek (m_pMySQLRes, nOffset);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Fetch Field
///
/// \return Field
///
LIBALT_API MYSQL_FIELD * altMySQLRes::FetchField()
{
  return (mysql_fetch_field (m_pMySQLRes));
}

///
/// \brief  Fetch Field Number
///
/// \param  nFieldNo  [I ] Field Number
///
/// \return Field
///
LIBALT_API MYSQL_FIELD * altMySQLRes::FetchFieldDirect(altUInt nFieldNo)
{
  return (mysql_fetch_field_direct (m_pMySQLRes, nFieldNo));
}

///
/// \brief  Fetch Fields
///
/// \return Fields Array
///
LIBALT_API MYSQL_FIELD * altMySQLRes::FetchFields()
{
  return (mysql_fetch_fields (m_pMySQLRes));
}

///
/// \brief  Fetch Fields Length
///
/// \return Fields Length
///
LIBALT_API altULong * altMySQLRes::FetchLengths()
{
  return (mysql_fetch_lengths (m_pMySQLRes));
}

///
/// \brief  Fetch Row
///
/// \return Row
///
LIBALT_API MYSQL_ROW altMySQLRes::FetchRow()
{
  return (mysql_fetch_row (m_pMySQLRes));
}

///
/// \brief  Field Seek
///
/// \param  nOffset [I ] Offset Value
///
/// \return previous value of field cursor
///
LIBALT_API MYSQL_FIELD_OFFSET altMySQLRes::FieldSeek(MYSQL_FIELD_OFFSET nOffset)
{
  return (mysql_field_seek (m_pMySQLRes, nOffset));
}

///
/// \brief  Field Tell
///
/// \return Current offset of field cursor
///
LIBALT_API MYSQL_FIELD_OFFSET altMySQLRes::FieldTell()
{
  return (mysql_field_tell (m_pMySQLRes));
}

///
/// \brief  Free Result
///
LIBALT_API void altMySQLRes::FreeResult()
{
  if (m_pMySQLRes != NULL) {
    mysql_free_result (m_pMySQLRes);
    m_pMySQLRes = NULL;
  }
}

///
/// \brief  Returns the number of columns in a result set.
///
/// \return the number of columns in a result set.
///
LIBALT_API altUInt altMySQLRes::NumFields()
{
  if (m_pMySQLRes == NULL) {
    return (0);
  }
  return (mysql_num_fields (m_pMySQLRes));
}

///
/// \brief  Returns the number of rows in the result set.
///
/// \return the number of rows in the result set.
///
LIBALT_API altULongLong altMySQLRes::NumRows()
{
  return (mysql_num_rows (m_pMySQLRes));
}

///
/// \brief  Seek Row
///
/// \param  pOffset [I ] a row offset that should be a value returned from mysql_row_tell() or from mysql_row_seek()
///
/// \return Offset
///
LIBALT_API MYSQL_ROW_OFFSET altMySQLRes::RowSeek(MYSQL_ROW_OFFSET pOffset)
{
  return mysql_row_seek (m_pMySQLRes, pOffset);
}

///
/// \brief  Returns the current position of the row cursor for the last mysql_fetch_row().
///
/// \return the current position of the row cursor for the last mysql_fetch_row().
///
LIBALT_API MYSQL_ROW_OFFSET altMySQLRes::RowTell()
{
  return mysql_row_tell (m_pMySQLRes);
}

///
/// \brief  Get MYSQL_RES Pointer
///
/// \return MYSQL_RES Pointer
///
LIBALT_API MYSQL_RES * altMySQLRes::GetMySQLRes()
{
  return (m_pMySQLRes);
}
