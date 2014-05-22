/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altRuntime.cpp
 * \brief   Runtime class implementation
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altRuntime.h"

#include <vector>

#ifdef ALT_LINUX
  #include <execinfo.h>
  #include <stdlib.h>
#endif

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altRuntime::altRuntime()
{
}

///
/// \brief  Destructor
///
LIBALT_API altRuntime::~altRuntime()
{
}

///
/// \brief  Get stack trace
///
/// \return  Stack trace
///
LIBALT_API altStr altRuntime::GetStackTrace()
{
#ifdef ALT_WIN
  
  HANDLE  hProcess = ::GetCurrentProcess();
  HANDLE  hThread = ::GetCurrentThread();
#if 0
  DWORD dwOpts = ::SymGetOptions();
  ::SymSetOptions (dwOpts | SYMOPT_LOAD_LINES);
#endif
  if (! ::SymInitialize (hProcess, NULL, TRUE)) {
    return ("");
  }

  CONTEXT ctx;
  ctx.ContextFlags = CONTEXT_FULL;
  ctx.ContextFlags = CONTEXT_ALL;
  std::vector<DWORD> vAddrs;

  if (::GetThreadContext (hThread, & ctx)) {
    STACKFRAME  frame;
    DWORD       dwMachine;
    memset (& frame, 0x00, sizeof (frame));
    frame.AddrPC.Mode = AddrModeFlat;

    dwMachine = IMAGE_FILE_MACHINE_I386;
    frame.AddrPC.Offset = ctx.Eip;
    frame.AddrStack.Offset = ctx.Esp;
    frame.AddrFrame.Offset = ctx.Ebp;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrStack.Mode = AddrModeFlat;
    frame.AddrFrame.Mode = AddrModeFlat;

#if 0
    BOOL bRet = SymLoadModule (hProcess, NULL, (PSTR)sImageName.GetCStr(), NULL, 0, 0);
#endif
    for (DWORD dw = 0; dw < 512; dw++) {
      if (! ::StackWalk (dwMachine, hProcess, hThread, & frame, & ctx, NULL, SymFunctionTableAccess, SymGetModuleBase, NULL)) {
        break;
      }
      if (frame.AddrPC.Offset != 0) {
        vAddrs.push_back (frame.AddrPC.Offset);
      }
    }
  }

  altStr  sStackTrace;
  altStr  sSym;
  for (altUInt i = 0; i < vAddrs.size(); i++) {
    ConvertAddress (hProcess, vAddrs[i], sSym);
    sStackTrace += sSym;
  }
  SymCleanup (hProcess);

  return (sStackTrace);
#endif

#ifdef ALT_LINUX
  void *      ar[100];
  altInt      nSize = 0;
  altChar **  ppStrings;
  altStr      sStackTrace;

  nSize = backtrace (ar,100);
  ppStrings = backtrace_symbols (ar, nSize);
  for (altInt i = 1; i < nSize; i++) {
    sStackTrace += "\t";
    sStackTrace += ppStrings[i];
    sStackTrace += "\n";
  }
  free (ppStrings);
  return (sStackTrace);
#endif
}

#ifdef ALT_WIN
///
/// \brief  Convert address
///
/// \param  hProcess  [I ] Proccess handle
/// \param  dwAddr    [I ] Address
/// \param  sOutBuf   [ O] Out buffer
///
/// \return System size
///
LIBALT_API void altRuntime::ConvertAddress(HANDLE hProcess, DWORD dwAddr, altStr & sOutBuf)
{
  altChar           szTmp[MAX_PATH + sizeof (IMAGEHLP_SYMBOL)];
  PIMAGEHLP_SYMBOL  pIHS = (PIMAGEHLP_SYMBOL)& szTmp;
  IMAGEHLP_MODULE   stIHM;
  altStr            sBuf;

  memset (pIHS, 0x00, sizeof (szTmp));
  pIHS->SizeOfStruct = sizeof (* pIHS);
  pIHS->Address = dwAddr;
  pIHS->MaxNameLength = MAX_PATH;

  memset (& stIHM, 0x00, sizeof (stIHM));
  stIHM.SizeOfStruct = sizeof (IMAGEHLP_MODULE);
  sOutBuf += sBuf.Format ("0x%08X ", dwAddr);

  if (::SymGetModuleInfo (hProcess, dwAddr, & stIHM)) {
    altChar * szName = strrchr (stIHM.ImageName, '\\');
    if (szName != NULL) {
      szName++;
    }
    else {
      szName = stIHM.ImageName;
    }
    sOutBuf += sBuf.Format ("%s: ", szName);
  }
  else {
    sOutBuf += sBuf.Format ("<Unknown Module>: ");
  }

  DWORD dwDisp;

  if (::SymGetSymFromAddr (hProcess, dwAddr, & dwDisp, pIHS)) {
    if (dwDisp == 0) {
      sOutBuf += sBuf.Format ("%s", pIHS->Name);
    }
    else {
      sOutBuf += sBuf.Format ("%s + %d bytes", pIHS->Name, dwDisp);
    }
    IMAGEHLP_LINE stIHL;
    memset (& stIHL, 0x00, sizeof (stIHL));
    stIHL.SizeOfStruct = sizeof (stIHL);

    if (::SymGetLineFromAddr (hProcess, dwAddr, & dwDisp, & stIHL)) {
      sOutBuf += sBuf.Format ("\n\t\t%s, Line %d", stIHL.FileName, stIHL.LineNumber);
      if (dwDisp == 0) {
        sOutBuf += sBuf.Format (" + %d bytes", dwDisp);
      }
    }
  }
  else {
    sOutBuf += sBuf.Format ("<Unknown Symbol>");
  }
  sOutBuf += sBuf.Format ("\n");
}
#endif
