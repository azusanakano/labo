#ifndef ALTTCPSOCKET_H
#define ALTTCPSOCKET_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTCPSocket.h
 * \brief   TCP socket class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altSocket.h>
#include <altBase/altStr.h>

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  TCP Socket Class
///
class altTCPSocket : public altSocket
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altTCPSocket();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altTCPSocket();

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
  LIBALT_API virtual alt_t Connect(const altStr & sHost, const altInt nPort);

  ///
  /// \brief  Disconnect
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API virtual alt_t Disconnect();
};

#endif
