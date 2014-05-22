#ifndef ALTMYSQLDBCONNECTION_H
#define ALTMYSQLDBCONNECTION_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMySQLDBConnection.h
 * \brief   MySQL DB connection class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altDB/altDBConnection.h>
#include <altDB/altMySQL.h>

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  MySQL DB Connection
///
class altMySQLDBConnection : public altDBConnection
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altMySQLDBConnection();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altMySQLDBConnection();

  ///
  /// \brief  Connect
  ///
  /// \param  sHost     [I ] Host Name
  /// \param  nPort     [I ] Port Number
  /// \param  sDB       [I ] DB Name
  /// \param  sUser     [I ] User ID
  /// \param  sPass     [I ] Password
  /// \param  sCharset  [I ] Charcter Set
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Connect(const altStr & sHost, const altUInt nPort, const altStr & sDB, const altStr & sUser, const altStr & sPass, const altStr & sCharset, const altBool bAutoCommit = false);

  ///
  /// \brief  Disconnect
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Disconnect();

  ///
  /// \brief  Execute SQL
  ///
  /// \param  oSQL    [I ] SQL
  /// \param  oResult [ O] Result Set
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_SQL     SQL Error
  ///
	LIBALT_API alt_t ExecuteSQL(const altSQL & oSQL, altDBResultSet & oResult);

  ///
  /// \brief  Execute SQL
  ///
  /// \param  oSQL          [I ] SQL
  /// \param  pAffectedRow  [ O] Affected Row
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_SQL     SQL Error
  ///
	LIBALT_API alt_t ExecuteSQL(const altSQL & oSQL, altULongLong * pAffectedRow = NULL);

  ///
  /// \brief  Get Prepared Statement
  ///
  /// \param  oSQL        [I ] SQL
  /// \param  pStatement  [ O] Prepared Statement
  ///
  /// \return ALT_S_SUCCESS Success
  /// \return ALT_E_SQL     SQL Error
  ///
  LIBALT_API alt_t GetPreparedStatement(const altSQL & oSQL, altPreparedStatement * & pStatement);

  ///
  /// \brief  Execute SQL
  ///
  /// \param  oStmt       [IO] Prepared Statement
  /// \param  oResultSet  [ O] ResultSet
  ///
  /// \return ALT_S_SUCCESS Success
  /// \return ALT_E_SQL     SQL Error
  ///
  LIBALT_API alt_t ExecuteSQL(altPreparedStatement & oStmt, altDBResultSet & oResultSet);

  ///
  /// \brief  Execute SQL
  ///
  /// \param  oStmt         [IO] Prepared Statement
  /// \param  pAffectedRow  [ O] ResultSet
  ///
  /// \return ALT_S_SUCCESS Success
  /// \return ALT_E_SQL     SQL Error
  ///
  LIBALT_API alt_t ExecuteSQL(altPreparedStatement & oStmt, altULongLong * pAffectedRow = NULL);

  ///
  /// \brief  Commit
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
	LIBALT_API alt_t Commit();

  ///
  /// \brief  Rollback
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
	LIBALT_API alt_t Rollback();

private:
  ///
  /// \brief  Execute SQL
  ///
  /// \param  sSQL    [I ] SQL
  /// \param  oResult [ O] Result Set
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_SQL     SQL Error
  ///
	LIBALT_API alt_t ExecuteSQL(const altStr & sSQL, altDBResultSet & oResult);

  ///
  /// \brief  Execute SQL
  ///
  /// \param  sSQL          [I ] SQL
  /// \param  pAffectedRow  [ O] Affected Row
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_SQL     SQL Error
  ///
	LIBALT_API alt_t ExecuteSQL(const altStr & sSQL, altULongLong * pAffectedRow = NULL);

  ///
  /// \brief  Write Explain Log
  ///
  /// \param  oStmt [I ] SQL
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_SQL     SQL Error
  ///
  LIBALT_API alt_t WriteExplainLog(const altPreparedStatement & oStmt);

  ///
  /// \brief  Write Explain Log
  ///
  /// \param  oSQL        [I ] SQL
  /// \param  oResultSet  [I ] ResultSet
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t WriteExplainLog(const altSQL & oSQL, const altDBResultSet oResultSet);

  altMySQL  m_oMySQL; ///< MySQL API Object
};

#endif //ALTMYSQLDBCONNECTION_H
