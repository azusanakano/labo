#ifndef ALTMEMINFO_H
#define ALTMEMINFO_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMemInfo.h
 * \brief   Memory Infomation class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>

#include <sys/timeb.h>
#include <string>

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
#define	ALT_MEM_GARBEGE  0xCC  ///< garbege

/*----------------------------------------------------------------*
  Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  memory management infomation manager
///
class altMemInfo
{
public:
  ///
  /// \brief  Constructor
  ///
  altMemInfo();

  ///
  /// \brief  Destructor
  ///
  virtual ~altMemInfo();

  ///
  /// \brief  Init Memory Infomation
  ///
  /// \param  nSize       [I ] memory size
  /// \param  szFileName  [I ] file name
  /// \param  nLine       [I ] file line number
  ///
  void Init(const altUInt nSize, const altChar * szFileName, const altUInt nLine);

  ///
  /// \brief  Write memory infomation
  ///
  /// \param  pPtr  [IO] pointer of real memory
  ///
  void Write(void * pPtr) const;

  ///
  /// \brief  Read Memory Infomation
  ///
  /// \param  pRealPtr  [I ] pointer of real memory
  ///
  void Read(const void * pRealPtr);

  ///
  /// \brief  Get memory size
  ///
  /// \return memory size
  ///
  altUInt GetSize() const;

  ///
  /// \brief  Get memory infomation block size
  ///
  /// \return memory infomation block size
  ///
  altUInt GetInfoSize() const;
  
  ///
  /// \brief  Get memory real size
  ///
  /// \return memory real size
  ///
  altUInt GetRealSize() const;

  ///
  /// \brief  check over write memory detected
  ///
  /// \return true  detected
  /// \return false not detected
  ///
  altBool OverWriteDetected() const;

  altUChar      m_cMagic;               ///< magic number
  altUInt       m_nSize;                ///< allocated size
#ifdef USE_MEM_MANAGER_FULL
  altUInt       m_nFileNameSize;        ///< allocated filename size
  std::string   m_szFileName;           ///< allocated filename
  altUInt       m_nLine;                ///< allocated line number
  struct timeb  m_oTime;                ///< allocated time
#endif
  const void *  m_pAddr;                ///< allocated address

  static const altUChar ALT_MEM_MAGIC;    ///< memory magic number
  static const altUChar ALT_MEM_END_SIG;  ///< memory magic number
};

#endif

