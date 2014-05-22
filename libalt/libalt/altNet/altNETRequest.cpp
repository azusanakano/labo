/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altNETRequest.cpp
 * \brief   Network request call back function class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altNETRequest.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
altNETRequest::altNETRequest() :
m_pReceiveCallBackFunc (NULL),
m_pConnection (NULL),
m_pData (),
m_nSize (0)
{
}

///
/// \brief  Destructor
///
altNETRequest::~altNETRequest()
{
}
