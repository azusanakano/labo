#ifndef ALTBLOWFISH_H
#define ALTBLOWFISH_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altBlowFish.h
 * \brief   Blowfish class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altLog.h>
#include <altBase/altCharPtr.h>

#ifdef ALT_WIN
#include <altNet/openssl/blowfish.h>
#endif

#ifdef ALT_LINUX
#include <openssl/blowfish.h>
#endif

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  File
///
class altBlowFish : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altBlowFish();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altBlowFish();

  ///
  /// \brief  Initialize
  ///
  /// \param  pKey  [I ] Crypt Key
  /// \param  nSize [I ] Crypt Key Size
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  /// \return ALT_E_INVAL     invalid paramter
  ///
  LIBALT_API alt_t Initialize(const altByte * pKey, altInt nSize);

  ///
  /// \brief  Encrypt
  ///
  /// \param  pData [IO] Data
  /// \param  nSize [IO] Data Size
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_NOMEM     out of memory
  /// \return ALT_E_ERROR     error
  /// \return ALT_E_INVAL     invalid paramter
  ///
  LIBALT_API alt_t Encode(altCharPtr & pData, altUInt & nSize);

  ///
  /// \brief  Decrypt
  ///
  /// \param  pData [IO] Data
  /// \param  nSize [IO] Data Size
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_NOMEM     out of memory
  /// \return ALT_E_ERROR     error
  /// \return ALT_E_INVAL     invalid paramter
  ///
  LIBALT_API alt_t Decode(altCharPtr & pData, altUInt & nSize);

private:
  altBool   m_bInitialized;   ///< Initialized
  BF_KEY    m_oBFKey;         ///< BlowFish Key
};

#endif
