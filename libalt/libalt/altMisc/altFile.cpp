/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altFile.cpp
 * \brief   File class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altFile.h"
#include "altMiscUtil.h"
#include "altBase/altUtil.h"

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altFile::altFile()
{
  m_pFile = NULL;
}

///
/// \brief  Destructor
///
LIBALT_API altFile::~altFile()
{
  alt_t status = Close();
  ALT_LOG (status);
}

///
/// \brief  Open file
///
/// \param  sFileName [I ] file name
/// \param  sMode     [I ] open mode
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altFile::Open(const altStr & sFileName, const altStr & sMode)
{
  altFOpen (sFileName.GetCStr(), sMode.GetCStr(), m_pFile);
  if (m_pFile == NULL) {
    altInt  nErrNo = errno;
    altStr  sBuf;
#ifdef ALT_WIN
    altChar szBuf[ALT_BUFSIZ];
    strerror_s (szBuf, sizeof (szBuf), nErrNo);
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("Error Code=%d (%s)[%s]", nErrNo, szBuf, sFileName.GetCStr()));
#endif
#ifdef ALT_LINUX
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("Error Code=%d (%s)[%s]", nErrNo, strerror (nErrNo), sFileName.GetCStr()));
#endif
  }
  m_sFileName = sFileName;

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Close file
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altFile::Close()
{
  if (m_pFile == NULL) {
    ALT_RET (ALT_S_SUCCESS);
  }
  altInt nRet = fclose (m_pFile);
  if (nRet == EOF) {
    altInt  nErrNo = errno;
    altStr  sBuf;
#ifdef ALT_WIN
    altChar szBuf[ALT_BUFSIZ];
    strerror_s (szBuf, sizeof (szBuf), nErrNo);
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%d (%s)[%s]", nErrNo, szBuf, m_sFileName.GetCStr()));
#endif
#ifdef ALT_LINUX
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%d (%s)[%s]", nErrNo, strerror (nErrNo), m_sFileName.GetCStr()));
#endif
  }
  m_pFile = NULL;
  m_sFileName = "";
  ALT_RET (ALT_S_SUCCESS);
}

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
LIBALT_API alt_t altFile::ReadLine(altChar * pBuf, const altUInt nBufSize)
{
  if (m_pFile == NULL) {
    ALT_RET_P (ALT_E_ERROR, "file is not opened");
  }
  if (fgets (pBuf, nBufSize, m_pFile) == NULL) {
    if (feof (m_pFile)) {
      clearerr (m_pFile);
      ALT_RET (ALT_S_EOF);
    }
    else{
      altInt  nErrNo = errno;
      altStr  sBuf;
#ifdef ALT_WIN
      altChar szBuf[ALT_BUFSIZ];
      strerror_s (szBuf, sizeof (szBuf), nErrNo);
      ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%d (%s)[%s]", nErrNo, szBuf, m_sFileName.GetCStr()));
#endif
#ifdef ALT_LINUX
      ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%d (%s)[%s]", nErrNo, strerror (nErrNo), m_sFileName.GetCStr()));
#endif
    }
  }

  ALT_RET (ALT_S_SUCCESS);
}

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
LIBALT_API alt_t altFile::Read(altChar * pBuf, const altUInt nBufSize)
{
  if (m_pFile == NULL) {
    ALT_RET_P (ALT_E_ERROR, "file is not opened");
  }

  altUInt nReadSize = static_cast<altUInt>(fread (pBuf, sizeof (* pBuf), nBufSize, m_pFile));
  if (nReadSize == 0) {
    if (feof (m_pFile)) {
      clearerr (m_pFile);
      ALT_RET (ALT_S_EOF);
    }
    else {
      altInt  nErrNo = errno;
      altStr  sBuf;
#ifdef ALT_WIN
      altChar szBuf[ALT_BUFSIZ];
      strerror_s (szBuf, sizeof (szBuf), nErrNo);
      ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%d (%s)[%s]", nErrNo, szBuf, m_sFileName.GetCStr()));
#endif
#ifdef ALT_LINUX
      ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%d (%s)[%s]", nErrNo, strerror (nErrNo), m_sFileName.GetCStr()));
#endif
    }
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Write String
///
/// \param  sStr  [I ] String
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
/// \return ALT_E_WRITE     write error
///
LIBALT_API alt_t altFile::WriteLine(const altStr & sStr)
{
  if (m_pFile == NULL) {
    ALT_RET_P (ALT_E_ERROR, "file is not opened");
  }
  alt_t status;

  status = altFPuts (sStr.GetCStr(), m_pFile);
  ALT_ERR_RET (status);

  status = altFPuts ("\n", m_pFile);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Write
///
/// \param  sStr  [I ] String
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
/// \return ALT_E_WRITE     write error
///
LIBALT_API alt_t altFile::Write(const altStr & sStr)
{
  if (m_pFile == NULL) {
    ALT_RET (ALT_E_ERROR);
  }
  alt_t status;
  status = altFPuts (sStr.GetCStr(), m_pFile);
  ALT_ERR_RET (status);
  ALT_RET (ALT_S_SUCCESS);
}

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
LIBALT_API alt_t altFile::Write(const altChar * pData, const altUInt nSize)
{
  if (m_pFile == NULL) {
    ALT_RET (ALT_E_ERROR);
  }

  ALT_P_ASSERT (pData != NULL);

  altInt  nErrorCount = 0;
  size_t  nTotalWriteSize = 0;

  while (nTotalWriteSize != nSize) {
    size_t nWriteSize = fwrite (& pData[nTotalWriteSize], sizeof (* pData), nSize - nTotalWriteSize, m_pFile);
    if (nWriteSize > 0) {
      nTotalWriteSize += nWriteSize;
      nErrorCount = 0;
    }
    else {
      nErrorCount++;
    }
    if (nErrorCount > 10) {
      ALT_RET (ALT_E_WRITE);
    }
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Delete file
///
/// \param  sFileName [I ] File name
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altFile::Delete(const altStr & sFileName)
{
#ifdef ALT_WIN
  altInt nRet = _unlink (sFileName.GetCStr());
  if (nRet < 0) {
    altInt  nErrNo = errno;
    altChar szBuf[ALT_BUFSIZ];
    strerror_s (szBuf, sizeof (szBuf), nErrNo);
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("file delete error (%s) errno=%d(%s)", sFileName.GetCStr(), nErrNo, szBuf));
  }
#endif
#ifdef ALT_LINUX
  altInt nRet = unlink (sFileName.GetCStr());
  if (nRet < 0) {
    altInt  nErrNo = errno;
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("file delete error (%s) errno=%d(%s)", sFileName.GetCStr(), nErrNo, strerror (nErrNo)));
  }
#endif
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get file descriptor
///
/// \param  nFileNo [I ] File descriptor
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altFile::GetFileNo(altInt & nFileNo)
{
  if (m_pFile == NULL) {
    ALT_RET_P (ALT_E_ERROR, "m_pFile is NULL");
  }
#ifdef ALT_WIN
  nFileNo = _fileno (m_pFile);
  if (nFileNo < 0) {
    altInt  nErrNo = errno;
    altStr  sBuf;
    altChar szBuf[BUFSIZ];
    strerror_s (szBuf, sizeof (szBuf), nErrNo);
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%s:%s", m_sFileName.GetCStr(), szBuf));
  }
#endif
#ifdef ALT_LINUX
  nFileNo = fileno (m_pFile);
  if (nFileNo < 0) {
    altInt  nErrNo = errno;
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%s:%s", m_sFileName.GetCStr(), strerror (nErrNo)));
  }
#endif
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get file size
///
/// \param  nFileSize [ O] File size
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altFile::GetFileSize(altLong & nFileSize)
{
  alt_t   status;
  altInt  nFileNo;

  status = GetFileNo (nFileNo);
  ALT_ERR_RET (status);

#ifdef ALT_WIN
  struct _stat  oBuf;
  altInt        nRet;

  nRet = _fstat (nFileNo, & oBuf);
  if (nRet < 0) {
    altInt  nErrNo = errno;
    altStr  sBuf;
    altChar szBuf[BUFSIZ];
    strerror_s (szBuf, sizeof (szBuf), nErrNo);
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%s:%s", m_sFileName.GetCStr(), szBuf));
  }
  nFileSize = oBuf.st_size;
#endif
#ifdef ALT_LINUX
  struct stat oBuf;
  altInt      nRet;

  nRet = fstat (nFileNo, & oBuf);
  if (nRet < 0) {
    altInt  nErrNo = errno;
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%s:%s", m_sFileName.GetCStr(), strerror (nErrNo)));
  }
  nFileSize = oBuf.st_size;
#endif

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Load
///
/// \param  pData     [ O] Data
/// \param  nDataSize [ O] Data size
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altFile::Load(altCharPtr & pData, altLong & nDataSize)
{
  alt_t status;

  status = GetFileSize (nDataSize);
  ALT_ERR_RET (status);

  status = ALT_MALLOC (pData, nDataSize);
  ALT_ERR_RET (status);

  status = Read (pData, nDataSize);
  ALT_ERR_RET (status);

  ALT_RET (ALT_S_SUCCESS);
}
