#ifndef ALTMD5_H
#define ALTMD5_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altMD5.h
 * \brief   MD5 class
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
#include <altNet/openssl/md5.h>
#endif
#ifdef ALT_LINUX
#include <openssl/md5.h>
#endif

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  MD5
///
class altMD5 : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altMD5();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altMD5();

  ///
  /// \brief  Update MD5 digest
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

  altUChar  m_aHash[MD5_DIGEST_LENGTH]; ///< SHA1 digest
};

#endif
