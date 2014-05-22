/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETServerConnection.cpp
 * \brief   Server Network Connection
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altNETServerConnection.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altNETServerConnection::altNETServerConnection(const altNETServerInfo & oServerInfo) :
m_oServerInfo (oServerInfo)
{
}

///
/// \brief  Destructor
///
LIBALT_API altNETServerConnection::~altNETServerConnection()
{
}

///
/// \brief  Call accept call back function
///
/// \param  nPort           [I ] Accepted port number
/// \param  pNETConnection  [I ] Pointer of server connection
///
void altNETServerConnection::CallAcceptCallBack(const altInt nPort) const
{
  m_oServerInfo.CallAcceptCallBack (nPort, this);
}

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
alt_t altNETServerConnection::CallReceiveCallBack(const altCharPtr & pData, const altUInt nSize) const
{
  alt_t status;
  status = m_oServerInfo.CallReceiveCallBack (this, pData, nSize);
  ALT_ERR_RET (status);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Call disconnect call back function
///
/// \param  pConnection [I ] Pointer of server connection
///
void altNETServerConnection::CallDisconnectCallBack() const
{
  m_oServerInfo.CallDisconnectCallBack (this);
}
