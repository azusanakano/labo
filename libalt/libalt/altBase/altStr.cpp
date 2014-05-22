/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altStr.cpp
 * \brief   String class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altStr.h"
#include "altBaseMem.h"
#include "altUtil.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altStr::altStr() :
m_szStr (NULL)
{
  ALT_BASE_STRALLOC (m_szStr, "");
}

///
/// \brief  Constructor
///
/// \param  szStr [I ] string
///
LIBALT_API altStr::altStr(const altChar * szStr) :
m_szStr (NULL)
{
  ALT_BASE_STRALLOC (m_szStr, szStr);
}

///
/// \brief  Copy Constructor
///
/// \param  szStr [I ] string
///
LIBALT_API altStr::altStr(const altStr & oStr) :
m_szStr (NULL)
{
  ALT_BASE_STRALLOC (m_szStr, oStr.m_szStr);
}

///
/// \brief  Destructor
///
LIBALT_API altStr::~altStr()
{
  ALT_BASE_FREE (m_szStr);
}

///
/// \brief  = operator
///
/// \param  oStr  [I ] string object
///
/// \return this object
///
LIBALT_API altStr & altStr::operator =(const altStr & oStr)
{
  if (m_szStr == oStr.m_szStr) {
    return (* this);
  }
  ALT_BASE_FREE (m_szStr);
  ALT_BASE_STRALLOC (m_szStr, oStr.m_szStr);
  return (* this);
}

///
/// \brief  + operator
///
/// \param  oStr  [I ] string object
///
LIBALT_API const altStr & altStr::operator +(const altStr & oStr)
{
  ALT_BASE_STRALLOC_CAT (m_szStr, oStr.m_szStr);
  return (* this);
}

