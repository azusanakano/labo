/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSignal.cpp
 * \brief   Signal class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altSignal.h"
#ifdef ALT_LINUX
#include "altStr.h"
#include <errno.h>

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altSignal::altSignal()
{
}

///
/// \brief  Destructor
///
LIBALT_API altSignal::~altSignal()
{
}

///
/// \brief  Signal block
///
/// \param  nSignal [I ] Signal Number
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altSignal::Block(altInt nSignal)
{
  struct sigaction  oAction;
  struct sigaction  oOldAction;

  memset (& oAction, 0x00, sizeof (oOldAction));
  memset (& oOldAction, 0x00, sizeof (oOldAction));

  oAction.sa_handler = altSignal::BlockHandler;

  altInt  nRet = sigaction (nSignal, & oAction, & oOldAction);
  if (nRet < 0) {
    altInt  nErrNo = errno;
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("%d:%s", nErrNo, strerror (nErrNo)));
  }

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Signal block handler
///
/// \param  nSignal [I ] Signal number
///
LIBALT_API void altSignal::BlockHandler(int nSignal)
{
}

#endif
