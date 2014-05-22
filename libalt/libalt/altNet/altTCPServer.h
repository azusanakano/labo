#ifndef ALTTCPSERVER_H
#define ALTTCPSERVER_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTCPServer.h
 * \brief   TCP network server class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETConnectionManager.h>
#include <altNet/altTCPAcceptor.h>
#include <altBase/altLog.h>
#include <altBase/altStatus.h>
#include <altBase/altSyncThread.h>
#include <altBase/altUncopyable.h>

#include <map>

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
///
/// \brief  Get TCP Server Instance
///
#define aiTCPServer altTCPServer::GetInstance()

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
class altTCPAcceptor;
typedef std::map<altInt, altTCPAcceptor *> altTCPAcceptorMap;   ///< TCP Acceptor Map

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  TCP Server Class
///
class altTCPServer : public altSingleton<altTCPServer>, protected altSyncThread
{
friend class altSingleton<altTCPServer>;
protected:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altTCPServer();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altTCPServer();

public:
  ///
  /// \brief  Open Port
  ///
  /// \param  nPort               [I ] Port NO
  /// \param  pReceiveCallBack    [I ] Receive Call Back Function
  /// \param  pAcceptCallBack     [I ] Accept Call Back Function
  /// \param  pDisconnectCallBack [I ] Disconnected Call Back Function
  /// \param  nThreadCount        [I ] Request Thread Count
  /// \param  nListenQueSize      [I ] Listen Que Size
  ///
  /// \return ALT_S_SUCCESS     success
  /// \return ALT_E_WSASTARTUP  start up error
  /// \return ALT_E_WSAVERSION  WinSock version error
  /// \return ALT_E_NOMEM       Out Of Memory error
  /// \return ALT_E_INVAL       Invalid Paramter
  ///
  LIBALT_API alt_t OpenPort(const altInt nPort, const altNETReceiveCallBack pReceiveCallBack, const altNETAcceptCallBack pAcceptCallBack = NULL, const altNETDisconnectCallBackFunc pDisconnectCallBack = NULL, const altUInt nThreadCount = 10, const altInt nListenQueSize = 5);

  ///
  /// \brief  Close Port
  ///
  /// \param  nPort   [I ] Port NO
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API alt_t ClosePort(const altInt nPort);

  ///
  /// \brief  Close All Port
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API alt_t ClosePortAll();

  ///
  /// \brief  Close all client connection
  ///
  LIBALT_API void CloseAllClientConnection();

  ///
  /// \brief  Get Instance
  ///
  /// \return Instance
  ///
  LIBALT_API static altTCPServer & GetInstance();

protected:
  ///
  /// \brief  ReStart Threads
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t ReStartThreads();

  altTCPAcceptorMap m_oAcceptorMap; ///< TCP Acceptor Map
};
#endif  //ALTNETTCPSERVER_H
