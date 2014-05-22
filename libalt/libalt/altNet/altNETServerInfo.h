#ifndef ALTNETSERVERINFO_H
#define ALTNETSERVERINFO_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETServerInfo.h
 * \brief   Server Network Infomation
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCharPtr.h>
#include <altBase/altStr.h>
#include <altBase/altLog.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
class altNETServerConnection;
typedef altPtr<const altNETServerConnection> altCNETServerConnectionPtr;

typedef void (* altNETServerAcceptCallBack)(const altInt nPort, const altCNETServerConnectionPtr & pNETConnection);                           ///< Accept call back function
typedef alt_t(* altNETServerReceiveCallBack)(const altCNETServerConnectionPtr & pConnection, const altCharPtr & pData, const altUInt nSize);  ///< Data receive call back function
typedef void (* altNETServerDisconnectCallBack)(const altCNETServerConnectionPtr & pConnection);                                              ///< Disconnect call back function

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Server Network Infomation Class
///
class altNETServerInfo : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altNETServerInfo();
  
  ///
  /// \brief  Constructor
  ///
  /// \param  pAcceptCallBackFunc     [I ] Accept call back function
  /// \param  pReceiveCallBackFunc    [I ] Receive call back function
  /// \param  pDisconnectCallBackFunc [I ] Disconnect call back function
  ///
  LIBALT_API altNETServerInfo(altNETServerAcceptCallBack pAcceptCallBackFunc, altNETServerReceiveCallBack pReceiveCallBackFunc, altNETServerDisconnectCallBack pDisconnectCallBackFunc);

  ///
  /// \brief  Copy constructor
  ///
  /// \param  oServerInfo [I ] Server infomation
  ///
  LIBALT_API altNETServerInfo(const altNETServerInfo & oServerInfo);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altNETServerInfo();

  ///
  /// \brief  Call accept call back function
  ///
  /// \param  nPort           [I ] Accepted port number
  /// \param  pNETConnection  [I ] Pointer of server connection
  ///
  void CallAcceptCallBack(const altInt nPort, const altCNETServerConnectionPtr & pNETConnection) const;

  ///
  /// \brief  Call receive call back function
  ///
  /// \param  pConnection [I ] Pointer of server connection
  /// \param  pData       [I ] Receive data
  /// \param  nSize       [I ] Receive data size
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  alt_t CallReceiveCallBack(const altCNETServerConnectionPtr & pConnection, const altCharPtr & pData, const altUInt nSize) const;

  ///
  /// \brief  Call disconnect call back function
  ///
  /// \param  pConnection [I ] Pointer of server connection
  ///
  void CallDisconnectCallBack(const altCNETServerConnectionPtr & pConnection) const;

private:
  altNETServerAcceptCallBack      m_pAcceptCallBackFunc;      ///< Server accept callback function
  altNETServerReceiveCallBack     m_pReceiveCallBackFunc;     ///< Server receive callback function
  altNETServerDisconnectCallBack  m_pDisconnectCallBackFunc;  ///< Server disconnect callback function
};

#endif
