/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSSLServer.cpp
 * \brief   SSL network server class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altSSLServer.h"
#include "altSSLAcceptor.h"
#include "altNetUtil.h"
#include "altBase/altRuntime.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altSSLServer::altSSLServer()
{
}

///
/// \brief  Destructor
///
LIBALT_API altSSLServer::~altSSLServer()
{
}

///
/// \brief  Open Port
///
/// \param  nPort               [I ] Port NO
/// \param  pReceiveCallBack    [I ] Receive Call Back Function
/// \param  pAcceptCallBack     [I ] Accept Call Back Function
/// \param  pDisconnectCallBack [I ] Disconnected Call Back Function
/// \param  nThreadCount        [I ] Request Thread Count
/// \param  nListenQueSize      [I ] Listen Que Size
/// \param  nAcceptThreadCount  [I ] Accept Thread Count
/// \param  nSSLVersion         [I ] SSL Version Number
///
/// \return ALT_S_SUCCESS     success
/// \return ALT_E_WSASTARTUP  start up error
/// \return ALT_E_WSAVERSION  WinSock version error
/// \return ALT_E_NOMEM       Out Of Memory error
/// \return ALT_E_INVAL       Invalid Paramter
///
LIBALT_API alt_t altSSLServer::OpenPort(const altInt nPort, const altNETReceiveCallBack pReceiveCallBack, const altNETAcceptCallBack pAcceptCallBack, const altNETDisconnectCallBackFunc pDisconnectCallBack, const altUInt nThreadCount, const altInt nListenQueSize, const altUInt nAcceptThreadCount, const altByte nSSLVersion)
{
  alt_t status;

  status = altNetUtil::WSAStartup();
  ALT_ERR_RET (status);

  status = altNetUtil::SSLLibraryInit();
  ALT_ERR_RET (status);

  if (pReceiveCallBack == NULL) {
    ALT_RET_P (ALT_E_INVAL, "pReceiveCallBack is NULL");
  }

  altSSLAcceptor * pAcceptor = ALT_NEW altSSLAcceptor(pReceiveCallBack, nThreadCount, nAcceptThreadCount, nSSLVersion);
  if (pAcceptor == NULL) {
    ALT_RET (ALT_E_NOMEM);
  }
  status = pAcceptor->OpenPort (nPort, nListenQueSize, pAcceptCallBack);
  ALT_ERR_RET (status);

  BeginLock();
  m_oAcceptorMap[nPort] = pAcceptor;
  EndLock();

  status = aiNETConnectionManager.SetDisconnectedCallBackFunc (pDisconnectCallBack);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Close Port
///
/// \param  nPort   [I ] Port NO
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altSSLServer::ClosePort(const altInt nPort)
{
  BeginLock();
  altSSLAcceptor * pAcceptor = m_oAcceptorMap[nPort];
  if (pAcceptor == NULL) {
    EndLock();
    ALT_RET (ALT_S_SUCCESS);
  }
  altSSLAcceptorMap::iterator i = m_oAcceptorMap.find (nPort);
  m_oAcceptorMap.erase (i);

  delete pAcceptor;

  EndLock();
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Close All Port
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altSSLServer::ClosePortAll()
{
  BeginLock();
  for (altSSLAcceptorMap::iterator i = m_oAcceptorMap.begin(); i != m_oAcceptorMap.end(); i++) {
    delete i->second;
    i->second = NULL;
  }
  m_oAcceptorMap.clear();
  EndLock();

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Instance
///
/// \return Instance
///
LIBALT_API altSSLServer & altSSLServer::GetInstance()
{
  return (altSingleton<altSSLServer>::GetInstance());
}

