#ifndef ALTSSLSERVERCONNECTION_H
#define ALTSSLSERVERCONNECTION_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSSLServerConnection.h
 * \brief   SSL server network connection class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETServerInfo.h>
#include <altNet/altNETServerConnection.h>
#include <altNet/altSSLConnection.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  SSL Server Network Connection Class
///
class altSSLServerConnection : public altSSLConnection, public altNETServerConnection
{
public:
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
  LIBALT_API altSSLServerConnection(SSL * pSSL, SSL_CTX * pSSLContext, const SOCKET nSocket, const SOCKADDR_IN & oSockAddrIn, const altInt nAcceptedPortNo, altNETSenderBroker & oSenderBroker, const altNETServerInfo & oServerInfo);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altSSLServerConnection();

private:
  altNETServerInfo  m_oServerInfo;
};

#endif
