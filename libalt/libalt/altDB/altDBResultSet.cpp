/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDBResultSet.cpp
 * \brief   DB result set class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altDBResultSet.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altDBResultSet::altDBResultSet()
{
}

///
/// \brief  Destructor
///
LIBALT_API altDBResultSet::~altDBResultSet()
{
}

///
/// \brief  Add Row
///
/// \param  oRow  [I ] Row Data
///
/// \return ALT_S_SUCCESS
///
LIBALT_API alt_t altDBResultSet::Add(const altDBRow & oRow)
{
  m_oResultData.push_back (oRow);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Size
///
/// \return Row Count
///
LIBALT_API altUInt altDBResultSet::Size() const
{
  return ((altUInt)m_oResultData.size());
}

///
/// \brief  [] operator
///
/// \param  nIndex [I ] index
///
/// \return Row Data of index position
///
LIBALT_API const altDBRow & altDBResultSet::operator [](const altUInt nIndex) const ALT_THROWS (alt_t)
{
  if (nIndex >= Size()) {
    altStr sBuf;
    ALT_LOG_P (ALT_E_OUT_OF_INDEX, sBuf.Format ("[%u] >= [%u]", nIndex, Size()));
    throw (ALT_E_OUT_OF_INDEX);
  }
  return (m_oResultData[nIndex]);
}


