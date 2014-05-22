#ifndef ALTCHARPTR_H
#define ALTCHARPTR_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altCharPtr.h
 * \brief   Char Pointer class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altPtr.h>
#include <altBase/altMem.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
class altCharPtr;

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Pointer Class
///
class altCharPtr : public altPtr<altChar>
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altCharPtr();

  ///
  /// \brief  Constructor
  ///
  /// \param  p [I ] Data
  ///
  LIBALT_API altCharPtr(altChar * p) ALT_THROWS (alt_t);

  ///
  /// \brief  Constructor
  ///
  /// \param  p [I ] Data
  ///
  LIBALT_API altCharPtr(const altCharPtr & p);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altCharPtr();

  ///
  /// \brief  Cast altChar *
  ///
  /// \return Pointer
  ///
  LIBALT_API operator altChar * () const;

  ///
  /// \brief  Cast altByte *
  ///
  /// \return Pointer
  ///
  LIBALT_API operator altByte * () const;

  ///
  /// \brief  = operator
  ///
  /// \param  pPtr  [I ] Pointer of altChar
  ///
  /// \return Pointer of altChar
  ///
  LIBALT_API altChar * operator = (altChar * pPtr) ALT_THROWS (alt_t);

  ///
  /// \brief  = operator
  ///
  /// \param  pPtr  [I ] Pointer of altByte
  ///
  /// \return Pointer of altByte
  ///
  LIBALT_API altByte * operator = (altByte * pPtr) ALT_THROWS (alt_t);
};

#endif
