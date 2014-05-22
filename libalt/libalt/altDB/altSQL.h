#ifndef ALTSQL_H
#define ALTSQL_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSQL.h
 * \brief   SQL class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altStr.h>
#include <altBase/altStatus.h>
#include <altBase/altLog.h>
#include <altBase/altBase.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  SQL
///
class altSQL : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altSQL();

  ///
  /// \brief  Copy Constructor
  ///
  /// \param  oSQL  [I ] SQL
  ///
  LIBALT_API altSQL(const altSQL & oSQL);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altSQL();

  ///
  /// \brief  Set SQL
  ///
  /// \param  sSQL      [I ] SQL
  /// \param  sSQLName  [I ] SQL Name
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetSQL(const altStr & sSQL, const altStr & sSQLName);

  ///
  /// \brief  Get SQL
  ///
  /// \return SQL
  ///
  LIBALT_API const altStr & GetSQL() const;

  ///
  /// \brief  Get SQL Name
  ///
  /// \return SQL Name
  ///
  LIBALT_API const altStr & GetSQLName() const;

  ///
  /// \brief  Set Value
  ///
  /// \param  sVarName  [I ] Variable Name
  /// \param  sValue    [I ] Value
  ///
  /// \return ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t Set(const altStr & sVarName, const altStr & sValue);

  ///
  /// \brief  Set Value
  ///
  /// \param  sVarName  [I ] Variable Name
  /// \param  nVal      [I ] Value
  ///
  /// \param  ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t SetChar(const altStr & sVarName, const altChar nVal);

  ///
  /// \brief  Set Value
  ///
  /// \param  sVarName  [I ] Variable Name
  /// \param  nVal      [I ] Value
  ///
  /// \param  ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t SetUChar(const altStr & sVarName, const altUChar nVal);

  ///
  /// \brief  Set Value
  ///
  /// \param  sVarName  [I ] Variable Name
  /// \param  nVal      [I ] Value
  ///
  /// \param  ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t SetByte(const altStr & sVarName, const altByte nVal);

  ///
  /// \brief  Set Value
  ///
  /// \param  sVarName  [I ] Variable Name
  /// \param  nVal      [I ] Value
  ///
  /// \param  ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t SetShort(const altStr & sVarName, const altShort nVal);

  ///
  /// \brief  Set Value
  ///
  /// \param  sVarName  [I ] Variable Name
  /// \param  nVal      [I ] Value
  ///
  /// \param  ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t SetUShort(const altStr & sVarName, const altUShort nVal);

  ///
  /// \brief  Set Value
  ///
  /// \param  sVarName  [I ] Variable Name
  /// \param  nVal      [I ] Value
  ///
  /// \param  ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t SetInt(const altStr & sVarName, const altInt nVal);

  ///
  /// \brief  Set Value
  ///
  /// \param  sVarName  [I ] Variable Name
  /// \param  nVal      [I ] Value
  ///
  /// \param  ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t SetUInt(const altStr & sVarName, const altUInt nVal);

  ///
  /// \brief  Set Value
  ///
  /// \param  sVarName  [I ] Variable Name
  /// \param  nVal      [I ] Value
  ///
  /// \param  ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t SetLong(const altStr & sVarName, const altLong nVal);

  ///
  /// \brief  Set Value
  ///
  /// \param  sVarName  [I ] Variable Name
  /// \param  nVal      [I ] Value
  ///
  /// \param  ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t SetULong(const altStr & sVarName, const altULong nVal);

  ///
  /// \brief  Set Value
  ///
  /// \param  sVarName  [I ] Variable Name
  /// \param  dwVal     [I ] Value
  ///
  /// \param  ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t SetDWORD(const altStr & sVarName, const DWORD dwVal);

  ///
  /// \brief  Set Value
  ///
  /// \param  sVarName  [I ] Variable Name
  /// \param  nVal      [I ] Value
  ///
  /// \param  ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t SetLongLong(const altStr & sVarName, const altLongLong nVal);

  ///
  /// \brief  Set Value
  ///
  /// \param  sVarName  [I ] Variable Name
  /// \param  nVal      [I ] Value
  ///
  /// \param  ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t SetULongLong(const altStr & sVarName, const altULongLong nVal);

  ///
  /// \brief  Set Value
  ///
  /// \param  sVarName  [I ] Variable Name
  /// \param  sVal      [I ] Value
  ///
  /// \param  ALT_S_SUCCESS   Success
  ///
  LIBALT_API alt_t SetStr(const altStr & sVarName, const altStr & sVal);

private:
  altStr  m_sSQL;     ///< SQL
  altStr  m_sSQLName; ///< SQL Name
};

#endif // ALTSQL_H

