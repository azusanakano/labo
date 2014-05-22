#ifndef ALTNETREQUESTINVOKER_H
#define ALTNETREQUESTINVOKER_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETRequestInvoker.h
 * \brief   Network request invoker class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETRequest.h>
#include <altNet/altNETPacket.h>
#include <altMisc/altQue.h>
#include <altBase/altLoopThread.h>

#include <vector>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef altQue<altNETPacket *>        altNETPacketQue;                  ///< Packet Que
typedef altQue<altNETRequest *>       altNETRequestQue;                 ///< Request Que
typedef std::vector<altLoopThread *>  altNETRequestThreadContainer;     ///< Request Thread Container

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Request Invoker Class
///
class altNETRequestInvoker : public altBase, private altUncopyable
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  oPacketQue            [I ] Packet Que
  /// \param  pReceiveCallBackFunc  [I ] Receive Call Back Func
  /// \param  nThreadCount          [I ] Request Thread Count
  ///
  LIBALT_API altNETRequestInvoker(altNETPacketQue & oPacketQue, const altNETReceiveCallBack pReceiveCallBackFunc, const altUInt nThreadCount = 10);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altNETRequestInvoker();

  ///
  /// \brief  Restart threads
  ///
  /// \\return  ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t ReStart();

protected:
  ///
  /// \brief  Request Invoker Thread
  ///
  /// \param  pParam  [IO] altNETRequestInvoker object
  ///
  LIBALT_API static alt_t RequestInvokerThread(void * pParam);

  ///
  /// \brief  Request Thread
  ///
  /// \param  pParam  [I ] Request Infomation
  ///
  LIBALT_API static alt_t RequestThread(void * pParam);

  altNETRequestQue              m_oRequestQue;              ///< Request Que
  altNETRequestThreadContainer  m_oRequestThreadContainer;  ///< Request Thread Container
  altNETPacketQue &             m_oPacketQue;               ///< Packet Que
  altLoopThread                 m_oRequestInvoker;          ///< NET Receive Thread
  altNETReceiveCallBack         m_pReceiveCallBackFunc;     ///< NET Receive Call Back Function
};

#endif  //ALTNETREQUESTINVOKER_H
