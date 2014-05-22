/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSQLLoader.cpp
 * \brief   SQL loader class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altSQLLoader.h"
#include "altMisc/altFile.h"
#include "altBase/altMem.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altSQLLoader::altSQLLoader() :
m_oSQLContainer(),
m_sBaseDir()
{
}

///
/// \brief  Destructor
///
LIBALT_API altSQLLoader::~altSQLLoader()
{
  for (altSQLContainer::iterator i = m_oSQLContainer.begin(); i != m_oSQLContainer.end(); i++) {
    ALT_FREE (i->second);
  }
  m_oSQLContainer.clear();
}

///
/// \brief  Set Directory
///
/// \param  sDir  [I ] Directory Path
///
/// \return ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altSQLLoader::SetDir(const altStr & sDir)
{
  m_sBaseDir = sDir;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get SQL
///
/// \param  sFilePath   [I ] File Path
/// \param  oSQL        [ O] SQL
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altSQLLoader::GetSQL(const altStr & sFilePath, altSQL & oSQL)
{
  altStr  sPath;
  altStr  sSQL;

  if (m_sBaseDir.GetLen() > 0) {
    sPath += m_sBaseDir;
    sPath += "/";
  }
  sPath += sFilePath;

  alt_t status;
  altChar * szSQL = m_oSQLContainer[sPath];
  if (szSQL != NULL) {
    status = oSQL.SetSQL (szSQL, sFilePath);
    ALT_ERR_RET (status);
    ALT_RET (ALT_S_SUCCESS);
  }

  altFile oFile;

  status = oFile.Open (sPath, "r");
  ALT_ERR_RET (status);

  altChar szBuf[BUFSIZ];
  while ((status = oFile.ReadLine (szBuf, sizeof (szBuf))) == ALT_S_SUCCESS) {
    // comment
    if (szBuf[0] == '#') {
      continue;
    }
    sSQL += szBuf;
  }

  status = oFile.Close();
  ALT_ERR_RET (status);

  status = ALT_STRALLOC (szSQL, sSQL.GetCStr());
  ALT_ERR_RET (status);
  m_oSQLContainer[sPath] = szSQL;

  status = oSQL.SetSQL (szSQL, sFilePath);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Prepared Statement SQL
///
/// \param  sFilePath     [I ] File Path
/// \param  oDBConnection [I ] DB Connection
/// \param  pStmt         [ O] Prepared Statement SQL
///
/// \return ALT_S_SUCCESS   Success
/// \return ALT_E_ERROR     Error
///
LIBALT_API alt_t altSQLLoader::GetSQL(const altStr & sFilePath, altDBConnection & oDBConnection, altPreparedStatement * & pStmt)
{
  alt_t   status;
  altSQL  oSQL;

  status = GetSQL (sFilePath, oSQL);
  ALT_ERR_RET (status);

  status = oDBConnection.GetPreparedStatement (oSQL, pStmt);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}
