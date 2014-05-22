/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altWStr.cpp
 * \brief   Wide string class
 * \date    2013
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altWStr.h"
#include "altBaseMem.h"
#include "altUtil.h"
#include "alt_wrapper/alt_string.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altWStr::altWStr() :
m_szStr (NULL),
m_nLen (0)
{
  ALT_BASE_WSTRALLOC (m_szStr, "");
}

///
/// \brief  Constructor
///
/// \param  c [I ] Character
///
LIBALT_API altWStr::altWStr(const altWChar c) :
m_szStr (NULL),
m_nLen (1)
{
  altWChar  szBuf[2];
  szBuf[0] = c;
  szBuf[1] = 0x0000;
  ALT_BASE_WSTRALLOC (m_szStr, szBuf);
}

///
/// \brief  Constructor
///
/// \param  szStr [I ] string
///
LIBALT_API altWStr::altWStr(const altChar * szStr) :
m_szStr (NULL),
m_nLen (0)
{
  m_nLen = altWStrLen ((altWChar *)szStr);
  ALT_BASE_WSTRALLOC (m_szStr, szStr);
}

///
/// \brief  Constructor
///
/// \param  szStr [I ] string
///
LIBALT_API altWStr::altWStr(const altWChar * szStr) :
m_szStr (NULL),
m_nLen (0)
{
  m_nLen = altWStrLen (szStr);
  ALT_BASE_WSTRALLOC (m_szStr, szStr);
}

///
/// \brief  Constructor
///
/// \param  szStr [I ] string
///
LIBALT_API altWStr::altWStr(const wchar_t * szStr) :
m_szStr (NULL),
m_nLen (0)
{
  m_nLen = altWStrLen ((altWChar *)szStr);
  ALT_BASE_WSTRALLOC (m_szStr, szStr);
}


///
/// \brief  Copy Constructor
///
/// \param  szStr [I ] string
///
LIBALT_API altWStr::altWStr(const altWStr & oStr) :
m_szStr (NULL),
m_nLen (0)
{
  m_nLen = oStr.m_nLen;
  ALT_BASE_WSTRALLOC (m_szStr, oStr.m_szStr);
}

///
/// \brief  Destructor
///
LIBALT_API altWStr::~altWStr()
{
  ALT_BASE_FREE (m_szStr);
  m_nLen = 0;
}
  
///
/// \brief  = operator
///
/// \param  oStr  [I ] string object
///
/// \return this object
///
LIBALT_API altWStr &  altWStr::operator =(const altWStr & oStr)
{
  if (m_szStr == oStr.m_szStr) {
    return (* this);
  }
  ALT_BASE_FREE (m_szStr);
  m_nLen = oStr.m_nLen;
  ALT_BASE_WSTRALLOC (m_szStr, oStr.m_szStr);
  return (* this);
}

///
/// \brief  + operator
///
/// \param  oStr  [I ] string object
///
/// \return this object
///
LIBALT_API const altWStr altWStr::operator +(const altWStr & oStr)
{
  altWStr sTmp;
  sTmp += (* this);
  sTmp += oStr;
  return (sTmp);
}

///
/// \brief  += operator
///
/// \param  oStr  [I ] string object
///
/// \return this object
///
LIBALT_API const altWStr & altWStr::operator +=(const altWStr & oStr)
{
  ALT_BASE_EXALLOC (m_szStr, (m_nLen + 1) * sizeof (altWChar), (m_nLen + oStr.m_nLen + 1) * sizeof (altWChar));
  memcpy (m_szStr + m_nLen, oStr.m_szStr, oStr.m_nLen * sizeof (altWChar));
  m_nLen += oStr.m_nLen;
  return (* this);
}

///
/// \brief  == operator
///
/// \param  oStr  [I ] string object
///
/// \return true  same string
/// \return false other string
///
LIBALT_API const altBool altWStr::operator ==(const altWStr & oStr) const
{
  if (m_szStr == oStr.m_szStr) {
    return (true);
  }
  if (m_nLen != oStr.m_nLen) {
    return (false);
  }
  if (memcmp (m_szStr, oStr.m_szStr, m_nLen) == 0) {
    return (true);
  }
  return (false);
}

///
/// \brief  != operator
///
/// \param  oStr  [I ] string object
///
/// \return true  other string
/// \return false same string
///
LIBALT_API const altBool altWStr::operator !=(const altWStr & oStr) const
{
  altBool b = ((* this) == oStr);
  return (! b);
}

