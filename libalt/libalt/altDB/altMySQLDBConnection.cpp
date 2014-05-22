/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMySQLDBConnection.cpp
 * \brief   MySQL DB connection class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altMySQLDBConnection.h"
#include "altMySQLPreparedStatement.h"
#include "altMisc/altFile.h"
#include "altBase/altUtil.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altMySQLDBConnection::altMySQLDBConnection()
{
}

///
/// \brief  Destructor
///
LIBALT_API altMySQLDBConnection::~altMySQLDBConnection()
{
}

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
LIBALT_API alt_t altMySQLDBConnection::Connect(const altStr & sHost, const altUInt nPort, const altStr & sDB, const altStr & sUser, const altStr & sPass, const altStr & sCharset, const altBool bAutoCommit)
{
  alt_t status;

  status = m_oMySQL.Connect (sHost, sUser, sPass, sDB, static_cast<altInt>(nPort));
  ALT_ERR_RET (status);

  status = m_oMySQL.SetAutoCommit (bAutoCommit);
  ALT_ERR_RET (status);

  my_bool bReConnect = 1;
  status = m_oMySQL.Options (MYSQL_OPT_RECONNECT, & bReConnect);
  ALT_ERR_RET (status);

  status = m_oMySQL.SetCharacterSet (sCharset);
  ALT_ERR_RET (status);

  altSQL oSQL;
  status = oSQL.SetSQL ("set sql_mode='IGNORE_SPACE'", "");
  ALT_ERR_RET (status);

  status = ExecuteSQL (oSQL);
  ALT_ERR_RET (status);

  status = ClearPreparedStatementCache();
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Disconnect
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altMySQLDBConnection::Disconnect()
{
  alt_t status;

  status = m_oMySQL.Close();
  ALT_ERR_RET (status);

  status = ClearPreparedStatementCache();
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Execute SQL
///
/// \param  oSQL    [I ] SQL
/// \param  oResult [ O] Result Set
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_SQL     SQL Error
///
LIBALT_API alt_t altMySQLDBConnection::ExecuteSQL(const altSQL & oSQL, altDBResultSet & oResult)
{
  alt_t status;

  status = ExecuteSQL (oSQL.GetSQL(), oResult);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Execute SQL
///
/// \param  oSQL          [I ] SQL
/// \param  pAffectedRow  [ O] Affected Row
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_SQL     SQL Error
///
LIBALT_API alt_t altMySQLDBConnection::ExecuteSQL(const altSQL & oSQL, altULongLong * pAffectedRow)
{
  alt_t status;

  // Execute Query
  status = ExecuteSQL (oSQL.GetSQL(), pAffectedRow);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Prepared Statement
///
/// \param  oSQL        [I ] SQL
/// \param  pStatement  [ O] Prepared Statement
///
/// \return ALT_S_SUCCESS Success
/// \return ALT_E_SQL     SQL Error
///
LIBALT_API alt_t altMySQLDBConnection::GetPreparedStatement(const altSQL & oSQL, altPreparedStatement * & pStatement)
{
  pStatement = m_oPreparedStatementMap[oSQL.GetSQLName()];
  if (pStatement != NULL) {
    ALT_RET (ALT_S_SUCCESS);
  }

  alt_t status;
  altMySQLPreparedStatement * pNewStmt = ALT_NEW altMySQLPreparedStatement (oSQL, m_oMySQL);

  status = pNewStmt->Prepare();
  ALT_ERR_RET (status);

  m_oPreparedStatementMap[oSQL.GetSQLName()] = pNewStmt;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Execute SQL
///
/// \param  oStmt       [IO] Prepared Statement
/// \param  oResultSet  [ O] ResultSet
///
/// \return ALT_S_SUCCESS Success
/// \return ALT_E_SQL     SQL Error
///
LIBALT_API alt_t altMySQLDBConnection::ExecuteSQL(altPreparedStatement & oStmt, altDBResultSet & oResultSet)
{
  alt_t status;

  status = oStmt.ExcecuteSQL (oResultSet);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Execute SQL
///
/// \param  oStmt         [IO] Prepared Statement
/// \param  pAffectedRow  [ O] ResultSet
///
/// \return ALT_S_SUCCESS Success
/// \return ALT_E_SQL     SQL Error
///
LIBALT_API alt_t altMySQLDBConnection::ExecuteSQL(altPreparedStatement & oStmt, altULongLong * pAffectedRow)
{
  alt_t status;

  status = oStmt.ExcecuteSQL (pAffectedRow);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Commit
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altMySQLDBConnection::Commit()
{
  alt_t status;

  status = m_oMySQL.Commit();
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Rollback
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altMySQLDBConnection::Rollback()
{
  alt_t status;

  status = m_oMySQL.Rollback();
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Execute SQL
///
/// \param  sSQL    [I ] SQL
/// \param  oResult [ O] Result Set
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_SQL     SQL Error
///
LIBALT_API alt_t altMySQLDBConnection::ExecuteSQL(const altStr & sSQL, altDBResultSet & oResult)
{
  alt_t status;

  // Execute Query
  status = m_oMySQL.Query (sSQL);
  if (ALT_IS_ERR (status)) {
    ALT_RET_P (ALT_E_SQL, sSQL.GetCStr());
  }

  // Get Result
  altMySQLRes oRes = m_oMySQL.StoreResult();

  // Get Row Count
  altULongLong  nRowCount = oRes.NumRows();
  MYSQL_ROW     ppRow = oRes.FetchRow();
  altULong *    pLen = oRes.FetchLengths();
  altUInt       nFieldCount = oRes.NumFields();
  MYSQL_FIELD * pField = oRes.FetchField();

  if (nRowCount > 0) {
    for (altULongLong i = 0; i < nRowCount; i++) {
      altDBRow oRow;
      for (altUInt j = 0; j < nFieldCount; j++) {
        oRow.Add (pField[j].name, ppRow[j], pLen[j]);
      }
      oResult.Add (oRow);
      ppRow = oRes.FetchRow();
      pLen = oRes.FetchLengths();
    }
  }

  oRes.FreeResult();

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Execute SQL
///
/// \param  sSQL          [I ] SQL
/// \param  pAffectedRow  [ O] Affected Row
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_SQL     SQL Error
///
LIBALT_API alt_t altMySQLDBConnection::ExecuteSQL(const altStr & sSQL, altULongLong * pAffectedRow)
{
  alt_t status;

  // Execute Query
  status = m_oMySQL.Query (sSQL);
  if (ALT_IS_ERR (status)) {
    ALT_RET_P (ALT_E_SQL, sSQL.GetCStr());
  }

  if (pAffectedRow != NULL) {
    (* pAffectedRow) = m_oMySQL.GetAffectedRow();
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Write Explain Log
///
/// \param  oStmt [I ] SQL
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_SQL     SQL Error
///
LIBALT_API alt_t altMySQLDBConnection::WriteExplainLog(const altPreparedStatement & oStmt)
{
  alt_t           status;
  altSQL          oSQL;
  altDBResultSet  oResultSet;
  altStr          sSQL;

  sSQL += "explain ";
  sSQL += oStmt.toString();

  status = ExecuteSQL (sSQL, oResultSet);
  ALT_ERR_RET (status);

  status = oSQL.SetSQL (sSQL, oStmt.GetSQLName());
  ALT_ERR_RET (status);

  status = WriteExplainLog (oSQL, oResultSet);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Write Explain Log
///
/// \param  oSQL        [I ] SQL
/// \param  oResultSet  [I ] ResultSet
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altMySQLDBConnection::WriteExplainLog(const altSQL & oSQL, const altDBResultSet oResultSet)
{
  if (oResultSet.Size() == 0) {
    ALT_RET (ALT_S_SUCCESS);
  }

  altStr  sPath;

  if (m_bExplainLogDir.GetLen() > 0) {
    sPath += m_bExplainLogDir;
    sPath += "/";
  }
  sPath += oSQL.GetSQLName();
  sPath += ".log";

  altInt nIndex = sPath.FindLastOfChar("/\\");
  if (nIndex >= 0) {
    altStr sDir = sPath.SubStr (0, nIndex - 1);
    altMkDirR (sDir.GetCStr());
  }

  altFile oFile;

  alt_t status = oFile.Open (sPath, "a");
  ALT_ERR_RET (status);
  oFile.WriteLine (oSQL.GetSQL());
  for (altUInt i = 0; i < oResultSet.Size(); i++) {
    for (altUInt j = 0; j < oResultSet[i].Size(); j++) {
      if (j > 0) {
        oFile.Write ("\t");
      }

      if (oResultSet[i][j] != NULL) {
        oFile.Write (oResultSet[i][j]);
      }
      else {
        oFile.Write ("\t");
      }
    }
    oFile.Write ("\n");
  }
  oFile.Close();

  ALT_RET (ALT_S_SUCCESS);
}

