#ifndef ALTSSLACCEPTOR_H
#define ALTSSLACCEPTOR_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSSLAcceptor.h
 * \brief   SSL network server acceptor class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETSenderBroker.h>
#include <altNet/altNETReceiverBroker.h>
#include <altNet/altTCPAcceptor.h>
#include <altNet/altNetCommon.h>
#include <altBase/altLoopThread.h>
#include <altBase/altLog.h>
#include <altBase/altStatus.h>

#include <vector>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef std::vector<altLoopThread *> altSSLAcceptThreadContainer; ///< Accept Thread Container

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  SSL Acceptor Class
///
class altSSLAcceptor : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  pReceiveCallBack    [I ] receive call back function
  /// \param  nThreadCount        [I ] Reqeust Thread Count
  /// \param  nAcceptThreadCount  [I ] Accept Thread Count
  /// \param  nSSLVersion         [I ] SSL Version (ALT_SSL_V23 or ALT_SSL_V2 or ALT_SSL_V3 or ALT_TSL_V1)
  ///
  LIBALT_API altSSLAcceptor(const altNETReceiveCallBack pReceiveCallBack, const altUInt nThreadCount, const altUInt nAcceptThreadCount, const altByte nSSLVersion);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altSSLAcceptor();

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
  LIBALT_API alt_t OpenPort(const altInt nPort, const altInt nListenQueSize, const altNETAcceptCallBack pAcceptCallBack);

  ///
  /// \brief  Close Port
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t ClosePort();

protected:
  ///
  /// \brief  Accept Thread
  ///
  /// \param  pParam  [I ] parameter
  ///
  LIBALT_API static alt_t AcceptThread(void * pParam);

  altNETReceiveCallBack         m_pReceiveCallBack;       ///< NET Receive CallBack
  altNETReceiverBroker          m_oReceiverBroker;        ///< NET Receiver Broker
  altNETAcceptCallBack          m_pAcceptCallBack;        ///< NET Accept CallBack
  altInt                        m_nPort;                  ///< Port NO
  altSocket                     m_nListenSocket;          ///< Listen Socket
  altUInt                       m_nAcceptThreadCount;     ///< Accept Thread Count
  altSSLAcceptThreadContainer   m_oAcceptThreadContainer; ///< Accept Thread Container
  altNETSenderBroker            m_oSenderBroker;          ///< NET Sender Broker
  altByte                       m_nSSLVersion;            ///< SSL Version
};

#endif  //ALTNETSSLACCEPTOR_H

