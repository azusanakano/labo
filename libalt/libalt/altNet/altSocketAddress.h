#ifndef ALTSOCKETADDRESS_H
#define ALTSOCKETADDRESS_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSocketAddress.h
 * \brief   Socket address class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNetCommon.h>
#include <altBase/altLog.h>
#include <altBase/altStatus.h>
#include <altBase/altBase.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/


/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Socket Address Class
///
class altSocketAddress : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altSocketAddress();

  ///
  /// \brief  Constructor
  ///
  /// \param  oAddr     [I ] Socket Address
  /// \param  nAddrLen  [I ] Socket Address Length
  ///
  LIBALT_API altSocketAddress(const SOCKADDR & oAddr, const altUInt nAddrLen);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altSocketAddress();

  ///
  /// \brief  Get Socket Address
  ///
  /// \return Socket Address
  ///
  LIBALT_API const SOCKADDR & GetAddr() const;

  ///
  /// \brief  Get Socket Address Length
  ///
  /// \return Socket Address Length
  ///
  LIBALT_API altUInt GetAddrLen() const;

  ///
  /// \brief  Get Pointer of Socket Address
  ///
  /// \return Pointer of Socket Address
  ///
  LIBALT_API const SOCKADDR * GetAddrPtr() const;

protected:
  SOCKADDR    m_oAddr;
  altUInt     m_nAddrLen;
};
#endif  //ALTSOCKETADDRESS_H
