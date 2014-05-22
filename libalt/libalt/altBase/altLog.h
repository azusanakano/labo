#ifndef ALTLOG_H
#define ALTLOG_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altBaseLog.h
 * \brief   Base Log Class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altStatus.h>
#include <altBase/altSingleton.h>
#include <altBase/altSyncThread.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
///
/// \brief  Get Instance
///
/// \return altLog Instance
///
#define aiLog altLog::GetInstance()

//-------------------------------------------------------
// output log macro
//-------------------------------------------------------
///
/// \brief  Output Log Message
///
/// \param  status  [I ] status
///
#define ALT_LOG(status) \
  ALT_BASE_LOG (aiLog, (status))

///
/// \brief  Output Log Message with message
///
/// \param  status  [I ] status
/// \param  message [I ] message
///
#define ALT_LOG_P(status, message) \
  ALT_BASE_LOG_P (aiLog, (status), (message))

///
/// \brief  Output Log Message and return status
///
/// \param  status  [I ] status
///
#define ALT_RET(status) \
  ALT_LOG(status); \
  return (status)

///
/// \brief  Output Log Message and return status
///
/// \param  status  [I ] status
/// \param  message [I ] message
///
#define ALT_RET_P(status, message) \
  ALT_LOG_P(status, message); \
  return (status)

///
/// \brief  If error status, output Log Message and return status
///
/// \param  status  [I ] status
///
#define ALT_ERR_RET(status) \
  if (ALT_IS_ERR (status)) { \
    ALT_LOG(status); \
    return (status); \
  }

///
/// \brief  If error status, output Log Message and return status
///
/// \param  status  [I ] status
/// \param  message [I ] message
///
#define ALT_ERR_RET_P(status, message) \
  if (ALT_IS_ERR (status)) { \
    ALT_LOG_P(status, message); \
    return (status); \
  }

//-------------------------------------------------------
// assert macro
//-------------------------------------------------------
///
/// \brief  If condition is false, output Log Message and return ALT_A_ASSERT
///
/// \param  _cond_  [I ] condition
///
#define ALT_ASSERT(_cond_) \
  if (! (_cond_)) {\
    ALT_RET_P (ALT_A_ASSERT, #_cond_);\
  }

///
/// \brief  If condition is false, output Log Message and stop proccess
///
/// \param  _cond_  [I ] condition
///
#define ALT_E_ASSERT(_cond_) \
  if (! (_cond_)) {\
    ALT_LOG_P (ALT_A_ASSERT, #_cond_);\
    exit (1) \
  }

///
/// \brief  If condition is false, output Log Message and return ALT_E_INVAL
///
/// \param  _cond_  [I ] condition
///
#define ALT_P_ASSERT(_cond_) \
  if (! (_cond_)) {\
    ALT_RET_P (ALT_E_INVAL, #_cond_);\
  }

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Log
///
class altLog : public altBaseLog, public altSingleton<altLog>
{
friend class altSingleton<altLog>;
protected:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altLog();
  
  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altLog();
};

#endif  // ALTBASELOG_H

