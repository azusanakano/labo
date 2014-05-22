#ifndef ALTDBCONNECTION_H
#define ALTDBCONNECTION_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDBConnection.h
 * \brief   DB connection class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altDB/altDBResultSet.h>
#include <altDB/altSQL.h>
#include <altDB/altPreparedStatement.h>

#include <map>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef std::map<altStr, altPreparedStatement *> altPreparedStatementMap;

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  DB Connection
///
class altDBConnection : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  altDBConnection();

  ///
  /// \brief  Destructor
  ///
  virtual ~altDBConnection();

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
  virtual alt_t Connect(const altStr & sHost, const altUInt nPort, const altStr & sDB, const altStr & sUser, const altStr & sPass, const altStr & sCharset, const altBool bAutoCommit = false) = 0;

  ///
  /// \brief  Disconnect
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  virtual alt_t Disconnect() = 0;

  ///
  /// \brief  Execute SQL
  ///
  /// \param  oSQL    [I ] SQL
  /// \param  oResult [ O] Result Set
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_SQL     SQL Error
  ///
	virtual alt_t ExecuteSQL(const altSQL & oSQL, altDBResultSet & oResult) = 0;

  ///
  /// \brief  Execute SQL
  ///
  /// \param  oSQL          [I ] SQL
  /// \param  pAffectedRow  [ O] Affected Row
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_SQL     SQL Error
  ///
	virtual alt_t ExecuteSQL(const altSQL & oSQL, altULongLong * pAffectedRow = NULL) = 0;

  ///
  /// \brief  Get Prepared Statement
  ///
  /// \param  oSQL        [I ] SQL
  /// \param  pStatement  [ O] Prepared Statement
  ///
  /// \return ALT_S_SUCCESS Success
  /// \return ALT_E_SQL     SQL Error
  ///
  virtual alt_t GetPreparedStatement(const altSQL & oSQL, altPreparedStatement * & pStatement) = 0;

  ///
  /// \brief  Execute SQL
  ///
  /// \param  oStmt       [IO] Prepared Statement
  /// \param  oResultSet  [ O] ResultSet
  ///
  /// \return ALT_S_SUCCESS Success
  /// \return ALT_E_SQL     SQL Error
  ///
  virtual alt_t ExecuteSQL(altPreparedStatement & oStmt, altDBResultSet & oResultSet) = 0;

  ///
  /// \brief  Execute SQL
  ///
  /// \param  oStmt         [IO] Prepared Statement
  /// \param  pAffectedRow  [ O] ResultSet
  ///
  /// \return ALT_S_SUCCESS Success
  /// \return ALT_E_SQL     SQL Error
  ///
  virtual alt_t ExecuteSQL(altPreparedStatement & oStmt, altULongLong * pAffectedRow = NULL) = 0;

  ///
  /// \brief  Commit
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
	virtual alt_t Commit() = 0;

  ///
  /// \brief  Rollback
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
	virtual alt_t Rollback() = 0;

  ///
  /// \brief  Set Explain Log
  ///
  /// \param  bEnable [I ] Enable or not
  /// \param  sLogDir [I ] Explain Log Directory
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  alt_t SetExplainLog(altBool bEnable, const altStr & sLogDir);

  ///
  /// \brief  Clear Prepared Statement Cache
  ///
  /// \return ALT_S_SUCCESS Success
  ///
  alt_t ClearPreparedStatementCache();

protected:
  altBool                 m_bExplainLogEnable;      ///< Explain Log Enable
  altStr                  m_bExplainLogDir;         ///< Explain LOg Directory
  altPreparedStatementMap m_oPreparedStatementMap;  ///< Prepared Statement Cache
};

#endif  //ALTDBCONNECTION_H
