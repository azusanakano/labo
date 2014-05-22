/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDBRow.cpp
 * \brief   DB result row class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altDBRow.h"

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
altDBRow::altDBRow()
{
}

///
/// \brief  Destructor
///
altDBRow::~altDBRow()
{
  for (altUInt i = 0; i < m_oDataList.size(); i++) {
    ALT_FREE (m_oDataList[i]);
  }
  m_oDataList.clear();
  m_oDataMap.clear();
}

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
alt_t altDBRow::Add(const altStr & sColumnName, altChar * pValue, const altUInt nValueSize)
{
  altChar * pBuf = NULL;
  alt_t     status;

  if (nValueSize > 0) {
    status = ALT_DUPALLOC (pBuf, pValue, nValueSize);
    ALT_ERR_RET (status);
  }

  m_oDataList.push_back (pBuf);
  m_oDataMap[sColumnName] = pBuf;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Size
///
/// \return Row Count
///
altUInt altDBRow::Size() const
{
  return ((altUInt)m_oDataList.size());
}

///
/// \brief  [] operator
///
/// \param  nIndex [I ] index
///
/// \return Column Value
///
LIBALT_API altChar * altDBRow::operator [](const altUInt nIndex) const ALT_THROWS (alt_t)
{
  if (nIndex >= Size()) {
    altStr sBuf;
    ALT_LOG_P (ALT_E_OUT_OF_INDEX, sBuf.Format ("[%u] >= [%u]", nIndex, Size()));
    throw (ALT_E_OUT_OF_INDEX);
  }
  return (m_oDataList[nIndex]);
}

///
/// \brief  [] operator
///
/// \param  sColumnName [I ] Column Name
///
/// \return Column Value
///
LIBALT_API altChar * altDBRow::operator [](const altStr & sColumnName) const
{
  return (m_oDataMap[sColumnName]);
}


