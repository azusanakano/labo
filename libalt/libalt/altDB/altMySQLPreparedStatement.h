#ifndef ALTMYSQLPREPAREDSTATEMENT_H
#define ALTMYSQLPREPAREDSTATEMENT_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMySQLPreparedStatement.h
 * \brief   MySQL prepared statement class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altDB/altPreparedStatement.h>
#include <altDB/altMySQLStmt.h>
#include <altDB/altMySQLRes.h>
#include <altDB/altMySQL.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  MySQL Prepared Statement
///
class altMySQLPreparedStatement : public altPreparedStatement
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  oSQL  [I ] SQL
  ///
  LIBALT_API altMySQLPreparedStatement(const altSQL & oSQL, altMySQL & oMySQL);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altMySQLPreparedStatement();

  ///
  /// \brief  Prepare
  ///
  /// \param  oMySQL  [I ] MySQL Object
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_SQL       SQL Error
  ///
  LIBALT_API alt_t Prepare();

  ///
  /// \brief  Execute
  ///
  /// \param  oResultSet  [ O] Result Set
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_SQL       SQL Error
  ///
  LIBALT_API alt_t ExcecuteSQL(altDBResultSet & oResultSet);

  ///
  /// \brief  Execute
  ///
  /// \param  pAffectedRow  [ O] Affected Count
  ///
  /// \return ALT_S_SUCCESS   Success
  /// \return ALT_E_SQL       SQL Error
  ///
  LIBALT_API alt_t ExcecuteSQL(altULongLong * pAffectedRow);

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Add(const altChar nVal, const altBool bIsNULL = false);

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Add(const altByte nVal, const altBool bIsNULL = false);

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Add(const altShort nVal, const altBool bIsNULL = false);

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Add(const altUShort nVal, const altBool bIsNULL = false);

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Add(const altInt nVal, const altBool bIsNULL = false);

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Add(const altUInt nVal, const altBool bIsNULL = false);

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Add(const altLong nVal, const altBool bIsNULL = false);

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Add(const altULong nVal, const altBool bIsNULL = false);

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Add(const altLongLong nVal, const altBool bIsNULL = false);

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Add(const altULongLong nVal, const altBool bIsNULL = false);

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Add(const altFloat nVal, const altBool bIsNULL = false);

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Add(const altDouble nVal, const altBool bIsNULL = false);

  ///
  /// \brief  Add Value
  ///
  /// \param  sVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Add(const altStr & sVal, const altBool bIsNULL = false);

  ///
  /// \brief  Add Value
  ///
  /// \param  oVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Add(const altDateTime & oVal, const altBool bIsNULL = false);

  ///
  /// \brief  Clear Query Parameter
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t Clear();

  ///
  /// \brief  Get SQL String
  ///
  /// \return SQL String
  ///
  LIBALT_API altStr toString() const;

private:
  ///
  /// \brief	Extend Query Buffer
  ///
  /// \return ALT_S_SUCCESS	Success
  /// \return ALT_E_NOMEM		Out of Memory
  ///
  alt_t ExntendQueryBuffer();

  ///
  /// \brief	Bind Query Buffer
  ///
  /// \return ALT_S_SUCCESS Success
  /// \return ALT_E_SQL     SQL Error
  ///
  alt_t BindParam();

  altMySQL        m_oMySQL;
  altMySQLStmt    m_oMySQLStmt;
  
	MYSQL_BIND *    m_pQueryBind;
	my_bool *       m_pQueryIsNULL;
	DWORD *         m_pQueryLength;
	altUInt         m_nParamCount;

  altMySQLRes     m_oMetaResult;
	MYSQL_BIND *    m_pResultBind;
	my_bool *       m_pResultIsNULL;
	DWORD *         m_pResultLength;
	my_bool *       m_pResultError;
	altUInt         m_nResultColumnCount;
};

#endif

