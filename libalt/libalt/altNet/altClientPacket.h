#ifndef ALTCLIENTPACKET_H
#define ALTCLIENTPACKET_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altClientPacket.h
 * \brief   Network packet data class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCharPtr.h>
#include <altBase/altStatus.h>
#include <altBase/altLog.h>
#include <altBase/altBase.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Client Packet Data
///
class altClientPacket : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altClientPacket();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altClientPacket();

  ///
  /// \brief  Set Data
  ///
  /// \param  pData           [I ] Data
  /// \param  nSize           [I ] Data Size
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  /// \return ALT_E_INVAL   invalid paramter
  ///
  LIBALT_API alt_t Set(const altCharPtr & pData, const altUInt nSize);

  ///
  /// \brief  Get Data
  ///
  /// \return Data
  ///
  LIBALT_API const altCharPtr GetData() const;

  ///
  /// \brief  Get Size
  ///
  /// \return Size
  ///
  LIBALT_API altUInt GetSize() const;

protected:
  altCharPtr  m_pData;  ///< Data
  altUInt     m_nSize;  ///< Data Size
};
#endif  //ALTCLIENTPACKET_H
