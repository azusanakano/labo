/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0


  Description:
  This class is logging and exception object.

 *---------------------------------------------------------------------------*/
/**
 * \file    altStatus.cpp
 * \brief   Status class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altStatus.h"

/*----------------------------------------------------------------*
 * Status Define
 *----------------------------------------------------------------*/
ALT_T_DEF (ALT_A_ASSERT,          ALT, ALT_LE_ASSERT,   "assertion failed.");
ALT_T_DEF (ALT_E_ERROR,           ALT, ALT_LE_ERROR,    "ERROR");
ALT_T_DEF (ALT_E_NOMEM,           ALT, ALT_LE_ERROR,    "out of memory");
ALT_T_DEF (ALT_E_INVAL,           ALT, ALT_LE_ERROR,    "invalid parameter");
ALT_T_DEF (ALT_E_MAXLIMIT,        ALT, ALT_LE_ERROR,    "memory over max limit");
ALT_T_DEF (ALT_E_WSASTARTUP,      ALT, ALT_LE_ERROR,    "WSAStartup error");
ALT_T_DEF (ALT_E_WSAVERSION,      ALT, ALT_LE_ERROR,    "WinSock API Version error");
ALT_T_DEF (ALT_E_SOCKET,          ALT, ALT_LE_ERROR,    "create socket failed.");
ALT_T_DEF (ALT_E_BIND,            ALT, ALT_LE_ERROR,    "bind failed.");
ALT_T_DEF (ALT_E_LISTEN,          ALT, ALT_LE_ERROR,    "listen failed.");
ALT_T_DEF (ALT_E_SEND,            ALT, ALT_LE_ERROR,    "send failed.");
ALT_T_DEF (ALT_E_RECV,            ALT, ALT_LE_ERROR,    "recv failed.");
ALT_T_DEF (ALT_E_UNKNOWN_HOST,    ALT, ALT_LE_ERROR,    "unknown host.");
ALT_T_DEF (ALT_E_CONNECT,         ALT, ALT_LE_ERROR,    "connect failed.");
ALT_T_DEF (ALT_E_OUT_OF_INDEX,    ALT, ALT_LE_ERROR,    "out of index.");
ALT_T_DEF (ALT_E_SQL,             ALT, ALT_LE_ERROR,    "SQL error.");
ALT_T_DEF (ALT_E_WRITE,           ALT, ALT_LE_ERROR,    "Write error.");
ALT_T_DEF (ALT_W_WARNING,         ALT, ALT_LE_WARNING,  "WARNING");
ALT_T_DEF (ALT_N_NOTICE,          ALT, ALT_LE_NOTICE,   "NOTICE");
ALT_T_DEF (ALT_I_INFO,            ALT, ALT_LE_INFO,     "INFO");
ALT_T_DEF (ALT_I_MAX,             ALT, ALT_LE_INFO,     "max file descriptor");
ALT_T_DEF (ALT_D_DEBUG,           ALT, ALT_LE_DEBUG,    "DEBUG");
ALT_T_DEF (ALT_D_RECV,            ALT, ALT_LE_DEBUG,    "RECV");
ALT_T_DEF (ALT_D_SEND,            ALT, ALT_LE_DEBUG,    "SEND");
ALT_T_DEF (ALT_D_MEMORY,          ALT, ALT_LE_DEBUG,    "MEMORY");
ALT_T_DEF (ALT_S_SUCCESS,         ALT, ALT_LE_SUCCESS,  "SUCCESS");
ALT_T_DEF (ALT_S_TIMEOUT,         ALT, ALT_LE_SUCCESS,  "timeout");
ALT_T_DEF (ALT_S_NOT_FOUND,       ALT, ALT_LE_SUCCESS,  "not found");
ALT_T_DEF (ALT_S_NET_EOF,         ALT, ALT_LE_SUCCESS,  "connection closed");
ALT_T_DEF (ALT_S_EOF,             ALT, ALT_LE_SUCCESS,  "end of file");
ALT_T_DEF (ALT_S_NO_MORE_RESULT,  ALT, ALT_LE_SUCCESS,  "no more result");
ALT_T_DEF (ALT_S_NO_DATA,         ALT, ALT_LE_SUCCESS,  "no data");
ALT_T_DEF (ALT_S_DATA_TRUNCATED,  ALT, ALT_LE_SUCCESS,  "data truncated");
ALT_T_DEF (ALT_S_NOCOMPRESS,      ALT, ALT_LE_SUCCESS,  "no compress");
ALT_T_DEF (ALT_S_OUTBUFFER_FULL,  ALT, ALT_LE_SUCCESS,  "out buffer full");
