#ifndef ALTSHA1_H
#define ALTSHA1_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSHA1.h
 * \brief   SHA1 class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altStr.h>
#include <altBase/altLog.h>
#include <altBase/altStatus.h>

#ifdef ALT_WIN
#include <altNet/openssl/sha.h>
#endif
#ifdef ALT_LINUX
#include <openssl/sha.h>
#endif

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  SHA1
///
class altSHA1 : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altSHA1();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altSHA1();

  ///
  /// \brief  Update SHA1 digest
  ///
  /// \param  pData [I ] Data
  /// \param  nSize [I ] Data size
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t Update(const altUChar * pData, const altUInt nSize);

  ///
  /// \brief  To string
  ///
  /// \return string
  ///
  LIBALT_API altStr ToStr();

  altUChar  m_aHash[SHA_DIGEST_LENGTH]; ///< SHA1 digest
};

#endif
