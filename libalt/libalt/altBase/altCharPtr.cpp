/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altCharPtr.cpp
 * \brief   Char Pointer class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altCharPtr.h"
#include "altBase/altStatus.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altCharPtr::altCharPtr()
{
  m_bInherited = true;
}

///
/// \brief  Constructor
///
/// \param  p [I ] Data
///
LIBALT_API altCharPtr::altCharPtr(altChar * p) ALT_THROWS (alt_t)
{
  m_bInherited = true;
  try {
    (* this) = p;
  }
  catch (alt_t e) {
    ALT_LOG (e);
    throw e;
  }
}

///
/// \brief  Constructor
///
/// \param  p [I ] Data
///
LIBALT_API altCharPtr::altCharPtr(const altCharPtr & p)
{
  m_bInherited = true;
  (* this) = p.m_pPtr;
}

///
/// \brief  Destructor
///
LIBALT_API altCharPtr::~altCharPtr()
{
  oSync.BeginLock();
  oPtrMap[m_pPtr] = oPtrMap[m_pPtr] - 1;
  if (oPtrMap[m_pPtr] == 0) {
    ALT_FREE (m_pPtr);
  }
  oSync.EndLock();
};

///
/// \brief  Cast altChar *
///
/// \return Pointer
///
LIBALT_API altCharPtr::operator altChar * () const
{
  return (m_pPtr);
}

///
/// \brief  Cast altByte *
///
/// \return Pointer
///
LIBALT_API altCharPtr::operator altByte * () const
{
  return (altByte *)(m_pPtr);
}

///
/// \brief  = operator
///
/// \param  pPtr  [I ] Pointer of altChar
///
/// \return Pointer of altChar
///
LIBALT_API altChar * altCharPtr::operator = (altChar * pPtr) ALT_THROWS (alt_t)
{
  oSync.BeginLock();
  
  if (pPtr != NULL) {
    if (altMemValidate (pPtr) == false) {
      ALT_LOG (ALT_E_INVAL);
      oSync.EndLock();
      throw (ALT_E_INVAL);
    }
  }

  if (m_pPtr != NULL) {
    oPtrMap[m_pPtr] = oPtrMap[m_pPtr] - 1;
    if (oPtrMap[m_pPtr] == 0) {
      ALT_FREE (m_pPtr);
    }
  }
  m_pPtr = pPtr;
  if (m_pPtr != NULL) {
    oPtrMap[m_pPtr] = oPtrMap[m_pPtr] + 1;
  }
  oSync.EndLock();
  return (m_pPtr);
}

///
/// \brief  = operator
///
/// \param  pPtr  [I ] Pointer of altByte
///
/// \return Pointer of altByte
///
LIBALT_API altByte * altCharPtr::operator = (altByte * pPtr) ALT_THROWS (alt_t)
{
  return (altByte *)(this->operator = ((altChar *)pPtr));
}
