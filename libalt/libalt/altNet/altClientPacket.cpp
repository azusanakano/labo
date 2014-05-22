/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altClientPacket.cpp
 * \brief   Network packet data class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altClientPacket.h"
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
LIBALT_API altClientPacket::altClientPacket() :
m_pData(),
m_nSize(0)
{
}

///
/// \brief  Destructor
///
LIBALT_API altClientPacket::~altClientPacket()
{
  m_nSize = 0;
}

///
/// \brief  Set Data
///
/// \param  pData           [I ] Data
/// \param  nSize           [I ] Data Size
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
/// \return ALT_E_INVAL   invalid paramter
///
LIBALT_API alt_t altClientPacket::Set(const altCharPtr & pData, const altUInt nSize)
{
  m_pData = pData;
  m_nSize = nSize;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Data
///
/// \return Data
///
LIBALT_API const altCharPtr altClientPacket::GetData() const
{
  return (m_pData);
}

///
/// \brief  Get Size
///
/// \return Size
///
LIBALT_API altUInt altClientPacket::GetSize() const
{
  return (m_nSize);
}

