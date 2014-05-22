/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMemManager.cpp
 * \brief   Memory Manager class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altMemManager.h"
#include "altBase.h"

#include <algorithm>

/*----------------------------------------------------------------*
 * Class Variables
 *----------------------------------------------------------------*/
altMemManager *  altMemManager::pInstance = NULL;

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
altMemManager::altMemManager() :
m_oMemInfoMap(),
m_nTotalSize(0),
m_nTotalRealSize(0),
m_nMaxAllocateLimitSize(0xFFFFFFFF)
{
}

///
/// \brief  Destructor
///
altMemManager::~altMemManager()
{
}

///
/// \brief  Add
///
/// \param  pRealPtr  [I ] pointer of real memory
/// \param  pUserPtr  [I ] pointer of user memory
///
void altMemManager::Add(const altChar * pRealPtr, const altChar * pUserPtr)
{
  BeginLock();
  m_oMemInfoMap[pUserPtr] = pRealPtr;

  altMemInfo    oMemInfo;
  oMemInfo.Read (pRealPtr);
  m_nTotalSize += oMemInfo.GetSize();
  m_nTotalRealSize += oMemInfo.GetRealSize();
  EndLock();
}

///
/// \brief  Delete
///
/// \param  pPtr  [I ] pointer of user memory
///
void altMemManager::Del(const altChar * pUserPtr)
{
  BeginLock();
  const altChar * pRealPtr = m_oMemInfoMap[pUserPtr];
  m_oMemInfoMap.erase (m_oMemInfoMap.find (pUserPtr));
  
  altMemInfo    oMemInfo;
  oMemInfo.Read (pRealPtr);

  m_nTotalSize -= oMemInfo.GetSize();
  m_nTotalRealSize -= oMemInfo.GetRealSize();
  EndLock();
}

///
/// \brief  Get pointer of real memory
///
/// \param  pUserPtr  [I ] pointer of user memory
///
/// \return pointer of real memory
///
const altChar * altMemManager::GetRealPtr(const altChar * pUserPtr)
{
  BeginLock();
  const altChar * pRealPtr = m_oMemInfoMap[pUserPtr];
  EndLock();
  return (pRealPtr);
}

///
/// \brief  Get user memory size
///
/// \param  pUserPtr  [I ] pointer of user memory
///
/// \return size of user memory
///
const altUInt altMemManager::GetUserSize(const altChar * pUserPtr)
{
  const altChar * pRealPtr = GetRealPtr (pUserPtr);
  altMemInfo      oMemInfo;
  oMemInfo.Read (pRealPtr);
  return oMemInfo.GetSize();
}

///
/// \brief  check allocation limit size
///
/// \return true  over limit size
/// \return false not over limit size
///
altBool altMemManager::OverLimitSize(altUInt nAllocateSize) const
{
  if (m_nTotalSize + nAllocateSize > m_nMaxAllocateLimitSize) {
    return true;
  }
  return false;
}

///
/// \brief  set max allocate limit size
///
/// \param  max allocate limit size(byte)
///
LIBALT_API void altMemManager::SetLimitSize(const altUInt nMaxAllocateLimitSize)
{
  m_nMaxAllocateLimitSize = nMaxAllocateLimitSize;
}

///
/// \brief  get total allocated size(byte)
///
/// \return total allocated size
///
LIBALT_API altUInt altMemManager::GetTotalSize() const
{
  return m_nTotalSize;
}

///
/// \brief  get total allocated real size(byte)
///
/// \return total allocated real size
///
LIBALT_API altUInt altMemManager::GetTotalRealSize() const
{
  return m_nTotalRealSize;
}

///
/// \brief  get max allocate limit size(byte)
///
/// \return max allocate limit size(byte)
///
LIBALT_API altUInt altMemManager::GetMaxAllocateLimitSize() const
{
  return m_nMaxAllocateLimitSize;
}

///
/// \brief  get allocated memory block count
///
/// \return allocated memory block count
///
LIBALT_API altUInt altMemManager::GetBlockCount() const
{
  return (altUInt)m_oMemInfoMap.size();
}

///
/// \brief  Get memory infomation list
///
/// \return Memory infomation list
///
LIBALT_API altMemInfoList altMemManager::GetMemInfoList()
{
  altMemInfoList  oMemInfoList;

  BeginLock();
  for (altMemInfoContainer::iterator i = m_oMemInfoMap.begin(); i != m_oMemInfoMap.end(); i++) {
    if ((* i).second == NULL) {
      continue;
    }
    altMemInfo  oMemInfo;
    oMemInfo.Read ((* i).second);
    oMemInfoList.push_back (oMemInfo);
  }
  EndLock();

  std::sort (oMemInfoList.begin(), oMemInfoList.end(), altMemInfoTimeSortComparator());

  return (oMemInfoList);
}

///
/// \brief  Get Instance
///
/// \return Instance
///
LIBALT_API altMemManager & altMemManager::GetInstance()
{
  if (pInstance == NULL) {
    pInstance = new altMemManager();
  }
  return (* pInstance);
}

/*----------------------------------------------------------------*
 * Time sort comparator
 *----------------------------------------------------------------*/
///
/// \brief  Compare
///
/// \param  a [I ] element1
/// \param  b [I ] element2
///
/// \return true
/// \return false
///
altBool altMemInfoTimeSortComparator::operator () (const altMemInfo & a, const altMemInfo & b) const
{
#ifdef USE_MEM_MANAGER_FULL
  return (a.m_oTime.time < b.m_oTime.time);
#else
  return (0);
#endif
}
