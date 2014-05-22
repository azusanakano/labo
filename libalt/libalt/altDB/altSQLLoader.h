#ifndef ALTSQLLOADER_H
#define ALTSQLLOADER_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSQLLoader.h
 * \brief   SQL loader class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altDB/altSQL.h>
#include <altDB/altDBConnection.h>

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
///
/// \brief  Get Instance
///
/// \return altSQLLoader Instance
///
#define aiSQLLoader altSQLLoader::GetInstance()

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef std::map<altStr, altChar *> altSQLContainer;

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  SQL Loader
///
class altSQLLoader : public altSingleton<altSQLLoader>
{
friend class altSingleton<altSQLLoader>;
protected:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altSQLLoader();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altSQLLoader();

public:
  ///
  /// \brief  Set Directory
  ///
  /// \param  sDir  [I ] Directory Path
  ///
  /// \return ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t SetDir(const altStr & sDir);

  ///
  /// \brief  Get SQL
  ///
  /// \param  sFilePath   [I ] File Path
  /// \param  oSQL        [ O] SQL
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_ERROR     Error
  ///
  LIBALT_API alt_t GetSQL(const altStr & sFilePath, altSQL & oSQL);

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
  LIBALT_API alt_t GetSQL(const altStr & sFilePath, altDBConnection & oDBConnection, altPreparedStatement * & pStmt);

private:
  altSQLContainer m_oSQLContainer;  ///< SQL Container
  altStr          m_sBaseDir;       ///< SQL Base Directory
};
#endif  //ALTSQLLOADER_H
