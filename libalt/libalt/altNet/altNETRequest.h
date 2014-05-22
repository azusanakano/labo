#ifndef ALTNETREQUEST_H
#define ALTNETREQUEST_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETRequest.h
 * \brief   Network request call back function class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETConnection.h>
#include <altMisc/altQue.h>
#include <altBase/altPtr.h>
#include <altBase/altMem.h>
#include <altBase/altUncopyable.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef alt_t(* altNETReceiveCallBack)(const altCNETConnectionPtr &, const altCharPtr &, const altUInt); ///< Call Back Data Receive Function

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Request Infomation Class
///
class altNETRequest : public altBase, private altUncopyable
{
public:
  ///
  /// \brief  Constructor
  ///
  altNETRequest();

  ///
  /// \brief  Destructor
  ///
  virtual ~altNETRequest();

  altNETReceiveCallBack   m_pReceiveCallBackFunc;   ///< Call Back Function
  altCNETConnectionPtr    m_pConnection;            ///< NET Connection
  altCharPtr              m_pData;                  ///< Received Data
  altUInt                 m_nSize;                  ///< Received Data Size
};

#endif  //ALTNETREQUEST_H
