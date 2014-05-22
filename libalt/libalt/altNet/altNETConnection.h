#ifndef ALTNETCONNECTION_H
#define ALTNETCONNECTION_H
/*--------------------------------------------------------------------------*

   Alternative Llibrary

  $Id: altNETConnection.h 718 2007-11-23 14:58:14Z nekosys $

  Copyright (C) 2007-2013 Azusa Nakano All rights reserved.
    
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETConnection.h
 * \brief   Network connection class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETSenderBroker.h>
#include <altNet/altInetAddress.h>
#include <altNet/altNetCommon.h>
#include <altBase/altCharPtr.h>
#include <altBase/altStr.h>
#include <altBase/altLog.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
class altNETConnection;
typedef const altNETConnection      altCNETConnection;      ///< const altNETConnection
typedef altPtr<altCNETConnection>   altCNETConnectionPtr;   ///< pointer of const altNETConnection

class altNETSenderBroker;

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Network Connection Class
///
class altNETConnection : public altBase, public altSyncThread
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altNETConnection(const SOCKADDR_IN & oSockAddrIn, const altInt nAcceptedPortNo, altNETSenderBroker & oSenderBroker);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altNETConnection();

  ///
  /// \brief  Get Socket
  ///
  /// \return Socket
  ///
  LIBALT_API virtual const SOCKET GetSocket() const = 0;
  
  ///
  /// \brief Get IP Address
  ///
  /// \return IP Address
  ///
  LIBALT_API virtual const altStr GetIP() const;

  ///
  /// \brief Get Port NO
  ///
  /// \return Port NO
  ///
  LIBALT_API virtual altInt GetPort() const;

  ///
  /// \brief  Get accepted port number
  ///
  /// \return Accepted port number
  ///
  LIBALT_API const altInt GetAcceptedPort() const;

  ///
  /// \brief  Close Socket
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API virtual alt_t Close() = 0;

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
  LIBALT_API virtual alt_t Recv(altCharPtr & pData, altUInt & nSize) const = 0;

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
  LIBALT_API alt_t Send(const altCharPtr & pData, const altInt nSize) const;

  ///
  /// \brief  Real Send Data
  ///
  /// \param  pData [I ] send data
  /// \param  nSize [I ] send data size
  ///
  /// \return ALT_S_SUCCESS   successs
  /// \return ALT_E_SEND      send error
  ///
  LIBALT_API virtual alt_t RealSend(const altCharPtr & pData, const altInt nSize) const = 0;

  ///
  /// \brief  Get connecting or not
  ///
  /// \return true  connecting
  /// \return false not connecting
  ///
  LIBALT_API virtual altBool Connected() const = 0;

  ///
  /// \brief  Get server connection or not
  ///
  /// \return true  server connection
  /// \return false client connection
  ///
  LIBALT_API altBool IsServerConnection() const;

protected:
  altInetAddress                m_oSockAddrIn;        ///< internet address
  altInt                        m_nAcceptedPortNo;    ///< accepted port number
#ifdef ALT_WIN
  mutable altNETSenderBroker &  m_oSenderBroker;      ///< send broker
#else
  altNETSenderBroker &          m_oSenderBroker;      ///< send broker
#endif
  altBool                       m_bServerConnection;  ///< server connection or not
};

#endif
