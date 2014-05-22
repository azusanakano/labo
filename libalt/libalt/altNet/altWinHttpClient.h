#ifndef ALTWINHTTPCLIENT_H
#define ALTWINHTTPCLIENT_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altWinHttpClient.h
 * \brief   Windows http client
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altStr.h>
#include <altBase/altLog.h>
#include <altBase/altStatus.h>
#ifdef ALT_WIN
#include <Wininet.h>
/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Windows Http Client
///
class altWinHttpClient : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altWinHttpClient();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altWinHttpClient();

  ///
  /// \brief  Connect
  ///
  /// \param  sServer [I ] server address
  /// \param  nPort   [I ] server port number
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Connect(const altStr & sServer, const altInt nPort = 80);

  ///
  /// \brief  Disconnect
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t Disconnect();

  ///
  /// \brief  Send GET request
  ///
  /// \param  sFilePath [I ] File path
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t SendGetRequest(const altStr & sFilePath);

  ///
  /// \brief  Receive status code
  ///
  /// \param  dwStatusCode  [ O] Status code
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t RecvStatusCode(DWORD & dwStatusCode);

  ///
  /// \brief  Receive file size
  ///
  /// \param  dwFileSize  [ O] File size
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t RecvFileSize(DWORD & dwFileSize);

  ///
  /// \brief  Receive file content
  ///
  /// \param  pBuf        [ O] Data buffer
  /// \param  dwBufSize   [I ] Data buffer size
  /// \param  dwRecvSize  [ O] Receive size(byte)
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t RecvFile(altChar * pBuf, const DWORD dwBufSize, DWORD & dwRecvSize);

private:
  HINTERNET m_hSession; ///< Session
  HINTERNET m_hConnect; ///< Connection
  HINTERNET m_hRequest; ///< Request
};

#endif
#endif
