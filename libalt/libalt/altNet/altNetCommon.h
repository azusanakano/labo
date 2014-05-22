#ifndef ALTNETCOMMON_H
#define ALTNETCOMMON_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNetCommon.h
 * \brief   Network common functions class
 * \date    2007
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_LINUX
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
#endif

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
#define ALT_NO_SSL  0x00    ///< No SSL
#define ALT_SSL_V23 0x01    ///< SSL ver2,3
#define ALT_SSL_V2  0x02    ///< SSL ver2
#define ALT_SSL_V3  0x03    ///< SSL ver3
#define ALT_TSL_V1  0x04    ///< TSL ver1

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
#ifdef ALT_LINUX
  typedef int                 SOCKET;
  typedef struct sockaddr     SOCKADDR;
  typedef struct sockaddr_in  SOCKADDR_IN;
  typedef struct hostent *    LPHOSTENT;
  typedef unsigned int *      LPIN_ADDR;
#endif


#endif  //ALTNETCOMMON_H