///
/// \brief  += operator
///
/// \param  oStr  [I ] string object
///
/// \return this object
///
LIBALT_API const altStr & altStr::operator +=(const altStr & oStr)
{
  ALT_BASE_STRALLOC_CAT (m_szStr, oStr.m_szStr);
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
LIBALT_API const altBool altStr::operator ==(const altStr & oStr) const
{
  altInt nRet = strcmp (m_szStr, oStr.m_szStr);
  if (nRet == 0) {
    return true;
  }
  else {
    return false;
  }
}

///
/// \brief  != operator
///
/// \param  oStr  [I ] string object
///
/// \return true  other string
/// \return false same string
///
LIBALT_API const altBool altStr::operator !=(const altStr & oStr) const
{
  return (! (oStr == m_szStr));
}

///
/// \brief  < operator
///
/// \param  oStr  [I ] string object
///
/// \return true  
/// \return false 
///
LIBALT_API const altBool altStr::operator <(const altStr & oStr) const
{
  if (this->m_szStr == NULL && oStr.m_szStr != NULL) {
    return true;
  }
  if (this->m_szStr != NULL && oStr.m_szStr == NULL) {
    return false;
  }
  if (this->m_szStr == NULL && oStr.m_szStr == NULL) {
    return false;
  }
  altInt nRet = strcmp (this->m_szStr, oStr.m_szStr);
  if (nRet < 0) {
    return true;
  }
  else {
    return false;
  }
}

///
/// \brief  <= operator
///
/// \param  oStr  [I ] string object
///
/// \return true  
/// \return false 
///
LIBALT_API const altBool altStr::operator <=(const altStr & oStr) const
{
  altInt nRet = strcmp (m_szStr, oStr.m_szStr);
  if (nRet <= 0) {
    return true;
  }
  else {
    return false;
  }
}

///
/// \brief  > operator
///
/// \param  oStr  [I ] string object
///
/// \return true  
/// \return false 
///
LIBALT_API const altBool altStr::operator >(const altStr & oStr) const
{
  altInt nRet = strcmp (m_szStr, oStr.m_szStr);
  if (nRet > 0) {
    return true;
  }
  else {
    return false;
  }
}

///
/// \brief  >= operator
///
/// \param  oStr  [I ] string object
///
/// \return true  
/// \return false 
///
LIBALT_API const altBool altStr::operator >=(const altStr & oStr) const
{
  altInt nRet = strcmp (m_szStr, oStr.m_szStr);
  if (nRet >= 0) {
    return true;
  }
  else {
    return false;
  }
}

///
/// \brief  [] operator
///
/// \param  nIndex [I ] index
///
/// \return character of index position
///
LIBALT_API altChar altStr::operator [](const altUInt nIndex) const
{
  altUInt nLen = GetLen();
  if (nIndex > nLen) {
    return 0x00;
  }
  return (m_szStr[nIndex]);
}

///
/// \brief  format string
///
/// \param  szFormat  [I ] format
/// \param  ...       [I ] parameter
///
/// \return formated string
///
LIBALT_API const altChar * altStr::Format(const altChar * szFormat, ...)
{
  altChar * pBuf = NULL;
  va_list   oArgs;
  altUInt   nNowSize = 0;
  altUInt   nNewSize = BUFSIZ;
  altInt    nRet;

  while (1) {
    nRet = ALT_BASE_EXALLOC (pBuf, nNowSize, nNewSize);
    if (nRet != ALT_SUCCESS) {
      ALT_BASE_FREE (pBuf);
      return NULL;
    }
    nNowSize = nNewSize;

    va_start (oArgs, szFormat);
    nRet = alt_vsnprintf (pBuf, nNowSize, szFormat, oArgs);
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
  ALT_BASE_STRALLOC (m_szStr, pBuf);
  ALT_BASE_FREE (pBuf);

  return m_szStr;
}

///
/// \brief  Get C styte string
///
/// \return pointer of string
///
LIBALT_API const altChar * altStr::GetCStr() const
{
  return m_szStr;
}

///
/// \brief  Get string length
///
/// \return string length
///
LIBALT_API const altUInt altStr::GetLen() const
{
  altUInt nLen = static_cast<altUInt>(strlen (m_szStr));
  return nLen;
}

///
/// \brief  left trim
///
/// \return left trimed string
///
LIBALT_API const altChar * altStr::LTrim()
{
  altChar * p = m_szStr;
  altUInt   nLen = GetLen();

  if (nLen == 0) {
    return m_szStr;
  }

  for (altUInt i = 0; isspace (* p) && i <= nLen; i++) {
    p++;
  }

  if (* p == 0x00) {
    return m_szStr;
  }

  nLen = static_cast<altUInt>(strlen (p));
  memmove (m_szStr, p, nLen + 1);

  altChar * pNewPtr = NULL;
  ALT_BASE_STRALLOC (pNewPtr, m_szStr);
  ALT_BASE_FREE (m_szStr);
  m_szStr = pNewPtr;
  return m_szStr;
}

///
/// \brief  right trim
///
/// \return right trimed string
///
LIBALT_API const altChar * altStr::RTrim()
{
  altUInt   nLen = GetLen();
  
  if (nLen == 0) {
    return m_szStr;
  }

  altChar * p = & m_szStr[nLen - 1];

  for (altUInt i = 0; i < nLen && isspace (* p); i++) {
    p--;
  }
  p++;
  (* p) = 0x00;

  altChar * pNewPtr = NULL;
  ALT_BASE_STRALLOC (pNewPtr, m_szStr);
  ALT_BASE_FREE (m_szStr);
  m_szStr = pNewPtr;
  return m_szStr;
}

///
/// \brief  trim
///
/// \return trimed string
///
LIBALT_API const altChar * altStr::Trim()
{
  LTrim();
  RTrim();
  return m_szStr;
}

///
/// \brief  to upper string
///
/// \return uppered string
///
LIBALT_API const altChar * altStr::ToUpper()
{
  altUInt nLen = GetLen();
  for (altUInt i = 0; i < nLen; i++) {
    m_szStr[i] = toupper (m_szStr[i]);
  }
  return m_szStr;
}

///
/// \brief  to lower string
///
/// \return lowered string
///
LIBALT_API const altChar * altStr::ToLower()
{
  altUInt nLen = GetLen();
  for (altUInt i = 0; i < nLen; i++) {
    m_szStr[i] = tolower (m_szStr[i]);
  }
  return m_szStr;
}

///
/// \brief  Search string
///
/// \param  sStr  [I ] search string
///
/// \return found index
/// \return -1  not found
///
LIBALT_API altInt altStr::Find(const altStr & sStr) const
{
  /// Using Boyer-Moore Algorithm
  altUInt aSkip[256];
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
LIBALT_API altInt altStr::FindLastOf(const altStr & sStr) const
{
  /// Using Boyer-Moore Algorithm
  altUInt aSkip[256];
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
LIBALT_API altInt altStr::FindChar(const altStr & sCharList) const
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
/// \brief  Search character
///
/// \param  nBegin     [I ] begin index
/// \param  sCharList  [I ] character list
///
/// \return found index
/// \return -1  not found
///
LIBALT_API altInt altStr::FindChar(const altUInt nBegin, const altStr & sCharList) const
{
  altUInt nLen = GetLen();
  altUInt nListLen = sCharList.GetLen();

  for (altUInt i = nBegin; i < nLen; i++) {
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
LIBALT_API altInt altStr::FindLastOfChar(const altStr & sCharList) const
{
  altUInt nLen = GetLen();
  if (nLen == 0) {
    return (-1);
  }

  altUInt nListLen = sCharList.GetLen();

  for (altUInt i = nLen - 1; i >= 0; i--) {
    for (altUInt j = 0; j < nListLen; j++) {
      if (m_szStr[i] == sCharList[j]) {
        return (i);
      }
    }
    if (i == 0) {
      break;
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
LIBALT_API altStr altStr::SubStr(const altUInt nIndex) const
{
  altStr sSubStr;

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
LIBALT_API altStr altStr::SubStr(const altUInt nBegin, const altUInt nEnd) const
{
  if (nBegin > nEnd) {
    return "";
  }
  altChar * pSubStr = NULL;
  ALT_BASE_STRALLOC (pSubStr, m_szStr);

  // no memory
  if (pSubStr == NULL) {
    return "";
  }

  // Revision end index
  altUInt nLen = GetLen();

  altUInt nRealEnd = nEnd;
  if (nRealEnd >= nLen) {
    nRealEnd = nLen - 1;
  }

  altUInt nSubStrLen = nRealEnd - nBegin + 1;

  // create sub string
  memmove (pSubStr, & pSubStr[nBegin], nSubStrLen);
  pSubStr[nSubStrLen] = 0x00;

  altStr sSubStr = pSubStr;
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
LIBALT_API altUInt altStr::Replace(const altStr & sTarget, const altStr & sReplaced)
{
  altInt  nIndex = this->Find (sTarget);
  if (nIndex < 0) {
    return (0);
  }

  if (sTarget.GetLen() != sReplaced.GetLen()) {
    altUInt   nNowSize = static_cast<altUInt>(strlen (m_szStr) + 1);
    altUInt   nNewSize = nNowSize + (sReplaced.GetLen() - sTarget.GetLen());
    altChar * pPtr = NULL;
    
    altUInt nRet = ALT_BASE_MALLOC (pPtr, nNewSize);
    if (nRet != ALT_SUCCESS) {
      return (0);
    }
    if (nIndex > 0) {
      memcpy (pPtr, m_szStr, nIndex);
    }
    memcpy (& pPtr[nIndex], sReplaced.GetCStr(), sReplaced.GetLen());
    memcpy (& pPtr[nIndex + sReplaced.GetLen()], & m_szStr[nIndex + sTarget.GetLen()], nNowSize - (nIndex + sTarget.GetLen()));

    ALT_BASE_FREE (m_szStr);
    m_szStr = pPtr;
  }
  else {
    memcpy (& m_szStr[nIndex], sReplaced.GetCStr(), sReplaced.GetLen());
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
LIBALT_API altUInt altStr::ReplaceAll(const altStr & sTarget, const altStr & sReplaced)
{
  altUInt nRet;
  altUInt nCount = 0;
  while ((nRet = Replace (sTarget, sReplaced)) == 1) {
    nCount++;
  }
  return (nCount);
}

///
/// \brief  Separate string
///
/// \param  sSeparator [I ] Separator character list
///
/// \return Separated string list
///
LIBALT_API altStrList altStr::Separate(const altStr & sSeparator) const
{
  altStrList  oList;
  altInt      nBegin = 0;
  altInt      nEnd;
  altStr      sTmp;

  while ((nEnd = this->FindChar (nBegin, sSeparator)) > 0) {
	  sTmp = this->SubStr (nBegin, nEnd - 1);
	  oList.push_back (sTmp);
      nBegin = nEnd + 1;
  }
  sTmp = this->SubStr (nBegin);
  oList.push_back (sTmp);

  return (oList);
}

///
/// \brief  Get Boolean Value
///
/// \return Boolean Value
///
LIBALT_API altBool altStr::ToBool() const
{
  return ((* this) == "true");
}

///
/// \brief  Get Byte Value
///
/// \return Byte Value
///
LIBALT_API altByte altStr::ToByte() const
{
  altByte nValue = 0;
#ifdef ALT_WIN
  ::sscanf_s (m_szStr, "%hhu", & nValue);
#endif
#ifdef ALT_LINUX
  ::sscanf (m_szStr, "%hhu", & nValue);
#endif
  return (nValue);
}

///
/// \brief  Get Short Value
///
/// \return Short Value
///
LIBALT_API altShort altStr::ToShort() const
{
  altShort nValue = 0;
#ifdef ALT_WIN
  ::sscanf_s (m_szStr, "%hd", & nValue);
#endif
#ifdef ALT_LINUX
  ::sscanf (m_szStr, "%hd", & nValue);
#endif
  return (nValue);
}

///
/// \brief  Get Unsigned Short Value
///
/// \return Unsigned Short Value
///
LIBALT_API altUShort altStr::ToUShort() const
{
  altUShort nValue = 0;
#ifdef ALT_WIN
  ::sscanf_s (m_szStr, "%hu", & nValue);
#endif
#ifdef ALT_LINUX
  ::sscanf (m_szStr, "%hu", & nValue);
#endif
  return (nValue);
}

///
/// \brief  Get Int Value
///
/// \return Int Value
///
LIBALT_API altInt altStr::ToInt() const
{
  altInt nValue = 0;
#ifdef ALT_WIN
  ::sscanf_s (m_szStr, "%d", & nValue);
#endif
#ifdef ALT_LINUX
  ::sscanf (m_szStr, "%d", & nValue);
#endif
  return (nValue);
}

///
/// \brief  Get Unsigned Int Value
///
/// \return Unsinged Int Value
///
LIBALT_API altUInt altStr::ToUInt() const
{
  altUInt nValue = 0;
#ifdef ALT_WIN
  ::sscanf_s (m_szStr, "%u", & nValue);
#endif
#ifdef ALT_LINUX
  ::sscanf (m_szStr, "%u", & nValue);
#endif
  return (nValue);
}

///
/// \brief  Get Long Value
///
/// \return Long Value
///
LIBALT_API altLong altStr::ToLong() const
{
  altLong nValue = 0;
#ifdef ALT_WIN
  ::sscanf_s (m_szStr, "%ld", & nValue);
#endif
#ifdef ALT_LINUX
  ::sscanf (m_szStr, "%ld", & nValue);
#endif
  return (nValue);
}

///
/// \brief  Get Unsigned Long Value
///
/// \return Unsinged Long Value
///
LIBALT_API altULong altStr::ToULong() const
{
  altULong nValue = 0;
#ifdef ALT_WIN
  ::sscanf_s (m_szStr, "%lu", & nValue);
#endif
#ifdef ALT_LINUX
  ::sscanf (m_szStr, "%lu", & nValue);
#endif
  return (nValue);
}

///
/// \brief  Get DWORD Value
///
/// \return DWORD Value
///
LIBALT_API DWORD altStr::ToDWORD() const
{
  return (this->ToULong());
}

///
/// \brief  Get Long Long Value
///
/// \return Long Long Value
///
LIBALT_API altLongLong altStr::ToLongLong() const
{
  altLongLong nValue = 0;
#ifdef ALT_WIN
  ::sscanf_s (m_szStr, "%lld", & nValue);
#endif
#ifdef ALT_LINUX
  ::sscanf (m_szStr, "%lld", & nValue);
#endif
  return (nValue);
}

///
/// \brief  Get Unsigned Long Long Value
///
/// \return Unsigned Long Long Value
///
LIBALT_API altULongLong altStr::ToULongLong() const
{
  altULongLong nValue = 0;
#ifdef ALT_WIN
  ::sscanf_s (m_szStr, "%llu", & nValue);
#endif
#ifdef ALT_LINUX
  ::sscanf (m_szStr, "%llu", & nValue);
#endif
  return (nValue);
}

///
/// \brief  Get float Value
///
/// \return float Value
///
LIBALT_API altFloat altStr::ToFloat() const
{
  altFloat nValue = 0;
#ifdef ALT_WIN
  ::sscanf_s (m_szStr, "%f", & nValue);
#endif
#ifdef ALT_LINUX
  ::sscanf (m_szStr, "%f", & nValue);
#endif
  return (nValue);
}

///
/// \brief  Get double Value
///
/// \return double Value
///
LIBALT_API altDouble altStr::ToDouble() const
{
  altDouble nValue = 0;
#ifdef ALT_WIN
  ::sscanf_s (m_szStr, "%lf", & nValue);
#endif
#ifdef ALT_LINUX
  ::sscanf (m_szStr, "%lf", & nValue);
#endif
  return (nValue);
}

///
/// \brief  Set Char Value
///
/// \param  nVal  [I ] value
///
/// \return this object
///
LIBALT_API altStr & altStr::SetChar(const altChar nVal)
{
  this->Format ("%hhd", nVal);
  return (* this);
}

///
/// \brief  Set UChar Value
///
/// \param  nVal  [I ] value
///
/// \return this object
///
LIBALT_API altStr & altStr::SetUChar(const altUChar nVal)
{
  this->Format ("%hhu", nVal);
  return (* this);
}

///
/// \brief  Set Byte Value
///
/// \param  nVal  [I ] value
///
/// \return this object
///
LIBALT_API altStr & altStr::SetByte(const altByte nVal)
{
  this->Format ("%hhu", nVal);
  return (* this);
}

///
/// \brief  Set Short Value
///
/// \param  nVal  [I ] value
///
/// \return this object
///
LIBALT_API altStr & altStr::SetShort(const altShort nVal)
{
  this->Format ("%hd", nVal);
  return (* this);
}

///
/// \brief  Set UShort Value
///
/// \param  nVal  [I ] value
///
/// \return this object
///
LIBALT_API altStr & altStr::SetUShort(const altUShort nVal)
{
  this->Format ("%hu", nVal);
  return (* this);
}

///
/// \brief  Set Int Value
///
/// \param  nVal  [I ] value
///
/// \return this object
///
LIBALT_API altStr & altStr::SetInt(const altInt nVal)
{
  this->Format ("%d", nVal);
  return (* this);
}

///
/// \brief  Set UInt Value
///
/// \param  nVal  [I ] value
///
/// \return this object
///
LIBALT_API altStr & altStr::SetUInt(const altUInt nVal)
{
  this->Format ("%u", nVal);
  return (* this);
}

///
/// \brief  Set Long Value
///
/// \param  nVal  [I ] value
///
/// \return this object
///
LIBALT_API altStr & altStr::SetLong(const altLong nVal)
{
  this->Format ("%ld", nVal);
  return (* this);
}

///
/// \brief  Set ULong Value
///
/// \param  nVal  [I ] value
///
/// \return this object
///
LIBALT_API altStr & altStr::SetULong(const altULong nVal)
{
  this->Format ("%lu", nVal);
  return (* this);
}

///
/// \brief  Set DWORD Value
///
/// \param  nVal  [I ] value
///
/// \return this object
///
LIBALT_API altStr & altStr::SetDWORD(const DWORD nVal)
{
  this->Format ("%lu", nVal);
  return (* this);
}

///
/// \brief  Set LongLong Value
///
/// \param  nVal  [I ] value
///
/// \return this object
///
LIBALT_API altStr & altStr::SetLongLong(const altLongLong nVal)
{
  this->Format ("%lld", nVal);
  return (* this);
}

///
/// \brief  Set ULongLong Value
///
/// \param  nVal  [I ] value
///
/// \return this object
///
LIBALT_API altStr & altStr::SetULongLong(const altULongLong nVal)
{
  this->Format ("%llu", nVal);
  return (* this);
}

///
/// \brief  Set Float Value
///
/// \param  nVal  [I ] value
///
/// \return this object
///
LIBALT_API altStr & altStr::SetFloat(const altFloat nVal)
{
  this->Format ("%f", nVal);
  return (* this);
}

///
/// \brief  Set Double Value
///
/// \param  nVal  [I ] value
///
/// \return this object
///
LIBALT_API altStr & altStr::SetDouble(const altDouble nVal)
{
  this->Format ("%lf", nVal);
  return (* this);
}

///
/// \brief  is SJIS string
///
/// \return true  SJIS
/// \return false not SJIS
///
LIBALT_API const altBool altStr::IsSJIS() const
{
  altUChar *  p = (altUChar *)m_szStr;
  altBool     b2ByteChar = false;
  altUInt     nSJISCount = 0;
  altUInt     n2ByteCount = 0;
  altUInt     nLen = GetLen();

  for (altUInt i = 0; i < nLen; i++) {
    // first byte of two byte char
    if ((b2ByteChar) == false && ((* p) >= 0x80)) {
      // is SJIS char
      if ((* p) < 0xA1) {
        nSJISCount++;
      }
      n2ByteCount++;
      b2ByteChar = true;
    }
    else {
      b2ByteChar = false;
    }
    p++;
  }

  if ((n2ByteCount * 50 / 100) < nSJISCount) {
    return true;
  }
  return false;
}

///
/// \brief  + operator
///
/// \param  oLeftStr  [I ] Left String Parameter
/// \param  oRightStr [I ] Right String Parameter
///
LIBALT_API altStr operator + (const altStr & oLeftStr, const altStr & oRightStr)
{
  altStr oStr = oLeftStr;
  oStr += oRightStr;
  return oStr;
}

///
/// \brief  == operator
///
/// \param  szLeftStr [I ] Left String Parameter
/// \param  oRightStr [I ] Right String Parameter
///
/// \return true same string
/// \return false not same string
///
LIBALT_API altBool operator == (const altChar * szLeftStr, const altStr & oRightStr)
{
  return (oRightStr == szLeftStr);
}

///
/// \brief  != operator
///
/// \param  oLeftStr  [I ] Left String Parameter
/// \param  oRightStr [I ] Right String Parameter
///
/// \return true not same string
/// \return false same string
///
LIBALT_API altBool operator != (const altChar * szLeftStr, const altStr & oRightStr)
{
  return (oRightStr != szLeftStr);
}

///
/// \brief  < operator
///
/// \param  oLeftStr  [I ] Left String Parameter
/// \param  oRightStr [I ] Right String Parameter
///
/// \return true  Left String <  Right String
/// \return false Left String >= Right String
///
LIBALT_API altBool operator < (const altChar * szLeftStr, const altStr & oRightStr)
{
  return (oRightStr > szLeftStr);
}

///
/// \brief  <= operator
///
/// \param  oLeftStr  [I ] Left String Parameter
/// \param  oRightStr [I ] Right String Parameter
///
/// \return true  Left String <=  Right String
/// \return false Left String > Right String
///
LIBALT_API altBool operator <= (const altChar * szLeftStr, const altStr & oRightStr)
{
  return (oRightStr >= szLeftStr);
}

///
/// \brief  > operator
///
/// \param  oLeftStr  [I ] Left String Parameter
/// \param  oRightStr [I ] Right String Parameter
///
/// \return true  Left String >  Right String
/// \return false Left String <= Right String
///
LIBALT_API altBool operator > (const altChar * szLeftStr, const altStr & oRightStr)
{
  return (oRightStr < szLeftStr);
}

///
/// \brief  >= operator
///
/// \param  oLeftStr  [I ] Left String Parameter
/// \param  oRightStr [I ] Right String Parameter
///
/// \return true  Left String >=  Right String
/// \return false Left String < Right String
///
LIBALT_API altBool operator >= (const altChar * szLeftStr, const altStr & oRightStr)
{
  return (oRightStr <= szLeftStr);
}

