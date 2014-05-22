#ifndef ALTDBRESULTSET_H
#define ALTDBRESULTSET_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDBResultSet.h
 * \brief   DB result set class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altDB/altDBRow.h>

#include <vector>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef std::vector<altDBRow> altResultContainer; ///< DB Record Container

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Result Set
///
class altDBResultSet : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altDBResultSet();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altDBResultSet();

  ///
  /// \brief  Add Row
  ///
  /// \param  oRow  [I ] Row Data
  ///
  /// \return ALT_S_SUCCESS
  ///
  LIBALT_API alt_t Add(const altDBRow & oRow);

  ///
  /// \brief  Get Size
  ///
  /// \return Row Count
  ///
  LIBALT_API altUInt Size() const;

  ///
  /// \brief  [] operator
  ///
  /// \param  nIndex [I ] index
  ///
  /// \return Row Data of index position
  ///
  LIBALT_API const altDBRow & operator [](const altUInt nIndex) const ALT_THROWS (alt_t);

private:
  altResultContainer  m_oResultData;  ///< DB Result Set Data
};

#endif //ALTDBRESULTSET_H

