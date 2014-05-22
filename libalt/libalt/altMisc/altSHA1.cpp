/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSHA1.cpp
 * \brief   SHA1 class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altSHA1.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altSHA1::altSHA1()
{
  memset (m_aHash, 0x00, sizeof (m_aHash));
}

///
/// \brief  Destructor
///
LIBALT_API altSHA1::~altSHA1()
{
}

///
/// \brief  Update SHA1 digest
///
/// \param  pData [I ] Data
/// \param  nSize [I ] Data size
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altSHA1::Update(const altUChar * pData, const altUInt nSize)
{
  if (pData == NULL) {
    ALT_RET (ALT_E_ERROR);
  }
  SHA1 (pData, nSize, m_aHash);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  To string
///
/// \return string
///
LIBALT_API altStr altSHA1::ToStr()
{
  altStr  sRet;
  for (altUInt i = 0; i < ALT_ARRAY_SIZE (m_aHash); i++) {
    altStr  sTmp;
    sRet += sTmp.Format ("%02x", m_aHash[i]);
  }
  return (sRet);
}
