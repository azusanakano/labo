/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSocket.cpp
 * \brief   Socket class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altSocket.h"
#include "altNetUtil.h"
#include "altBase/altStr.h"
#include "altBase/altMem.h"

#include <errno.h>

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
/// \param  nSocket   [I ] Socket Descriptor
///
LIBALT_API altSocket::altSocket(const SOCKET nSocket) :
m_nSocket(nSocket)
{
}

///
/// \brief  Init
///
/// \param  nAf       [I ] Address Family
/// \param  nType     [I ] Socket Type
/// \param  nProtocol [I ] Protocol
///
/// \return ALT_S_SUCCESS success
/// \return	ALT_E_SOCKET  error
///
LIBALT_API alt_t altSocket::Init(const altInt nAf, const altInt nType, const altInt nProtocol)
{
  if (m_nSocket != 0) {
    ALT_RET (ALT_E_ERROR);
  }
  alt_t status;
  status = altNetUtil::CreateSocket (nAf, nType, nProtocol, m_nSocket);
  if (ALT_IS_ERR (status)) {
    altStr  sBuf;
    ALT_RET_P (status, sBuf.Format ("nAf=%d nType=%d nProtocol=%d", nAf, nType, nProtocol));
  }

  // set SO_REUSEADDR option
  altInt nOpt = 1;
  setsockopt (m_nSocket, SOL_SOCKET, SO_REUSEADDR, (const altChar *)& nOpt, sizeof (nOpt));

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Destructor
///
LIBALT_API altSocket::~altSocket()
{
  alt_t status = Close();
  ALT_LOG (status);
}

///
/// \brief  Get Socket
///
/// \return Socket
///
LIBALT_API const SOCKET altSocket::GetSocket() const
{
  return (m_nSocket);
}

///
/// \brief  Close Socket
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altSocket::Close()
{
  if (m_nSocket == 0) {
    ALT_RET (ALT_S_SUCCESS);
  }
  alt_t status = altNetUtil::CloseSocket (m_nSocket);
  ALT_RET (status);
}

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
LIBALT_API alt_t altSocket::Listen(const altInt nPort, const altInt nListenQueSize)
{
  alt_t           status;
  altStr          sBuf;
  altInetAddress  oSockAddr (nPort);

  // bind
  status = altNetUtil::Bind (m_nSocket, oSockAddr);
  ALT_ERR_RET_P (status, sBuf.Format ("nPort=%d nListenQueSize=%d", nPort, nListenQueSize));

  // start listen
  status = altNetUtil::Listen (m_nSocket, nListenQueSize);
  ALT_ERR_RET_P (status, sBuf.Format ("nPort=%d nListenQueSize=%d", nPort, nListenQueSize));

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Connect
///
/// \param  oInetAddr [I ] Internet Socket Address
///
/// \return ALT_S_SUCCESS   success
/// \retrun ALT_E_CONNECT   connect error
///
LIBALT_API alt_t altSocket::Connect(const altInetAddress & oInetAddr)
{
  alt_t status;

  status = altNetUtil::Connect (m_nSocket, oInetAddr);
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
/// \return ALT_E_NOMEM     out of memory error
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altSocket::Recv(altCharPtr & pData, altUInt & nSize) const
{
  alt_t     status;
  altChar * pRecvBuf = NULL;
  altInt    nRecvSize = 0;
  altChar * pBuf = NULL;

  status = ALT_MALLOC (pRecvBuf, nSize);
  ALT_ERR_RET (status);

  status = altNetUtil::Recv (m_nSocket, pRecvBuf, nSize, nRecvSize);
  if (ALT_IS_ERR (status)) {
    ALT_FREE (pRecvBuf);
    ALT_RET (status);
  }

  if (status == ALT_S_NET_EOF) {
    ALT_FREE (pRecvBuf);
    ALT_RET (status);
  }

  status = ALT_DUPALLOC (pBuf, pRecvBuf, nRecvSize);
  ALT_FREE (pRecvBuf);
  ALT_ERR_RET (status);

  pData = pBuf;
  nSize = nRecvSize;

  ALT_RET (ALT_S_SUCCESS);
}

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
LIBALT_API alt_t altSocket::Send(const altChar * pData, const altInt nSize) const
{
  alt_t   status;
  altInt  nSendByte;
  
  status = altNetUtil::Send (m_nSocket, pData, nSize, nSendByte);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get connecting or not
///
/// \return true  connecting
/// \return false not connecting
///
LIBALT_API altBool altSocket::Connected() const
{
  return (m_nSocket != 0);
}

