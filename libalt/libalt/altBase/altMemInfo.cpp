/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMemInfo.cpp
 * \brief   Memory Infomation class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altMemInfo.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/
const altUChar altMemInfo::ALT_MEM_MAGIC = 0xAA;    ///< memory magic number
const altUChar altMemInfo::ALT_MEM_END_SIG = 0xAC;  ///< memory end signature

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
altMemInfo::altMemInfo() :
m_cMagic (ALT_MEM_MAGIC),
m_nSize (0),
#ifdef USE_MEM_MANAGER_FULL
m_nFileNameSize (0),
m_szFileName (""),
m_nLine (0),
m_oTime (),
#endif
m_pAddr (NULL)
{
}

///
/// \brief  Destructor
///
altMemInfo::~altMemInfo()
{
  m_cMagic = ALT_MEM_MAGIC;
  m_nSize = 0;
#ifdef USE_MEM_MANAGER_FULL
  m_nFileNameSize = 0;
  m_szFileName = "";
  m_nLine = 0;
  memset (& m_oTime, 0x00, sizeof (m_oTime));
#endif
  m_pAddr = NULL;
}

///
/// \brief  Init Memory Infomation
///
/// \param  pPtr        [IO] pointer of real memory
/// \param  nSize       [I ] memory size
/// \param  szFileName  [I ] file name
/// \param  nLine       [I ] file line number
///
void altMemInfo::Init(const altUInt nSize, const altChar * szFileName, const  altUInt nLine)
{
  m_nSize = nSize;
#ifdef USE_MEM_MANAGER_FULL
  m_nFileNameSize = (altUInt)(strlen (szFileName) + 1);
  m_szFileName = szFileName;
  m_nLine = nLine;
  ftime (& m_oTime);
#endif
}

///
/// \brief  Write memory infomation
///
/// \param  pPtr  [IO] pointer of real memory
///
void altMemInfo::Write(void * pPtr) const
{
  if (pPtr == NULL) {
    return;
  }
  altChar * p = static_cast<altChar *>(pPtr);
  altInt i = 0;

  memcpy (p + i, & m_cMagic, sizeof (m_cMagic));
  i += sizeof (m_cMagic);

  memcpy (p + i, & m_nSize, sizeof (m_nSize));
  i += sizeof (m_nSize);

#ifdef USE_MEM_MANAGER_FULL
  memcpy (p + i, & m_nFileNameSize, sizeof (m_nFileNameSize));
  i += sizeof (m_nFileNameSize);

  memcpy (p + i, m_szFileName.c_str(), m_nFileNameSize);
  i += m_nFileNameSize;

  memcpy (p + i, & m_nLine, sizeof (m_nLine));
  i += sizeof (m_nLine);

  memcpy (p + i, & m_oTime, sizeof (m_oTime));
  i += sizeof (m_oTime);
#endif

  memset (p + i, 0x00, m_nSize);
  i += m_nSize;

  memcpy (p + i, & ALT_MEM_END_SIG, sizeof (ALT_MEM_END_SIG));
  i += sizeof (ALT_MEM_END_SIG);

  ALT_BASE_ASSERT ((altUInt)i == GetRealSize());

  return;
}

///
/// \brief  Read Memory Infomation
///
/// \param  pRealPtr  [I ] pointer of real memory
///
void altMemInfo::Read(const void * pRealPtr)
{
  if (pRealPtr == NULL) {
    return;
  }
  const altChar * p = (const altChar *)pRealPtr;
  altInt i = 0;

  memcpy (& m_cMagic, p + i, sizeof (m_cMagic));
  i += sizeof (m_cMagic);

  memcpy (& m_nSize, p + i, sizeof (m_nSize));
  i += sizeof (m_nSize);

#ifdef USE_MEM_MANAGER_FULL
  memcpy (& m_nFileNameSize, p + i, sizeof (m_nFileNameSize));
  i += sizeof (m_nFileNameSize);

  m_szFileName = (p + i);
  i += m_nFileNameSize;

  memcpy (& m_nLine, p + i, sizeof (m_nLine));
  i += sizeof (m_nLine);

  memcpy (& m_oTime, p + i, sizeof (m_oTime));
  i += sizeof (m_oTime);
#endif

  m_pAddr = (p + i);
  i += m_nSize;

  i += sizeof (ALT_MEM_END_SIG);
  ALT_BASE_ASSERT ((altUInt)i == GetRealSize());
}

///
/// \brief  Get memory infomation block size
///
/// \return memory infomation block size
///
altUInt altMemInfo::GetSize() const
{
  return m_nSize;
}

///
/// \brief  Get memory infomation block size
///
/// \return memory infomation block size
///
altUInt altMemInfo::GetInfoSize() const
{
  altUInt nSize = 0;
  nSize += sizeof (m_cMagic);
  nSize += sizeof (m_nSize);
#ifdef USE_MEM_MANAGER_FULL
  nSize += sizeof (m_nFileNameSize);
  nSize += m_nFileNameSize;
  nSize += sizeof (m_nLine);
  nSize += sizeof (m_oTime);
#endif
  return nSize;
}

///
/// \brief  Get memory real size
///
/// \return memory real size
///
altUInt altMemInfo::GetRealSize() const
{
  altUInt nSize = GetInfoSize() + m_nSize + sizeof (ALT_MEM_END_SIG);
  return nSize;
}

///
/// \brief  check over write memory detected
///
/// \return true  detected
/// \return false not detected
///
altBool altMemInfo::OverWriteDetected() const
{
  const altUInt nUserSize = GetSize();
  const altBool bDetected = (static_cast<const altUChar *>(m_pAddr)[nUserSize] != ALT_MEM_END_SIG);
  return (bDetected);
}

