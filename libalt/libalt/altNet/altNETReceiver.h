#ifndef ALTNETRECEIVER_H
#define ALTNETRECEIVER_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETReceiver.h
 * \brief   Network data receiver class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETRequestInvoker.h>
#include <altMisc/altQue.h>
#include <altBase/altSyncThread.h>

#include <map>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef std::map<SOCKET, altCNETConnectionPtr> altNETConnectionMap;  ///< Connection Map

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  NET Receiver Class
///
class altNETReceiver : public altBase, protected altSyncThread, private altUncopyable
{
public:
  ///
  /// \brief  Constructor
  ///
  /// \param  pReceiveCallBackFunc  [I ] Receive Call Back Function
  /// \param  nThreadCount          [I ] Request Thread Count
  ///
  LIBALT_API altNETReceiver(const altNETReceiveCallBack pReceiveCallBackFunc, const altUInt nThreadCount, const altUInt nRecvBufferSize);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altNETReceiver();

  ///
  /// \brief  Add Connection
  ///
  /// \param  pConnection [I ] NET Connection
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_I_MAX       max
  ///
  LIBALT_API alt_t Add(const altCNETConnectionPtr & pConnection);

  ///
  /// \brief  Del Connection
  ///
  /// \param  pConnection [I ] NET Connection
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_S_NOT_FOUND not found
  ///
  LIBALT_API alt_t Del(const altCNETConnectionPtr & pConnection);

  ///
  /// \brief  Get Size
  ///
  /// \return content size
  ///
  LIBALT_API altUInt Size() const;

  ///
  /// \brief  Start Receive Thread
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API virtual alt_t Start();

  ///
  /// \brief  Stop Receiver Thread
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t Stop();

  ///
  /// \brief  Pop received packet
  ///
  /// \param  pPacket [ O] pointer of packet
  ///
  /// \return ALT_S_SUCCESS     success
  /// \return ALT_S_NOT_FOUND   not data
  ///
  LIBALT_API alt_t Pop (altNETPacket * & pPacket);

  ///
  /// \brief  Delete all client connection
  ///
  LIBALT_API void DelAllClient();

  ///
  /// \brief  Set receive buffer size
  ///
  /// \param  nSize [I ] receive buffer size
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_INVAL   invalid paramter
  ///
  LIBALT_API alt_t SetRecvBufferSize(const altUInt nSize);

protected:
  ///
  /// \brief  receive thread
  ///
  /// \param  pParam  [I ] altNETReceiver object
  ///
  LIBALT_API static alt_t ReceiveThread(void * pParam);

  altNETConnectionMap   m_oConnectionMap;       ///< NET Connection Map
  altLoopThread         m_oReceiveThreaed;      ///< Receive Thread
  altNETPacketQue       m_oPacketQue;           ///< Packet Que
  altNETRequestInvoker  m_oRequestInvoker;      ///< Request Invoker
  altUInt               m_nRecvBufferSize;      ///< Receive buffer size
};
#endif  //ALTNETNETRECEIVER_H