///
/// \brief  < operator
///
/// \param  oStr  [I ] string object
///
/// \return true  
/// \return false 
///
LIBALT_API const altBool altWStr::operator <(const altWStr & oStr) const
{
  if (m_szStr == oStr.m_szStr) {
    return (false);
  }

  for (altUInt i = 0; i < m_nLen && i < oStr.m_nLen; i++) {
    if (m_szStr[i] > oStr.m_szStr[i]) {
      return (false);
    }
    else if (m_szStr[i] < oStr.m_szStr[i]) {
      return (true);
    }
  }

  if (m_nLen == oStr.m_nLen) {
    return (false);
  }
  else if (m_nLen < oStr.m_nLen) {
    return (true);
  }

  return (false);
}

///
/// \brief  <= operator
///
/// \param  oStr  [I ] string object
///
/// \return true  
/// \return false 
///
LIBALT_API const altBool altWStr::operator <=(const altWStr & oStr) const
{
  if (m_szStr == oStr.m_szStr) {
    return (true);
  }

  for (altUInt i = 0; i < m_nLen && i < oStr.m_nLen; i++) {
    if (m_szStr[i] > oStr.m_szStr[i]) {
      return (false);
    }
    else if (m_szStr[i] < oStr.m_szStr[i]) {
      return (true);
    }
  }

  if (m_nLen == oStr.m_nLen) {
    return (true);
  }
  else if (m_nLen < oStr.m_nLen) {
    return (true);
  }

  return (false);
}

///
/// \brief  > operator
///
/// \param  oStr  [I ] string object
///
/// \return true  
/// \return false 
///
LIBALT_API const altBool altWStr::operator >(const altWStr & oStr) const
{
  if (m_szStr == oStr.m_szStr) {
    return (false);
  }

  for (altUInt i = 0; i < m_nLen && i < oStr.m_nLen; i++) {
    if (m_szStr[i] > oStr.m_szStr[i]) {
      return (true);
    }
    else if (m_szStr[i] < oStr.m_szStr[i]) {
      return (false);
    }
  }

  if (m_nLen == oStr.m_nLen) {
    return (false);
  }
  else if (m_nLen < oStr.m_nLen) {
    return (false);
  }

  return (true);
}

///
/// \brief  >= operator
///
/// \param  oStr  [I ] string object
///
/// \return true  
/// \return false 
///
LIBALT_API const altBool altWStr::operator >=(const altWStr & oStr) const
{
  if (m_szStr == oStr.m_szStr) {
    return (true);
  }

  for (altUInt i = 0; i < m_nLen && i < oStr.m_nLen; i++) {
    if (m_szStr[i] > oStr.m_szStr[i]) {
      return (true);
    }
    else if (m_szStr[i] < oStr.m_szStr[i]) {
      return (false);
    }
  }

  if (m_nLen == oStr.m_nLen) {
    return (true);
  }
  else if (m_nLen < oStr.m_nLen) {
    return (false);
  }

  return (true);
}

///
/// \brief  [] operator
///
/// \param  nIndex [I ] index
///
/// \return character of index position
///
LIBALT_API altWChar & altWStr::operator [](const altUInt nIndex) const
{
#if 0
  if (nIndex >= m_nLen) {
    return (0x0000);
  }
#endif
  return (m_szStr[nIndex]);
}

///
/// \brief  Get C styte string
///
/// \return pointer of string
///
LIBALT_API const altWChar * altWStr::GetCStr() const
{
  return (m_szStr);
}

///
/// \brief  Get string length
///
/// \return string length
///
LIBALT_API const altUInt altWStr::GetLen() const
{
  return (m_nLen);
}

///
/// \brief  Get buffer size
///
/// \return buffer size
///
LIBALT_API const altUInt altWStr::GetSize() const
{
  return (m_nLen * sizeof (altWChar));
}

