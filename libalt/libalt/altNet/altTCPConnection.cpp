/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTCPConnection.cpp
 * \brief   TCP network connection class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altTCPConnection.h"
#include "altNetUtil.h"
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
/// \param  nSocket         [I ] Socket
/// \param  oSockAddrIn     [I ] Internet Address of Socket
/// \param  nAcceptedPortNo [I ] Accepted Port Number
/// \param  oSendBroker     [I ] Send Broker
///
LIBALT_API altTCPConnection::altTCPConnection(const SOCKET nSocket, const SOCKADDR_IN & oSockAddrIn, const altInt nAcceptedPortNo, altNETSenderBroker & oSenderBroker) :
altNETConnection (oSockAddrIn, nAcceptedPortNo, oSenderBroker),
m_oSocket(nSocket)
{
}

///
/// \brief  Destructor
///
LIBALT_API altTCPConnection::~altTCPConnection()
{
}

///
/// \brief  Get Socket
///
/// \return Socket
///
LIBALT_API const SOCKET altTCPConnection::GetSocket() const
{
  return (m_oSocket.GetSocket());
}

///
/// \brief  Close Socket
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altTCPConnection::Close()
{
  alt_t status = m_oSocket.Close();
  ALT_ERR_RET (status);
  ALT_RET (ALT_S_SUCCESS);
}

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
LIBALT_API alt_t altTCPConnection::Recv(altCharPtr & pData, altUInt & nSize) const
{
  alt_t   status;

  status = m_oSocket.Recv(pData, nSize);
  ALT_ERR_RET (status);

  ALT_RET (status);
}

///
/// \brief  Real Send Data
///
/// \param  pData [I ] send data
/// \param  nSize [I ] send data size
///
/// \return ALT_S_SUCCESS   successs
/// \return ALT_E_SEND      send error
///
LIBALT_API alt_t altTCPConnection::RealSend(const altCharPtr & pData, const altInt nSize) const
{
  alt_t   status;
  altInt  nSendByte = 0;
  altInt  nTotalSendSize = 0;

  while (nTotalSendSize < nSize) {
    status = altNetUtil::Send(m_oSocket.GetSocket(), & pData[nTotalSendSize], nSize - nTotalSendSize, nSendByte);
    ALT_ERR_RET (status);
    nTotalSendSize += nSendByte;
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get connecting or not
///
/// \return true  connecting
/// \return false not connecting
///
LIBALT_API altBool altTCPConnection::Connected() const
{
  return (m_oSocket.Connected());
}
