#ifndef ALTNETSENDER_H
#define ALTNETSENDER_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETSender.h
 * \brief   Network data sender class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETPacket.h>
#include <altNet/altNETConnection.h>
#include <altMisc/altQue.h>
#include <altBase/altCharPtr.h>
#include <altBase/altPtr.h>
#include <altBase/altLoopThread.h>
#include <altBase/altLog.h>
#include <altBase/altStatus.h>
#include <altBase/altSyncThread.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
class altNETPacket;
class altNETConnection;
typedef const altNETConnection      altCNETConnection;      ///< const altNETConnection
typedef altPtr<altCNETConnection>   altCNETConnectionPtr;   ///< pointer of const altNETConnection

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  NET Sender
///
class altNETSender : public altBase, protected altSyncThread
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altNETSender();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altNETSender();

  ///
  /// \brief  Send
  ///
  /// \param  pConnection [I ] Connection
  /// \param  pData       [I ] Data
  /// \param  nSize       [I ] Data Size
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t Send(const altCNETConnectionPtr & pConnection, const altCharPtr & pData, const altInt nSize) const;

  ///
  /// \brief  Get Queue Size
  ///
  /// \return Queue Size
  ///
  LIBALT_API altUInt GetQueSize() const;

  ///
  /// \brief  Start Send Thread
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t Start();

  ///
  /// \brief  Stop Send Thread
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t Stop();

protected:
  ///
  /// \brief  Send Thread
  ///
  /// \param  pParam  [I ] altNETSender object
  ///
  LIBALT_API static alt_t SendThread(void * pParam);

  mutable altQue<altNETPacket *>  m_oPacketQue;   ///< send packet queue
  altLoopThread                   m_oSendThread;  ///< send thread
};
#endif  //ALTNETNETSENDER_H

