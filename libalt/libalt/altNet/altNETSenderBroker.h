#ifndef ALTNETSENDBROKER_H
#define ALTNETSENDBROKER_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNetNETSendBroker.h
 * \brief   Network data sender broker class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETSender.h>
#include <altBase/altPtr.h>
#include <altBase/altLog.h>
#include <altBase/altStatus.h>
#include <altBase/altSyncThread.h>

#include <vector>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
class altNETConnectionManager;
class altNETConnection;
class altNETSender;

typedef std::vector<altNETSender *> altNetNETSenderContainer;


/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  NET Send Broker
///
class altNETSenderBroker : public altBase, protected altSyncThread
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altNETSenderBroker();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altNETSenderBroker();

  ///
  /// \brief  Send
  ///
  /// \param  nSocket  [I ] socket
  /// \param  pData    [I ] data
  /// \param  nSize    [I ] data size
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_NOMEM     out of memory
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t Send(const altCNETConnectionPtr & pConnection, const altCharPtr & pData, const altInt nSize) const;

protected:
  ///
  /// \brief  Create New Sender
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t CreateNewSender() const;

  ///
  /// \brief  Deleter Thread
  ///
  /// \param  pParam  [IO] this object
  ///
  LIBALT_API static alt_t DeleterThread(void * pParam);

  mutable altNetNETSenderContainer  m_oNETSenderContainer;    ///< NET Sender Container
  altLoopThread                     m_oDeleterThread;         ///< Deleter Thread
};
#endif  //ALTNETNETSENDBROKER_H
