/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altInetAddress.cpp
 * \brief   Internet socket address class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altInetAddress.h"
#include "altNetUtil.h"
#include "altBase/altStr.h"

#ifdef ALT_LINUX
  #include <netdb.h>
#endif

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altInetAddress::altInetAddress()
{
  memset (& m_oAddr, 0x00, sizeof (m_oAddr));
  m_nAddrLen = sizeof (m_oAddr);
}

///
/// \brief  Constructor
///
LIBALT_API altInetAddress::altInetAddress(const SOCKADDR_IN & oAddr)
{
  m_oAddr = oAddr;
  m_nAddrLen = sizeof (m_oAddr);
}

///
/// \brief  Constructor
///
/// \param  nPort   [I ] Port Number
///
LIBALT_API altInetAddress::altInetAddress(const altInt nPort)
{
  memset (& m_oAddr, 0x00, sizeof (m_oAddr));
	m_oAddr.sin_family = AF_INET;
	m_oAddr.sin_port = htons (nPort);
#ifdef ALT_LINUX
	m_oAddr.sin_addr.s_addr = htonl (INADDR_ANY);
#endif
  m_nAddrLen = sizeof (m_oAddr);
}

///
/// \brief  Destructor
///
LIBALT_API altInetAddress::~altInetAddress()
{
}

///
/// \brief  Initialize
///
/// \param  szIP    [I ] IP Address
/// \param  nPort   [I ] Port Number
///
/// \return ALT_S_SUCCESS       success
/// \return ALT_E_UNKOWN_HOST   unknown host error
///
LIBALT_API alt_t altInetAddress::Init(const altChar * szIP, const altInt nPort)
{
  altStr  sBuf;

#ifdef ALT_WIN
  // Windows Sockets DLL Start up
  alt_t status = altNetUtil::WSAStartup();
  ALT_ERR_RET (status);
#endif

  memset (& m_oAddr, 0x00, sizeof (m_oAddr));
  m_oAddr.sin_family = AF_INET;
  m_oAddr.sin_port = htons (nPort);
  m_oAddr.sin_addr.s_addr = inet_addr (szIP);

  // host name
  if (m_oAddr.sin_addr.s_addr == INADDR_NONE) {
    LPHOSTENT lpHostEntry = gethostbyname (szIP); // pointer of hostent
    if (lpHostEntry == NULL) {
      // Unknown Host
      ALT_RET_P (ALT_E_UNKNOWN_HOST, sBuf.Format ("IP=%s PORT=%d", szIP, nPort));
    }
#ifdef ALT_WIN
    m_oAddr.sin_addr = *((LPIN_ADDR)lpHostEntry->h_addr_list[0]);
#endif
#ifdef ALT_LINUX
    m_oAddr.sin_addr.s_addr = *((LPIN_ADDR)lpHostEntry->h_addr_list[0]);
#endif
  }
  m_nAddrLen = sizeof (m_oAddr);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Pointer of Internet Socket Address
///
/// \return Pointer of Internet Socket Address
///
LIBALT_API const SOCKADDR_IN * altInetAddress::GetAddrInPtr() const
{
  return (& m_oAddr);
}

///
/// \brief  Set Internet Socket Address
///
/// \param  oAddr [I ] Internet Socket Address
///
LIBALT_API void altInetAddress::SetAddr(const SOCKADDR_IN & oAddr)
{
  m_oAddr = oAddr;
}

///
/// \brief Get IP Address
///
/// \return IP Address
///
LIBALT_API const altStr altInetAddress::GetIP() const
{
  altStr sIP = (inet_ntoa (m_oAddr.sin_addr));
	return sIP;
}

///
/// \brief Get Port NO
///
/// \return Port NO
///
LIBALT_API altInt altInetAddress::GetPort() const
{
	return (ntohs (m_oAddr.sin_port));
}

