/*--------------------------------------------------------------------------*

   Alternative Llibrary

  $Id: altNEKOServer.cpp 795 2008-01-21 07:12:10Z nekosys $

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
 * \file    altNEKOServer.cpp
 * \brief   NEKO Network Server
 * \date    2007
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altNEKOServer.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altNEKOServer::altNEKOServer() :
m_oRemoteFuncMap(),
m_oPortMap(),
m_oSSLAcceptorMap(),
m_oTCPAcceptorMap()
{
}

///
/// \brief  Destructor
///
LIBALT_API altNEKOServer::~altNEKOServer()
{
}

///
/// \brief  Open Port
///
/// \param  nPort               [I ] Port NO
/// \param  oRemoteFunc         [I ] Remote function
/// \param  nRemoteFuncSize     [I ] Remote function count
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
LIBALT_API alt_t altNEKOServer::OpenPort(const altInt nPort, const altRemoteFuncDef oRemoteFunc[], const altUInt nRemoteFuncSize, const altNETAcceptCallBack pAcceptCallBack, const altNETDisconnectCallBackFunc pDisconnectCallBack, const altUInt nThreadCount, const altInt nListenQueSize, const altUInt nAcceptThreadCount, const altByte nSSLVersion)
{
  for (altUInt i = 0; i < nRemoteFuncSize; i++) {
    m_oRemoteFuncMap[oRemoteFunc[i].sFuncName] = oRemoteFunc[i].pRemoteFunc;
  }

  alt_t status;

  status = altNetUtil::WSAStartup();
  ALT_ERR_RET (status);

  if (nSSLVersion == ALT_NO_SSL) {
#ifdef ALT_LINUX
    status = altSignal::Block (SIGPIPE);
    ALT_ERR_RET (status);
#endif

    altTCPAcceptor * pAcceptor = ALT_NEW altTCPAcceptor(ReceiveCallBack, nThreadCount);
    if (pAcceptor == NULL) {
      ALT_RET (ALT_E_NOMEM);
    }
    status = pAcceptor->OpenPort (nPort, nListenQueSize, pAcceptCallBack);
    ALT_ERR_RET (status);

    BeginLock();
    m_oTCPAcceptorMap[nPort] = pAcceptor;
    EndLock();

    status = aiNETConnectionManager.SetDisconnectedCallBackFunc (pDisconnectCallBack);
    ALT_ERR_RET (status);
  }
  else {
    status = altNetUtil::SSLLibraryInit();
    ALT_ERR_RET (status);

    altSSLAcceptor * pAcceptor = ALT_NEW altSSLAcceptor(ReceiveCallBack, nThreadCount, nAcceptThreadCount, nSSLVersion);
    if (pAcceptor == NULL) {
      ALT_RET (ALT_E_NOMEM);
    }
    status = pAcceptor->OpenPort (nPort, nListenQueSize, pAcceptCallBack);
    ALT_ERR_RET (status);

    BeginLock();
    m_oSSLAcceptorMap[nPort] = pAcceptor;
    EndLock();

    status = aiNETConnectionManager.SetDisconnectedCallBackFunc (pDisconnectCallBack);
    ALT_ERR_RET (status);
  }
  ALT_ERR_RET (status);
  m_oPortMap[nPort] = nSSLVersion;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Close Port
///
/// \param  nPort   [I ] Port NO
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altNEKOServer::ClosePort(const altInt nPort)
{
  if (m_oPortMap[nPort] == ALT_NO_SSL) {
    BeginLock();
    altTCPAcceptor * pAcceptor = m_oTCPAcceptorMap[nPort];
    if (pAcceptor == NULL) {
      EndLock();
      ALT_RET (ALT_S_SUCCESS);
    }
    altTCPAcceptorMap::iterator i = m_oTCPAcceptorMap.find (nPort);
    m_oTCPAcceptorMap.erase (i);
    delete pAcceptor;
    EndLock();
  }
  else {
    BeginLock();
    altSSLAcceptor * pAcceptor = m_oSSLAcceptorMap[nPort];
    if (pAcceptor == NULL) {
      EndLock();
      ALT_RET (ALT_S_SUCCESS);
    }
    altSSLAcceptorMap::iterator i = m_oSSLAcceptorMap.find (nPort);
    m_oSSLAcceptorMap.erase (i);
    delete pAcceptor;
    EndLock();
  }
  m_oPortMap.erase (nPort);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Close All Port
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altNEKOServer::ClosePortAll()
{
  aiTCPServer.ClosePortAll();
  aiSSLServer.ClosePortAll();
  m_oPortMap.clear();
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Instance
///
/// \return Instance
///
LIBALT_API altNEKOServer & altNEKOServer::GetInstance()
{
  return (altSingleton<altNEKOServer>::GetInstance());
}

///
/// \brief  Receive call back function
///
/// \param  oConnection [I ] Connection
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_NOMEM   out of memory
///
LIBALT_API alt_t altNEKOServer::ReceiveCallBack(const altCNETConnectionPtr & pConnection, const altCharPtr & pData, const altUInt nSize)
{
  alt_t         status;
  altDataStream oDataStream;

  status = oDataStream.SetData (pData, nSize);
  ALT_ERR_RET (status);

  altStr  sFuncName;

  status = oDataStream.Read (sFuncName);
  ALT_ERR_RET (status);

  DWORD   dwSessionID;
  status = oDataStream.Read (dwSessionID);
  ALT_ERR_RET (status);

  altRemoteFunction pRemoteFunc = aiNEKOServer.m_oRemoteFuncMap[sFuncName];
  if (pRemoteFunc != NULL) {
    altDataStream oReturnDataStream;
    
    status = oReturnDataStream.Write (sFuncName);
    ALT_ERR_RET (status);

    status = oReturnDataStream.Write (dwSessionID);
    ALT_ERR_RET (status);

    pRemoteFunc (pConnection, oDataStream, oReturnDataStream);

    altCharPtr  pReturnData;
    status = oReturnDataStream.GetData (pReturnData);
    ALT_ERR_RET (status);

    status = pConnection->Send (pReturnData, oReturnDataStream.GetDataSize());
    ALT_ERR_RET (status);
  }

  ALT_RET (ALT_S_SUCCESS);
}
