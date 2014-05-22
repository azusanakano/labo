/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMySQL.cpp
 * \brief   MySQL class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altMySQL.h"
#include "altBase/altMem.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/
altBool  altMySQL::bInitDone = false;

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altMySQL::altMySQL() :
m_pMySQL (NULL)
{
#ifdef ALT_WIN
  if (! bInitDone) {
    my_init();
  }
#endif
  m_pMySQL = mysql_init (NULL);
}

///
/// \brief  Destructor
///
LIBALT_API altMySQL::~altMySQL()
{
  alt_t status = Close();
  ALT_LOG (status);
}

///
/// \brief  Get Affected Row Count
///
/// \return Affected Row Count
///
LIBALT_API altULongLong altMySQL::GetAffectedRow()
{
  if (m_pMySQL == NULL) {
    return (0);
  }
  return (mysql_affected_rows (m_pMySQL));
}

///
/// \brief  Set AutCommit Mode
///
/// \param  bAutoCommit true...auto commit false...not auto commit
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::SetAutoCommit(const altBool bAutoCommit)
{
  if (m_pMySQL == NULL) {
    ALT_RET_P (ALT_E_ERROR, "m_pMySQL is NULL");
  }
  my_bool b = mysql_autocommit (m_pMySQL, bAutoCommit);
  if (b == 0) {
    ALT_RET (ALT_S_SUCCESS);
  }
  ALT_RET (ALT_E_ERROR);
}