///
/// \brief  Search string
///
/// \param  sStr  [I ] search string
///
/// \return found index
/// \return -1  not found
///
LIBALT_API altInt altWStr::Find(const altWStr & sStr) const
{
  /// Using Boyer-Moore Algorithm
  altUInt aSkip[256 * 256];
  altUInt nStrLen = sStr.GetLen();
  if (nStrLen == 0) {
    return (-1);
  }

  // create skip table
  for (altUInt i = 0; i < ALT_ARRAY_SIZE (aSkip); i++) {
    aSkip[i] = nStrLen;
  }
  for (altUInt i = 0; i < nStrLen - 1; i++) {
    aSkip[static_cast<altUInt>(sStr[i])] = nStrLen - (i + 1);
  }

  altUInt i = nStrLen - 1;
  altUInt nLen = GetLen();

  while (i < nLen) {
    altUInt j = nStrLen - 1;

    while (m_szStr[i] == sStr[j]) {

      // string found
      if (j == 0) {
        return i;
      }

      i--;
      j--;
    }

    if (aSkip[static_cast<altUInt>(m_szStr[i])] > nStrLen - j) {
      i += aSkip[static_cast<altUInt>(m_szStr[i])];
    }
    else {
      i += (nStrLen - j);
    }
  }

  // string not found
  return (-1);
}

///
/// \brief  Search String from last
///
/// \param  sStr  [I ] search string
///
/// \return found index
/// \return -1    not found
///
LIBALT_API altInt altWStr::FindLastOf(const altWStr & sStr) const
{
  /// Using Boyer-Moore Algorithm
  altUInt aSkip[256 * 256];
  altUInt nStrLen = sStr.GetLen();

  // create skip table
  for (altUInt i = 0; i < ALT_ARRAY_SIZE (aSkip); i++) {
    aSkip[i] = nStrLen;
  }
  for (altUInt i = 0; i < nStrLen - 1; i++) {
    aSkip[static_cast<altUInt>(sStr[i])] = nStrLen - (i + 1);
  }

  altUInt nLen = GetLen();
  altUInt i = nLen - 1;

  while (i >= (nStrLen - 1)) {
    altUInt j = nStrLen - 1;

    while (m_szStr[i] == sStr[j]) {

      // string found
      if (j == 0) {
        return i;
      }

      i--;
      j--;
    }

    if (aSkip[static_cast<altUInt>(m_szStr[i])] > nStrLen - j) {
      i -= aSkip[static_cast<altUInt>(m_szStr[i])];
    }
    else {
      i -= (nStrLen - j);
    }
  }

  // string not found
  return (-1);
}

///
/// \brief  Search character
///
/// \param  sCharList  [I ] character list
///
/// \return found index
/// \return -1  not found
///
LIBALT_API altInt altWStr::FindChar(const altWStr & sCharList) const
{
  altUInt nLen = GetLen();
  altUInt nListLen = sCharList.GetLen();

  for (altUInt i = 0; i < nLen; i++) {
    for (altUInt j = 0; j < nListLen; j++) {
      if (m_szStr[i] == sCharList[j]) {
        return (altInt)(i);
      }
    }
  }
  return (-1);
}

///
/// \brief  Search character from last
///
/// \param  sCharList  [I ] character list
///
/// \return found index
/// \return -1  not found
///
LIBALT_API altInt altWStr::FindLastOfChar(const altWStr & sCharList) const
{
  altUInt nLen = GetLen();
  altUInt nListLen = sCharList.GetLen();

  for (altUInt i = nLen - 1; i >= 0; i--) {
    for (altUInt j = 0; j < nListLen; j++) {
      if (m_szStr[i] == sCharList[j]) {
        return (i);
      }
    }
  }

  return (-1);
}

///
/// \brief  sub string
///
/// \param  nIndex  [I ] begin index
///
/// \return string
///
LIBALT_API altWStr altWStr::SubStr(const altUInt nIndex) const
{
  altWStr sSubStr;

  if ((* this)[nIndex] == 0x00) {
    return sSubStr;
  }

  sSubStr = & m_szStr[nIndex];

  return (sSubStr);
}

///
/// \brief  sub string
///
/// \param  nBegin  [I ] begin index
/// \param  nEnd    [I ] end index
///
/// \return string
///
LIBALT_API altWStr altWStr::SubStr(const altUInt nBegin, const altUInt nEnd) const
{
  if (nBegin > nEnd) {
    altWStr sRet;
    return (sRet);
  }
  altWChar * pSubStr = NULL;
  ALT_BASE_DUPALLOC (pSubStr, m_szStr, m_nLen * sizeof (altWChar));

  // no memory
  if (pSubStr == NULL) {
    altWStr sRet;
    return (sRet);
  }

  // Revision end index
  altUInt nLen = GetLen();

  altUInt nRealEnd = nEnd;
  if (nRealEnd >= nLen) {
    nRealEnd = nLen - 1;
  }

  altUInt nSubStrLen = nRealEnd - nBegin + 1;

  // create sub string
  memmove (pSubStr, & pSubStr[nBegin], nSubStrLen * sizeof (* pSubStr));
  pSubStr[nSubStrLen - 1] = 0x0000;

  altWStr sSubStr = pSubStr;
  ALT_BASE_FREE (pSubStr);

  return sSubStr;
}

