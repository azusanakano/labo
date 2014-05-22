#ifndef ALTFILE_H
#define ALTFILE_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altFile.h
 * \brief   File class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altStr.h>
#include <altBase/altCharPtr.h>
#include <altBase/altBaseLog.h>
#include <altBase/altUncopyable.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  File
///
class altFile : private altUncopyable
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altFile();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altFile();

  ///
  /// \brief  Open file
  ///
  /// \param  sFileName [I ] file name
  /// \param  sMode     [I ] open mode
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t Open(const altStr & sFileName, const altStr & sMode);

  ///
  /// \brief  Close file
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t Close();

  ///
  /// \brief  Read Line from File
  ///
  /// \param  pBuf      [IO] Read Buffer
  /// \param  nBufSize  [I ] Read Buffer Size
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_S_EOF       end of file
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t ReadLine(altChar * pBuf, const altUInt nBufSize);

  ///
  /// \brief  Read
  ///
  /// \param  pBuf      [IO] Read Buffer
  /// \param  nBufSize  [I ] Read Buffer Size
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_S_EOF       end of file
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t Read(altChar * pBuf, const altUInt nBufSize);

  ///
  /// \brief  Write String
  ///
  /// \param  sStr  [I ] String
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  /// \return ALT_E_WRITE     write error
  ///
  LIBALT_API alt_t WriteLine(const altStr & sStr);

  ///
  /// \brief  Write
  ///
  /// \param  sStr  [I ] String
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  /// \return ALT_E_WRITE     write error
  ///
  LIBALT_API alt_t Write(const altStr & sStr);

  ///
  /// \brief  Write
  ///
  /// \param  pData [I ] Data
  /// \param  nSize [I ] Data size
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  /// \return ALT_E_INVAL     invalid paramter
  /// \return ALT_E_WRITE     write error
  ///
  LIBALT_API alt_t Write(const altChar * pData, const altUInt nSize);

  ///
  /// \brief  Delete file
  ///
  /// \param  sFileName [I ] File name
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Delete(const altStr & sFileName);

  ///
  /// \brief  Get file descriptor
  ///
  /// \param  nFileNo [I ] File descriptor
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t GetFileNo(altInt & nFileNo);

  ///
  /// \brief  Get file size
  ///
  /// \param  nFileSize [ O] File size
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t GetFileSize(altLong & nFileSize);

  ///
  /// \brief  Load
  ///
  /// \param  pData     [ O] Data
  /// \param  nDataSize [ O] Data size
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t Load(altCharPtr & pData, altLong & nDataSize);

protected:
  FILE *    m_pFile;
  altStr    m_sFileName;
};

#endif  // ALTFILE_H