///
/// \brief  Change User
///
/// \param  sUser   [I ] User
/// \param  sPasswd [I ] Password
/// \param  szDB    [I ] DB
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::ChangeUser(const altStr & sUser, const altStr & sPasswd, const altChar * szDB)
{
  if (m_pMySQL == NULL) {
    ALT_RET_P (ALT_E_ERROR, "m_pMySQL is NULL");
  }
  my_bool bError = mysql_change_user (m_pMySQL, sUser.GetCStr(), sPasswd.GetCStr(), szDB);
  if (bError) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("Failed to change user. Error: %s", Error().GetCStr()));
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Default Character Set Name
///
/// \param  sCharSetName  [ O] Default Character Set Name
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::GetCharacterSetName(altStr & sCharSetName)
{
  if (m_pMySQL == NULL) {
    ALT_RET_P (ALT_E_ERROR, "m_pMySQL is NULL");
  }
  sCharSetName = mysql_character_set_name (m_pMySQL);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Close
///
/// \return ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altMySQL::Close()
{
  if (m_pMySQL == NULL) {
    ALT_RET (ALT_S_SUCCESS);
  }
  mysql_close (m_pMySQL);
  m_pMySQL = NULL;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Commit
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::Commit()
{
  if (m_pMySQL == NULL) {
    ALT_RET_P (ALT_E_ERROR, "m_pMySQL is NULL");
  }
  my_bool bError = mysql_commit (m_pMySQL);
  if (bError) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("Failed to commit. Error: %s", Error().GetCStr()));
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Dump Debug Info
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::DumpDebugInfo()
{
  if (m_pMySQL == NULL) {
    ALT_RET_P (ALT_E_ERROR, "m_pMySQL is NULL");
  }
  altInt nRet = mysql_dump_debug_info (m_pMySQL);
  if (nRet != 0) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("Failed to commit. Error: %s", Error().GetCStr()));
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get errno
///
/// \return error number
///
LIBALT_API altUInt altMySQL::ErrorNo()
{
  return (mysql_errno (m_pMySQL));
}

///
/// \brief  Get Error Message
///
/// \return Error Message
///
LIBALT_API altStr altMySQL::Error()
{
  return (mysql_error (m_pMySQL));
}

///
/// \brief  Get Field Count
///
/// \return Field Count
///
LIBALT_API altInt altMySQL::GetFieldCount()
{
  if (m_pMySQL == NULL) {
    return (0);
  }
  return (mysql_field_count (m_pMySQL));
}

///
/// \brief  Get Character Set Info
///
/// \param  pCharSetInfo  [ O] Character Set Infomation
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::GetCharacterSetInfo(MY_CHARSET_INFO * pCharSetInfo)
{
  if (m_pMySQL == NULL) {
    ALT_RET_P (ALT_E_ERROR, "m_pMySQL is NULL");
  }
  mysql_get_character_set_info (m_pMySQL, pCharSetInfo);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Client Info
///
/// \return Client Info
///
LIBALT_API altStr altMySQL::GetClientInfo()
{
  return (mysql_get_client_info());
}

///
/// \brief  Get Client Version
///
/// \return Client Version
///
LIBALT_API altULong altMySQL::GetClientVersion()
{
  return (mysql_get_client_version());
}

///
/// \brief  Get Host Info
///
/// \return Host Info
///
LIBALT_API altStr altMySQL::GetHostInfo()
{
  return (mysql_get_host_info (m_pMySQL));
}

///
/// \brief  Get Protocol Info
///
/// \return Protocol Info
///
LIBALT_API altUInt altMySQL::GetProtoInfo()
{
  return (mysql_get_proto_info (m_pMySQL));
}

///
/// \brief  Get Server Info
///
/// \return Server Info
///
LIBALT_API altStr altMySQL::GetServerInfo()
{
  return (mysql_get_server_info (m_pMySQL));
}

///
/// \brief  Get Server Version
///
/// \return Server Version
///
LIBALT_API altULong altMySQL::GetServerVersion()
{
  return (mysql_get_server_version (m_pMySQL));
}

///
/// \brief  Get Statement Info
///
/// \return Statement Info
///
LIBALT_API altStr altMySQL::Info()
{
  return (mysql_info (m_pMySQL));
}

///
/// \brief  Get Insert ID
///
/// \return Insert ID
///
LIBALT_API altULongLong altMySQL::InsertID()
{
  return (mysql_insert_id (m_pMySQL));
}

///
/// \brief  KILL
///
/// \param  nPid  [I ] Proccess ID
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::Kill(const altULong nPid)
{
  altInt nRet = mysql_kill (m_pMySQL, nPid);
  if (nRet != 0) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("Failed to kill. Error: %s", Error().GetCStr()));
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get DBS
///
/// \param  sWild [I ] Database name
/// \param  pRes  [ O] Database result set
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
/// \return ALT_E_NOMEM     Out of memory
///
LIBALT_API alt_t altMySQL::ListDBS(const altStr & sWild, altPtr<altMySQLRes> pRes)
{
  MYSQL_RES * p = mysql_list_dbs (m_pMySQL, sWild.GetCStr());
  if (p == NULL) {
    ALT_RET_P (ALT_E_ERROR, Error().GetCStr());
  }

  pRes = ALT_NEW altMySQLRes (p);
  if (pRes == NULL) {
    ALT_RET (ALT_E_NOMEM);
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Current Server Threads
///
/// \param  pRes  [ O] Current Server Threads
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
/// \return ALT_E_NOMEM     Out of memory
///
LIBALT_API alt_t altMySQL::ListProcesses(altPtr<altMySQLRes> pRes)
{
  MYSQL_RES * p = mysql_list_processes (m_pMySQL);
  if (p == NULL) {
    ALT_RET_P (ALT_E_ERROR, Error().GetCStr());
  }

  pRes = ALT_NEW altMySQLRes (p);
  if (pRes == NULL) {
    ALT_RET (ALT_E_NOMEM);
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Tables
///
/// \param  sWild [I ] Table name
/// \param  pRes  [ O] Tables
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
/// \return ALT_E_NOMEM     Out of memory
///
LIBALT_API alt_t altMySQL::ListTables(const altStr & sWild, altPtr<altMySQLRes> pRes)
{
  MYSQL_RES * p = mysql_list_tables (m_pMySQL, sWild.GetCStr());
  if (p == NULL) {
    ALT_RET_P (ALT_E_ERROR, Error().GetCStr());
  }

  pRes = ALT_NEW altMySQLRes (p);
  if (pRes == NULL) {
    ALT_RET (ALT_E_NOMEM);
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Check More Results
///
/// \return true  Results exsit
/// \return false Not More Results exsit
///
LIBALT_API altBool altMySQL::MoreResults()
{
  my_bool b = mysql_more_results (m_pMySQL);
  if (b) {
    return (true);
  }
  return (false);
}

///
/// \brief  Check Next Results
///
/// \return ALT_S_SUCCESS         Successful and there are more results
/// \return ALT_S_NO_MORE_RESULT  Successful and there are no more results
/// \return ALT_E_ERROR           An error occurred
///
LIBALT_API alt_t altMySQL::NextResults()
{
  altInt nRet = mysql_next_result (m_pMySQL);
  if (nRet == 0) {
    ALT_RET (ALT_S_SUCCESS);
  }
  else if (nRet == -1) {
    ALT_RET (ALT_S_NO_MORE_RESULT);
  }
  ALT_RET_P (ALT_E_ERROR, Error().GetCStr());
}

///
/// \brief  Returns the number of columns in a result set.
///
/// \return the number of columns in a result set.
///
LIBALT_API altUInt altMySQL::NumFields()
{
  return (mysql_field_count (m_pMySQL));
}

///
/// \brief  Set extra connect options
///
/// \param  nOption [I ] Option Number
/// \param  pArg    [I ] Arguments
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::Options(mysql_option nOption, const altChar * pArg)
{
  altInt nRet = mysql_options (m_pMySQL, nOption, pArg);
  if (nRet == 0) {
    ALT_RET (ALT_S_SUCCESS);
  }
  ALT_RET_P (ALT_E_ERROR, Error().GetCStr());
}

///
/// \brief  Checks whether the connection to the server is working
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::Ping()
{
  altInt nRet = mysql_ping (m_pMySQL);
  if (nRet != 0) {
    ALT_RET_P (ALT_E_ERROR, Error().GetCStr());
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Execute Query
///
/// \param  sQuery  [I ] SQL
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::Query(const altStr & sQuery)
{
  altInt nRet = mysql_query (m_pMySQL, sQuery.GetCStr());
  if (nRet != 0) {
    ALT_RET_P (ALT_E_ERROR, Error().GetCStr());
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Connect to DB Server
///
/// \param  sHost         [I ] Host Name
/// \param  sUser         [I ] User ID
/// \param  sPasswd       [I ] Password
/// \param  sDB           [I ] DB Name
/// \param  nPort         [I ] Port Number
/// \param  szUnixSocket  [I ] Unix Socket String
/// \param  nClientFlag   [I ] Client Flags
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::Connect(const altStr & sHost, const altStr & sUser, const altStr & sPasswd, const altStr & sDB, const altInt nPort, const altChar * szUnixSocket, altULong nClientFlag)
{
  m_pMySQL = mysql_real_connect (m_pMySQL, sHost.GetCStr(), sUser.GetCStr(), sPasswd.GetCStr(), sDB.GetCStr(), nPort, szUnixSocket, nClientFlag);
  if (m_pMySQL == NULL) {
    ALT_RET_P (ALT_E_ERROR, Error().GetCStr());
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Escape String
///
/// \param  sTo   [ O] Escape Result
/// \param  sFrom [I ] String
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_NOMEM     Out of memory
///
LIBALT_API alt_t altMySQL::EscapeString(altStr & sTo, const altStr & sFrom)
{
  altChar * pBuf = NULL;
  alt_t     status;

  status = ALT_MALLOC (pBuf, (sFrom.GetLen() * 2 + 1));
  ALT_ERR_RET (status);

  mysql_real_escape_string (m_pMySQL, pBuf, sFrom.GetCStr(), sFrom.GetLen());
  sTo += pBuf;

  status = ALT_FREE (pBuf);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Execute Real Query
///
/// \param  sQuery  [I ] SQL
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::RealQuery(const altStr & sQuery)
{
  altInt nRet = mysql_real_query (m_pMySQL, sQuery.GetCStr(), sQuery.GetLen());
  if (nRet != 0) {
    ALT_RET_P (ALT_E_ERROR, Error().GetCStr());
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  This functions flushes tables or caches, or resets replication server information. 
///
/// \param  nOptions  [I ] Options
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::Refresh(altUInt nOptions)
{
  altInt nRet = mysql_refresh (m_pMySQL, nOptions);
  if (nRet != 0) {
    ALT_RET_P (ALT_E_ERROR, Error().GetCStr());
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Rollback
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::Rollback()
{
  my_bool nRet = mysql_rollback (m_pMySQL);
  if (nRet != 0) {
    ALT_RET_P (ALT_E_ERROR, Error().GetCStr());
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Select DB
///
/// \param  sDB [I ] DB Name
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::SelectDB(const altStr & sDB)
{
  altInt nRet = mysql_select_db (m_pMySQL, sDB.GetCStr());
  if (nRet != 0) {
    ALT_RET_P (ALT_E_ERROR, Error().GetCStr());
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set Character Set
///
/// \param  sCharsetName  [I ] Character Set Name
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::SetCharacterSet(const altStr & sCharsetName)
{
  altInt nRet = mysql_set_character_set (m_pMySQL, sCharsetName.GetCStr());
  if (nRet != 0) {
    ALT_RET_P (ALT_E_ERROR, Error().GetCStr());
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Call mysql_set_local_infile_default
///
/// \return ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altMySQL::SetLocalInfileDefault()
{
  mysql_set_local_infile_default (m_pMySQL);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Call mysql_set_local_infile_handler
///
/// \param  pInitFunc   [I ] Init Handler
/// \param  pReadFunc   [I ] Read Handler
/// \param  pEndFunc    [I ] End Handler
/// \param  pErrorFunc  [I ] Error Handler
/// \param  pUserData   [I ] User Data
///
/// \return ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altMySQL::SetLocalInfileHandler(local_infile_init pInitFunc, local_infile_read pReadFunc, local_infile_end pEndFunc, local_infile_error pErrorFunc, void * pUserData)
{
  mysql_set_local_infile_handler (m_pMySQL, pInitFunc, pReadFunc, pEndFunc, pErrorFunc, pUserData);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Shutdown MySQL Server
///
/// \param  nLevel  [I ] Shutdown Level
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::Shutdown(enum mysql_enum_shutdown_level nLevel)
{
  altInt nRet = mysql_shutdown (m_pMySQL, nLevel);
  if (nRet != 0) {
    ALT_RET_P (ALT_E_ERROR, Error().GetCStr());
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get State String
///
/// \return State String
///
LIBALT_API altStr altMySQL::SQLState()
{
  return mysql_sqlstate (m_pMySQL);
}

///
/// \brief  establishing secure connections using SSL
///
/// \param  szKey     [I ] the pathname to the key file
/// \param  szCert    [I ] the pathname to the certificate file.
/// \param  szCA      [I ] the pathname to the certificate authority file.
/// \param  szCAPath  [I ] the pathname to a directory that contains trusted SSL CA certificates in pem format.
/// \param  szCipher  [I ] a list of allowable ciphers to use for SSL encryption.
///
LIBALT_API void altMySQL::SSLSet(const altChar * szKey, const altChar * szCert, const altChar * szCA, const altChar * szCAPath, const altChar * szCipher)
{
  mysql_ssl_set (m_pMySQL, szKey, szCert, szCA, szCAPath, szCipher);
}

///
/// \brief  Returns a character string containing information
///
/// \return A character string describing the server status.
///
LIBALT_API altStr altMySQL::Stat()
{
  const altChar * szDesc = mysql_stat (m_pMySQL);
  if (szDesc == NULL) {
    ALT_LOG_P (ALT_E_ERROR, Error().GetCStr());
    return ("");
  }
  return (szDesc);
}

///
/// \brief  Store Query Result
///
/// \return result structure with the results.
///
LIBALT_API altMySQLRes altMySQL::StoreResult() ALT_THROWS (alt_t)
{
  MYSQL_RES * pRes = mysql_store_result (m_pMySQL);
  if (pRes == NULL) {
    ALT_LOG_P (ALT_E_ERROR, Error().GetCStr());
    throw (ALT_E_ERROR);
  }
  return altMySQLRes (pRes);
}

///
/// \brief  Get Thread ID
///
/// \return Thread ID
///
LIBALT_API altULong altMySQL::ThreadID()
{
  return mysql_thread_id (m_pMySQL);
}

///
/// \brief  Use Query Result
///
/// \return result structure with the results.
///
LIBALT_API altMySQLRes altMySQL::UseResult() ALT_THROWS (alt_t)
{
  MYSQL_RES * pRes = mysql_use_result (m_pMySQL);
  if (pRes == NULL) {
    ALT_LOG_P (ALT_E_ERROR, Error().GetCStr());
    throw (ALT_E_ERROR);
  }
  return altMySQLRes (pRes);
}

///
/// \brief  Get Warning Count
///
/// \return Warning Count
///
LIBALT_API altUInt altMySQL::WarningCount()
{
  return (mysql_warning_count (m_pMySQL));
}

///
/// \brief  Prepared Statement Init
///
/// \return Prepared Statement Object
///
LIBALT_API altMySQLStmt altMySQL::StmtInit() ALT_THROWS (alt_t)
{
  MYSQL_STMT * pStmt = mysql_stmt_init (m_pMySQL);
  if (pStmt == NULL) {
    ALT_LOG_P (ALT_E_ERROR, Error().GetCStr());
    throw (ALT_E_ERROR);
  }
  return altMySQLStmt (pStmt);
}

///
/// \brief  MySQL Library End
///
LIBALT_API void altMySQL::LibraryEnd()
{
  mysql_library_end();
}

///
/// \brief  MySQL Library Init
///
/// \param  argc    [I ] 
/// \param  argv    [I ] 
/// \param  groups  [I ]
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altMySQL::LibraryInit(altInt argc, altChar ** argv, altChar ** groups)
{
  altInt nRet = mysql_library_init (argc, argv, groups);
  if (nRet != 0) {
    ALT_RET (ALT_E_ERROR);
  }
  ALT_RET (ALT_S_SUCCESS);
}

