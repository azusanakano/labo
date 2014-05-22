#ifndef ALTINETADDRESS_H
#define ALTINETADDRESS_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altInetAddress.h
 * \brief   Internet socket address class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altSocketAddress.h>
#include <altBase/altLog.h>
#include <altBase/altStatus.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/


/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Internet Socket Address Class
///
class altInetAddress : public altSocketAddress
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altInetAddress();

  ///
  /// \brief  Constructor
  ///
  LIBALT_API altInetAddress(const SOCKADDR_IN & oAddr);

  ///
  /// \brief  Constructor
  ///
  /// \param  nPort   [I ] Port Number
  ///
  LIBALT_API altInetAddress(const altInt nPort);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altInetAddress();

  ///
  /// \brief  Initialize
  ///
  /// \param  szIP    [I ] IP Address
  /// \param  nPort   [I ] Port Number
  ///
  /// \return ALT_S_SUCCESS       success
  /// \return ALT_E_UNKOWN_HOST   unknown host error
  ///
  LIBALT_API alt_t Init(const altChar * szIP, const altInt nPort);

  ///
  /// \brief  Get Pointer of Internet Socket Address
  ///
  /// \return Pointer of Internet Socket Address
  ///
  LIBALT_API const SOCKADDR_IN * GetAddrInPtr() const;

  ///
  /// \brief  Set Internet Socket Address
  ///
  /// \param  oAddr [I ] Internet Socket Address
  ///
  LIBALT_API void SetAddr(const SOCKADDR_IN & oAddr);

  ///
  /// \brief Get IP Address
  ///
  /// \return IP Address
  ///
  LIBALT_API const altStr GetIP() const;

  ///
  /// \brief Get Port NO
  ///
  /// \return Port NO
  ///
  LIBALT_API altInt GetPort() const;

protected:
  SOCKADDR_IN m_oAddr;    ///< Internet Socket Address
};
#endif  //ALTINETADDRESS_H
