/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altWinHttpClient.cpp
 * \brief   Windows http client class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altWinHttpClient.h"

#ifdef ALT_WIN
/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altWinHttpClient::altWinHttpClient() :
m_hSession (NULL),
m_hConnect (NULL),
m_hRequest (NULL)
{
}

///
/// \brief  Destructor
///
LIBALT_API altWinHttpClient::~altWinHttpClient()
{
  Disconnect();
}

///
/// \brief  Connect
///
/// \param  sServer [I ] server address
/// \param  nPort   [I ] server port number
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altWinHttpClient::Connect(const altStr & sServer, const altInt nPort)
{
  m_hSession = InternetOpen (_T(""), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
  if (m_hSession == NULL) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("GetLastError=%u", GetLastError()));
  }

  m_hConnect = InternetConnectA (m_hSession, sServer.GetCStr(), nPort, "", "", INTERNET_SERVICE_HTTP, 0, 0);
  if (m_hConnect == NULL) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("GetLastError=%u", GetLastError()));
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Disconnect
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altWinHttpClient::Disconnect()
{
  if (m_hRequest != NULL) {
    InternetCloseHandle (m_hRequest);
    m_hRequest = NULL;
  }

  if (m_hConnect != NULL) {
    InternetCloseHandle (m_hConnect);
    m_hConnect = NULL;
  }

  if (m_hSession != NULL) {
    InternetCloseHandle (m_hSession);
    m_hConnect = NULL;
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Send GET request
///
/// \param  sFilePath [I ] File path
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altWinHttpClient::SendGetRequest(const altStr & sFilePath)
{
  if (m_hConnect == NULL) {
    ALT_RET_P (ALT_E_ERROR, "m_hConnect is NULL");
  }

  if (m_hRequest != NULL) {
    InternetCloseHandle (m_hRequest);
    m_hRequest = NULL;
  }

  m_hRequest = HttpOpenRequestA (m_hConnect, "GET", sFilePath.GetCStr(), NULL, NULL, NULL, INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_RAW_DATA, NULL);
  if (m_hRequest == NULL) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("GetLastError=%u (%s)", GetLastError()));
  }

  if (HttpSendRequestA (m_hRequest, NULL, 0, NULL, 0) == FALSE) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("GetLastError=%u (%s)", GetLastError()));
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Receive status code
///
/// \param  dwStatusCode  [ O] Status code
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altWinHttpClient::RecvStatusCode(DWORD & dwStatusCode)
{
  if (m_hRequest == NULL) {
    ALT_RET_P (ALT_E_ERROR, "m_hRequest is NULL");
  }

  altChar szBuf[ALT_BUFSIZ];
  DWORD   dwBufSize = sizeof (szBuf) - 1;

  BOOL bRet = HttpQueryInfoA (m_hRequest, HTTP_QUERY_STATUS_CODE, szBuf, & dwBufSize, 0);
  if (bRet == FALSE) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("GetLastError=%u (%s)", GetLastError()));
  }
  szBuf[dwBufSize] = 0x00;

  altStr  sStatusCode = szBuf;
  dwStatusCode = sStatusCode.ToDWORD();

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Receive file size
///
/// \param  dwFileSize  [ O] File size
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altWinHttpClient::RecvFileSize(DWORD & dwFileSize)
{
  if (m_hRequest == NULL) {
    ALT_RET_P (ALT_E_ERROR, "m_hRequest is NULL");
  }

  altChar szBuf[ALT_BUFSIZ];
  DWORD   dwBufSize = sizeof (szBuf) - 1;

  BOOL bRet = HttpQueryInfoA (m_hRequest, HTTP_QUERY_CONTENT_LENGTH, szBuf, & dwBufSize, 0);
  if (bRet == FALSE) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("GetLastError=%u", GetLastError()));
  }
  szBuf[dwBufSize] = 0x00;

  altStr  sFileSize = szBuf;
  dwFileSize = sFileSize.ToDWORD();

  ALT_RET (ALT_S_SUCCESS);
}

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
LIBALT_API alt_t altWinHttpClient::RecvFile(altChar * pBuf, const DWORD dwBufSize, DWORD & dwRecvSize)
{
  if (m_hRequest == NULL) {
    ALT_RET_P (ALT_E_ERROR, "m_hRequest is NULL");
  }

  if (pBuf == NULL) {
    ALT_RET_P (ALT_E_ERROR, "pBuf is NULL");
  }

  BOOL bRet = InternetReadFile (m_hRequest, pBuf, dwBufSize, & dwRecvSize);
  if (bRet == FALSE) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("GetLastError=%u (%s)", GetLastError()));
  }

  ALT_RET (ALT_S_SUCCESS);
}

#endif
