/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETConnectionManager.cpp
 * \brief   Network connection manager class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altNETConnectionManager.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altNETConnectionManager::altNETConnectionManager() :
m_oClientConnectionMap(),
m_oServerConnectionMap(),
m_oNETReceiverBrokerMap(),
m_pDisconnectedCallBackFunc (NULL),
m_oServerInfoMap(),
m_nReceiveBufferSize (1024 * 5)
{
}

///
/// \brief  Destructor
///
LIBALT_API altNETConnectionManager::~altNETConnectionManager()
{
  m_pDisconnectedCallBackFunc = NULL;
}

///
/// \brief  Set Disconnected Call Back Function
///
/// \param  pDisconnectedFunc [I ] Disconnected Call Back Function
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altNETConnectionManager::SetDisconnectedCallBackFunc(altNETDisconnectCallBackFunc pDisconnectedFunc)
{
  m_pDisconnectedCallBackFunc = pDisconnectedFunc;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Add Connection
///
/// \param  pConnection   [I ] Pointer of NET Connection
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altNETConnectionManager::Add(const altCNETConnectionPtr & pConnection)
{
  BeginLock();
  try {
    if (IsServerIP (pConnection->GetIP())) {
      m_oServerConnectionMap[pConnection->GetSocket()] = pConnection;
    }
    else {
      m_oClientConnectionMap[pConnection->GetSocket()] = pConnection;
    }
  }
  catch (std::exception & e) {
    EndLock();
    ALT_RET_P (ALT_E_ERROR, e.what());
  }
  catch (...) {
    EndLock();
    ALT_RET (ALT_E_ERROR);
  }
  EndLock();
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Delete Connection
///
/// \param  pConnection   [I ] Pointer of NET Connection
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altNETConnectionManager::Del(const altCNETConnectionPtr & pConnection)
{
  alt_t status;
  BeginLock();

  for (altNETReceiverBrokerMap::iterator i = m_oNETReceiverBrokerMap.begin(); i != m_oNETReceiverBrokerMap.end(); i++) {
    status = i->second->Del (pConnection);
    if (status == ALT_S_SUCCESS) {
      break;
    }
  }

  if (pConnection->IsServerConnection()) {
    altNETConnectionMap::iterator i = m_oServerConnectionMap.find (pConnection->GetSocket());
    if (i != m_oServerConnectionMap.end()) {
      // Call Disconnected Call Back Function
      altNETServerConnection & oServerConnection = (altNETServerConnection &)(* (i->second));
      oServerConnection.CallDisconnectCallBack();

      // Close Connection
      altNETConnection & oNETConnection = const_cast<altNETConnection &>(* (i->second));
      status = oNETConnection.Close();
      ALT_LOG (status);
      m_oServerConnectionMap.erase (i);
    }
  }
  else {
    altNETConnectionMap::iterator i = m_oClientConnectionMap.find (pConnection->GetSocket());
    if (i != m_oClientConnectionMap.end()) {

      // Call Disconnected Call Back Function
      if (m_pDisconnectedCallBackFunc != NULL) {
        m_pDisconnectedCallBackFunc (i->second);
      }

      // Close Connection
      altNETConnection & oNETConnection = const_cast<altNETConnection &>(* (i->second));
      status = oNETConnection.Close();
      ALT_LOG (status);

      m_oClientConnectionMap.erase (i);
    }
  }
  EndLock();
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Connection Count
///
/// \return Connection Count
///
LIBALT_API altUInt altNETConnectionManager::Size() const
{
  return static_cast<altUInt>(m_oClientConnectionMap.size());
}

///
/// \brief  Add NET Receiver Broker
///
/// \param  nPort               [I ] Port Number
/// \param  pTCPReceiverBroker  [I ] Pointer of TCP Receiver Broker
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altNETConnectionManager::Add(const altInt nPort, altNETReceiverBroker * pNETReceiverBroker)
{
  try {
    m_oNETReceiverBrokerMap[nPort] = pNETReceiverBroker;
  }
  catch (std::exception & e) {
    ALT_RET_P (ALT_E_ERROR, e.what());
  }
  catch (...) {
    ALT_RET (ALT_E_ERROR);
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Delete TCP Receiver Broker
///
/// \param  nPort [I ] Port Number
///
LIBALT_API void altNETConnectionManager::DeletePort(const altInt nPort)
{
  BeginLock();
  m_oNETReceiverBrokerMap.erase (nPort);
  EndLock();
}

///
/// \brief  Close all client connection
///
LIBALT_API void altNETConnectionManager::CloseAllClientConnection()
{
  BeginLock();
  for (altNETReceiverBrokerMap::iterator i = m_oNETReceiverBrokerMap.begin(); i != m_oNETReceiverBrokerMap.end(); i++) {
    i->second->DelAllClient();
  }
  for (altNETConnectionMap::iterator i = m_oClientConnectionMap.begin(); i != m_oClientConnectionMap.end(); i++) {
    // Close Connection
    altNETConnection & oNETConnection = const_cast<altNETConnection &>(* (i->second));
    alt_t status = oNETConnection.Close();
    ALT_LOG (status);

    m_oClientConnectionMap.erase (i);
  }
  EndLock();
}

///
/// \brief  Add server
///
/// \param  sIP         [I ] IP address
/// \param  oServerInfo [I ] Server infomation
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altNETConnectionManager::AddServer(const altStr & sIP, const altNETServerInfo & oServerInfo)
{
  altNETServerInfo *  pServerInfo = ALT_NEW altNETServerInfo (oServerInfo);
  if (pServerInfo == NULL) {
    ALT_RET (ALT_S_SUCCESS);
  }

  try {
    m_oServerInfoMap[sIP] = pServerInfo;
  }
  catch (std::exception & e) {
    ALT_RET_P (ALT_E_ERROR, e.what());
  }
  catch (...) {
    ALT_RET (ALT_E_ERROR);
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get server IP address or not
///
/// \param  sIP [I ] IP address
///
/// \return true  Server IP address
/// \return false Not server IP address
///
LIBALT_API altBool altNETConnectionManager::IsServerIP(const altStr & sIP)
{
  return (m_oServerInfoMap[sIP] != NULL);
}

///
/// \brief  Get server infomation
///
/// \param  sIP [I ] IP address
///
/// \return Server infomation
///
LIBALT_API const altNETServerInfo altNETConnectionManager::GetServerInfo(const altStr & sIP)
{
  altNETServerInfo *  pServerInfo = m_oServerInfoMap[sIP];
  if (pServerInfo == NULL) {
    altNETServerInfo oRet;
    return (oRet);
  }
  return (* pServerInfo);
}

///
/// \brief  Set receive buffer size
///
/// \param  nSize [I ] Receive buffer size
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_INVAL   invalid paramter
///
LIBALT_API alt_t altNETConnectionManager::SetRecvBufferSize(const altUInt nSize)
{
  ALT_P_ASSERT (nSize != 0);
  BeginLock();
  m_nReceiveBufferSize = nSize;
  for (altNETReceiverBrokerMap::iterator i = m_oNETReceiverBrokerMap.begin(); i != m_oNETReceiverBrokerMap.end(); i++) {
    alt_t status = i->second->SetRecvBufferSize (m_nReceiveBufferSize);
    if (ALT_IS_ERR (status)) {
      EndLock();
      ALT_RET (status);
    }
  }
  EndLock();
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get receive buffer size
///
/// \return Receive buffer size
///
LIBALT_API const altUInt altNETConnectionManager::GetRecvBufferSize()
{
  return (m_nReceiveBufferSize);
}
