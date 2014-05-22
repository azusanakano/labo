#ifndef ALTEXTERNALIZABLE_H
#define ALTEXTERNALIZABLE_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0


  Description:
  This class is I/O interface for data class.

 *---------------------------------------------------------------------------*/
/**
 * \file    altExternalizable.h
 * \brief   Externalizable class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altMisc/altDataStream.h>

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Data Stream
///
class altExternalizable : public altBase
{
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altExternalizable();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altExternalizable();

  ///
  /// \brief  Write
  ///
  /// \param  oDataStream [ O] Data stream
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t virtual Write(altDataStream & oDataStream) const = 0;
  
  ///
  /// \brief  Read
  ///
  /// \param  oDataStream [I ] Data stream
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  ///
  LIBALT_API alt_t virtual Read(altDataStream & oDataStream) const = 0;
};

#endif
