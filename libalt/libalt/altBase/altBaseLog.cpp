/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altBaseLog.cpp
 * \brief   Base Log
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altStatus.h"
#include "altBaseLog.h"
#include "altUtil.h"
#include "altBaseMem.h"

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * static variables
 *----------------------------------------------------------------*/
altLogOLEMap altBaseLog::aOLEMap[] = {
  { ALT_OLE_NONE,     ALT_OLE_NONE_S    },
  { ALT_OLE_ERROR,    ALT_OLE_ERROR_S   },
  { ALT_OLE_WARNING,  ALT_OLE_WARNING_S },
  { ALT_OLE_NOTICE,   ALT_OLE_NOTICE_S  },
  { ALT_OLE_DEFAULT,  ALT_OLE_DEFAULT_S },
  { ALT_OLE_DEBUG,    ALT_OLE_DEBUG_S   },
  { ALT_OLE_ALL,      ALT_OLE_ALL_S     },
};

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altBaseLog::altBaseLog() :
m_pOut (NULL),
m_nOutPutLogLevel (ALT_OLE_DEFAULT),
m_bFileMode (false),
m_nDate (0)
{
}

///
/// \brief  Destructor
///
LIBALT_API altBaseLog::~altBaseLog()
{
  if (m_pOut != NULL) {
      fclose (m_pOut);
      m_pOut = NULL;
  }
}

///
/// \brief  open log file
///
/// \param  sFileName [I ] file name
/// \param  sMode     [I ] file open mode
///
/// \return true  success
/// \return false error
///
LIBALT_API const altBool altBaseLog::Open(const altStr & sFileName, const altStr & sMode)
{
  m_sFileName = sFileName;
  m_bFileMode = true;
  m_sMode = sMode;
  return OpenFile (m_sMode);
}

///
/// \brief  open log file
///
/// \param  pOut [I ] output stream
///
/// \return true  success
///
LIBALT_API const altBool altBaseLog::Open(FILE * pOut)
{
  m_bFileMode = false;
  m_pOut = pOut;
  return (true);
}

///
/// \brief  set log level
///
/// \param  nOutLevel  [I ] out level
///
LIBALT_API void altBaseLog::SetOutLevel(const altByte nOutLevel)
{
  m_nOutPutLogLevel = nOutLevel;
}

///
/// \brief  set log level by string
///
/// \param  sOutLevel  [I ] out level string
///
LIBALT_API void altBaseLog::SetOutLevel(const altStr & sOutLevel)
{
  for (altUInt i = 0; i < ALT_ARRAY_SIZE (aOLEMap); i++) {
    if (aOLEMap[i].sOLE == sOutLevel.GetCStr()) {
      SetOutLevel (aOLEMap[i].nOLE);
      return;
    }
  }
}

///
/// \brief  set log level
///
/// \param  sModuleName [I ] module name
/// \param  nOutLevel   [I ] out level
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altBaseLog::SetOutLevel(const altStr & sModuleName, const altByte nOutLevel)
{
  altByte * pOutLevel = NULL;
  altChar * p = NULL;
  altInt nRet = ALT_BASE_MALLOC (p, sizeof (* pOutLevel));
  if (nRet != ALT_SUCCESS) {
    altStr sBuf;
    ALT_BASE_RET_P (* this, ALT_E_ERROR, sBuf.Format ("%d", nRet));
  }
  pOutLevel = (altByte *)(p);
  (* pOutLevel) = nOutLevel;
  m_oSetting[sModuleName.GetCStr()] = pOutLevel;
  ALT_BASE_RET (* this, ALT_S_SUCCESS);
}

///
/// \brief  set log level
///
/// \param  sModuleName [I ] module name
/// \param  sOutLevel   [I ] out level
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altBaseLog::SetOutLevel(const altStr & sModuleName, const altStr & sOutLevel)
{
  for (altUInt i = 0; i < ALT_ARRAY_SIZE (aOLEMap); i++) {
    if (aOLEMap[i].sOLE == sOutLevel.GetCStr()) {
      ALT_BASE_RET (* this, SetOutLevel (sModuleName, aOLEMap[i].nOLE));
    }
  }
  altStr sBuf;
  ALT_BASE_RET_P (* this, ALT_E_ERROR, sBuf.Format("%s not found", sModuleName.GetCStr()));
}

///
/// \brief  add output stream
///
/// \param  pOut  [I ] output stream
///
/// \return ALT_S_SUCCESS success
///
LIBALT_API alt_t altBaseLog::AddOutStream(FILE * pOut)
{
  m_oAddtionalOutStreams.push_back (pOut);
  ALT_BASE_RET (* this, ALT_S_SUCCESS);
}

///
/// \brief  output log
///
/// \param  szFileName  [I ] source file name
/// \param  nLine       [I ] source file line number
/// \param  pStatus     [I ] status
/// \param  szMessage   [I ] log message
///
LIBALT_API void altBaseLog::Write(const altChar * szFileName, const altInt nLine, alt_t pStatus, const altChar * szMessage)
{
  FILE * pOut = stdout;
  if (! IsOutLog (pStatus)) {
    return;
  }
  altDateTime oNow;

  if (m_bFileMode) {
    BeginLock();
    if (m_nDate != oNow.m_nDay) {
      OpenFile (m_sMode);
    }
    EndLock();
  }

  if (m_pOut != NULL) {
    pOut = m_pOut;
  }

  BeginLock();
  Write (pOut, oNow, szFileName, nLine, pStatus, szMessage);
  for (altUInt i = 0; i < m_oAddtionalOutStreams.size(); i++) {
    Write (m_oAddtionalOutStreams[i], oNow, szFileName, nLine, pStatus, szMessage);
  }
  EndLock();
}

