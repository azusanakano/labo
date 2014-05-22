/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSSLConnection.cpp
 * \brief   SSL connection class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altSSLConnection.h"
#include "altNetUtil.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
/// \param  pSSL            [I ] Pointer of SSL Object
/// \param  m_pSSLContext   [I ] Pointer of SSL Context Object
/// \param  nSocket         [I ] Socket
/// \param  oSockAddrIn     [I ] Internet Address of Socket
/// \param  nAcceptedPortNo [I ] Accepted Port Number
/// \param  oSendBroker     [I ] Send Broker
///
LIBALT_API altSSLConnection::altSSLConnection(SSL * pSSL, SSL_CTX * pSSLContext, const SOCKET nSocket, const SOCKADDR_IN & oSockAddrIn, const altInt nAcceptedPortNo, altNETSenderBroker & oSenderBroker) :
altNETConnection (oSockAddrIn, nAcceptedPortNo, oSenderBroker),
m_oSocket (nSocket)
{
  m_oSocket.SetSSL (pSSL, pSSLContext);
}

///
/// \brief  Destructor
///
LIBALT_API altSSLConnection::~altSSLConnection()
{
}

///
/// \brief  Get Socket
///
/// \return Socket
///
LIBALT_API const SOCKET altSSLConnection::GetSocket() const
{
  return (m_oSocket.GetSocket());
}

///
/// \brief  Close Socket
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altSSLConnection::Close()
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
LIBALT_API alt_t altSSLConnection::Recv(altCharPtr & pData, altUInt & nSize) const
{
  alt_t   status;

  status = m_oSocket.Recv (pData, nSize);
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
LIBALT_API alt_t altSSLConnection::RealSend(const altCharPtr & pData, const altInt nSize) const
{
  alt_t   status;
  altInt  nSendSize = 0;
  altInt  nTotalSendSize = 0;

  while (nTotalSendSize < nSize) {
    status = altNetUtil::SendSSL (m_oSocket.GetSSL(), & pData[nTotalSendSize], nSize - nTotalSendSize, nSendSize);
    ALT_ERR_RET (status);
    nTotalSendSize += nSendSize;
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get connecting or not
///
/// \return true  connecting
/// \return false not connecting
///
LIBALT_API altBool altSSLConnection::Connected() const
{
  return (m_oSocket.Connected());
}
