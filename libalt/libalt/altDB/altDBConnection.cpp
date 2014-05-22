/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDBConnection.cpp
 * \brief   DB connection class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altDBConnection.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
altDBConnection::altDBConnection()
{
}

///
/// \brief  Destructor
///
altDBConnection::~altDBConnection()
{
  alt_t status = ClearPreparedStatementCache();
  ALT_LOG (status);
}

///
/// \brief  Set Explain Log
///
/// \param  bEnable [I ] Enable or not
/// \param  sLogDir [I ] Explain Log Directory
///
/// \return ALT_S_SUCCESS   success
///
alt_t altDBConnection::SetExplainLog(altBool bEnable, const altStr & sLogDir)
{
  m_bExplainLogEnable = bEnable;
  m_bExplainLogDir = sLogDir;
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Clear Prepared Statement Cache
///
/// \return ALT_S_SUCCESS Success
///
alt_t altDBConnection::ClearPreparedStatementCache()
{
  for (altPreparedStatementMap::iterator i = m_oPreparedStatementMap.begin(); i != m_oPreparedStatementMap.end(); i++) {
    delete i->second;
    i->second = NULL;
  }
  m_oPreparedStatementMap.clear();
  ALT_RET (ALT_S_SUCCESS);
}


