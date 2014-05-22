/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMySQLStmt.cpp
 * \brief   MySQL prepared statement class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altMySQLStmt.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altMySQLStmt::altMySQLStmt() :
m_pStmt (NULL)
{
}

///
/// \brief  Constructor
///
/// \param  pStmt [I ] Pointer of MySQL Prepared Statement Structure
///
LIBALT_API altMySQLStmt::altMySQLStmt(MYSQL_STMT * pStmt) :
m_pStmt (pStmt)
{
}

///
/// \brief  Destructor
///
LIBALT_API altMySQLStmt::~altMySQLStmt()
{
  alt_t status = Close();
  ALT_LOG (status);
}

///
/// \brief  Get Affected Row Count
///
/// \return Affected Row Count
///
LIBALT_API altULongLong altMySQLStmt::AffectedRows()
{
  return (mysql_stmt_affected_rows (m_pStmt));
}

///
/// \brief  Get Statement Attribute
///
/// \param  nOption [I ] Option Number
/// \param  pArg    [ O] Option Value
///
LIBALT_API void altMySQLStmt::AttrGet(enum enum_stmt_attr_type nOption, void * pArg)
{
  mysql_stmt_attr_get (m_pStmt, nOption, pArg);
}

///
/// \brief  Set Statement Attribute
///
/// \param  nOption [I ] Option Number
/// \param  pArg    [I ] Option Value
///
LIBALT_API void altMySQLStmt::AttrSet(enum enum_stmt_attr_type nOption, const void * pArg)
{
  mysql_stmt_attr_set (m_pStmt, nOption, pArg);
}

