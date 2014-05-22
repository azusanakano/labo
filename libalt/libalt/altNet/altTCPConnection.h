#ifndef ALTTCPCONNECTION_H
#define ALTTCPCONNECTION_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTCPConnection.h
 * \brief   TCP network connection class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETConnection.h>
#include <altNet/altNETSenderBroker.h>
#include <altNet/altSocket.h>
#include <altNet/altNetCommon.h>
#include <altBase/altStr.h>
#include <altBase/altLog.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  TCP Connection Class
///
class altTCPConnection : public altNETConnection
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  nSocket         [I ] Socket
  /// \param  oSockAddrIn     [I ] Internet Address of Socket
  /// \param  nAcceptedPortNo [I ] Accepted Port Number
  /// \param  oSendBroker     [I ] Send Broker
  ///
  LIBALT_API altTCPConnection(const SOCKET nSocket, const SOCKADDR_IN & oSockAddrIn, const altInt nAcceptedPortNo, altNETSenderBroker & oSenderBroker);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altTCPConnection();

  ///
  /// \brief  Get Socket
  ///
  /// \return Socket
  ///
  LIBALT_API const SOCKET GetSocket() const;

  ///
  /// \brief  Close Socket
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API virtual alt_t Close();

  ///
  /// \brief  Read Data
  ///
  /// \param  pData [ O] receive data
  /// \param  nSize [IO] receive data size
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_S_NET_EOF   connection closed
  /// \return ALT_S_TIMEOUT   timeout
  /// \return ALT_E_NOMEM     out of memory error
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API virtual alt_t Recv(altCharPtr & pData, altUInt & nSize) const;

  ///
  /// \brief  Real Send Data
  ///
  /// \param  pData [I ] send data
  /// \param  nSize [I ] send data size
  ///
  /// \return ALT_S_SUCCESS   successs
  /// \return ALT_E_SEND      send error
  ///
  LIBALT_API virtual alt_t RealSend(const altCharPtr & pData, const altInt nSize) const;

  ///
  /// \brief  Get connecting or not
  ///
  /// \return true  connecting
  /// \return false not connecting
  ///
  LIBALT_API virtual altBool Connected() const;

protected:
  altSocket       m_oSocket;          ///< socket
};
#endif  //ALTTCPCONNECTION_H
