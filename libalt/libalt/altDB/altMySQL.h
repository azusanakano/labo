#ifndef ALTMYSQL_H
#define ALTMYSQL_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMySQL.h
 * \brief   MySQL class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altDB/altMySQLRes.h>
#include <altDB/altMySQLStmt.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  MySQL Class
///
class altMySQL : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altMySQL();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altMySQL();

  ///
  /// \brief  Get Affected Row Count
  ///
  /// \return Affected Row Count
  ///
  LIBALT_API altULongLong GetAffectedRow();

  ///
  /// \brief  Set AutCommit Mode
  ///
  /// \param  bAutoCommit true...auto commit false...not auto commit
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t SetAutoCommit(const altBool bAutoCommit);

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
  LIBALT_API alt_t ChangeUser(const altStr & sUser, const altStr & sPasswd, const altChar * szDB = NULL);

  ///
  /// \brief  Get Default Character Set Name
  ///
  /// \param  sCharSetName  [ O] Default Character Set Name
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t GetCharacterSetName(altStr & sCharSetName);

  ///
  /// \brief  Close
  ///
  /// \return ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t Close();

  ///
  /// \brief  Commit
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t Commit();

  ///
  /// \brief  Dump Debug Info
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t DumpDebugInfo();

  ///
  /// \brief  Get errno
  ///
  /// \return Error Number
  ///
  LIBALT_API altUInt ErrorNo();

  ///
  /// \brief  Get Error Message
  ///
  /// \return Error Message
  ///
  LIBALT_API altStr Error();

  ///
  /// \brief  Get Field Count
  ///
  /// \return Field Count
  ///
  LIBALT_API altInt GetFieldCount();

  ///
  /// \brief  Get Character Set Info
  ///
  /// \param  pCharSetInfo  [ O] Character Set Infomation
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t GetCharacterSetInfo(MY_CHARSET_INFO * pCharSetInfo);

  ///
  /// \brief  Get Client Info
  ///
  /// \return Client Info
  ///
  LIBALT_API altStr GetClientInfo();

  ///
  /// \brief  Get Client Version
  ///
  /// \return Client Version
  ///
  LIBALT_API altULong GetClientVersion();

  ///
  /// \brief  Get Host Info
  ///
  /// \return Host Info
  ///
  LIBALT_API altStr GetHostInfo();

  ///
  /// \brief  Get Protocol Info
  ///
  /// \return Protocol Info
  ///
  LIBALT_API altUInt GetProtoInfo();

  ///
  /// \brief  Get Server Info
  ///
  /// \return Server Info
  ///
  LIBALT_API altStr GetServerInfo();

  ///
  /// \brief  Get Server Version
  ///
  /// \return Server Version
  ///
  LIBALT_API altULong GetServerVersion();

  ///
  /// \brief  Get Statement Info
  ///
  /// \return Statement Info
  ///
  LIBALT_API altStr Info();

  ///
  /// \brief  Get Insert ID
  ///
  /// \return Insert ID
  ///
  LIBALT_API altULongLong InsertID();

  ///
  /// \brief  KILL
  ///
  /// \param  nPid  [I ] Proccess ID
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t Kill(const altULong nPid);

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
  LIBALT_API alt_t ListDBS(const altStr & sWild, altPtr<altMySQLRes> pRes);

  ///
  /// \brief  Get Current Server Threads
  ///
  /// \param  pRes  [ O] Current Server Threads
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  /// \return ALT_E_NOMEM     Out of memory
  ///
  LIBALT_API alt_t ListProcesses(altPtr<altMySQLRes> pRes);

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
  LIBALT_API alt_t ListTables(const altStr & sWild, altPtr<altMySQLRes> pRes);

  ///
  /// \brief  Check More Results
  ///
  /// \return true  Results exsit
  /// \return false Not More Results exsit
  ///
  LIBALT_API altBool MoreResults();

  ///
  /// \brief  Check Next Results
  ///
  /// \return ALT_S_SUCCESS         Successful and there are more results
  /// \return ALT_S_NO_MORE_RESULT  Successful and there are no more results
  /// \return ALT_E_ERROR           An error occurred
  ///
  LIBALT_API alt_t NextResults();

  ///
  /// \brief  Returns the number of columns in a result set.
  ///
  /// \return the number of columns in a result set.
  ///
  LIBALT_API altUInt NumFields();

  ///
  /// \brief  Set extra connect options
  ///
  /// \param  nOption [I ] Option Number
  /// \param  pArg    [I ] Arguments
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t Options(mysql_option nOption, const altChar * pArg);

  ///
  /// \brief  Checks whether the connection to the server is working
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t Ping();

  ///
  /// \brief  Execute Query
  ///
  /// \param  sQuery  [I ] SQL
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t Query(const altStr & sQuery);

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
  LIBALT_API alt_t Connect(const altStr & sHost, const altStr & sUser, const altStr & sPasswd, const altStr & sDB, const altInt nPort, const altChar * szUnixSocket = NULL, altULong nClientFlag = 0);

  ///
  /// \brief  Escape String
  ///
  /// \param  sTo   [ O] Escape Result
  /// \param  sFrom [I ] String
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_NOMEM     Out of memory
  ///
  LIBALT_API alt_t EscapeString(altStr & sTo, const altStr & sFrom);

  ///
  /// \brief  Execute Real Query
  ///
  /// \param  sQuery  [I ] SQL
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t RealQuery(const altStr & sQuery);

  ///
  /// \brief  This functions flushes tables or caches, or resets replication server information. 
  ///
  /// \param  nOptions  [I ] Options
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t Refresh(altUInt nOptions);

  ///
  /// \brief  Rollback
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t Rollback();

  ///
  /// \brief  Select DB
  ///
  /// \param  sDB [I ] DB Name
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t SelectDB(const altStr & sDB);

  ///
  /// \brief  Set Character Set
  ///
  /// \param  sCharsetName  [I ] Character Set Name
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t SetCharacterSet(const altStr & sCharsetName);

  ///
  /// \brief  Call mysql_set_local_infile_default
  ///
  /// \return ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t SetLocalInfileDefault();

  typedef int (* local_infile_init)(void **, const char *, void *);
  typedef int (* local_infile_read)(void *, char *, unsigned int);
  typedef void (* local_infile_end)(void *);
  typedef int (* local_infile_error)(void *, char *, unsigned int);
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
  LIBALT_API alt_t SetLocalInfileHandler(local_infile_init pInitFunc, local_infile_read pReadFunc, local_infile_end pEndFunc, local_infile_error pErrorFunc, void * pUserData);

  ///
  /// \brief  Shutdown MySQL Server
  ///
  /// \param  nLevel  [I ] Shutdown Level
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t Shutdown(enum mysql_enum_shutdown_level nLevel);

  ///
  /// \brief  Get State String
  ///
  /// \return State String
  ///
  LIBALT_API altStr SQLState();

  ///
  /// \brief  establishing secure connections using SSL
  ///
  /// \param  szKey     [I ] the pathname to the key file
  /// \param  szCert    [I ] the pathname to the certificate file.
  /// \param  szCA      [I ] the pathname to the certificate authority file.
  /// \param  szCAPath  [I ] the pathname to a directory that contains trusted SSL CA certificates in pem format.
  /// \param  szCipher  [I ] a list of allowable ciphers to use for SSL encryption.
  ///
  LIBALT_API void SSLSet(const altChar * szKey, const altChar * szCert, const altChar * szCA, const altChar * szCAPath, const altChar * szCipher);

  ///
  /// \brief  Returns a character string containing information
  ///
  /// \return A character string describing the server status.
  ///
  LIBALT_API altStr Stat();

  ///
  /// \brief  Store Query Result
  ///
  /// \return result structure with the results.
  ///
  LIBALT_API altMySQLRes StoreResult() ALT_THROWS (alt_t);

  ///
  /// \brief  Get Thread ID
  ///
  /// \return Thread ID
  ///
  LIBALT_API altULong ThreadID();

  ///
  /// \brief  Use Query Result
  ///
  /// \return result structure with the results.
  ///
  LIBALT_API altMySQLRes UseResult() ALT_THROWS (alt_t);

  ///
  /// \brief  Get Warning Count
  ///
  /// \return Warning Count
  ///
  LIBALT_API altUInt WarningCount();

  ///
  /// \brief  Prepared Statement Init
  ///
  /// \return Prepared Statement Object
  ///
  LIBALT_API altMySQLStmt StmtInit() ALT_THROWS (alt_t);

  ///
  /// \brief  MySQL Library End
  ///
  LIBALT_API static void LibraryEnd();

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
  LIBALT_API static alt_t LibraryInit(altInt argc, altChar ** argv, altChar ** groups);

private:
  static altBool  bInitDone;    ///< Init Done or not
  MYSQL *         m_pMySQL;     ///< Pointer of MySQL structure
};

#endif	// ALT_MYSQL_H
