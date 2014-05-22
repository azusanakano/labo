#ifndef ALTTCPACCEPTOR_H
#define ALTTCPACCEPTOR_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTCPAcceptor.h
 * \brief   Network server acceptor class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETSenderBroker.h>
#include <altNet/altNETReceiverBroker.h>
#include <altNet/altSocket.h>
#include <altNet/altNetCommon.h>
#include <altBase/altLoopThread.h>
#include <altBase/altLog.h>
#include <altBase/altStatus.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef void (* altNETAcceptCallBack)(const altInt nPort, const altCNETConnectionPtr & pNETConnection);
class altTCPServer;

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  network server class
///
class altTCPAcceptor : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  pReceiveCallBack    [I ] Receive call back function
  /// \param  nThreadCount        [I ] Reqeust Thread Count
  ///
  LIBALT_API altTCPAcceptor(const altNETReceiveCallBack pReceiveCallBack, const altUInt nThreadCount = 10);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altTCPAcceptor();

  ///
  /// \brief  Open Port
  ///
  /// \param  nPort               [I ] Port NO
  /// \param  nListenQueSize      [I ] Listen Queue Size
  /// \param  pAcceptCallBack     [I ] Accept Call Back Function
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_INVAL     parameter error
  /// \return ALT_E_SOCKET    create socket error
  /// \return ALT_E_BIND      bind error
  /// \return ALT_E_LISTEN    listen error
  ///
  LIBALT_API virtual alt_t OpenPort(const altInt nPort, const altInt nListenQueSize, const altNETAcceptCallBack pAcceptCallBack);

protected:
  ///
  /// \brief  Close Port
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API virtual alt_t ClosePort();

  ///
  /// \brief  Accept Thread
  ///
  /// \param  pParam  [I ] parameter
  ///
  LIBALT_API static alt_t AcceptThread(void * pParam);

  altNETReceiverBroker        m_oReceiverBroker;      ///< NET receiver broker
  altNETSenderBroker          m_oSenderBroker;        ///< NET send broker
  altInt                      m_nPort;                ///< port no
  altSocket                   m_nListenSocket;        ///< listen socket
  altLoopThread               m_oAcceptThread;        ///< accept thread
  altNETAcceptCallBack        m_pAcceptCallBackFunc;  ///< accept call back function
};

#endif  //ALTNETTCPACCEPTOR_H

