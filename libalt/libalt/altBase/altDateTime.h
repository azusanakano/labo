#ifndef ALTDATETIME_H
#define ALTDATETIME_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDateTime.h
 * \brief   Date time Class
 * \date    2013
 * \author  NEKO SYSTEM
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altBase.h>
#include <altBase/altStr.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
#define DAY_MONTH(y, m) (((m) == 2 && altDateTime::IsLeepYear (y)) ? 29 : altDateTime::GetDayByMonth (m))

#define YEAR_MIN  0
#define YEAR_MAX  9999
#define MONTH_MIN 1
#define MONTH_MAX 12
#define DAY_MIN   1
#define DAY_MAX(y, m)	(DAY_MONTH ((y) , (m)))
#define HOUR_MIN  0
#define HOUR_MAX  23
#define MIN_MIN   0
#define MIN_MAX   59
#define SEC_MIN   0
#define SEC_MAX   59
#define MSEC_MIN  0
#define MSEC_MAX  999

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Date Time
///
class altDateTime : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altDateTime();
  
  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altDateTime();

  ///
  /// \brief  Format to string
  ///
  /// \param  sFormat [I ] format string
  ///
  /// \return formated string
  ///
  LIBALT_API altStr Format(const altStr & sFormat) const;

  ///
  /// \brief  Validate date time
  ///
  /// \return true  valid date
  /// \return false invalid date
  ///
  LIBALT_API altBool Validate();

  ///
  /// \brief  Check Leap Year
  ///
  /// \param  nYear [I ] year
  ///
  /// \return true  Leap Year
  /// \return false Not Leap Year
  ///
  LIBALT_API static altBool IsLeepYear(const altUShort nYear);

  ///
  /// \brief  Get day by month
  ///
  /// \param  nMonth  [I ] month
  ///
  /// \return number of day by month
  ///
  LIBALT_API static altByte GetDayByMonth(const altByte nMonth);

  altUShort   m_nYear;      ///< Year
  altByte     m_nMonth;     ///< Month
  altByte     m_nDay;       ///< Day
  altByte     m_nHour;      ///< Hour
  altByte     m_nMin;       ///< Min
  altByte     m_nSec;       ///< Second
  altUShort   m_nMilliSec;  ///< milli-second

private:
  static const altByte aDayTable[]; ///< month day table
};

#endif  // ALTBASELOG_H
