#ifndef ALTSSLSERVER_H
#define ALTSSLSERVER_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSSLServer.h
 * \brief   SSL network server class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETConnectionManager.h>
#include <altNet/altSSLAcceptor.h>
#include <altBase/altLog.h>
#include <altBase/altStatus.h>
#include <altBase/altSyncThread.h>
#include <altBase/altUncopyable.h>

#include <map>

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
#define aiSSLServer altSSLServer::GetInstance()

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef std::map<altInt, altSSLAcceptor *> altSSLAcceptorMap;   ///< SSL Acceptor Map

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  SSL Server Class
///
class altSSLServer : public altSingleton<altSSLServer>, protected altSyncThread
{
friend class altSingleton<altSSLServer>;
protected:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altSSLServer();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altSSLServer();

public:
  ///
  /// \brief  Open Port
  ///
  /// \param  nPort               [I ] Port NO
  /// \param  pAcceptCallBack     [I ] Accept Call Back Function
  /// \param  pDisconnectCallBack [I ] Disconnected Call Back Function
  /// \param  nThreadCount        [I ] Request Thread Count
  /// \param  nListenQueSize      [I ] Listen Que Size
  /// \param  nAcceptThreadCount  [I ] Accept Thread Count
  /// \param  nSSLVersion         [I ] SSL Version Number(ALT_SSL_V23 or ALT_SSL_V2 or ALT_SSL_V3 or ALT_TSL_V1)
  ///
  /// \return ALT_S_SUCCESS     success
  /// \return ALT_E_WSASTARTUP  start up error
  /// \return ALT_E_WSAVERSION  WinSock version error
  /// \return ALT_E_NOMEM       Out Of Memory error
  /// \return ALT_E_INVAL       Invalid Paramter
  ///
  LIBALT_API alt_t OpenPort(const altInt nPort, const altNETReceiveCallBack pReceiveCallBack, const altNETAcceptCallBack pAcceptCallBack = NULL, const altNETDisconnectCallBackFunc pDisconnectCallBack = NULL, const altUInt nThreadCount = 10, const altInt nListenQueSize = 5, const altUInt nAcceptThreadCount = 1, const altByte nSSLVersion = ALT_SSL_V3);

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
  /// \brief  Get Instance
  ///
  /// \return Instance
  ///
  LIBALT_API static altSSLServer & GetInstance();

private:
  altSSLAcceptorMap m_oAcceptorMap;  ///< SSL Acceptor Map
};

#endif  //ALTSSLSERVER_H
