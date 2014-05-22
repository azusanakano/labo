#ifndef ALTPREPAREDSTATEMENT_H
#define ALTPREPAREDSTATEMENT_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altPreparedStatement.h
 * \brief   Prepared statement class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altBase.h>
#include <altDB/altSQL.h>
#include <altDB/altDBResultSet.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Prepared Statement
///
class altPreparedStatement : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  oSQL  [I ] SQL
  ///
  LIBALT_API altPreparedStatement(const altSQL & oSQL);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altPreparedStatement();

  ///
  /// \brief  Get SQL Name
  ///
  /// \return SQL Name
  ///
  LIBALT_API const altStr & GetSQLName() const;

  ///
  /// \brief  Execute
  ///
  /// \param  oResultSet  [ O] Result Set
  ///
  LIBALT_API virtual alt_t ExcecuteSQL(altDBResultSet & oResultSet) = 0;

  ///
  /// \brief  Execute
  ///
  /// \param  pCount      [ O] Affected Count
  ///
  LIBALT_API virtual alt_t ExcecuteSQL(altULongLong * pCount) = 0;

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API virtual alt_t Add(const altChar nVal, const altBool bIsNULL = false) = 0;

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API virtual alt_t Add(const altByte nVal, const altBool bIsNULL = false) = 0;

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API virtual alt_t Add(const altShort nVal, const altBool bIsNULL = false) = 0;

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API virtual alt_t Add(const altUShort nVal, const altBool bIsNULL = false) = 0;

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API virtual alt_t Add(const altInt nVal, const altBool bIsNULL = false) = 0;

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API virtual alt_t Add(const altUInt nVal, const altBool bIsNULL = false) = 0;

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API virtual alt_t Add(const altLong nVal, const altBool bIsNULL = false) = 0;

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API virtual alt_t Add(const altULong nVal, const altBool bIsNULL = false) = 0;

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API virtual alt_t Add(const altLongLong nVal, const altBool bIsNULL = false) = 0;

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API virtual alt_t Add(const altULongLong nVal, const altBool bIsNULL = false) = 0;

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API virtual alt_t Add(const altFloat nVal, const altBool bIsNULL = false) = 0;

  ///
  /// \brief  Add Value
  ///
  /// \param  nVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API virtual alt_t Add(const altDouble nVal, const altBool bIsNULL = false) = 0;

  ///
  /// \brief  Add Value
  ///
  /// \param  sVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API virtual alt_t Add(const altStr & sVal, const altBool bIsNULL = false) = 0;

  ///
  /// \brief  Add Value
  ///
  /// \param  oVal    [I ] Value
  /// \param  bIsNULL [I ] true...null false...not null
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API virtual alt_t Add(const altDateTime & oVal, const altBool bIsNULL = false) = 0;

  ///
  /// \brief  Clear Value
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API virtual alt_t Clear() = 0;

  ///
  /// \brief  Get SQL String
  ///
  /// \return SQL String
  ///
  LIBALT_API virtual altStr toString() const = 0;

protected:
  altSQL    m_oSQL;   ///< SQL
};

#endif //ALTPREPAREDSTATEMENT_H
