#ifndef ALTNETSERVERCONNECTION_H
#define ALTNETSERVERCONNECTION_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETServerConnection.h
 * \brief   Server Network Connection
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETServerInfo.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
class altNETServerInfo;
class altNETServerConnection;
typedef const altNETServerConnection     altCNETServerConnection;
typedef altPtr<altCNETServerConnection>  altCNETServerConnectionPtr;

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Server Network Connection Class
///
class altNETServerConnection : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  oServerInfo [I ] Server infomation
  ///
  LIBALT_API altNETServerConnection(const altNETServerInfo & oServerInfo);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altNETServerConnection();

  ///
  /// \brief  Call accept call back function
  ///
  /// \param  nPort           [I ] Accepted port number
  /// \param  pNETConnection  [I ] Pointer of server connection
  ///
  void CallAcceptCallBack(const altInt nPort) const;

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
  alt_t CallReceiveCallBack(const altCharPtr & pData, const altUInt nSize) const;

  ///
  /// \brief  Call disconnect call back function
  ///
  /// \param  pConnection [I ] Pointer of server connection
  ///
  void CallDisconnectCallBack() const;

private:
  altNETServerInfo  m_oServerInfo;
};

#endif
