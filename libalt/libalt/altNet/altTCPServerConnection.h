#ifndef ALTTCPSERVERCONNECTION_H
#define ALTTCPSERVERCONNECTION_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTCPServerConnection.h
 * \brief   TCP server network connection class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETServerInfo.h>
#include <altNet/altNETServerConnection.h>
#include <altNet/altTCPConnection.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Server Network Connection Class
///
class altTCPServerConnection : public altTCPConnection, public altNETServerConnection
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  nSocket         [I ] Socket
  /// \param  oSockAddrIn     [I ] Internet socket address
  /// \param  nAcceptedPortNo [I ] Accepted port number
  /// \param  oSenderBroker   [I ] Sender broker
  /// \param  oServerInfo     [I ] Server infomation
  ///
  LIBALT_API altTCPServerConnection(const SOCKET nSocket, const SOCKADDR_IN & oSockAddrIn, const altInt nAcceptedPortNo, altNETSenderBroker & oSenderBroker, const altNETServerInfo & oServerInfo);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altTCPServerConnection();

private:
  altNETServerInfo  m_oServerInfo;
};

#endif
