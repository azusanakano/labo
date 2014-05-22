/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altProperty.cpp
 * \brief   Property file class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altProperty.h"
#include "altFile.h"
#include "altBase/altLog.h"
#include "altBase/altStatus.h"

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
///
/// \brief  Get method template
///
/// \param  method  [I ] method name
///
#define ALT_PROPERTY_TO_X(method) \
  altStr * pValue = m_oPropertyDataMap[sKey]; \
  if (pValue == NULL) { \
    return (nDefault); \
  } \
  return (pValue->method());

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altProperty::altProperty()
{
}

///
/// \brief  Destructor
///
LIBALT_API altProperty::~altProperty()
{
}

///
/// \brief  Load Property File
///
/// \param  sFileName [I ] file name
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altProperty::Load(const altStr & sFileName)
{
  alt_t   status;
  altFile oFile;
  altStr  sBuf;
  altChar szBuf[ALT_BUFSIZ];

  status = oFile.Open (sFileName, "r");
  ALT_ERR_RET (status);

  while (true) {
    status = oFile.ReadLine (szBuf, sizeof (szBuf));

    // end of file
    if (status == ALT_S_EOF) {
      status = oFile.Close();
      ALT_LOG (status);
      break;
    }

    // error caused
    if (ALT_IS_ERR (status)) {
      ALT_LOG (status);
      oFile.Close();
      ALT_RET (status);
    }

    sBuf = szBuf;

    // delete comment
    altInt nCommentIndex = sBuf.Find("#");
    if (nCommentIndex > 0 && sBuf[nCommentIndex - 1] != '\\') {
      sBuf = sBuf.SubStr(0, nCommentIndex - 1);
    }

    altInt nEqualIndex = sBuf.Find("=");
    if (nEqualIndex > 0) {
      altStr  sKey = sBuf.SubStr (0, nEqualIndex - 1);
      altStr  sValue = sBuf.SubStr (nEqualIndex + 1);
      sKey.Trim();
      sValue.Trim();
      m_oPropertyDataMap[sKey] = ALT_NEW altStr (sValue);
    }
  }
  oFile.Close();

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get Boolean Value
///
/// \param  sKey      [I ] Key Name
/// \param  bDefault  [I ] Default Value
///
/// \return Boolean Value
///
LIBALT_API altBool altProperty::GetBool(const altStr & sKey, const altBool nDefault)
{
  ALT_PROPERTY_TO_X (ToBool);
}

///
/// \brief  Get Short Value
///
/// \param  sKey      [I ] Key Name
/// \param  nDefault  [I ] Default Value
///
/// \return Short Value
///
LIBALT_API altShort altProperty::GetShort(const altStr & sKey, const altShort nDefault)
{
  ALT_PROPERTY_TO_X (ToShort);
}

///
/// \brief  Get Unsigned Short Value
///
/// \param  sKey      [I ] Key Name
/// \param  nDefault  [I ] Default Value
///
/// \return Unsigned Short Value
///
LIBALT_API altUShort altProperty::GetUShort(const altStr & sKey, const altUShort nDefault)
{
  ALT_PROPERTY_TO_X (ToUShort);
}

///
/// \brief  Get Int Value
///
/// \param  sKey      [I ] Key Name
/// \param  nDefault  [I ] Default Value
///
/// \return Int Value
///
LIBALT_API altInt altProperty::GetInt(const altStr & sKey, const altInt nDefault)
{
  ALT_PROPERTY_TO_X (ToInt);
}

///
/// \brief  Get Unsigned Int Value
///
/// \param  sKey      [I ] Key Name
/// \param  nDefault  [I ] Default Value
///
/// \return Unsigned Int Value
///
LIBALT_API altUInt altProperty::GetUInt(const altStr & sKey, const altUInt nDefault)
{
  ALT_PROPERTY_TO_X (ToUInt);
}
  
///
/// \brief  Get Long Value
///
/// \param  sKey      [I ] Key Name
/// \param  nDefault  [I ] Default Value
///
/// \return Long Value
///
LIBALT_API altLong altProperty::GetLong(const altStr & sKey, const altLong nDefault)
{
  ALT_PROPERTY_TO_X (ToLong);
}

///
/// \brief  Get Unsigned Long Value
///
/// \param  sKey      [I ] Key Name
/// \param  nDefault  [I ] Default Value
///
/// \return Unsigned Long Value
///
LIBALT_API altULong altProperty::GetULong(const altStr & sKey, const altULong nDefault)
{
  ALT_PROPERTY_TO_X (ToULong);
}

///
/// \brief  Get Long Long Value
///
/// \param  sKey      [I ] Key Name
/// \param  nDefault  [I ] Default Value
///
/// \return Long Long Value
///
LIBALT_API altLongLong altProperty::GetLongLong(const altStr & sKey, const altLongLong nDefault)
{
  ALT_PROPERTY_TO_X (ToLongLong);
}

///
/// \brief  Get Unsigned Long Long Value
///
/// \param  sKey      [I ] Key Name
/// \param  nDefault  [I ] Default Value
///
/// \return Unsigned Long Long Value
///
LIBALT_API altULongLong altProperty::GetULongLong(const altStr & sKey, const altULongLong nDefault)
{
  ALT_PROPERTY_TO_X (ToULongLong);
}

///
/// \brief  Get Float Value
///
/// \param  sKey      [I ] Key Name
/// \param  nDefault  [I ] Default Value
///
/// \return Float Value
///
LIBALT_API altFloat altProperty::GetFloat(const altStr & sKey, const altFloat nDefault)
{
  ALT_PROPERTY_TO_X (ToFloat);
}

///
/// \brief  Get Double Value
///
/// \param  sKey      [I ] Key Name
/// \param  nDefault  [I ] Default Value
///
/// \return Double Value
///
LIBALT_API altDouble altProperty::GetDouble(const altStr & sKey, const altDouble nDefault)
{
  ALT_PROPERTY_TO_X (ToDouble);
}

///
/// \brief  Get String Value
///
/// \param  sKey      [I ] Key Name
/// \param  sDefault  [I ] Default Value
///
/// \return String Value
///
LIBALT_API const altStr & altProperty::GetStr(const altStr & sKey, const altStr & sDefault)
{
  altStr * pValue = m_oPropertyDataMap[sKey];
  if (pValue == NULL) {
    return sDefault;
  }
  return (* pValue);
}