///
/// \brief  replace
///
/// \param  sTarget   [I ] target string
/// \param  sReplaced [I ] replace string
///
/// \return 0 target not found
/// \return 1 target replaced
///
LIBALT_API altUInt altWStr::Replace(const altWStr & sTarget, const altWStr & sReplaced)
{
  altInt  nIndex = this->Find (sTarget);
  if (nIndex < 0) {
    return (0);
  }

  if (sTarget.GetLen() != sReplaced.GetLen()) {
    altUInt     nNowSize = (m_nLen + 1) * sizeof (altWChar);
    altUInt     nNewSize = nNowSize + ((sReplaced.GetLen() - sTarget.GetLen()) * sizeof (altWChar));
    altWChar *  pPtr = NULL;
    
    altUInt nRet = ALT_BASE_MALLOC (pPtr, nNewSize);
    if (nRet != ALT_SUCCESS) {
      return (0);
    }
    if (nIndex > 0) {
      memcpy (pPtr, m_szStr, nIndex);
    }
    memcpy (& pPtr[nIndex], sReplaced.GetCStr(), sReplaced.GetLen() * sizeof (altWChar));
    memcpy (& pPtr[nIndex + sReplaced.GetLen()], & m_szStr[nIndex + sTarget.GetLen()], nNowSize - ((nIndex + sTarget.GetLen()) * sizeof (altWChar)));

    ALT_BASE_FREE (m_szStr);
    m_szStr = pPtr;
  }
  else {
    memcpy (& m_szStr[nIndex], sReplaced.GetCStr(), sReplaced.GetLen() * sizeof (altWChar));
  }

  return (1);
}

///
/// \brief  replace all
///
/// \param  sTarget   [I ] target string
/// \param  sReplaced [I ] replace string
///
/// \return replaced count
///
LIBALT_API altUInt altWStr::ReplaceAll(const altWStr & sTarget, const altWStr & sReplaced)
{
  altUInt nRet;
  altUInt nCount = 0;
  while ((nRet = Replace (sTarget, sReplaced)) == 1) {
    nCount++;
  }
  return (nCount);
}

///
/// \brief  Format
///
/// \param  szFormat  [I ] Format
///
/// \return Format string
///
LIBALT_API const altWChar * altWStr::Format(const wchar_t * szFormat, ...)
{
  altWChar *  pBuf = NULL;
  va_list     oArgs;
  altUInt     nNowSize = 0;
  altUInt     nNewSize = BUFSIZ;
  altInt      nRet;

  while (1) {
    nRet = ALT_BASE_EXALLOC (pBuf, nNowSize * sizeof (* pBuf), nNewSize * sizeof (* pBuf));
    if (nRet != ALT_SUCCESS) {
      ALT_BASE_FREE (pBuf);
      return NULL;
    }
    nNowSize = nNewSize;

    va_start (oArgs, szFormat);
    nRet = alt_vsnprintf ((altChar *)pBuf, nNowSize, (const altChar *)szFormat, oArgs);
    va_end (oArgs);
    if (nRet > -1 && static_cast<altUInt>(nRet) < nNowSize) {
      break;
    }

    if (static_cast<altUInt>(nRet) >= nNowSize) {
      nNewSize = nRet + 1;
    }
    else {
      nNewSize = nNowSize * 2;
    }
  }

  ALT_BASE_FREE (m_szStr);
  ALT_BASE_WSTRALLOC (m_szStr, pBuf);
  ALT_BASE_FREE (pBuf);
  return (m_szStr);
}

///
/// \brief  Delete last character
///
/// \return true  success
/// \return false failed
///
LIBALT_API altBool altWStr::DeleteLastChar()
{
  if (m_nLen == 0) {
    return (false);
  }
  (* this) = SubStr(0, m_nLen - 1);
  return (true);
}
