#ifndef ALTNETCONNECTIONMANAGER_H
#define ALTNETCONNECTIONMANAGER_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETConnectionManager.h
 * \brief   Network connection manager class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETServerInfo.h>
#include <altNet/altNETServerConnection.h>
#include <altNet/altNETConnection.h>
#include <altNet/altNETReceiverBroker.h>
#include <altNet/altNetUtil.h>
#include <altBase/altStr.h>
#include <altBase/altPtr.h>
#include <altBase/altLog.h>
#include <altBase/altSingleton.h>

#include <map>

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
///
/// \brief  Get Instance
///
#define aiNETConnectionManager altNETConnectionManager::GetInstance()

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef std::map<SOCKET, altCNETConnectionPtr>    altNETConnectionMap;        ///< Map of altCNETConnectionPtr
typedef std::map<altInt, altNETReceiverBroker *>  altNETReceiverBrokerMap;    ///< NET Receiver Broker Map
typedef std::map<altStr, altNETServerInfo *>      altNETServerInfoMap;        ///< Map of server infomation

typedef void (* altNETDisconnectCallBackFunc)(const altCNETConnectionPtr &);

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  NET Connection Manager Class
///
class altNETConnectionManager : public altSingleton<altNETConnectionManager>, private altSyncThread
{
friend class altSingleton<altNETConnectionManager>;
protected:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altNETConnectionManager();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altNETConnectionManager();

public:
  ///
  /// \brief  Set Disconnected Call Back Function
  ///
  /// \param  pDisconnectedFunc [I ] Disconnected Call Back Function
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetDisconnectedCallBackFunc(altNETDisconnectCallBackFunc pDisconnectedFunc);

  ///
  /// \brief  Add Connection
  ///
  /// \param  pConnection   [I ] Pointer of NET Connection
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Add(const altCNETConnectionPtr & pConnection);

  ///
  /// \brief  Delete Connection
  ///
  /// \param  pConnection   [I ] Pointer of NET Connection
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t Del(const altCNETConnectionPtr & pConnection);

  ///
  /// \brief  Get Connection Count
  ///
  /// \return Connection Count
  ///
  LIBALT_API altUInt Size() const;
  
  ///
  /// \brief  Add NET Receiver Broker
  ///
  /// \param  nPort               [I ] Port Number
  /// \param  pTCPReceiverBroker  [I ] Pointer of TCP Receiver Broker
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Add(const altInt nPort, altNETReceiverBroker * pNETReceiverBroker);

  ///
  /// \brief  Delete NET Receiver Broker
  ///
  /// \param  nPort [I ] Port Number
  ///
  LIBALT_API void DeletePort(const altInt nPort);

  ///
  /// \brief  Close all client connection
  ///
  LIBALT_API void CloseAllClientConnection();

  ///
  /// \brief  Add server
  ///
  /// \param  sIP         [I ] IP address
  /// \param  oServerInfo [I ] Server infomation
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t AddServer(const altStr & sIP, const altNETServerInfo & oServerInfo);

  ///
  /// \brief  Get server IP address or not
  ///
  /// \param  sIP [I ] IP address
  ///
  /// \return true  Server IP address
  /// \return false Not server IP address
  ///
  LIBALT_API altBool IsServerIP(const altStr & sIP);

  ///
  /// \brief  Get server infomation
  ///
  /// \param  sIP [I ] IP address
  ///
  /// \return Server infomation
  ///
  LIBALT_API const altNETServerInfo GetServerInfo(const altStr & sIP);

  ///
  /// \brief  Set receive buffer size
  ///
  /// \param  nSize [I ] Receive buffer size
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_INVAL   invalid paramter
  ///
  LIBALT_API alt_t SetRecvBufferSize(const altUInt nSize);

  ///
  /// \brief  Get receive buffer size
  ///
  /// \return Receive buffer size
  ///
  LIBALT_API const altUInt GetRecvBufferSize();

private:
  altNETConnectionMap             m_oClientConnectionMap;       ///< Client connection map
  altNETConnectionMap             m_oServerConnectionMap;       ///< Server connection map
  altNETReceiverBrokerMap         m_oNETReceiverBrokerMap;      ///< Receiver broker
  altNETDisconnectCallBackFunc    m_pDisconnectedCallBackFunc;  ///< Disconnected call back function
  altNETServerInfoMap             m_oServerInfoMap;             ///< Server infomation map
  altUInt                         m_nReceiveBufferSize;         ///< Receive buffer size
};
#endif  //altTCPConnectionManager_H


