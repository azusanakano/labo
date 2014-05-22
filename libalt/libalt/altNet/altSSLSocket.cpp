/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSSLSocket.cpp
 * \brief   SSL socket class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altSSLSocket.h"
#include "altNetUtil.h"
#include "altBase/altMem.h"

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
/// \param  nSocket   [I ] Socket Descriptor
///
LIBALT_API altSSLSocket::altSSLSocket(const SOCKET nSocket) :
altSocket (nSocket),
m_pSSL (NULL),
m_pSSLContext (NULL)
{
}

///
/// \brief  Destructor
///
LIBALT_API altSSLSocket::~altSSLSocket()
{
  alt_t status;
  status = Close();
  ALT_LOG (status);
}

///
/// \breif  Set SSL Object
///
/// \param  pSSL        [I ] Pointer of SSL Object
/// \param  pSSLContext [I ] Pointer of SSL Context Object
///
LIBALT_API void altSSLSocket::SetSSL(SSL * pSSL, SSL_CTX * pSSLContext)
{
#ifdef ALT_LINUX
  m_pSSL = pSSL;
  m_pSSLContext = pSSLContext;
#endif
}

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
LIBALT_API alt_t altSSLSocket::Connect(const altInetAddress & oInetAddr, const altByte nSSLVersion)
{
  alt_t   status;

  status = altNetUtil::WSAStartup();
  ALT_ERR_RET (status);

  status = altNetUtil::SSLLibraryInit();
  ALT_ERR_RET (status);

  status = altNetUtil::Connect (m_nSocket, oInetAddr);
  ALT_ERR_RET (status);

  if (m_pSSLContext == NULL) {
    if (nSSLVersion == ALT_SSL_V23) {
      ALT_LOG_P (ALT_D_DEBUG, "use SSLv23_client_method()");
      m_pSSLContext = SSL_CTX_new (SSLv23_client_method ());
    }
    else if (nSSLVersion == ALT_SSL_V2) {
      ALT_LOG_P (ALT_D_DEBUG, "use SSLv2_client_method()");
      m_pSSLContext = SSL_CTX_new (SSLv2_client_method ());
    }
    else if (nSSLVersion == ALT_SSL_V3) {
      ALT_LOG_P (ALT_D_DEBUG, "use SSLv3_client_method()");
      m_pSSLContext = SSL_CTX_new (SSLv3_client_method ());
    }
    else if (nSSLVersion == ALT_TSL_V1) {
      ALT_LOG_P (ALT_D_DEBUG, "use TLSv1_client_method()");
      m_pSSLContext = SSL_CTX_new (TLSv1_client_method ());
    }
    if (m_pSSLContext == NULL) {
      altNetUtil::CloseSocket (m_nSocket);
      ALT_RET_P (ALT_E_CONNECT, "SSL_CTX_new error");
    }
  }

  if (m_pSSL == NULL) {
    m_pSSL = SSL_new (m_pSSLContext);
    if (m_pSSL == NULL) {
      SSL_CTX_free (m_pSSLContext);
      m_pSSLContext = NULL;
      altNetUtil::CloseSocket (m_nSocket);
      ALT_RET_P (ALT_E_CONNECT, "SSL_new error");
    }
  }

  altInt nRet = SSL_set_fd (m_pSSL, (altInt)m_nSocket);
  if (nRet == 0) {
    SSL_free (m_pSSL);
    m_pSSL = NULL;
    SSL_CTX_free (m_pSSLContext);
    m_pSSLContext = NULL;
    altNetUtil::CloseSocket (m_nSocket);
    ALT_RET_P (ALT_E_CONNECT, "SSL_set_fd error");
  }

#if 0
  nRet = SSL_CTX_set_cipher_list (m_pSSLContext, "DHE-RSA-AES256-SHA");
  if (nRet != 1) {
    ALT_LOG_P (ALT_E_ERROR, "SSL_CTX_set_cipher_list");
  }

  RAND_poll();
  while (RAND_status() == 0) {
    altUShort nRandRet = rand() % 65536;
    RAND_seed (& nRandRet, sizeof (nRandRet));
  }
#endif

retry_ssl_connect:
  nRet = SSL_connect (m_pSSL);
  if (nRet != 1) {
    altInt nErrNo = SSL_get_error (m_pSSL, nRet);
    if (nErrNo == SSL_ERROR_WANT_CONNECT) {
      goto retry_ssl_connect;
    }
    else {
      SSL_free (m_pSSL);
      m_pSSL = NULL;
      SSL_CTX_free (m_pSSLContext);
      m_pSSLContext = NULL;
      altNetUtil::CloseSocket (m_nSocket);
      altStr  sBuf;
      ALT_RET_P (ALT_E_CONNECT, sBuf.Format ("SSL_connect error (%d)", nErrNo));
    }
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Close Socket
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altSSLSocket::Close()
{
  if (m_pSSLContext != NULL) {
    SSL_CTX_free (m_pSSLContext);
    m_pSSLContext = NULL;
  }

  if (m_pSSL != NULL) {
    SSL_free (m_pSSL);
    m_pSSL = NULL;
  }
  
  alt_t status = altSocket::Close();
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
LIBALT_API alt_t altSSLSocket::Recv(altCharPtr & pData, altUInt & nSize) const
{
  
  alt_t     status;
  altChar * pRecvBuf = NULL;
  altInt    nRecvSize = 0;

  status = ALT_MALLOC (pRecvBuf, nSize);
  ALT_ERR_RET (status);

  status = altNetUtil::RecvSSL (m_pSSL, pRecvBuf, nSize, nRecvSize);
  if (ALT_IS_ERR (status)) {
    ALT_FREE (pRecvBuf);
    ALT_ERR_RET (status);
  }

  if (status == ALT_S_NET_EOF) {
    ALT_FREE (pRecvBuf);
    ALT_RET (status);
  }

  altChar * pBuf = NULL;

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
LIBALT_API alt_t altSSLSocket::Send(const altChar * pData, const altInt nSize)
{
  alt_t   status;
  altInt  nSendByte = 0;

  ALT_P_ASSERT (pData != NULL);
  
  status = altNetUtil::SendSSL (m_pSSL, pData, nSize, nSendByte);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get connecting or not
///
/// \return true  connecting
/// \return false not connecting
///
LIBALT_API altBool altSSLSocket::Connected() const
{
  return (m_pSSL != NULL);
}

///
/// \brief  Get pointer of SSL object
///
/// \return pointer of SSL object
///
LIBALT_API SSL * altSSLSocket::GetSSL() const
{
  return (m_pSSL);
}
