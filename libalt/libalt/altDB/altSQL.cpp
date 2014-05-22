/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSQL.cpp
 * \brief   SQL class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altSQL.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altSQL::altSQL() :
m_sSQL(),
m_sSQLName()
{
}

///
/// \brief  Copy Constructor
///
/// \param  oSQL  [I ] SQL
///
LIBALT_API altSQL::altSQL(const altSQL & oSQL) : 
m_sSQL(oSQL.m_sSQL),
m_sSQLName(oSQL.m_sSQLName)
{
}

///
/// \brief  Destructor
///
LIBALT_API altSQL::~altSQL()
{
}

///
/// \brief  Set SQL
///
/// \param  sSQL      [I ] SQL
/// \param  sSQLName  [I ] SQL Name
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altSQL::SetSQL(const altStr & sSQL, const altStr & sSQLName)
{
  m_sSQL = sSQL;
  m_sSQLName = sSQLName;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get SQL
///
/// \return SQL
///
LIBALT_API const altStr & altSQL::GetSQL() const
{
  return (m_sSQL);
}

///
/// \brief  Get SQL Name
///
/// \return SQL Name
///
LIBALT_API const altStr & altSQL::GetSQLName() const
{
  return (m_sSQLName);
}

///
/// \brief  Set Value
///
/// \param  sVarName  [I ] Variable Name
/// \param  sValue    [I ] Value
///
/// \return ALT_S_SUCCESS
///
LIBALT_API alt_t altSQL::Set(const altStr & sVarName, const altStr & sValue)
{
  m_sSQL.ReplaceAll (sVarName, sValue);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set Value
///
/// \param  sVarName  [I ] Variable Name
/// \param  nVal      [I ] Value
///
/// \param  ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altSQL::SetChar(const altStr & sVarName, const altChar nVal)
{
  altStr  sVal;
  m_sSQL.ReplaceAll (sVarName, sVal.SetChar (nVal));
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set Value
///
/// \param  sVarName  [I ] Variable Name
/// \param  nVal      [I ] Value
///
/// \param  ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altSQL::SetUChar(const altStr & sVarName, const altUChar nVal)
{
  altStr  sVal;
  m_sSQL.ReplaceAll (sVarName, sVal.SetUChar (nVal));
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set Value
///
/// \param  sVarName  [I ] Variable Name
/// \param  nVal      [I ] Value
///
/// \param  ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altSQL::SetByte(const altStr & sVarName, const altByte nVal)
{
  altStr  sVal;
  m_sSQL.ReplaceAll (sVarName, sVal.SetByte (nVal));
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set Value
///
/// \param  sVarName  [I ] Variable Name
/// \param  nVal      [I ] Value
///
/// \param  ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altSQL::SetShort(const altStr & sVarName, const altShort nVal)
{
  altStr  sVal;
  m_sSQL.ReplaceAll (sVarName, sVal.SetShort (nVal));
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set Value
///
/// \param  sVarName  [I ] Variable Name
/// \param  nVal      [I ] Value
///
/// \param  ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altSQL::SetUShort(const altStr & sVarName, const altUShort nVal)
{
  altStr  sVal;
  m_sSQL.ReplaceAll (sVarName, sVal.SetUShort (nVal));
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set Value
///
/// \param  sVarName  [I ] Variable Name
/// \param  nVal      [I ] Value
///
/// \param  ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altSQL::SetInt(const altStr & sVarName, const altInt nVal)
{
  altStr  sVal;
  m_sSQL.ReplaceAll (sVarName, sVal.SetInt (nVal));
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set Value
///
/// \param  sVarName  [I ] Variable Name
/// \param  nVal      [I ] Value
///
/// \param  ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altSQL::SetUInt(const altStr & sVarName, const altUInt nVal)
{
  altStr  sVal;
  m_sSQL.ReplaceAll (sVarName, sVal.SetUInt (nVal));
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set Value
///
/// \param  sVarName  [I ] Variable Name
/// \param  nVal      [I ] Value
///
/// \param  ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altSQL::SetLong(const altStr & sVarName, const altLong nVal)
{
  altStr  sVal;
  m_sSQL.ReplaceAll (sVarName, sVal.SetLong (nVal));
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set Value
///
/// \param  sVarName  [I ] Variable Name
/// \param  nVal      [I ] Value
///
/// \param  ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altSQL::SetULong(const altStr & sVarName, const altULong nVal)
{
  altStr  sVal;
  m_sSQL.ReplaceAll (sVarName, sVal.SetULong (nVal));
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set Value
///
/// \param  sVarName  [I ] Variable Name
/// \param  dwVal     [I ] Value
///
/// \param  ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altSQL::SetDWORD(const altStr & sVarName, const DWORD dwVal)
{
  altStr  sVal;
  m_sSQL.ReplaceAll (sVarName, sVal.SetDWORD (dwVal));
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set Value
///
/// \param  sVarName  [I ] Variable Name
/// \param  nVal      [I ] Value
///
/// \param  ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altSQL::SetLongLong(const altStr & sVarName, const altLongLong nVal)
{
  altStr  sVal;
  m_sSQL.ReplaceAll (sVarName, sVal.SetLongLong (nVal));
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set Value
///
/// \param  sVarName  [I ] Variable Name
/// \param  nVal      [I ] Value
///
/// \param  ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altSQL::SetULongLong(const altStr & sVarName, const altULongLong nVal)
{
  altStr  sVal;
  m_sSQL.ReplaceAll (sVarName, sVal.SetULongLong (nVal));
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set Value
///
/// \param  sVarName  [I ] Variable Name
/// \param  sVal      [I ] Value
///
/// \param  ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altSQL::SetStr(const altStr & sVarName, const altStr & sVal)
{
  altStr  sTmp;
  sTmp += "'";
  sTmp += sVal;
  sTmp += "'";
  m_sSQL.ReplaceAll (sVarName, sTmp);
  ALT_RET (ALT_S_SUCCESS);
}

