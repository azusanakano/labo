#ifndef ALT_CAST_H
#define ALT_CAST_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    alt_cast.h
 * \brief   Cast wrapper functions
 * \date    2013
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#include <stdio.h>

#ifdef ALT_WIN
#include <io.h>
#endif

/*----------------------------------------------------------------*
 * Function Declare
 *----------------------------------------------------------------*/

/**
 * \brief Cast void * to altChar *
 *
 * \param p [I ] void * pointer
 *
 * \return altChar * pointer
 */
LIBALT_API inline altChar * alt_cast2_char_p(void * p)
{
  return reinterpret_cast<altChar *>(p);
}


/**
 * \brief Cast const void * to altChar *
 *
 * \param p [I ] const void * pointer
 *
 * \return altChar * pointer
 */
LIBALT_API inline altChar * alt_cast2_char_p(const void * p)
{
  return (altChar *)(p);
}



/**
 * \brief Cast void * to const altChar *
 *
 * \param p [I ] void * pointer
 *
 * \return const altChar * pointer
 */
LIBALT_API inline const altChar * alt_cast2_c_char_p(void * p)
{
  return static_cast<const altChar *>(p);
}


/**
 * \brief Cast altChar * to const altChar *
 *
 * \param p [I ] altChar * pointer
 *
 * \return const altChar * pointer
 */
LIBALT_API inline const altChar * alt_cast2_c_char_p(altChar * p)
{
  return static_cast<const altChar *>(p);
}



/**
 * \brief Cast const void * to void *
 *
 * \param p [I ] const void * pointer
 *
 * \return void * pointer
 */
LIBALT_API inline void * alt_cast2_void_p(const void * p)
{
  return const_cast<void *>(p);
}


/**
 * \brief Cast altChar * to void *
 *
 * \param p [I ] altChar * pointer
 *
 * \return void * pointer
 */
LIBALT_API inline void * alt_cast2_void_p(altChar * p)
{
  return static_cast<void *>(p);
}


/**
 * \brief Cast altChar * to void *
 *
 * \param p [I ] altChar * pointer
 *
 * \return void * pointer
 */
LIBALT_API inline void *& alt_cast2_void_p_ref(altChar *& p)
{
  return (void *&)p;
}

#endif  // ALT_CAST_H


