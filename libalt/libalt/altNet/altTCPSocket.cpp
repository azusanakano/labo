/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTCPSocket.cpp
 * \brief   TCP socket class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altTCPSocket.h"
#include "altInetAddress.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altTCPSocket::altTCPSocket() :
altSocket()
{
}

///
/// \brief  Destructor
///
LIBALT_API altTCPSocket::~altTCPSocket()
{
  alt_t status = altSocket::Close();
  ALT_LOG (status);
}

///
/// \brief  Connect
///
/// \param  sHost [I ] Host name or IP address
/// \param  nPort [I ] Port number
///
/// \return ALT_S_SUCCESS       success
/// \retrun ALT_E_CONNECT       connect error
/// \return	ALT_E_SOCKET        create socket error
/// \return ALT_E_UNKOWN_HOST   unknown host error
///
LIBALT_API alt_t altTCPSocket::Connect(const altStr & sHost, const altInt nPort)
{
  alt_t status;
  altInetAddress  oInetAddr;

  status = altSocket::Init (AF_INET, SOCK_STREAM, 0);
  ALT_ERR_RET (status);

  status = oInetAddr.Init (sHost.GetCStr(), nPort);
  ALT_ERR_RET (status);

  status = altSocket::Connect (oInetAddr);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Disconnect
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altTCPSocket::Disconnect()
{
  alt_t status;

  status = altSocket::Close();
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}
