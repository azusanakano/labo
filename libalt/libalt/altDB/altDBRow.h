#ifndef ALTDBROW_H
#define ALTDBROW_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDBRow.h
 * \brief   DB result row class
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

#include <vector>
#include <map>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef std::vector<altChar *>      altRowContainer;  ///< Result Row Data Container
typedef std::map<altStr, altChar *> altRowMap;        ///< Result Row Data Map

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Result Record Row
///
class altDBRow : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  altDBRow();

  ///
  /// \brief  Destructor
  ///
  ~altDBRow();

  ///
  /// \brief  Add Column
  ///
  /// \param  sColumnName [I ] Column Name
  /// \param  pValue      [I ] Column Value
  /// \param  nValueSize  [I ] Column Value Size
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_NOMEM     out of memory
  ///
  alt_t Add(const altStr & sColumnName, altChar * pValue, const altUInt nValueSize);

  ///
  /// \brief  Get Size
  ///
  /// \return Row Count
  ///
  altUInt Size() const;

  ///
  /// \brief  [] operator
  ///
  /// \param  nIndex [I ] index
  ///
  /// \return Column Value
  ///
  LIBALT_API altChar * operator [](const altUInt nIndex) const ALT_THROWS (alt_t);

  ///
  /// \brief  [] operator
  ///
  /// \param  sColumnName [I ] Column Name
  ///
  /// \return Column Value
  ///
  LIBALT_API altChar * operator [](const altStr & sColumnName) const;

private:
  altRowContainer   m_oDataList;  ///< Result Data List
  mutable altRowMap m_oDataMap;   ///< Result Data Map
};

#endif //ALTDBROW_H

