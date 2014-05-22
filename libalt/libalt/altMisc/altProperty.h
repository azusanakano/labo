#ifndef ALTPROPERTY_H
#define ALTPROPERTY_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altProperty.h
 * \brief   Property file class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altBaseLog.h>
#include <altBase/altStr.h>

#include <map>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef std::map<altStr, altStr *>  altPropertyData;  ///< setting data

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Property
///
class altProperty
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altProperty();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altProperty();

  ///
  /// \brief  Load Property File
  ///
  /// \param  sFileName [I ] file name
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t Load(const altStr & sFileName);

  ///
  /// \brief  Get Boolean Value
  ///
  /// \param  sKey      [I ] Key Name
  /// \param  bDefault  [I ] Default Value
  ///
  /// \return Boolean Value
  ///
  LIBALT_API altBool GetBool(const altStr & sKey, const altBool nDefault = false);

  ///
  /// \brief  Get Short Value
  ///
  /// \param  sKey      [I ] Key Name
  /// \param  nDefault  [I ] Default Value
  ///
  /// \return Short Value
  ///
  LIBALT_API altShort GetShort(const altStr & sKey, const altShort nDefault = 0);

  ///
  /// \brief  Get Unsigned Short Value
  ///
  /// \param  sKey      [I ] Key Name
  /// \param  nDefault  [I ] Default Value
  ///
  /// \return Unsigned Short Value
  ///
  LIBALT_API altUShort GetUShort(const altStr & sKey, const altUShort nDefault = 0);

  ///
  /// \brief  Get Int Value
  ///
  /// \param  sKey      [I ] Key Name
  /// \param  nDefault  [I ] Default Value
  ///
  /// \return Int Value
  ///
  LIBALT_API altInt GetInt(const altStr & sKey, const altInt nDefault = 0);

  ///
  /// \brief  Get Unsigned Int Value
  ///
  /// \param  sKey      [I ] Key Name
  /// \param  nDefault  [I ] Default Value
  ///
  /// \return Unsigned Int Value
  ///
  LIBALT_API altUInt GetUInt(const altStr & sKey, const altUInt nDefault = 0);

  ///
  /// \brief  Get Long Value
  ///
  /// \param  sKey      [I ] Key Name
  /// \param  nDefault  [I ] Default Value
  ///
  /// \return Long Value
  ///
  LIBALT_API altLong GetLong(const altStr & sKey, const altLong nDefault = 0);

  ///
  /// \brief  Get Unsigned Long Value
  ///
  /// \param  sKey      [I ] Key Name
  /// \param  nDefault  [I ] Default Value
  ///
  /// \return Unsigned Long Value
  ///
  LIBALT_API altULong GetULong(const altStr & sKey, const altULong nDefault = 0);

  ///
  /// \brief  Get Long Long Value
  ///
  /// \param  sKey      [I ] Key Name
  /// \param  nDefault  [I ] Default Value
  ///
  /// \return Long Long Value
  ///
  LIBALT_API altLongLong GetLongLong(const altStr & sKey, const altLongLong nDefault = 0);

  ///
  /// \brief  Get Unsigned Long Long Value
  ///
  /// \param  sKey      [I ] Key Name
  /// \param  nDefault  [I ] Default Value
  ///
  /// \return Unsigned Long Long Value
  ///
  LIBALT_API altULongLong GetULongLong(const altStr & sKey, const altULongLong nDefault = 0);

  ///
  /// \brief  Get Float Value
  ///
  /// \param  sKey      [I ] Key Name
  /// \param  nDefault  [I ] Default Value
  ///
  /// \return Float Value
  ///
  LIBALT_API altFloat GetFloat(const altStr & sKey, const altFloat nDefault = 0);

  ///
  /// \brief  Get Double Value
  ///
  /// \param  sKey      [I ] Key Name
  /// \param  nDefault  [I ] Default Value
  ///
  /// \return Double Value
  ///
  LIBALT_API altDouble GetDouble(const altStr & sKey, const altDouble nDefault = 0);

  ///
  /// \brief  Get String Value
  ///
  /// \param  sKey      [I ] Key Name
  /// \param  sDefault  [I ] Default Value
  ///
  /// \return String Value
  ///
  LIBALT_API const altStr & GetStr(const altStr & sKey, const altStr & sDefault = "");

protected:
  altPropertyData   m_oPropertyDataMap;   ///< property data map
};

#endif  // ALTPROPERTY_H

