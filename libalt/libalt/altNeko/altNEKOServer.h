#ifndef ALTNEKOSERVER_H
#define ALTNEKOSERVER_H
/*--------------------------------------------------------------------------*

   Alternative Llibrary

  $Id: altNEKOServer.h 794 2008-01-21 06:44:31Z nekosys $

  Copyright (C) 2007 NEKO SYSTEM
 
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or any later version.
 
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Library General Public License for more details.
 
  You should have received a copy of the GNU Library General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *---------------------------------------------------------------------------*/
/**
 * \file    altNEKOServer.h
 * \brief   NEKO Network Server
 * \date    2007
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altTCPServer.h>
#include <altNet/altSSLServer.h>
#include <altMisc/altDataStream.h>

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
#define aiNEKOServer altNEKOServer::GetInstance()
#define ALT_REMOTE_FUNC_ENT(function) {#function, function}

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef alt_t (* altRemoteFunction)(const altCNETConnectionPtr & oConnection, altDataStream & oDataStream, altDataStream & oReturnDataStream);
typedef std::map<altStr, altRemoteFunction> altRemoteFunctionMap;
typedef struct {
  altStr            sFuncName;
  altRemoteFunction pRemoteFunc;
} altRemoteFuncDef;

typedef std::map<altInt, altByte> altPortMap;

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  SSL Server Class
///
class altNEKOServer : public altSingleton<altNEKOServer>, protected altSyncThread
{
friend class altSingleton<altNEKOServer>;
protected:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altNEKOServer();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altNEKOServer();

public:
  ///
  /// \brief  Open Port
  ///
  /// \param  nPort               [I ] Port NO
  /// \param  oRemoteFunc         [I ] Remote function
  /// \param  nRemoteFuncSize     [I ] Remote function count
  /// \param  pReceiveCallBack    [I ] Receive Call Back Function
  /// \param  pAcceptCallBack     [I ] Accept Call Back Function
  /// \param  pDisconnectCallBack [I ] Disconnected Call Back Function
  /// \param  nThreadCount        [I ] Request Thread Count
  /// \param  nListenQueSize      [I ] Listen Que Size
  /// \param  nAcceptThreadCount  [I ] Accept Thread Count
  /// \param  nSSLVersion         [I ] SSL Version Number(ALT_NO_SSL or ALT_SSL_V23 or ALT_SSL_V2 or ALT_SSL_V3 or ALT_TSL_V1)
  ///
  /// \return ALT_S_SUCCESS     success
  /// \return ALT_E_WSASTARTUP  start up error
  /// \return ALT_E_WSAVERSION  WinSock version error
  /// \return ALT_E_NOMEM       Out Of Memory error
  /// \return ALT_E_INVAL       Invalid Paramter
  ///
  LIBALT_API alt_t OpenPort(const altInt nPort, const altRemoteFuncDef oRemoteFunc[], const altUInt nRemoteFuncSize, const altNETAcceptCallBack pAcceptCallBack = NULL, const altNETDisconnectCallBackFunc pDisconnectCallBack = NULL, const altUInt nThreadCount = 10, const altInt nListenQueSize = 5, const altUInt nAcceptThreadCount = 1, const altByte nSSLVersion = ALT_SSL_V3);
  
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
  LIBALT_API static altNEKOServer & GetInstance();

private:
  ///
  /// \brief  Receive call back function
  ///
  /// \param  oConnection [I ] Connection
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API static alt_t ReceiveCallBack(const altCNETConnectionPtr & oConnection, const altCharPtr & pData, const altUInt nSize);

  altRemoteFunctionMap  m_oRemoteFuncMap;
  altPortMap            m_oPortMap;
  altSSLAcceptorMap     m_oSSLAcceptorMap;
  altTCPAcceptorMap     m_oTCPAcceptorMap;  ///< TCP Acceptor Map
};

#endif