///
/// \brief  Bind Parameter
///
/// \param  pBind [I ] Bind Parameter
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQLStmt::BindParam(MYSQL_BIND * pBind)
{
  my_bool b = mysql_stmt_bind_param (m_pStmt, pBind);
  if (! b) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u:%s", Errno(), Error().GetCStr()));
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Bind Result
///
/// \param  pBind [I ] Bind Result
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQLStmt::BindResult(MYSQL_BIND * pBind)
{
  my_bool b = mysql_stmt_bind_result (m_pStmt, pBind);
  if (! b) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u:%s", Errno(), Error().GetCStr()));
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Close
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQLStmt::Close()
{
  my_bool b = mysql_stmt_close (m_pStmt);
  if (! b) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u:%s", Errno(), Error().GetCStr()));
  }
  m_pStmt = NULL;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Data Seek
///
/// \param  nOffset [I ] Offset
///
LIBALT_API void altMySQLStmt::DataSeek(const altULongLong nOffset)
{
  mysql_stmt_data_seek (m_pStmt, nOffset);
}

///
/// \brief  Get Error Number
///
/// \return Error Number
///
LIBALT_API altUInt altMySQLStmt::Errno()
{
  return (mysql_stmt_errno (m_pStmt));
}

///
/// \brief  Get Error String
///
/// \return Error String
///
LIBALT_API altStr altMySQLStmt::Error()
{
  return (mysql_stmt_error (m_pStmt));
}

///
/// \brief  Execute
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQLStmt::Execute()
{
  altInt nRet = mysql_stmt_execute (m_pStmt);
  if (nRet != 0) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u:%s", Errno(), Error().GetCStr()));
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Fetch
///
/// \return ALT_S_SUCCESS         Success
/// \return ALT_S_NO_DATA         No Data
/// \return ALT_S_DATA_TRUNCATED  Data Truncated
/// \return ALT_E_ERROR           Error
///
LIBALT_API alt_t altMySQLStmt::Fetch()
{
  altInt nRet = mysql_stmt_fetch (m_pStmt);
  if (nRet == 1) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u:%s", Errno(), Error().GetCStr()));
  }
  else if (nRet == MYSQL_NO_DATA) {
    ALT_RET (ALT_S_NO_DATA);
  }
  else if (nRet == MYSQL_DATA_TRUNCATED) {
    ALT_RET (ALT_S_DATA_TRUNCATED);
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Fetch Column
///
/// \param  pBind   [ O] Data Buffer
/// \param  nColumn [I ] Column Number
/// \param  nOffset [I ] Offset
///
/// \return ALT_S_SUCCESS         Success
/// \return ALT_E_ERROR           Error
///
LIBALT_API alt_t altMySQLStmt::FetchColumn(MYSQL_BIND * pBind, altUInt nColumn, altULong nOffset)
{
  if (pBind == NULL) {
    ALT_RET_P (ALT_E_ERROR, "pBind is NULL");
  }

  altInt nRet = mysql_stmt_fetch_column (m_pStmt, pBind, nColumn, nOffset);
  if (nRet != 0) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u:%s", Errno(), Error().GetCStr()));
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Field Count
///
/// \return Field Count
///
LIBALT_API altUInt altMySQLStmt::FieldCount()
{
  return (mysql_stmt_field_count (m_pStmt));
}

///
/// \brief  Free Result
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQLStmt::FreeResult()
{
  my_bool b = mysql_stmt_free_result (m_pStmt);
  if (b != 0) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u:%s", Errno(), Error().GetCStr()));
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Insert ID
///
/// \return Insert ID
///
LIBALT_API altULongLong altMySQLStmt::InsertID()
{
  return (mysql_stmt_insert_id (m_pStmt));
}

///
/// \brief  Get Number of Rows
///
/// \return Number of Rows
///
LIBALT_API altULongLong altMySQLStmt::NumRows()
{
  return (mysql_stmt_num_rows (m_pStmt));
}

///
/// \brief  Get Parameter Count
///
/// \return Parameter Count
///
LIBALT_API altULong altMySQLStmt::ParamCount()
{
  return (mysql_stmt_param_count (m_pStmt));
}

///
/// \brief  Prepare Statement
///
/// \param  sSQL  [I ] SQL
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQLStmt::Prepare(const altStr & sSQL)
{
  altInt nRet = mysql_stmt_prepare (m_pStmt, sSQL.GetCStr(), sSQL.GetLen());
  if (nRet != 0) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u:%s", Errno(), Error().GetCStr()));
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Reset Statement
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQLStmt::Reset()
{
  my_bool b = mysql_stmt_reset (m_pStmt);
  if (b != 0) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u:%s", Errno(), Error().GetCStr()));
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Result Meta Data
///
/// \return Result Meta Data
///
LIBALT_API altMySQLRes altMySQLStmt::ResultMetadata() ALT_THROWS (alt_t)
{
  MYSQL_RES * pRes = mysql_stmt_result_metadata (m_pStmt);
  if (pRes == NULL) {
    altStr sBuf;
    ALT_LOG_P (ALT_E_ERROR, sBuf.Format ("%u:%s", Errno(), Error().GetCStr()));
    throw (ALT_E_ERROR);
  }
  altMySQLRes oRes(pRes);
  return (oRes);
}

///
/// \brief  Row Seek
///
/// \param  nOffset [I ] Offset
///
/// \return The previous value of the row cursor.
///
LIBALT_API MYSQL_ROW_OFFSET altMySQLStmt::RowSeek(MYSQL_ROW_OFFSET nOffset)
{
  return (mysql_stmt_row_seek (m_pStmt, nOffset));
}

///
/// \brief  Row Tell
///
/// \return The current offset of the row cursor.
///
LIBALT_API MYSQL_ROW_OFFSET altMySQLStmt::RowTell()
{
  return (mysql_stmt_row_tell (m_pStmt));
}

///
/// \brief  Send Long Data
///
/// \param  nParameterNumber  [I ] Parameter Number
/// \param  pData             [I ] Data
/// \param  nLength           [I ] Data Length
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQLStmt::SendLongData(altUInt nParameterNumber, const altChar * pData, altULong nLength)
{
  my_bool b = mysql_stmt_send_long_data (m_pStmt, nParameterNumber, pData, nLength);
  if (b != 0) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u:%s", Errno(), Error().GetCStr()));
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get SQL State String
///
/// \return SQL State String
///
LIBALT_API altStr altMySQLStmt::SQLState()
{
  return (mysql_stmt_sqlstate (m_pStmt));
}

///
/// \brief  Store Result
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQLStmt::StoreResult()
{
  altInt nRet = mysql_stmt_store_result (m_pStmt);
  if (nRet != 0) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%u:%s", Errno(), Error().GetCStr()));
  }
  ALT_RET (ALT_S_SUCCESS);
}
