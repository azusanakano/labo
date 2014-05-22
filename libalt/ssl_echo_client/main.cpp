/*--------------------------------------------------------------------------*

   Alternative Library Test

  $Id: main.cpp 164 2007-05-24 07:18:46Z nekosys $

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
#include <time.h>
#include <vector>
/*----------------------------------------------------------------*
 * Structure Definition
 *----------------------------------------------------------------*/
typedef std::vector<altSSLClient *>  altSSLClientContainer;

/*----------------------------------------------------------------*
 * Static variables
 *----------------------------------------------------------------*/
static void RecvEcho(altSSLClient & oClient, const altChar * pData, const altUInt nSize);
static void Disconnected(altSSLClient & oClient);

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
  alt_t                     status;
  altProperty               oSetting;
  altSSLClient *         pClient;
  altSSLClientContainer  oClients;

  status = oSetting.Load ("ssl_echo_client.conf");
  ALT_LOG (status);

  aiLog.SetOutLevel (oSetting.GetStr ("LOG_LEVEL", "default"));
  for (altUInt i = 0; i < oSetting.GetUInt("CLIENT_COUNT", 10); i++) {
    try {
      pClient = new altSSLClient (RecvEcho, Disconnected, ALT_SSL_V3);
      pClient->Connect (oSetting.GetStr ("IP", "211.7.47.25"), oSetting.GetUInt ("PORT", 5432));
      oClients.push_back (pClient);
    }
    catch (alt_t error) {
      ALT_LOG (error);
    }
  }

  while (true) {
    for (altUInt i = 0; i < oClients.size(); i++) {
      clock_t nCurrent = clock();
      altChar * pData = NULL;
      ALT_DUPALLOC (pData, & nCurrent, sizeof (nCurrent));
      oClients[i]->Send (pData, sizeof (nCurrent));
    }
    altSleep (oSetting.GetUInt ("SEND_INTERVAL", 1000));
  }

  return (0);
}

static void RecvEcho(altSSLClient & oClient, const altChar * pData, const altUInt nSize)
{
  clock_t nCurrent = clock();
  clock_t nSendTime;
  memcpy (& nSendTime, pData, sizeof (nSendTime));
  altDouble fDuration = (altDouble)(nCurrent - nSendTime) / CLOCKS_PER_SEC;
  printf ("%4.3f\n", fDuration);
}

static void Disconnected(altSSLClient & oClient)
{
  printf ("Disconnect from server %s:%d\n", oClient.GetIP().GetCStr(), oClient.GetPort());
}
