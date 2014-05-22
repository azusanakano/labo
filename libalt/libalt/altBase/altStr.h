#ifndef ALTSTR_H
#define ALTSTR_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altStr.h
 * \brief   String class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altBase.h>

#include <vector>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
class altStr;
typedef std::vector<altStr> altStrList;

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  String
///
class altStr : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altStr();

  ///
  /// \brief  Constructor
  ///
  /// \param  szStr [I ] string
  ///
  LIBALT_API altStr(const altChar * szStr);

  ///
  /// \brief  Copy Constructor
  ///
  /// \param  szStr [I ] string
  ///
  LIBALT_API altStr(const altStr & oStr);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altStr();

  ///
  /// \brief  = operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return this object
  ///
  LIBALT_API altStr &  operator =(const altStr & oStr);

  ///
  /// \brief  + operator
  ///
  /// \param  oStr  [I ] string object
  ///
  LIBALT_API const altStr & operator +(const altStr & oStr);

  ///
  /// \brief  += operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return this object
  ///
  LIBALT_API const altStr & operator +=(const altStr & oStr);

  ///
  /// \brief  == operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return true  same string
  /// \return false other string
  ///
  LIBALT_API const altBool operator ==(const altStr & oStr) const;

  ///
  /// \brief  != operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return true  other string
  /// \return false same string
  ///
  LIBALT_API const altBool operator !=(const altStr & oStr) const;

  ///
  /// \brief  < operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return true  
  /// \return false 
  ///
  LIBALT_API const altBool operator <(const altStr & oStr) const;

  ///
  /// \brief  <= operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return true  
  /// \return false 
  ///
  LIBALT_API const altBool operator <=(const altStr & oStr) const;

  ///
  /// \brief  > operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return true  
  /// \return false 
  ///
  LIBALT_API const altBool operator >(const altStr & oStr) const;

  ///
  /// \brief  >= operator
  ///
  /// \param  oStr  [I ] string object
  ///
  /// \return true  
  /// \return false 
  ///
  LIBALT_API const altBool operator >=(const altStr & oStr) const;

  ///
  /// \brief  [] operator
  ///
  /// \param  nIndex [I ] index
  ///
  /// \return character of index position
  ///
  LIBALT_API altChar operator [](const altUInt nIndex) const;

  ///
  /// \brief  format string
  ///
  /// \param  szFormat  [I ] format
  /// \param  ...       [I ] parameter
  ///
  /// \return formated string
  ///
  LIBALT_API const altChar * Format(const altChar * szFormat, ...);

  ///
  /// \brief  Get C styte string
  ///
  /// \return pointer of string
  ///
  LIBALT_API const altChar * GetCStr() const;

  ///
  /// \brief  Get string length
  ///
  /// \return string length
  ///
  LIBALT_API const altUInt GetLen() const;

  ///
  /// \brief  left trim
  ///
  /// \return left trimed string
  ///
  LIBALT_API const altChar * LTrim();

  ///
  /// \brief  right trim
  ///
  /// \return right trimed string
  ///
  LIBALT_API const altChar * RTrim();

  ///
  /// \brief  trim
  ///
  /// \return trimed string
  ///
  LIBALT_API const altChar * Trim();

  ///
  /// \brief  to upper string
  ///
  /// \return uppered string
  ///
  LIBALT_API const altChar * ToUpper();

  ///
  /// \brief  to lower string
  ///
  /// \return lowered string
  ///
  LIBALT_API const altChar * ToLower();

  ///
  /// \brief  Search string
  ///
  /// \param  sStr  [I ] search string
  ///
  /// \return found index
  /// \return -1  not found
  ///
  LIBALT_API altInt Find(const altStr & sStr) const;

  ///
  /// \brief  Search String from last
  ///
  /// \param  sStr  [I ] search string
  ///
  /// \return found index
  /// \return -1    not found
  ///
  LIBALT_API altInt FindLastOf(const altStr & sStr) const;

  ///
  /// \brief  Search character
  ///
  /// \param  sCharList  [I ] character list
  ///
  /// \return found index
  /// \return -1  not found
  ///
  LIBALT_API altInt FindChar(const altStr & sCharList) const;

  ///
  /// \brief  Search character
  ///
  /// \param  nBegin     [I ] begin index
  /// \param  sCharList  [I ] character list
  ///
  /// \return found index
  /// \return -1  not found
  ///
  LIBALT_API altInt FindChar(const altUInt nBegin, const altStr & sCharList) const;

  ///
  /// \brief  Search character from last
  ///
  /// \param  sCharList  [I ] character list
  ///
  /// \return found index
  /// \return -1  not found
  ///
  LIBALT_API altInt FindLastOfChar(const altStr & sCharList) const;

  ///
  /// \brief  sub string
  ///
  /// \param  nIndex  [I ] begin index
  ///
  /// \return string
  ///
  LIBALT_API altStr SubStr(const altUInt nIndex) const;

  ///
  /// \brief  sub string
  ///
  /// \param  nBegin  [I ] begin index
  /// \param  nEnd    [I ] end index
  ///
  /// \return string
  ///
  LIBALT_API altStr SubStr(const altUInt nBegin, const altUInt nEnd) const;

  ///
  /// \brief  replace
  ///
  /// \param  sTarget   [I ] target string
  /// \param  sReplaced [I ] replace string
  ///
  /// \return 0 target not found
  /// \return 1 target replaced
  ///
  LIBALT_API altUInt Replace(const altStr & sTarget, const altStr & sReplaced);

  ///
  /// \brief  replace all
  ///
  /// \param  sTarget   [I ] target string
  /// \param  sReplaced [I ] replace string
  ///
  /// \return replaced count
  ///
  LIBALT_API altUInt ReplaceAll(const altStr & sTarget, const altStr & sReplaced);

  ///
  /// \brief  Separate string
  ///
  /// \param  sSeparator [I ] Separator character list
  ///
  /// \return Separated string list
  ///
  LIBALT_API altStrList Separate(const altStr & sSeparator) const;

  ///
  /// \brief  Get Boolean Value
  ///
  /// \return Boolean Value
  ///
  LIBALT_API altBool ToBool() const;

  ///
  /// \brief  Get Byte Value
  ///
  /// \return Byte Value
  ///
  LIBALT_API altByte ToByte() const;

  ///
  /// \brief  Get Short Value
  ///
  /// \return Short Value
  ///
  LIBALT_API altShort ToShort() const;

  ///
  /// \brief  Get Unsigned Short Value
  ///
  /// \return Unsigned Short Value
  ///
  LIBALT_API altUShort ToUShort() const;

  ///
  /// \brief  Get Int Value
  ///
  /// \return Int Value
  ///
  LIBALT_API altInt ToInt() const;

  ///
  /// \brief  Get Unsigned Int Value
  ///
  /// \return Unsinged Int Value
  ///
  LIBALT_API altUInt ToUInt() const;

  ///
  /// \brief  Get Long Value
  ///
  /// \return Long Value
  ///
  LIBALT_API altLong ToLong() const;

  ///
  /// \brief  Get Unsigned Long Value
  ///
  /// \return Unsinged Long Value
  ///
  LIBALT_API altULong ToULong() const;

  ///
  /// \brief  Get DWORD Value
  ///
  /// \return DWORD Value
  ///
  LIBALT_API DWORD ToDWORD() const;

  ///
  /// \brief  Get Long Long Value
  ///
  /// \return Long Long Value
  ///
  LIBALT_API altLongLong ToLongLong() const;

  ///
  /// \brief  Get Unsigned Long Long Value
  ///
  /// \return Unsigned Long Long Value
  ///
  LIBALT_API altULongLong ToULongLong() const;

  ///
  /// \brief  Get float Value
  ///
  /// \return float Value
  ///
  LIBALT_API altFloat ToFloat() const;

  ///
  /// \brief  Get double Value
  ///
  /// \return double Value
  ///
  LIBALT_API altDouble ToDouble() const;

  ///
  /// \brief  Set Char Value
  ///
  /// \param  nVal  [I ] value
  ///
  /// \return this object
  ///
  LIBALT_API altStr & SetChar(const altChar nVal);

  ///
  /// \brief  Set UChar Value
  ///
  /// \param  nVal  [I ] value
  ///
  /// \return this object
  ///
  LIBALT_API altStr & SetUChar(const altUChar nVal);

  ///
  /// \brief  Set Byte Value
  ///
  /// \param  nVal  [I ] value
  ///
  /// \return this object
  ///
  LIBALT_API altStr & SetByte(const altByte nVal);

  ///
  /// \brief  Set Short Value
  ///
  /// \param  nVal  [I ] value
  ///
  /// \return this object
  ///
  LIBALT_API altStr & SetShort(const altShort nVal);

  ///
  /// \brief  Set UShort Value
  ///
  /// \param  nVal  [I ] value
  ///
  /// \return this object
  ///
  LIBALT_API altStr & SetUShort(const altUShort nVal);

  ///
  /// \brief  Set Int Value
  ///
  /// \param  nVal  [I ] value
  ///
  /// \return this object
  ///
  LIBALT_API altStr & SetInt(const altInt nVal);

  ///
  /// \brief  Set UInt Value
  ///
  /// \param  nVal  [I ] value
  ///
  /// \return this object
  ///
  LIBALT_API altStr & SetUInt(const altUInt nVal);

  ///
  /// \brief  Set Long Value
  ///
  /// \param  nVal  [I ] value
  ///
  /// \return this object
  ///
  LIBALT_API altStr & SetLong(const altLong nVal);

  ///
  /// \brief  Set ULong Value
  ///
  /// \param  nVal  [I ] value
  ///
  /// \return this object
  ///
  LIBALT_API altStr & SetULong(const altULong nVal);

  ///
  /// \brief  Set DWORD Value
  ///
  /// \param  nVal  [I ] value
  ///
  /// \return this object
  ///
  LIBALT_API altStr & SetDWORD(const DWORD nVal);

  ///
  /// \brief  Set LongLong Value
  ///
  /// \param  nVal  [I ] value
  ///
  /// \return this object
  ///
  LIBALT_API altStr & SetLongLong(const altLongLong nVal);

  ///
  /// \brief  Set ULongLong Value
  ///
  /// \param  nVal  [I ] value
  ///
  /// \return this object
  ///
  LIBALT_API altStr & SetULongLong(const altULongLong nVal);

  ///
  /// \brief  Set Float Value
  ///
  /// \param  nVal  [I ] value
  ///
  /// \return this object
  ///
  LIBALT_API altStr & SetFloat(const altFloat nVal);

  ///
  /// \brief  Set Double Value
  ///
  /// \param  nVal  [I ] value
  ///
  /// \return this object
  ///
  LIBALT_API altStr & SetDouble(const altDouble nVal);

  ///
  /// \brief  is SJIS string
  ///
  /// \return true  SJIS
  /// \return false not SJIS
  ///
  LIBALT_API const altBool IsSJIS() const;

