/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMemLogger.cpp
 * \brief   Memory logger class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altMemLogger.h"
#include "altBase/altMemManager.h"

#include <time.h>

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altMemLogger::altMemLogger()
{
}

///
/// \brief  Destructor
///
LIBALT_API altMemLogger::~altMemLogger()
{
  Stop();
}

///
/// \brief  Open log file
///
/// \param  sFileName [I ] file name
/// \param  sMode     [I ] file open mode
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altMemLogger::Open(const altStr & sFileName, const altStr & sMode)
{
  if (altBaseLog::Open (sFileName, sMode) == false) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("[%s]", sFileName.GetCStr()));
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Write to log file
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altMemLogger::Write(const altChar * szFileName, const altInt nLine)
{
  altStr  sBuf;
  altStr  sFileLine;

  altMemInfoList  oMemInfoList = aiMemManager.GetMemInfoList();

  for (altMemInfoList::iterator i = oMemInfoList.begin(); i != oMemInfoList.end(); i++) {
#ifdef USE_MEM_MANAGER_FULL
    sFileLine.Format ("%s:%u", i->m_szFileName.c_str(), i->m_nLine);
#ifdef ALT_WIN
    struct tm oTime;
    localtime_s (& oTime, & i->m_oTime.time);
    altBaseLog::Write (szFileName, nLine, ALT_D_MEMORY, sBuf.Format ("[%x]%-40s\t(%04d/%02d/%02d %02d:%02d:%02d) size=%u", i->m_pAddr, sFileLine.GetCStr(), oTime.tm_year + 1900, oTime.tm_mon, oTime.tm_mday, oTime.tm_hour, oTime.tm_min, oTime.tm_sec, i->m_nSize));
#endif
#ifdef ALT_LINUX
    struct tm * pTime = localtime(& i->m_oTime.time);
    altBaseLog::Write (szFileName, nLine, ALT_D_MEMORY, sBuf.Format ("[%x]%-40s\t(%04d/%02d/%02d %02d:%02d:%02d) size=%u", i->m_pAddr, sFileLine.GetCStr(), pTime->tm_year + 1900, pTime->tm_mon, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec, i->m_nSize));
#endif
#else
    altBaseLog::Write (szFileName, nLine, ALT_D_MEMORY, sBuf.Format ("[%x]size=%u", i->m_pAddr, i->m_nSize));
#endif
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Close log file
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altMemLogger::Close()
{
  altBaseLog::Close();
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Start write memory log
///
/// \param  sFileName [I ] File name
/// \param  nInterval [I ] Write interval (msec)
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altMemLogger::Start(const altStr & sFileName, DWORD nInterval)
{
  altBaseLog::SetOutLevel (ALT_OLE_DEBUG);
  m_sFileName = sFileName;
  m_oLoopThread.SetInterval (nInterval);
  m_oLoopThread.Start (altMemLogger::WriteThread, this);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Stop write memory log
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altMemLogger::Stop()
{
  m_oLoopThread.Stop();
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get instance
///
/// \return instance
///
LIBALT_API altMemLogger & altMemLogger::GetInstance()
{
  return (altSingleton<altMemLogger>::GetInstance());
}

///
/// \brief  Memory log write thread
///
/// \param  pParam  [I ] this object
///
LIBALT_API alt_t altMemLogger::WriteThread(void * pParam)
{
  altMemLogger *  pMemLogger = (altMemLogger *)pParam;
  alt_t           status;

  status = pMemLogger->Open (pMemLogger->m_sFileName);
  ALT_ERR_RET (status);

  status = pMemLogger->Write (__FILE__, __LINE__);
  ALT_RET (status);

  status = pMemLogger->Close();
  ALT_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}
