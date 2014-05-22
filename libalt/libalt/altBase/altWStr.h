#ifndef ALTWSTR_H
#define ALTWSTR_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altWStr.h
 * \brief   Wide string class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altBase.h>

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  String
///
class altWStr : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altWStr();

  ///
  /// \brief  Constructor
  ///
  /// \param  c [I ] Character
  ///
  LIBALT_API altWStr(const altWChar c);

  ///
  /// \brief  Constructor
  ///
  /// \param  szStr [I ] string
  ///
  LIBALT_API altWStr(const altWChar * szStr);

  ///
  /// \brief  Constructor
  ///
  /// \param  szStr [I ] string
  ///
  LIBALT_API altWStr(const altChar * szStr);

  ///
  /// \brief  Constructor
  ///
  /// \param  szStr [I ] string
  ///
  LIBALT_API altWStr(const wchar_t * szStr);

  ///
  /// \brief  Copy Constructor
  ///
  /// \param  szStr [I ] string
  ///
  LIBALT_API altWStr(const altWStr & oStr);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altWStr();
  
  ///
  /// \brief  = operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return this object
  ///
  LIBALT_API altWStr &  operator =(const altWStr & oStr);

  ///
  /// \brief  + operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return this object
  ///
  LIBALT_API const altWStr operator +(const altWStr & oStr);

  ///
  /// \brief  += operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return this object
  ///
  LIBALT_API const altWStr & operator +=(const altWStr & oStr);

  ///
  /// \brief  == operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return true  same string
  /// \return false other string
  ///
  LIBALT_API const altBool operator ==(const altWStr & oStr) const;

  ///
  /// \brief  != operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return true  other string
  /// \return false same string
  ///
  LIBALT_API const altBool operator !=(const altWStr & oStr) const;

  ///
  /// \brief  < operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return true  
  /// \return false 
  ///
  LIBALT_API const altBool operator <(const altWStr & oStr) const;

  ///
  /// \brief  <= operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return true  
  /// \return false 
  ///
  LIBALT_API const altBool operator <=(const altWStr & oStr) const;

  ///
  /// \brief  > operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return true  
  /// \return false 
  ///
  LIBALT_API const altBool operator >(const altWStr & oStr) const;
  
  ///
  /// \brief  >= operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return true  
  /// \return false 
  ///
  LIBALT_API const altBool operator >=(const altWStr & oStr) const;

  ///
  /// \brief  [] operator
  ///
  /// \param  nIndex [I ] index
  ///
  /// \return character of index position
  ///
  LIBALT_API altWChar & operator [](const altUInt nIndex) const;

  ///
  /// \brief  Get C styte string
  ///
  /// \return pointer of string
  ///
  LIBALT_API const altWChar * GetCStr() const;

  ///
  /// \brief  Get string length
  ///
  /// \return string length
  ///
  LIBALT_API const altUInt GetLen() const;

  ///
  /// \brief  Get buffer size
  ///
  /// \return buffer size
  ///
  LIBALT_API const altUInt GetSize() const;
  
  ///
  /// \brief  Search string
  ///
  /// \param  sStr  [I ] search string
  ///
  /// \return found index
  /// \return -1  not found
  ///
  LIBALT_API altInt Find(const altWStr & sStr) const;

  ///
  /// \brief  Search String from last
  ///
  /// \param  sStr  [I ] search string
  ///
  /// \return found index
  /// \return -1    not found
  ///
  LIBALT_API altInt FindLastOf(const altWStr & sStr) const;

  ///
  /// \brief  Search character
  ///
  /// \param  sCharList  [I ] character list
  ///
  /// \return found index
  /// \return -1  not found
  ///
  LIBALT_API altInt FindChar(const altWStr & sCharList) const;

  ///
  /// \brief  Search character from last
  ///
  /// \param  sCharList  [I ] character list
  ///
  /// \return found index
  /// \return -1  not found
  ///
  LIBALT_API altInt FindLastOfChar(const altWStr & sCharList) const;

  ///
  /// \brief  sub string
  ///
  /// \param  nIndex  [I ] begin index
  ///
  /// \return string
  ///
  LIBALT_API altWStr SubStr(const altUInt nIndex) const;

  ///
  /// \brief  sub string
  ///
  /// \param  nBegin  [I ] begin index
  /// \param  nEnd    [I ] end index
  ///
  /// \return string
  ///
  LIBALT_API altWStr SubStr(const altUInt nBegin, const altUInt nEnd) const;

  ///
  /// \brief  replace
  ///
  /// \param  sTarget   [I ] target string
  /// \param  sReplaced [I ] replace string
  ///
  /// \return 0 target not found
  /// \return 1 target replaced
  ///
  LIBALT_API altUInt Replace(const altWStr & sTarget, const altWStr & sReplaced);

  ///
  /// \brief  replace all
  ///
  /// \param  sTarget   [I ] target string
  /// \param  sReplaced [I ] replace string
  ///
  /// \return replaced count
  ///
  LIBALT_API altUInt ReplaceAll(const altWStr & sTarget, const altWStr & sReplaced);

  ///
  /// \brief  Format
  ///
  /// \param  szFormat  [I ] Format
  ///
  /// \return Format string
  ///
  LIBALT_API const altWChar * Format(const wchar_t * szFormat, ...);

  ///
  /// \brief  Delete last character
  ///
  /// \return true  success
  /// \return false failed
  ///
  LIBALT_API altBool DeleteLastChar();

private:
  altWChar *  m_szStr;  ///< string buffer
  altUInt     m_nLen;   ///< string length
};

#endif
