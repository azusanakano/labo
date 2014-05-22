/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altPreparedStatement.cpp
 * \brief   Prepared statement class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altPreparedStatement.h"

/*----------------------------------------------------------------*
 * Class variables
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
/// \param	oSQL	[I ] SQL infomation
///
altPreparedStatement::altPreparedStatement(const altSQL & oSQL) :
m_oSQL (oSQL)
{
}

///
/// \brief  Destructor
///
altPreparedStatement::~altPreparedStatement()
{
}

///
/// \brief  Get SQL Name
///
/// \return SQL Name
///
const altStr & altPreparedStatement::GetSQLName() const
{
  return m_oSQL.GetSQLName();
}


