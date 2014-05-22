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
#include "altNETServerInfo.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altNETServerInfo::altNETServerInfo() :
m_pAcceptCallBackFunc (NULL),
m_pReceiveCallBackFunc (NULL),
m_pDisconnectCallBackFunc (NULL)
{
}

///
/// \brief  Constructor
///
LIBALT_API altNETServerInfo::altNETServerInfo(altNETServerAcceptCallBack pAcceptCallBackFunc, altNETServerReceiveCallBack pReceiveCallBackFunc, altNETServerDisconnectCallBack pDisconnectCallBackFunc) :
m_pAcceptCallBackFunc (pAcceptCallBackFunc),
m_pReceiveCallBackFunc (pReceiveCallBackFunc),
m_pDisconnectCallBackFunc (pDisconnectCallBackFunc)
{
}

///
/// \brief  Copy constructor
///
/// \param  oServerInfo [I ] Server infomation
///
LIBALT_API altNETServerInfo::altNETServerInfo(const altNETServerInfo & oServerInfo) :
m_pAcceptCallBackFunc (oServerInfo.m_pAcceptCallBackFunc),
m_pReceiveCallBackFunc (oServerInfo.m_pReceiveCallBackFunc),
m_pDisconnectCallBackFunc (oServerInfo.m_pDisconnectCallBackFunc)
{
}

///
/// \brief  Destructor
///
LIBALT_API altNETServerInfo::~altNETServerInfo()
{
}

///
/// \brief  Call accept call back function
///
/// \param  nPort           [I ] Accepted port number
/// \param  pNETConnection  [I ] Pointer of server connection
///
void altNETServerInfo::CallAcceptCallBack(const altInt nPort, const altCNETServerConnectionPtr & pNETConnection) const
{
  if (m_pAcceptCallBackFunc != NULL) {
    m_pAcceptCallBackFunc (nPort, pNETConnection);
  }
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
alt_t altNETServerInfo::CallReceiveCallBack(const altCNETServerConnectionPtr & pConnection, const altCharPtr & pData, const altUInt nSize) const
{
  alt_t status;

  if (m_pReceiveCallBackFunc != NULL) {
    status = m_pReceiveCallBackFunc (pConnection, pData, nSize);
    if (ALT_IS_ERR (status)) {
      ALT_RET (ALT_E_ERROR);
    }
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Call disconnect call back function
///
/// \param  pConnection [I ] Pointer of server connection
///
void altNETServerInfo::CallDisconnectCallBack(const altCNETServerConnectionPtr & pConnection) const
{
  if (m_pDisconnectCallBackFunc != NULL) {
    m_pDisconnectCallBackFunc (pConnection);
  }
}
