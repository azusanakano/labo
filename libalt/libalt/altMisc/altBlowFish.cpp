/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altBlowFish.cpp
 * \brief   Blowfish class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altBlowFish.h"
#include "altBase/altMem.h"
#include "altBase/altStatus.h"

/*----------------------------------------------------------------*
 * Static Variable
 *----------------------------------------------------------------*/
static const DWORD ALT_CRYPT_MAGIC = 0x32564523;   ///< Magic Number

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altBlowFish::altBlowFish() :
m_bInitialized (false),
m_oBFKey()
{
}

///
/// \brief  Destructor
///
LIBALT_API altBlowFish::~altBlowFish()
{
}

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
LIBALT_API alt_t altBlowFish::Initialize(const altByte * pKey, altInt nSize)
{
  ALT_P_ASSERT (pKey != NULL);

  BF_set_key (& m_oBFKey, nSize, pKey);
  m_bInitialized = true;

  ALT_RET (ALT_S_SUCCESS);
}

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
LIBALT_API alt_t altBlowFish::Encode(altCharPtr & pData, altUInt & nSize)
{
  ALT_P_ASSERT (pData != NULL);

  if (! m_bInitialized) {
    ALT_RET_P (ALT_E_ERROR, "Not Initialized");
  }

  alt_t status;

  altUInt   nAddSize = (8 - (nSize % 8)) + 8;
  altUInt   nNewSize = nSize + nAddSize;
  altChar * pEncodeData = NULL;

  status = ALT_MALLOC (pEncodeData, nNewSize);
  ALT_ERR_RET (status);

  memcpy (pEncodeData, (const altChar *)pData, nSize);
  memcpy (& pEncodeData[nNewSize - 9], & ALT_CRYPT_MAGIC, 4);
  memcpy (& pEncodeData[nNewSize - 5], & nAddSize, 4);

  BF_encrypt ((BF_LONG *)pEncodeData, & m_oBFKey);

  pData = pEncodeData;
  nSize = nNewSize;

  ALT_RET (ALT_S_SUCCESS);
}

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
LIBALT_API alt_t altBlowFish::Decode(altCharPtr & pData, altUInt & nSize)
{
  ALT_P_ASSERT (pData != NULL);

  if (! m_bInitialized) {
    ALT_RET_P (ALT_E_ERROR, "Not Initialized");
  }

  alt_t     status;

  BF_decrypt ((BF_LONG *)(altChar *)pData, & m_oBFKey);

  altUInt nDelSize;
  memcpy (& nDelSize, & pData[nSize - 5], 4);

  DWORD   dwMagic;
  memcpy (& dwMagic, & pData[nSize - 9], 4);

  if (dwMagic != ALT_CRYPT_MAGIC) {
    ALT_RET_P (ALT_E_ERROR, "crypto magic invalid");
  }

  altUInt   nNewSize = nSize - nDelSize;
  altChar * pOutData = NULL;

  status = ALT_MALLOC (pOutData, nNewSize);
  ALT_ERR_RET (status);
  memcpy (pOutData, (const altChar *)pData, nNewSize);

  pData = pOutData;
  nSize = nNewSize;

  ALT_RET (ALT_S_SUCCESS);
}

