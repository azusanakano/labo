/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDBConnectionPtr.cpp
 * \brief   DB connection pointer class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altDBConnectionPtr.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altDBConnectionPtr::altDBConnectionPtr() :
m_pDBConnection(NULL),
m_pDBManager(NULL)
{
}

///
/// \brief  Destructor
///
LIBALT_API altDBConnectionPtr::~altDBConnectionPtr()
{
  if (m_pDBManager != NULL) {
    alt_t status;
    status = m_pDBManager->ReleaseDBConnection (m_pDBConnection);
    ALT_LOG (status);
  }
}

///
/// \brief  Set Pointer
///
/// \param  pDBConnection   [I ] Pointer of DB Connection
/// \param  pDBManager      [I ] Pointer of DB Manager
///
/// \return ALT_S_SUCCESS   Success
///
LIBALT_API alt_t altDBConnectionPtr::Set(altDBConnection * pDBConnection, altDBManager * pDBManager)
{
  m_pDBConnection = pDBConnection;
  m_pDBManager = pDBManager;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  operator ->
///
/// \return Pointer of DB Connection
///
LIBALT_API altDBConnection * altDBConnectionPtr::operator -> () const
{
  return (m_pDBConnection);
}
