/*--------------------------------------------------------------------------*

   Alternative Library Test

  $Id: main.cpp 56 2007-05-11 20:28:50Z nekosys $

  Copyright (C) 2007 NEKO SYSTEM
 
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or any later version.
 
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Library General Public License for more details.
 
  You should have received a copy of the GNU Library General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *---------------------------------------------------------------------------*/
/**
 * \file    main.cpp
 * \brief   Alternative Library Test
 * \date    2007
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <libalt.h>

/*----------------------------------------------------------------*
 * Structure Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Static variables
 *----------------------------------------------------------------*/
///
/// \brief  echo
///
/// \param  pNetConnection  [I ] connection
/// \param  pData           [I ] data
/// \param  nSize           [I ] data size
///
/// \return ALT_S_SUCCESS   success
///
static alt_t Echo(const altCNETConnectionPtr & pNetConnection, const altCharPtr & pData, const altUInt nSize);

///
/// \brief  Accept Call Back Function
///
/// \param  nPort           [I ] Port Number
/// \param  pNetConnection  [I ] Connection
/// 
static void AcceptCallBack(const altInt nPort, const altCNETConnectionPtr & pNetConnection);

///
/// \brief  Disconnect Call Back Function
///
/// \param  pNetConnection  [I ] Connection
///
static void DisconnectedCallBack(const altCNETConnectionPtr & pNetConnection);

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  main
///
/// \param  argc  [I ] arguments count
/// \param  argv  [I ] arguments
///
/// \return 0
///
int main(int argc, char * argv[])
{
  alt_t       status;
  altProperty oSetting;

  status = oSetting.Load ("ssl_echo_server.conf");
  ALT_LOG (status);

  aiLog.SetOutLevel (oSetting.GetStr ("LOG_LEVEL", "default"));
  status = aiSSLServer.OpenPort (oSetting.GetInt ("PORT", 5432), Echo, AcceptCallBack, DisconnectedCallBack, oSetting.GetUInt ("THREAD_COUNT", 2));
  if (ALT_IS_ERR (status)) {
    ALT_LOG (status);
    return (1);
  }
  aiMemLogger.Start ("../Log/MemoryLog.log", 10 * 1000);

  while (1) {
    try {
      altSleep (1000);
      printf ("---------------------------------------------\n");
      printf ("Connection         = %u\n", aiNETConnectionManager.Size());
      printf ("memory size        = %u\n", aiMemManager.GetTotalSize());
      printf ("memory real size   = %u\n", aiMemManager.GetTotalRealSize());
      printf ("memory block count = %u\n", aiMemManager.GetBlockCount());
      printf ("---------------------------------------------\n");
    }
    catch (...) {

    }
  }

  return (0);
}

///
/// \brief  echo
///
/// \param  pNETConnection  [I ] connection
/// \param  pData           [I ] data
/// \param  nSize           [I ] data size
///
/// \return ALT_S_SUCCESS   success
///
static alt_t Echo(const altCNETConnectionPtr & pNETConnection, const altCharPtr & pData, const altUInt nSize)
{
  alt_t status = pNETConnection->Send (pData, nSize);
  ALT_LOG (status);
  ALT_RET (ALT_S_SUCCESS);
}


///
/// \brief  Accept Call Back Function
///
/// \param  nPort           [I ] Port Number
/// \param  pNETConnection  [I ] Connection
/// 
static void AcceptCallBack(const altInt nPort, const altCNETConnectionPtr & pNETConnection)
{
  printf ("Accept [%d] %s:%d\n", nPort, pNETConnection->GetIP().GetCStr(), pNETConnection->GetPort());
}

///
/// \brief  Disconnect Call Back Function
///
/// \param  pNETConnection  [I ] Connection
///
static void DisconnectedCallBack(const altCNETConnectionPtr & pNETConnection)
{
  printf ("Disconnect %s:%d\n", pNETConnection->GetIP().GetCStr(), pNETConnection->GetPort());
}
