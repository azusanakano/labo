/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSocketAddress.cpp
 * \brief   Socket address class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altSocketAddress.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altSocketAddress::altSocketAddress()
{
  memset (& m_oAddr, 0x00, sizeof (m_oAddr));
  m_nAddrLen = sizeof (m_oAddr);
}

///
/// \brief  Constructor
///
/// \param  oAddr     [I ] Socket Address
/// \param  nAddrLen  [I ] Socket Address Length
///
LIBALT_API altSocketAddress::altSocketAddress(const SOCKADDR & oAddr, const altUInt nAddrLen) :
m_oAddr (oAddr),
m_nAddrLen (nAddrLen)
{
}

///
/// \brief  Destructor
///
LIBALT_API altSocketAddress::~altSocketAddress()
{
}

///
/// \brief  Get Socket Address
///
/// \return Socket Address
///
LIBALT_API const SOCKADDR & altSocketAddress::GetAddr() const
{
  return m_oAddr;
}

///
/// \brief  Get Socket Address Length
///
/// \return Socket Address Length
///
LIBALT_API altUInt altSocketAddress::GetAddrLen() const
{
  return m_nAddrLen;
}

///
/// \brief  Get Pointer of Socket Address
///
/// \return Pointer of Socket Address
///
LIBALT_API const SOCKADDR * altSocketAddress::GetAddrPtr() const
{
  return & m_oAddr;
}
