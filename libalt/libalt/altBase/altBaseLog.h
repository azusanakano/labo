#ifndef ALTBASELOG_H
#define ALTBASELOG_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altBaseLog.h
 * \brief   Base Log Class
 * \date    2013
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altDateTime.h>
#include <altBase/altStr.h>
#include <altBase/altSyncThread.h>
#include <altBase/altBase.h>
#include <altBase/altUncopyable.h>

#include <map>
#include <vector>
#include <string>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
///
/// \brief status
///
typedef struct {
	const altChar * sName;      ///< status name
	const altChar * sModule;    ///< module name
	const altByte   nLevel;     ///< level
	const altChar * sMessage;	  ///< message
} altStatus;

///
/// \brief  pointer of status
///
typedef const altStatus * alt_t;

///
/// \brief  module output level setting
///
typedef std::map<const std::string, altByte *> altBaseLogSetting;

///
/// \brief  additional output stream
///
typedef std::vector<FILE *> altOutStreamContatiner;

///
/// \brief  output level map
///
typedef struct {
  const altByte     nOLE;
  const std::string sOLE;
} altLogOLEMap;

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
///
/// \brief status define
///
/// \param  name    [I ] status name
/// \param  module  [I ] module name
/// \param  level   [I ] log level
/// \param  message [I ] log message
///
#define ALT_T_DEF(name, module, level, message) \
  const altStatus g_##name = {#name, #module, level, message};\
  alt_t name = (& g_##name);

///
/// \brief  status extern declare
///
#define ALT_T_EXT(name) \
  LIBALT_API extern alt_t name

//-------------------------------------------------------
// log level
//-------------------------------------------------------
/// assert
#define ALT_LE_ASSERT  0x01

/// error
#define ALT_LE_ERROR   0x02

/// warning
#define ALT_LE_WARNING 0x04

/// notice
#define	ALT_LE_NOTICE  0x08

/// info
#define	ALT_LE_INFO    0x10

/// debug
#define ALT_LE_DEBUG   0x20

/// success
#define ALT_LE_SUCCESS 0x40

/// check error
#define ALT_IS_ERR(code) \
  ((code)->nLevel == ALT_LE_ERROR || (code)->nLevel == ALT_LE_ASSERT)

//-------------------------------------------------------
// log level setting macro
//-------------------------------------------------------
#define ALT_OLE_NONE     (0x0000)
#define ALT_OLE_ERROR    (ALT_LE_ASSERT | ALT_LE_ERROR)
#define ALT_OLE_WARNING  (ALT_LE_ASSERT | ALT_LE_ERROR | ALT_LE_WARNING)
#define ALT_OLE_NOTICE   (ALT_LE_ASSERT | ALT_LE_ERROR | ALT_LE_WARNING | ALT_LE_NOTICE)
#define ALT_OLE_DEFAULT  (ALT_LE_ASSERT | ALT_LE_ERROR | ALT_LE_WARNING | ALT_LE_NOTICE | ALT_LE_INFO)
#define ALT_OLE_DEBUG    (ALT_LE_ASSERT | ALT_LE_ERROR | ALT_LE_WARNING | ALT_LE_NOTICE | ALT_LE_INFO | ALT_LE_DEBUG)
#define ALT_OLE_ALL      (ALT_LE_ASSERT | ALT_LE_ERROR | ALT_LE_WARNING | ALT_LE_NOTICE | ALT_LE_INFO | ALT_LE_DEBUG | ALT_LE_SUCCESS)

#define ALT_OLE_NONE_S    "none"
#define ALT_OLE_ERROR_S   "error"
#define ALT_OLE_WARNING_S "warning"
#define ALT_OLE_NOTICE_S  "notice"
#define ALT_OLE_DEFAULT_S "default"
#define ALT_OLE_DEBUG_S   "debug"
#define ALT_OLE_ALL_S     "all"

//-------------------------------------------------------
// output log macro
//-------------------------------------------------------
///
/// \brief  Output Log Message
///
/// \param  o       [I ] altBaseLog Instance
/// \param  status  [I ] status
///
#define ALT_BASE_LOG(o, status) \
  (o).Write (__FILE__, __LINE__, (status))

///
/// \brief  Output Log Message with message
///
/// \param  o       [I ] altBaseLog Instance
/// \param  status  [I ] status
/// \param  message [I ] message
///
#define ALT_BASE_LOG_P(o, status, message) \
  (o).Write (__FILE__, __LINE__, (status), (message))

///
/// \brief  Output Log Message and return status
///
/// \param  o       [I ] altBaseLog Instance
/// \param  status  [I ] status
///
#define ALT_BASE_RET(o, status) \
  ALT_BASE_LOG(o, status); \
  return (status)

///
/// \brief  Output Log Message and return status
///
/// \param  o       [I ] altBaseLog Instance
/// \param  status  [I ] status
/// \param  message [I ] message
///
#define ALT_BASE_RET_P(o, status, message) \
  ALT_BASE_LOG_P(o, status, message); \
  return (status)

///
/// \brief  If error status, output Log Message and return status
///
/// \param  o       [I ] altBaseLog Instance
/// \param  status  [I ] status
///
#define ALT_BASE_ERR_RET(o, status) \
  if (ALT_IS_ERR (status)) { \
    ALT_BASE_LOG(o, status); \
    return (status); \
  }

///
/// \brief  If error status, output Log Message and return status
///
/// \param  o       [I ] altBaseLog Instance
/// \param  status  [I ] status
/// \param  message [I ] message
///
#define ALT_BASE_ERR_RET_P(o, status, message) \
  if (ALT_IS_ERR (status)) { \
    ALT_BASE_LOG_P(o, status, message); \
    return (status); \
  }

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Base Log
///
class altBaseLog : public altBase, protected altSyncThread, private altUncopyable
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altBaseLog();
  
  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altBaseLog();

  ///
  /// \brief  open log file
  ///
  /// \param  sFileName [I ] file name
  /// \param  sMode     [I ] file open mode
  ///
  /// \return true  success
  /// \return false error
  ///
  LIBALT_API const altBool Open(const altStr & sFileName, const altStr & sMode = "a+c");

  ///
  /// \brief  open log file
  ///
  /// \param  pOut [I ] output stream
  ///
  /// \return true  success
  ///
  LIBALT_API const altBool Open(FILE * pOut);

  ///
  /// \brief  set log level
  ///
  /// \param  nOutLevel  [I ] out level
  ///
  LIBALT_API void SetOutLevel(const altByte nOutLevel);

  ///
  /// \brief  set log level by string
  ///
  /// \param  sOutLevel  [I ] out level string
  ///
  LIBALT_API void SetOutLevel(const altStr & sOutLevel);

  ///
  /// \brief  set log level
  ///
  /// \param  sModuleName [I ] module name
  /// \param  nOutLevel   [I ] out level
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t SetOutLevel(const altStr & sModuleName, const altByte nOutLevel);

  ///
  /// \brief  set log level
  ///
  /// \param  sModuleName [I ] module name
  /// \param  sOutLevel   [I ] out level
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t SetOutLevel(const altStr & sModuleName, const altStr & sOutLevel);

  ///
  /// \brief  add output stream
  ///
  /// \param  pOut  [I ] output stream
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t AddOutStream(FILE * pOut);

  ///
  /// \brief  output log
  ///
  /// \param  szFileName  [I ] source file name
  /// \param  nLine       [I ] source file line number
  /// \param  pStatus     [I ] status
  /// \param  szMessage   [I ] log message
  ///
  LIBALT_API void Write(const altChar * szFileName, const altInt nLine, alt_t pStatus, const altChar * szMessage = "");

#ifdef ALT_WIN
  ///
  /// \brief  output log
  ///
  /// \param  szFileName  [I ] source file name
  /// \param  nLine       [I ] source file line number
  /// \param  pStatus     [I ] status
  /// \param  szMessage   [I ] log message
  ///
  LIBALT_API void Write(const altChar * szFileName, const altInt nLine, alt_t pStatus, const altWChar * szMessage);
#endif

  ///
  /// \brief  Close
  ///
  LIBALT_API void Close();

protected:
  ///
  /// \brief  output log
  ///
  /// \param  pStatus     [I ] status
  ///
  /// \return true  output
  /// \return false not output
  ///
  LIBALT_API const altBool IsOutLog(alt_t pStatus);

  ///
  /// \brief  open file
  ///
  /// \param  sMode     [I ] file open mode
  ///
  /// \return true  success
  /// \return false error
  ///
  LIBALT_API const altBool OpenFile(const altStr & sMode);

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
  LIBALT_API void Write(FILE * pOut, const altDateTime & oNow, const altChar * szFileName, const altInt nLine, alt_t pStatus, const altChar * szMessage);

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
  LIBALT_API void Write(FILE * pOut, const altDateTime & oNow, const altChar * szFileName, const altInt nLine, alt_t pStatus, const altWChar * szMessage);
#endif

  FILE *                  m_pOut;                       ///< output stream
  altByte                 m_nOutPutLogLevel;            ///< log level
  altStr                  m_sFileName;                  ///< file name
  altBool                 m_bFileMode;                  ///< output to file or not
  altStr                  m_sMode;                      ///< file open mode
  altByte                 m_nDate;                      ///< day
  altBaseLogSetting       m_oSetting;                   ///< module output level
  altOutStreamContatiner  m_oAddtionalOutStreams;       ///< additional output stream
private:
  static altLogOLEMap     aOLEMap[];                    ///< output level map
};

#endif  // ALTBASELOG_H
