#ifndef ALTDBMANAGER_H
#define ALTDBMANAGER_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDBManager.h
 * \brief   DB connection manager class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altDB/altDBConnectionPtr.h>
#include <altBase/altSyncThread.h>

#include <vector>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
///
/// \brief  Data Base Type
///
enum altDBTypes {
  ALT_DB_TYPE_MYSQL = 0,    ///< MySQL
};

typedef std::vector<altDBConnection *> altDBConnectionContainer;

class altDBConnectionPtr;
/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  DB Connection Manager
///
class altDBManager : public altBase, private altSyncThread
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  nDBType   [I ] DB Type
  ///
  altDBManager(const altDBTypes nDBType);

  ///
  /// \brief  Destructor
  ///
  ~altDBManager();

  ///
  /// \brief  Initialize
  ///
  /// \param  sHost     [I ] DB Host Name
  /// \param  nPort     [I ] DB Port Number
  /// \param  sDB       [I ] DB Name
  /// \param  sUser     [I ] DB User ID
  /// \param  sPasswd   [I ] DB Password
  /// \param  sCharset  [I ] DB Character Set
  /// \param  nPool     [I ] DB Connection Pool Count
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_NOMEM     Out of memory
  /// \return ALT_E_ERROR     Error
  ///
  alt_t Init(const altStr & sHost, const altInt nPort, const altStr & sDB, const altStr & sUser, const altStr & sPasswd, const altStr & sCharset, const altUInt nPool);

  ///
  /// \brief  Get DB Connection
  ///
  /// \param  pDBConnection [ O] DB Connection
  ///
  /// \return ALT_S_SUCCESS   Success
  ///
  alt_t GetDBConnection(altDBConnectionPtr & pDBConnection);

  ///
  /// \brief  Release DB Connection
  ///
  /// \param  pDBConneection  [IO] DB Connection
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  alt_t ReleaseDBConnection(altDBConnection * & pDBConnection);

private:
  ///
  /// \brief  Get DB Connection
  ///
  /// \param  pDBConnection [ O] DB Connection
  ///
  /// \return ALT_S_SUCCESS   Success
  ///
  alt_t GetDBConnection(altDBConnection * & pDBConnection);

  ///
  /// \brief  Create DB Connection
  ///
  /// \param  pDBConnection [ O] DB Connection
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_NOMEM     Out of memory
  /// \return ALT_E_ERROR     Error
  ///
  alt_t CreateDBConnection(altDBConnection * & pDBConnection);


  altDBTypes                m_nDBType;        ///< DB Type
  altDBConnectionContainer  m_oConnections;   ///< DB Connection Container
};

#endif //ALTDBMANAGER_H
