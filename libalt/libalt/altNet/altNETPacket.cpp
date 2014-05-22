/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETPacket.cpp
 * \brief   Network packet data class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altNETPacket.h"
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
LIBALT_API altNETPacket::altNETPacket() :
m_pData (),
m_nSize (0),
m_pConnection (NULL)
{
}

///
/// \brief  Destructor
///
LIBALT_API altNETPacket::~altNETPacket()
{
  m_nSize = 0;
  m_pConnection = NULL;
}

///
/// \brief  Set Data
///
/// \param  pNETConnection  [I ] NET Connection
/// \param  pData           [I ] network data
/// \param  nSize           [I ] data size
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
/// \return ALT_E_INVAL   invalid paramter
///
LIBALT_API alt_t altNETPacket::Set(const altCNETConnectionPtr & pNETConnection, const altCharPtr & pData, const altUInt nSize)
{
  ALT_P_ASSERT (pData != NULL);
  m_pData = pData;
  m_nSize = nSize;
  m_pConnection = pNETConnection;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Data
///
/// \param  pNETConnection  [ O] NET Connection
/// \param  pData           [ O] network data
/// \param  nSize           [ O] data size
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altNETPacket::Get(altCNETConnectionPtr & pNETConnection, altCharPtr & pData, altUInt & nSize)
{
  pData = m_pData;
  nSize = m_nSize;
  pNETConnection = m_pConnection;

  ALT_RET (ALT_S_SUCCESS);
}
