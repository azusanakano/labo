/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSSLServerConnection.cpp
 * \brief   SSL server network connection class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altSSLServerConnection.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
/// \param  pSSL            [I ] Pointer of SSL Object
/// \param  m_pSSLContext   [I ] Pointer of SSL Context Object
/// \param  nSocket         [I ] Socket
/// \param  oSockAddrIn     [I ] Internet socket address
/// \param  nAcceptedPortNo [I ] Accepted port number
/// \param  oSenderBroker   [I ] Sender broker
/// \param  oServerInfo     [I ] Server infomation
///
LIBALT_API altSSLServerConnection::altSSLServerConnection(SSL * pSSL, SSL_CTX * pSSLContext, const SOCKET nSocket, const SOCKADDR_IN & oSockAddrIn, const altInt nAcceptedPortNo, altNETSenderBroker & oSenderBroker, const altNETServerInfo & oServerInfo) :
altSSLConnection (pSSL, pSSLContext, nSocket, oSockAddrIn, nAcceptedPortNo, oSenderBroker),
altNETServerConnection (oServerInfo)
{
  m_bServerConnection = true;
}

///
/// \brief  Destructor
///
LIBALT_API altSSLServerConnection::~altSSLServerConnection()
{
}
