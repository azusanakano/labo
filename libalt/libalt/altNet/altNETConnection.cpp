/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETConnection.cpp
 * \brief   Network connection class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altNETConnection.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altNETConnection::altNETConnection(const SOCKADDR_IN & oSockAddrIn, const altInt nAcceptedPortNo, altNETSenderBroker & oSenderBroker) :
m_oSockAddrIn (oSockAddrIn),
m_nAcceptedPortNo (nAcceptedPortNo),
m_oSenderBroker (oSenderBroker),
m_bServerConnection (false)
{
}

///
/// \brief  Destructor
///
LIBALT_API altNETConnection::~altNETConnection()
{
}

///
/// \brief Get IP Address
///
/// \return IP Address
///
LIBALT_API const altStr altNETConnection::GetIP() const
{
  return m_oSockAddrIn.GetIP();
}

///
/// \brief Get Port NO
///
/// \return Port NO
///
LIBALT_API altInt altNETConnection::GetPort() const
{
  return m_oSockAddrIn.GetPort();
}

///
/// \brief  Get accepted port number
///
/// \return Accepted port number
///
LIBALT_API const altInt altNETConnection::GetAcceptedPort() const
{
  return (m_nAcceptedPortNo);
}

///
/// \brief  Send Data
///
/// \param  pData [I ] send data
/// \param  nSize [I ] send data size
///
/// \return ALT_S_SUCCESS   successs
/// \return ALT_E_NOMEM     out of memory
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altNETConnection::Send(const altCharPtr & pData, const altInt nSize) const
{
  if (pData == NULL || nSize == 0) {
    ALT_RET (ALT_S_SUCCESS);
  }

  alt_t status = m_oSenderBroker.Send (this, pData, nSize);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get server connection or not
///
/// \return true  server connection
/// \return false client connection
///
LIBALT_API altBool altNETConnection::IsServerConnection() const
{
  return (m_bServerConnection);
}
