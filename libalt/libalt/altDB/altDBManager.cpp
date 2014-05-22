/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDBManager.cpp
 * \brief   DB connection manager class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altDBManager.h"
#include "altMySQLDBConnection.h"
#include "altBase/altUtil.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
/// \param  nDBType   [I ] DB Type
///
altDBManager::altDBManager(const altDBTypes nDBType) :
m_nDBType (nDBType),
m_oConnections ()
{
}

///
/// \brief  Destructor
///
altDBManager::~altDBManager()
{
  for (altDBConnectionContainer::iterator i = m_oConnections.begin(); i != m_oConnections.end(); i++) {
    delete (* i);
  }
  m_oConnections.clear();
}

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
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_NOMEM     Out of memory
/// \return ALT_E_ERROR     error
///
alt_t altDBManager::Init(const altStr & sHost, const altInt nPort, const altStr & sDB, const altStr & sUser, const altStr & sPasswd, const altStr & sCharset, const altUInt nPool)
{
  alt_t  status;
  for (altUInt i = 0; i < nPool; i++) {
    altDBConnection * pDBConnection = NULL;
    
    status = CreateDBConnection (pDBConnection);
    ALT_ERR_RET (status);

    status = pDBConnection->Connect (sHost, nPort, sDB, sUser, sPasswd, sCharset);
    ALT_ERR_RET (status);
    
    m_oConnections.push_back (pDBConnection);
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get DB Connection
///
/// \param  pDBConnection [ O] DB Connection
///
/// \return ALT_S_SUCCESS   Success
///
alt_t altDBManager::GetDBConnection(altDBConnectionPtr & pDBConnection)
{
  alt_t status;
  altDBConnection * pDBConn = NULL;
  
  status = GetDBConnection (pDBConn);
  ALT_ERR_RET (status);

  status = pDBConnection.Set(pDBConn, this);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Release DB Connection
///
/// \param  pDBConneection  [IO] DB Connection
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
alt_t altDBManager::ReleaseDBConnection(altDBConnection * & pDBConnection)
{
  if (pDBConnection == NULL) {
    ALT_RET_P (ALT_E_ERROR, "pDBConnection is NULL");
  }

  pDBConnection->Rollback();
  BeginLock();
  m_oConnections.push_back (pDBConnection);
  EndLock();
  pDBConnection = NULL;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get DB Connection
///
/// \param  pDBConnection [ O] DB Connection
///
/// \return ALT_S_SUCCESS   Success
///
alt_t altDBManager::GetDBConnection(altDBConnection * & pDBConnection)
{
  altUInt nCount = 0;
  while (1) {
    BeginLock();
    if (! m_oConnections.empty()) {
      pDBConnection = m_oConnections.back();
      m_oConnections.pop_back();
      EndLock();
      ALT_RET (ALT_S_SUCCESS);
    }
    EndLock();
    if (nCount % 10 == 0) {
      ALT_LOG_P (ALT_W_WARNING, "Wating DB Connection");
    }
    nCount++;
    altSleep (1000);
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Create DB Connection
///
/// \param  pDBConnection [ O] DB Connection
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_NOMEM     Out of memory
/// \return ALT_E_ERROR     Error
///
alt_t altDBManager::CreateDBConnection(altDBConnection * & pDBConnection)
{
  switch (m_nDBType) {
    case  ALT_DB_TYPE_MYSQL:
      pDBConnection = ALT_NEW altMySQLDBConnection();
      break;
    default:
      altStr  sBuf;
      ALT_LOG_P (ALT_E_ERROR, sBuf.Format("Unknown DB Type[%d]", m_nDBType));
  }
  ALT_RET (ALT_S_SUCCESS);
}

