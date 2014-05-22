#ifndef ALTNETRECEIVERBROKER_H
#define ALTNETRECEIVERBROKER_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETReceiverBroker.h
 * \brief   Network receiver broker class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETReceiver.h>
#include <altNet/altNETConnection.h>
#include <altBase/altPtr.h>
#include <altBase/altUncopyable.h>
#include <altBase/altSyncThread.h>
#include <altBase/altLoopThread.h>

#include <vector>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef std::vector<altNETReceiver *>  altNETReceiverContainer; ///< NET Receiver Container

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  NET Connection Class
///
class altNETReceiverBroker : public altBase, private altUncopyable, private altSyncThread
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  pReceiveCallBack      [I ] NET Data Receive Call Back Function
  /// \param  nThreadCount          [I ] Request Thread Count
  ///
  LIBALT_API altNETReceiverBroker(const altNETReceiveCallBack pCallBackFunc, const altUInt nThreadCount = 10);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altNETReceiverBroker();

  ///
  /// \brief  Add NET Connection
  ///
  /// \param  pNETConnection  [I ] NET Connection
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t Add(const altCNETConnectionPtr & pNETConnection);

  ///
  /// \brief  Delete NET Connection
  ///
  /// \param  pNETConnection  [I ] NET Connection
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t Del(const altCNETConnectionPtr & pNETConnection);

  ///
  /// \brief  Delete all client connection
  ///
  LIBALT_API void DelAllClient();

  ///
  /// \brief  Set receive buffer size
  ///
  /// \param  nSize [I ] receive buffer size
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_INVAL     invalid paramter
  ///
  LIBALT_API alt_t SetRecvBufferSize(const altUInt nSize);

protected:
  ///
  /// \brief  New NET Receiver
  ///
  LIBALT_API void CreateNewNETReceiver();

  ///
  /// \brief  Deleter Thread
  ///
  /// \param  pParam  [IO] this object
  ///
  LIBALT_API static alt_t DeleterThread(void * pParam);

  altNETReceiverContainer    m_oNETReceiverContainer;  ///< NET Receiver Container
  altNETReceiveCallBack      m_pReceiveCallBackFunc;   ///< NET Receive Call Back Function
  altUInt                    m_nRequestThreadCount;    ///< Request Thread Count
  altLoopThread              m_oDeleterThread;         ///< Deleter Thread
};
#endif  //ALTNETRECEIVERBROKER_H
