/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTCPServerConnection.cpp
 * \brief   TCP server network connection class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altTCPServerConnection.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altTCPServerConnection::altTCPServerConnection(const SOCKET nSocket, const SOCKADDR_IN & oSockAddrIn, const altInt nAcceptedPortNo, altNETSenderBroker & oSenderBroker, const altNETServerInfo & oServerInfo) :
altTCPConnection (nSocket, oSockAddrIn, nAcceptedPortNo, oSenderBroker),
altNETServerConnection (oServerInfo)
{
  m_bServerConnection = true;
}

///
/// \brief  Destructor
///
LIBALT_API altTCPServerConnection::~altTCPServerConnection()
{
}
