#ifndef ALTDBCONNECTIONPTR_H
#define ALTDBCONNECTIONPTR_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDBConnectionPtr.h
 * \brief   DB connection pointer class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altDB/altDBConnection.h>
#include <altDB/altDBManager.h>

class altDBManager;
/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  DB Connection Pointer
///
class altDBConnectionPtr : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altDBConnectionPtr();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altDBConnectionPtr();

  ///
  /// \brief  Set Pointer
  ///
  /// \param  pDBConnection   [I ] Pointer of DB Connection
  /// \param  pDBManager      [I ] Pointer of DB Manager
  ///
  LIBALT_API alt_t Set(altDBConnection * pDBConnection, altDBManager * pDBManager);

  ///
  /// \brief  operator ->
  ///
  /// \return Pointer of DB Connection
  ///
  LIBALT_API altDBConnection * operator -> () const;

private:
  altDBConnection *   m_pDBConnection;
  altDBManager *      m_pDBManager;
};

#endif //ALTDBCONNECTIONPTR_H
