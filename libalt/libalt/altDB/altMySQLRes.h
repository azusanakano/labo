#ifndef ALTMYSQLRES_H
#define ALTMYSQLRES_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMySQLRes.h
 * \brief   MySQL results class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altPtr.h>
#include <altBase/altStatus.h>
#include <altBase/altLog.h>

#ifdef ALT_WIN
  #include <altDB/mysql/mysql.h>
#endif
#ifdef ALT_LINUX
  #include <mysql/mysql.h>
#endif

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  MySQL Results
///
class altMySQLRes : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altMySQLRes();

  ///
  /// \brief  Constructor
  ///
  /// \param  pMySQLRes [I ] Pointer of MySQL Response
  ///
  LIBALT_API altMySQLRes(MYSQL_RES * pMySQLRes);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altMySQLRes();

  ///
  /// \brief  Data Seek
  ///
  /// \param  nOffset [I ] Offset
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t Seek(altULongLong nOffset);

  ///
  /// \brief  Fetch Field
  ///
  /// \return Field
  ///
  LIBALT_API MYSQL_FIELD * FetchField();

  ///
  /// \brief  Fetch Field Number
  ///
  /// \param  nFieldNo  [I ] Field Number
  ///
  /// \return Field
  ///
  LIBALT_API MYSQL_FIELD * FetchFieldDirect(altUInt nFieldNo);

  ///
  /// \brief  Fetch Fields
  ///
  /// \return Fields Array
  ///
  LIBALT_API MYSQL_FIELD * FetchFields();

  ///
  /// \brief  Fetch Fields Length
  ///
  /// \return Fields Length
  ///
  LIBALT_API altULong * FetchLengths();

  ///
  /// \brief  Fetch Row
  ///
  /// \return Row
  ///
  LIBALT_API MYSQL_ROW FetchRow();

  ///
  /// \brief  Field Seek
  ///
  /// \param  nOffset [I ] Offset Value
  ///
  /// \return Previous value of field cursor
  ///
  LIBALT_API MYSQL_FIELD_OFFSET FieldSeek(MYSQL_FIELD_OFFSET nOffset);

  ///
  /// \brief  Field Tell
  ///
  /// \return Current offset of field cursor
  ///
  LIBALT_API MYSQL_FIELD_OFFSET FieldTell();

  ///
  /// \brief  Free Result
  ///
  LIBALT_API void FreeResult();

  ///
  /// \brief  Returns the number of columns in a result set.
  ///
  /// \return the number of columns in a result set.
  ///
  LIBALT_API altUInt NumFields();

  ///
  /// \brief  Returns the number of rows in the result set.
  ///
  /// \return the number of rows in the result set.
  ///
  LIBALT_API altULongLong NumRows();

  ///
  /// \brief  Seek Row
  ///
  /// \param  pOffset [I ] a row offset that should be a value returned from mysql_row_tell() or from mysql_row_seek()
  ///
  /// \return Offset
  ///
  LIBALT_API MYSQL_ROW_OFFSET RowSeek(MYSQL_ROW_OFFSET pOffset);

  ///
  /// \brief  Returns the current position of the row cursor for the last mysql_fetch_row().
  ///
  /// \return the current position of the row cursor for the last mysql_fetch_row().
  ///
  LIBALT_API MYSQL_ROW_OFFSET RowTell();

  ///
  /// \brief  Get MYSQL_RES Pointer
  ///
  /// \return MYSQL_RES Pointer
  ///
  LIBALT_API MYSQL_RES * GetMySQLRes();

private:
  MYSQL_RES *   m_pMySQLRes;    ///< MySQL Results
};

#endif  //ALTMYSQLRES_H

