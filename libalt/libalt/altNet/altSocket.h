#ifndef ALTSOCKET_H
#define ALTSOCKET_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSocket.h
 * \brief   Socket class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altInetAddress.h>
#include <altNet/altNetCommon.h>
#include <altBase/altCharPtr.h>
#include <altBase/altLog.h>
#include <altBase/altBase.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/


/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Socket Class
///
class altSocket : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  nSocket   [I ] Socket Descriptor
  ///
  LIBALT_API altSocket(const SOCKET nSocket = 0);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altSocket();

  ///
  /// \brief  Initialize
  ///
  /// \param  nAf       [I ] Address Family
  /// \param  nType     [I ] Socket Type
  /// \param  nProtocol [I ] Protocol
  ///
  /// \return ALT_S_SUCCESS success
  /// \return	ALT_E_SOCKET  error
  ///
  LIBALT_API alt_t Init(const altInt nAf, const altInt nType, const altInt nProtocol);

  ///
  /// \brief  Get Socket
  ///
  /// \return Socket
  ///
  LIBALT_API const SOCKET GetSocket() const;

  ///
  /// \brief  Close Socket
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API virtual alt_t Close();

  ///
  /// \brief  Listen
  ///
  /// \param  nPort           [I ] Port No
  /// \param  nListenQueSize  [I ] Listen Queue Size
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_BIND      bind error
  /// \return ALT_E_LISTEN    listen error
  ///
  LIBALT_API alt_t Listen(const altInt nPort, const altInt nListenQueSize);

  ///
  /// \brief  Connect
  ///
  /// \param  oInetAddr [I ] Internet Socket Address
  ///
  /// \return ALT_S_SUCCESS   success
  /// \retrun ALT_E_CONNECT   connect error
  ///
  LIBALT_API virtual alt_t Connect(const altInetAddress & oInetAddr);

  ///
  /// \brief  Read Data
  ///
  /// \param  pData [ O] receive data
  /// \param  nSize [IO] receive data size
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_S_NET_EOF   connection closed
  /// \return ALT_E_NOMEM     out of memory error
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API virtual alt_t Recv(altCharPtr & pData, altUInt & nSize) const;

  ///
  /// \brief  Send Data
  ///
  /// \param  pData [I ] send data
  /// \param  nSize [I ] send data size
  ///
  /// \return ALT_S_SUCCESS   successs
  /// \return ALT_E_INVAL     invalid parameter
  /// \return ALT_E_SEND      send error
  ///
  LIBALT_API virtual alt_t Send(const altChar * pData, const altInt nSize) const;

  ///
  /// \brief  Get connecting or not
  ///
  /// \return true  connecting
  /// \return false not connecting
  ///
  LIBALT_API virtual altBool Connected() const;

protected:
  SOCKET          m_nSocket;          ///< socket
};
#endif  //ALTSOCKET_H
