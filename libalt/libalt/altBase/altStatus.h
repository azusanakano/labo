#ifndef ALTSTATUS_H
#define ALTSTATUS_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0


  Description:
  This class is logging and exception object.

 *---------------------------------------------------------------------------*/
/**
 * \file    altStatus.h
 * \brief   Status class
 * \date    2007
 * \author  Azusa Nakano
 */

/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altBaseLog.h>

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
ALT_T_EXT (ALT_A_ASSERT);
ALT_T_EXT (ALT_E_ERROR);
ALT_T_EXT (ALT_E_NOMEM);
ALT_T_EXT (ALT_E_INVAL);
ALT_T_EXT (ALT_E_MAXLIMIT);
ALT_T_EXT (ALT_E_WSASTARTUP);
ALT_T_EXT (ALT_E_WSAVERSION);
ALT_T_EXT (ALT_E_SOCKET);
ALT_T_EXT (ALT_E_BIND);
ALT_T_EXT (ALT_E_LISTEN);
ALT_T_EXT (ALT_E_SEND);
ALT_T_EXT (ALT_E_RECV);
ALT_T_EXT (ALT_E_UNKNOWN_HOST);
ALT_T_EXT (ALT_E_CONNECT);
ALT_T_EXT (ALT_E_OUT_OF_INDEX);
ALT_T_EXT (ALT_E_SQL);
ALT_T_EXT (ALT_E_WRITE);
ALT_T_EXT (ALT_W_WARNING);
ALT_T_EXT (ALT_N_NOTICE);
ALT_T_EXT (ALT_I_INFO);
ALT_T_EXT (ALT_I_MAX);
ALT_T_EXT (ALT_D_DEBUG);
ALT_T_EXT (ALT_D_RECV);
ALT_T_EXT (ALT_D_SEND);
ALT_T_EXT (ALT_D_MEMORY);
ALT_T_EXT (ALT_S_SUCCESS);
ALT_T_EXT (ALT_S_TIMEOUT);
ALT_T_EXT (ALT_S_NOT_FOUND);
ALT_T_EXT (ALT_S_NET_EOF);
ALT_T_EXT (ALT_S_EOF);
ALT_T_EXT (ALT_S_NO_MORE_RESULT);
ALT_T_EXT (ALT_S_NO_DATA);
ALT_T_EXT (ALT_S_DATA_TRUNCATED);
ALT_T_EXT (ALT_S_NOCOMPRESS);
ALT_T_EXT (ALT_S_OUTBUFFER_FULL);

#endif  // ALTSTATUS_H