private:
  altChar * m_szStr;  ///< string buffer
};

///
/// \brief  + operator
///
/// \param  oLeftStr  [I ] Left String Parameter
/// \param  oRightStr [I ] Right String Parameter
///
/// \return + Operated String
///
LIBALT_API altStr operator + (const altStr & oLeftStr, const altStr & oRightStr);

///
/// \brief  == operator
///
/// \param  oLeftStr  [I ] Left String Parameter
/// \param  oRightStr [I ] Right String Parameter
///
/// \return true same string
/// \return false not same string
///
LIBALT_API altBool operator == (const altChar * szLeftStr, const altStr & oRightStr);

///
/// \brief  != operator
///
/// \param  oLeftStr  [I ] Left String Parameter
/// \param  oRightStr [I ] Right String Parameter
///
/// \return true not same string
/// \return false same string
///
LIBALT_API altBool operator != (const altChar * szLeftStr, const altStr & oRightStr);

///
/// \brief  < operator
///
/// \param  oLeftStr  [I ] Left String Parameter
/// \param  oRightStr [I ] Right String Parameter
///
/// \return true  Left String <  Right String
/// \return false Left String >= Right String
///
LIBALT_API altBool operator < (const altChar * szLeftStr, const altStr & oRightStr);

///
/// \brief  <= operator
///
/// \param  oLeftStr  [I ] Left String Parameter
/// \param  oRightStr [I ] Right String Parameter
///
/// \return true  Left String <=  Right String
/// \return false Left String > Right String
///
LIBALT_API altBool operator <= (const altChar * szLeftStr, const altStr & oRightStr);

///
/// \brief  > operator
///
/// \param  oLeftStr  [I ] Left String Parameter
/// \param  oRightStr [I ] Right String Parameter
///
/// \return true  Left String >  Right String
/// \return false Left String <= Right String
///
LIBALT_API altBool operator > (const altChar * szLeftStr, const altStr & oRightStr);

///
/// \brief  >= operator
///
/// \param  oLeftStr  [I ] Left String Parameter
/// \param  oRightStr [I ] Right String Parameter
///
/// \return true  Left String >=  Right String
/// \return false Left String < Right String
///
LIBALT_API altBool operator >= (const altChar * szLeftStr, const altStr & oRightStr);

#endif  // ALTSTR_H
