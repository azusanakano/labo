/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDateTime.cpp
 * \brief   Datetime class
 * \date    2013
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altDateTime.h"

#ifdef ALT_LINUX
  #include <sys/time.h>
  #include <time.h>
#endif

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/
const altByte altDateTime::aDayTable[] = {
  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
};

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altDateTime::altDateTime()
{
#ifdef ALT_WIN
  SYSTEMTIME now;
  GetLocalTime (& now);
  m_nYear = now.wYear;
  m_nMonth = static_cast<altByte>(now.wMonth);
  m_nDay = static_cast<altByte>(now.wDay);
  m_nHour = static_cast<altByte>(now.wHour);
  m_nMin = static_cast<altByte>(now.wMinute);
  m_nSec = static_cast<altByte>(now.wSecond);
  m_nMilliSec = now.wMilliseconds;
#endif

#ifdef ALT_LINUX
	struct timeval  now;
	struct tm       local;

	gettimeofday (& now, NULL);
	localtime_r (& now.tv_sec, & local);

	m_nYear = (local.tm_year + 1900);
	m_nMonth = (local.tm_mon + 1);
	m_nDay = local.tm_mday;
	m_nHour = local.tm_hour;
	m_nMin = local.tm_min;
	m_nSec = local.tm_sec;
	m_nMilliSec = (now.tv_usec / 1000);
#endif
}

///
/// \brief  Destructor
///
LIBALT_API altDateTime::~altDateTime()
{
}

///
/// \brief  Format to string
///
/// \param  sFormat [I ] format string
///
/// \return formated string
///
LIBALT_API altStr altDateTime::Format(const altStr & sFormat) const
{
  altStr  sStr = sFormat;
  altStr  sTmp;

  sStr.ReplaceAll ("YYYY", sTmp.Format ("%04d", m_nYear));
  sStr.ReplaceAll ("MM", sTmp.Format ("%02d", m_nMonth));
  sStr.ReplaceAll ("DD", sTmp.Format ("%02d", m_nDay));
  sStr.ReplaceAll ("HH", sTmp.Format ("%02d", m_nHour));
  sStr.ReplaceAll ("MI", sTmp.Format ("%02d", m_nMin));
  sStr.ReplaceAll ("SS", sTmp.Format ("%02d", m_nSec));
  sStr.ReplaceAll ("MS", sTmp.Format ("%03d", m_nMilliSec));

  return sStr;
}

///
/// \brief  Validate date time
///
/// \return true  valid date
/// \return false invalid date
///
LIBALT_API altBool altDateTime::Validate()
{
	if (m_nYear < YEAR_MIN || m_nYear > YEAR_MAX) {
		return (false);
	}
	else if (m_nMonth < MONTH_MIN || m_nMonth > MONTH_MAX) {
		return (false);
	}
	else if ((m_nDay < DAY_MIN) || (m_nDay > DAY_MAX (m_nYear, m_nMonth))) {
		return (false);
	}
	else if ((m_nHour < HOUR_MIN) || (m_nHour > HOUR_MAX)) {
		return (false);
	}
	else if ((m_nMin < MIN_MIN) || (m_nMin > MIN_MAX)) {
		return (false);
	}
	else if ((m_nSec < SEC_MIN) || (m_nSec > SEC_MAX)) {
		return (false);
	}
	else if ((m_nMilliSec < MSEC_MIN) || (m_nMilliSec > MSEC_MAX)) {
		return (false);
	}

  return (true);
}

///
/// \brief  Check Leap Year
///
/// \param  nYear [I ] year
///
/// \return true  Leap Year
/// \return false Not Leap Year
///
LIBALT_API altBool altDateTime::IsLeepYear(const altUShort nYear)
{
	if (((nYear % 4) == 0) && ((nYear % 100) != 0)) {
		return (true);
	}
	else if ((nYear % 400) == 0) {
		return (true);
	}

	return (false);
}

///
/// \brief  Get day by month
///
/// \param  nMonth  [I ] month
///
/// \return number of day by month
///
LIBALT_API altByte altDateTime::GetDayByMonth(const altByte nMonth)
{
  if (nMonth < 1 || nMonth > 12) {
    return (0);
  }
  return (aDayTable[nMonth - 1]);
}
