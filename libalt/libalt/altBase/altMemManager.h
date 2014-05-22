#ifndef ALTMEMMANAGER_H
#define ALTMEMMANAGER_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMemManager.h
 * \brief   Memory Manager class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altMemInfo.h>
#include <altBase/altSyncThread.h>
#include <altBase/altUncopyable.h>

#include <map>
#include <vector>

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
#define aiMemManager  altMemManager::GetInstance()

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
/// memory management infomation container
typedef std::map<const altChar *, const altChar *>  altMemInfoContainer;
typedef std::vector<altMemInfo>                     altMemInfoList;

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  memory management infomation manager
///
class altMemManager : private altSyncThread, private altUncopyable
{
private:
  ///
  /// \brief  Constructor
  ///
  altMemManager();

  ///
  /// \brief  Destructor
  ///
  virtual ~altMemManager();

public:
  ///
  /// \brief  Add
  ///
  /// \param  pRealPtr  [I ] pointer of real memory
  /// \param  pUserPtr  [I ] pointer of user memory
  ///
  void Add(const altChar * pRealPtr, const altChar * pUserPtr);

  ///
  /// \brief  Delete
  ///
  /// \param  pPtr  [I ] pointer of user memory
  ///
  void Del(const altChar * pUserPtr);

  ///
  /// \brief  Get pointer of real memory
  ///
  /// \param  pUserPtr  [I ] pointer of user memory
  ///
  /// \return pointer of real memory
  ///
  const altChar * GetRealPtr(const altChar * pUserPtr);

  ///
  /// \brief  Get user memory size
  ///
  /// \param  pUserPtr  [I ] pointer of user memory
  ///
  /// \return size of user memory
  ///
  const altUInt GetUserSize(const altChar * pUserPtr);

  ///
  /// \brief  Check allocation limit size
  ///
  /// \return true  over limit size
  /// \return false not over limit size
  ///
  altBool OverLimitSize(const altUInt nAllocateSize) const;

  ///
  /// \brief  Set max allocate limit size
  ///
  /// \param  max allocate limit size(byte)
  ///
  LIBALT_API void SetLimitSize(const altUInt nMaxAllocateLimitSize);

  ///
  /// \brief  Get total allocated size(byte)
  ///
  /// \return total allocated size
  ///
  LIBALT_API altUInt GetTotalSize() const;

  ///
  /// \brief  Get total allocated real size(byte)
  ///
  /// \return total allocated real size
  ///
  LIBALT_API altUInt GetTotalRealSize() const;

  ///
  /// \brief  Get max allocate limit size(byte)
  ///
  /// \return max allocate limit size(byte)
  ///
  LIBALT_API altUInt GetMaxAllocateLimitSize() const;

  ///
  /// \brief  Get allocated memory block count
  ///
  /// \return allocated memory block count
  ///
  LIBALT_API altUInt GetBlockCount() const;

  ///
  /// \brief  Get memory infomation list
  ///
  /// \return Memory infomation list
  ///
  LIBALT_API altMemInfoList GetMemInfoList();

  ///
  /// \brief  Get Instance
  ///
  /// \return Instance
  ///
  LIBALT_API static altMemManager & GetInstance();

private:
  altMemInfoContainer m_oMemInfoMap;              /** memory management infomations */
  altUInt             m_nTotalSize;               /** total allocated size(byte) */
  altUInt             m_nTotalRealSize;           /** total allocated real size(byte)*/
  altUInt             m_nMaxAllocateLimitSize;    /** max allocate limit size(byte) */

  static altMemManager *  pInstance;
};

///
/// \brief  Time sort comparator
///
class altMemInfoTimeSortComparator
{
public:
  ///
  /// \brief  Compare
  ///
  /// \param  a [I ] element1
  /// \param  b [I ] element2
  ///
  /// \return true
  /// \return false
  ///
  altBool operator () (const altMemInfo & a, const altMemInfo & b) const;
};

#endif

