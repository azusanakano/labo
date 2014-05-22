#ifndef ALTUNCOPYABLE_H
#define ALTUNCOPYABLE_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altUncopyable.h
 * \brief   Uncopyable class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Uncopyable Class
///
class altUncopyable
{
protected:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altUncopyable(){};
  
  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altUncopyable(){};

private:
  ///
  /// \brief  Copy Constructor
  ///
  LIBALT_API altUncopyable(const altUncopyable & o);

  ///
  /// \brief  Copy Constructor
  ///
  LIBALT_API altUncopyable & operator = (const altUncopyable & o);
};

#endif  // ALTUNCOPYABLE_H
