#ifndef ALTSSLCLIENT_H
#define ALTSSLCLIENT_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSSLClient.h
 * \brief   SSL network client class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altSSLSocket.h>
#include <altNet/altClientPacket.h>
#include <altMisc/altQue.h>
#include <altBase/altLoopThread.h>
#include <altBase/altLog.h>
#include <altBase/altStatus.h>
#include <altBase/altUncopyable.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
class altSSLClient;
typedef void (* altSSLClientCallBack)(altSSLClient & oClient, const altChar *, const altUInt); ///< Receive Call Back Function
typedef void (* altSSLClientDisconnectCallBack)(altSSLClient & oClient); ///< Disconnected Call Back Function

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  TCP client class
///
class altSSLClient : public altBase, private altUncopyable
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  pCallBackFunc       [I ] Recv Call Back Function
  /// \param  pDisconnectCallBack [I ] Disconnect Call Back Function
  /// \param  nSSLVersion         [I ] SSL Version (ALT_SSL_V2 or ALT_SSL_V3 or ALT_TSL_V1)
  ///
  LIBALT_API altSSLClient(altSSLClientCallBack pCallBackFunc, altSSLClientDisconnectCallBack pDisconnectCallBack, const altByte nSSLVersion = ALT_SSL_V3) ALT_THROWS (alt_t);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altSSLClient();

  ///
  /// \brief  Connect
  ///
  /// \param  sIP   [I ] IP Address
  /// \param  nPort [I ] Port NO
  ///
  /// \return ALT_S_SUCCESS       success
  /// \return ALT_E_UNKNOWN_HOST  unknown host error
  /// \return ALT_E_CONNECT       connect error
  /// \return ALT_E_ERROR         error
  ///
  LIBALT_API alt_t Connect(const altStr & sIP, const altUInt nPort);

  ///
  /// \brief  Disconnect
  ///
  /// \return ALT_S_SUCCESS       success
  ///
  LIBALT_API alt_t Disconnect();

  ///
  /// \brief  Send
  ///
  /// \param  pData [I ] Send Data
  /// \param  nSize [I ] Send Data Size
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_NOMEM     out of memory error
  ///
  LIBALT_API alt_t Send(const altChar * pData, const altUInt nSize);

  ///
  /// \brief  Send
  ///
  /// \param  pData [I ] Send Data
  /// \param  nSize [I ] Send Data Size
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_NOMEM     out of memory error
  ///
  LIBALT_API alt_t Send(const altCharPtr & pData, const altUInt nSize);

  ///
  /// \brief  Get IP
  ///
  /// \return IP Address
  ///
  LIBALT_API altStr GetIP() const;

  ///
  /// \brief Get Port NO
  ///
  /// \return Port NO
  ///
  LIBALT_API altInt GetPort() const;

protected:
  ///
  /// \brief  Disconnected
  ///
  /// \return ALT_S_SUCCESS       success
  ///
  LIBALT_API alt_t Disconnected();

  ///
  /// \brief  Send Thread
  ///
  /// \param  pParam  [I ] this Client Object
  ///
  LIBALT_API static alt_t SendThread(void * pParam);

  ///
  /// \brief  Recv Thread
  ///
  /// \param  pParam  [I ] this Client Object
  ///
  LIBALT_API static alt_t RecvThread(void * pParam);

  ///
  /// \brief  Request Thread
  ///
  /// \param  pParam  [I ] this Client Object
  ///
  LIBALT_API static alt_t RequestThread(void * pParam);

  altSSLClientCallBack              m_pCallBackFunc;        ///< Recv Call Back Function
  altSSLClientDisconnectCallBack    m_pDisconnectCallBack;  ///< Disconnect Call Back Function
  altSSLSocket                      m_oSocket;              ///< Socket
  altLoopThread                     m_oSendThread;          ///< Send Thread
  altLoopThread                     m_oRecvThread;          ///< Recv Thread
  altLoopThread                     m_oRequestThread;       ///< Reqeust Proccess Thread
  altQue<altClientPacket *>         m_oSendQue;             ///< Send Que
  altQue<altClientPacket *>         m_oRecvQue;             ///< Recv Que
  altInetAddress                    m_oInetAddr;            ///< Internet Address
  altByte                           m_nSSLVersion;          ///< SSL Version
};
#endif  //ALTSSLCLIENT_H
