#ifndef altTCPCLIENT_H
#define altTCPCLIENT_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTCPClient.h
 * \brief   TCP network client class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altSocket.h>
#include <altNet/altClientPacket.h>
#include <altMisc/altQue.h>
#include <altBase/altCharPtr.h>
#include <altBase/altLoopThread.h>
#include <altBase/altLog.h>
#include <altBase/altStatus.h>
#include <altBase/altUncopyable.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
class altTCPClient;
typedef void (* altNetClientCallBack)(altTCPClient & oClient, const altCharPtr, const altUInt); ///< Receive Call Back Function
typedef void (* altNetClientDisconnectCallBack)(altTCPClient & oClient); ///< Disconnected Call Back Function

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  TCP client class
///
class altTCPClient : public altBase, private altUncopyable
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  pCallBackFunc       [I ] Recv Call Back Function
  /// \param  pDisconnectCallBack [I ] Disconnect Call Back Function
  ///
  LIBALT_API altTCPClient(altNetClientCallBack pCallBackFunc, altNetClientDisconnectCallBack pDisconnectCallBack) ALT_THROWS (alt_t);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altTCPClient();

  ///
  /// \brief  Connect
  ///
  /// \param  sIP   [I ] IP Address
  /// \param  nPort [I ] Port NO
  ///
  /// \return ALT_S_SUCCESS       success
  /// \return ALT_E_UNKNOWN_HOST  unknown host error
  /// \return ALT_E_CONNECT       connect error
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
  LIBALT_API alt_t Send(const altCharPtr pData, const altUInt nSize);

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

  altNetClientCallBack            m_pCallBackFunc;        ///< Recv Call Back Function
  altNetClientDisconnectCallBack  m_pDisconnectCallBack;  ///< Disconnect Call Back Function
  altSocket                       m_oSocket;              ///< Socket
  altLoopThread                   m_oSendThread;          ///< Send Thread
  altLoopThread                   m_oRecvThread;          ///< Recv Thread
  altLoopThread                   m_oRequestThread;       ///< Reqeust Proccess Thread
  altQue<altClientPacket *>       m_oSendQue;             ///< Send Que
  altQue<altClientPacket *>       m_oRecvQue;             ///< Recv Que
  altInetAddress                  m_oInetAddr;            ///< Internet Address
};
#endif  //altTCPClient_H
