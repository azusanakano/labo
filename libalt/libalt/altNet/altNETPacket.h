#ifndef ALTNETPACKET_H
#define ALTNETPACKET_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETPacket.h
 * \brief   Network packet data class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altNet/altNETConnection.h>
#include <altBase/altCharPtr.h>
#include <altBase/altLog.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
class altNETConnection;
typedef const altNETConnection      altCNETConnection;      ///< const altNETConnection
typedef altPtr<altCNETConnection>   altCNETConnectionPtr;   ///< pointer of const altNETConnection

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Network Packet Data Class
///
class altNETPacket : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altNETPacket();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altNETPacket();

  ///
  /// \brief  Set Data
  ///
  /// \param  pNETConnection  [I ] NET Connection
  /// \param  pData           [I ] network data
  /// \param  nSize           [I ] data size
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_NOMEM   out of memory
  /// \return ALT_E_INVAL   invalid paramter
  ///
  LIBALT_API alt_t Set(const altCNETConnectionPtr & pNETConnection, const altCharPtr & pData, const altUInt nSize);

  ///
  /// \brief  Get Data
  ///
  /// \param  pNETConnection  [ O] NET Connection
  /// \param  pData           [ O] network data
  /// \param  nSize           [ O] data size
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t Get(altCNETConnectionPtr & pNETConnection, altCharPtr & pData, altUInt & nSize);

protected:
  altCharPtr                      m_pData;
  altUInt                         m_nSize;
  altPtr<const altNETConnection>  m_pConnection;
};
#endif  //ALTPACKET_H