#ifdef ALT_WIN
///
/// \brief  output log
///
/// \param  szFileName  [I ] source file name
/// \param  nLine       [I ] source file line number
/// \param  pStatus     [I ] status
/// \param  szMessage   [I ] log message
///
LIBALT_API void altBaseLog::Write(const altChar * szFileName, const altInt nLine, alt_t pStatus, const altWChar * szMessage)
{
  FILE * pOut = stdout;
  if (! IsOutLog (pStatus)) {
    return;
  }
  altDateTime oNow;

  if (m_bFileMode) {
    BeginLock();
    if (m_nDate != oNow.m_nDay) {
      OpenFile (m_sMode);
    }
    EndLock();
  }

  if (m_pOut != NULL) {
    pOut = m_pOut;
  }

  BeginLock();
  Write (pOut, oNow, szFileName, nLine, pStatus, szMessage);
  for (altUInt i = 0; i < m_oAddtionalOutStreams.size(); i++) {
    Write (m_oAddtionalOutStreams[i], oNow, szFileName, nLine, pStatus, szMessage);
  }
  EndLock();
}
#endif

///
/// \brief  Close
///
LIBALT_API void altBaseLog::Close()
{
  if (m_pOut != NULL) {
    fclose (m_pOut);
    m_pOut = NULL;
  }
  for (altUInt i = 0; i < m_oAddtionalOutStreams.size(); i++) {
    fclose (m_oAddtionalOutStreams[i]);
    m_oAddtionalOutStreams[i] = NULL;
  }
  m_oAddtionalOutStreams.clear();
}

///
/// \brief  output log
///
/// \param  pStatus     [I ] status
///
/// \return true  output
/// \return false not output
///
LIBALT_API const altBool altBaseLog::IsOutLog(alt_t pStatus)
{
  altByte * pOutLevel = m_oSetting[pStatus->sModule];
  if (pOutLevel != NULL) {
    if (! (pStatus->nLevel & (* pOutLevel))) {
      return (false);
    }
  }
  else if (! (pStatus->nLevel & m_nOutPutLogLevel)) {
    return (false);
  }
  return (true);
}

///
/// \brief  open file
///
/// \param  sMode     [I ] file open mode
///
/// \return true  success
/// \return false error
///
LIBALT_API const altBool altBaseLog::OpenFile(const altStr & sMode)
{
  altStr  sDirName;
  altStr  sFileName;
  altInt  nIndex = m_sFileName.FindLastOfChar ("\\/");

  if (nIndex >= 0) {
    sFileName = m_sFileName.SubStr (nIndex + 1);
    sDirName = m_sFileName.SubStr (0, nIndex - 1);
  }
  else {
    sFileName = m_sFileName;
  }

  altStr  sFileNameNoEx;
  altStr  sEx;
  nIndex = sFileName.FindLastOfChar (".");
  if (nIndex >= 0) {
    sFileNameNoEx = sFileName.SubStr (0, nIndex - 1);
    sEx = sFileName.SubStr (nIndex + 1);
  }
  else {
    sFileNameNoEx = sFileName;
  }

  altDateTime   oNow;
  altStr        sFilePath;
  if (sDirName.GetLen() > 0) {
    // create directory
    altMkDirR (sDirName.GetCStr());
    sFilePath.Format ("%s/%s_%s.%s", sDirName.GetCStr(), sFileNameNoEx.GetCStr(), oNow.Format ("YYYY_MM_DD").GetCStr(), sEx.GetCStr());
  }
  else {
    sFilePath.Format ("%s_%s", sFileNameNoEx.GetCStr(), oNow.Format ("YYYY_MM_DD").GetCStr());
  }

  // open file
  if (m_pOut != NULL) {
    fclose (m_pOut);
    m_pOut = NULL;
  }
  altFOpen (sFilePath.GetCStr(), sMode.GetCStr(), m_pOut);
  m_nDate = oNow.m_nDay;
  if (m_pOut != NULL) {
    setvbuf (m_pOut, NULL, _IONBF, 0);
  }

  return (true);
}

///
/// \brief  output log
///
/// \param  pOut        [I ] output stream
/// \param  oNow        [I ] current date time
/// \param  szFileName  [I ] source file name
/// \param  nLine       [I ] source file line number
/// \param  pStatus     [I ] status
/// \param  szMessage   [I ] log message
///
LIBALT_API void altBaseLog::Write(FILE * pOut, const altDateTime & oNow, const altChar * szFileName, const altInt nLine, alt_t pStatus, const altChar * szMessage)
{
  fprintf (pOut, "%s\t%s(%d)\t%s\t%s\t%s\n", oNow.Format ("YYYY/MM/DD HH:MI:SS.MS").GetCStr(), szFileName, nLine, pStatus->sName, pStatus->sMessage, szMessage);
}

#ifdef ALT_WIN
///
/// \brief  output log
///
/// \param  pOut        [I ] output stream
/// \param  oNow        [I ] current date time
/// \param  szFileName  [I ] source file name
/// \param  nLine       [I ] source file line number
/// \param  pStatus     [I ] status
/// \param  szMessage   [I ] log message
///
LIBALT_API void altBaseLog::Write(FILE * pOut, const altDateTime & oNow, const altChar * szFileName, const altInt nLine, alt_t pStatus, const altWChar * szMessage)
{
  _wsetlocale(LC_ALL, L"japanese");
  fwprintf (pOut, _T("%s\t%s(%d)\t%s\t%s\t%s\n"), oNow.Format ("YYYY/MM/DD HH:MI:SS.MS").GetCStr(), szFileName, nLine, pStatus->sName, pStatus->sMessage, szMessage);
}
#endif

