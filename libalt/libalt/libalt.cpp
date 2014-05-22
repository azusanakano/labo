/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    libalt.cpp
 * \brief   DLL entry point
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <libalt.h>

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
#ifdef ALT_WIN

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
  switch (ul_reason_for_call) {
    case  DLL_PROCESS_ATTACH:
      break;
    case  DLL_PROCESS_DETACH:
      altSetFreeHandler (NULL);
      break;
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      break;
  }
  return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

#endif  // ALT_WIN
