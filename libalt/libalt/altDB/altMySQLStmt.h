#ifndef ALTMYSQLSTMT_H
#define ALTMYSQLSTMT_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMySQLStmt.h
 * \brief   MySQL prepared statement class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altDB/altMySQLRes.h>

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  MySQL Prepared Statement Class
///
class altMySQLStmt : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altMySQLStmt();

  ///
  /// \brief  Constructor
  ///
  /// \param  pStmt [I ] Pointer of MySQL Prepared Statement Structure
  ///
  LIBALT_API altMySQLStmt(MYSQL_STMT * pStmt);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altMySQLStmt();

  ///
  /// \brief  Get Affected Row Count
  ///
  /// \return Affected Row Count
  ///
  LIBALT_API altULongLong AffectedRows();

  ///
  /// \brief  Get Statement Attribute
  ///
  /// \param  nOption [I ] Option Number
  /// \param  pArg    [ O] Option Value
  ///
  LIBALT_API void AttrGet(enum enum_stmt_attr_type nOption, void * pArg);

  ///
  /// \brief  Set Statement Attribute
  ///
  /// \param  nOption [I ] Option Number
  /// \param  pArg    [I ] Option Value
  ///
  LIBALT_API void AttrSet(enum enum_stmt_attr_type nOption, const void * pArg);

  ///
  /// \brief  Bind Parameter
  ///
  /// \param  pBind [I ] Bind Parameter
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t BindParam(MYSQL_BIND * pBind);

  ///
  /// \brief  Bind Result
  ///
  /// \param  pBind [I ] Bind Result
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t BindResult(MYSQL_BIND * pBind);

  ///
  /// \brief  Close
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t Close();

  ///
  /// \brief  Data Seek
  ///
  /// \param  nOffset [I ] Offset
  ///
  LIBALT_API void DataSeek(const altULongLong nOffset);

  ///
  /// \brief  Get Error Number
  ///
  /// \return Error Number
  ///
  LIBALT_API altUInt Errno();

  ///
  /// \brief  Get Error String
  ///
  /// \return Error String
  ///
  LIBALT_API altStr Error();

  ///
  /// \brief  Execute
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t Execute();

  ///
  /// \brief  Fetch
  ///
  /// \return ALT_S_SUCCESS         Success
  /// \return ALT_S_NO_DATA         No Data
  /// \return ALT_S_DATA_TRUNCATED  Data Truncated
  /// \return ALT_E_ERROR           Error
  ///
  LIBALT_API alt_t Fetch();

  ///
  /// \brief  Fetch Column
  ///
  /// \param  pBind   [ O] Data Buffer
  /// \param  nColumn [I ] Column Number
  /// \param  nOffset [I ] Offset
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t FetchColumn(MYSQL_BIND * pBind, altUInt nColumn, altULong nOffset);

  ///
  /// \brief  Get Field Count
  ///
  /// \return Field Count
  ///
  LIBALT_API altUInt FieldCount();

  ///
  /// \brief  Free Result
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t FreeResult();

  ///
  /// \brief  Get Insert ID
  ///
  /// \return Insert ID
  ///
  LIBALT_API altULongLong InsertID();

  ///
  /// \brief  Get Number of Rows
  ///
  /// \return Number of Rows
  ///
  LIBALT_API altULongLong NumRows();

  ///
  /// \brief  Get Parameter Count
  ///
  /// \return Parameter Count
  ///
  LIBALT_API altULong ParamCount();

  ///
  /// \brief  Prepare Statement
  ///
  /// \param  sSQL  [I ] SQL
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t Prepare(const altStr & sSQL);

  ///
  /// \brief  Reset Statement
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t Reset();

  ///
  /// \brief  Get Result Meta Data
  ///
  /// \return Result Meta Data
  ///
  LIBALT_API altMySQLRes ResultMetadata() ALT_THROWS (alt_t);

  ///
  /// \brief  Row Seek
  ///
  /// \param  nOffset [I ] Offset
  ///
  /// \return The previous value of the row cursor.
  ///
  LIBALT_API MYSQL_ROW_OFFSET RowSeek(MYSQL_ROW_OFFSET nOffset);

  ///
  /// \brief  Row Tell
  ///
  /// \return The current offset of the row cursor.
  ///
  LIBALT_API MYSQL_ROW_OFFSET RowTell();

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
  LIBALT_API alt_t SendLongData(altUInt nParameterNumber, const altChar * pData, altULong nLength);

  ///
  /// \brief  Get SQL State String
  ///
  /// \return SQL State String
  ///
  LIBALT_API altStr SQLState();

  ///
  /// \brief  Store Result
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t StoreResult();

private:
  MYSQL_STMT *  m_pStmt;
};

#endif //ALTMYSQLSTMT_H

