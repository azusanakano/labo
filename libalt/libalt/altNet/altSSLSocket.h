#ifndef ALTSSLSOCKET_H
#define ALTSSLSOCKET_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSSLSocket.h
 * \brief   SSL socket class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altSocket.h>
#include <altBase/altCharPtr.h>

#ifdef ALT_WIN
  #include <altNet/openssl/ssl.h>
#endif

#ifdef ALT_LINUX
  #include <openssl/ssl.h>
#endif

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  SSL Socket Class
///
class altSSLSocket : public altSocket
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  nSocket   [I ] Socket Descriptor
  ///
  LIBALT_API altSSLSocket(const SOCKET nSocket);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altSSLSocket();

  ///
  /// \breif  Set SSL Object
  ///
  /// \param  pSSL        [I ] Pointer of SSL Object
  /// \param  pSSLContext [I ] Pointer of SSL Context Object
  ///
  LIBALT_API void SetSSL(SSL * pSSL, SSL_CTX * pSSLContext);

  ///
  /// \brief  Connect
  ///
  /// \param  oInetAddr   [I ] Internet Socket Address
  /// \param  nSSLVersion [I ] SSL Version (ALT_SSL_V2 or ALT_SSL_V3 or ALT_TSL_V1)
  ///
  /// \return ALT_S_SUCCESS   success
  /// \retrun ALT_E_CONNECT   connect error
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t Connect(const altInetAddress & oInetAddr, const altByte nSSLVersion);

  ///
  /// \brief  Close Socket
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t Close();

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
  LIBALT_API alt_t Recv(altCharPtr & pData, altUInt & nSize) const;

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
  LIBALT_API alt_t Send(const altChar * pData, const altInt nSize);

  ///
  /// \brief  Get connecting or not
  ///
  /// \return true  connecting
  /// \return false not connecting
  ///
  LIBALT_API altBool Connected() const;

  ///
  /// \brief  Get pointer of SSL object
  ///
  /// \return pointer of SSL object
  ///
  LIBALT_API SSL *  GetSSL() const;

private:
  SSL *     m_pSSL;         ///< Pointer of SSL Object
  SSL_CTX * m_pSSLContext;  ///< Pointer of SSL Context Object
};

#endif  //ALTSSLSOCKET_H

