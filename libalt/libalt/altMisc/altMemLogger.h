#ifndef ALTMEMLOGGER_H
#define ALTMEMLOGGER_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMemLogger.h
 * \brief   Memory logger class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altLog.h>
#include <altBase/altLoopThread.h>

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
///
/// \brief  Get Instance
///
/// \return altLog Instance
///
#define aiMemLogger altMemLogger::GetInstance()

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Memory Logger
///
class altMemLogger : public altBaseLog, public altSingleton<altMemLogger>
{
friend class altSingleton<altMemLogger>;
protected:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altMemLogger();
  
  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altMemLogger();

  ///
  /// \brief  Open log file
  ///
  /// \param  sFileName [I ] file name
  /// \param  sMode     [I ] file open mode
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Open(const altStr & sFileName, const altStr & sMode = "w+c");

  ///
  /// \brief  Write to log file
  ///
  /// \param  szFileName  [I ] File name
  /// \param  nLine       [I ] Line number
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Write(const altChar * szFileName, const altInt nLine);

  ///
  /// \brief  Close log file
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t Close();

public:
  ///
  /// \brief  Start write memory log
  ///
  /// \param  nInterval [I ] Write interval (msec)
  ///
  /// \return ALT_S_SUCCESS   success
  ///
  LIBALT_API alt_t Start(const altStr & sFileName, DWORD nInterval);

  ///
  /// \brief  Stop write memory log
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t Stop();

  ///
  /// \brief  Get instance
  ///
  /// \return instance
  ///
  LIBALT_API static altMemLogger & GetInstance();

  ///
  /// \brief  Memory log write thread
  ///
  /// \param  pParam  [I ] this object
  ///
  LIBALT_API static alt_t WriteThread(void * pParam);

private:
  altLoopThread   m_oLoopThread;
  altStr          m_sFileName;
};

#endif
