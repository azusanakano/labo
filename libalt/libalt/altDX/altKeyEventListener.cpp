#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altKeyEventListener.cpp
 * \brief   Key event listener class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altKeyEventListener.h"
#ifdef ALT_WIN
#include "altDX.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altKeyEventListener::altKeyEventListener()
{
  alt_t status = aiDX.AddKeyEventListener (this);
  ALT_LOG (status);
}

///
/// \brief  Destructor
///
LIBALT_API altKeyEventListener::~altKeyEventListener()
{
  alt_t status = aiDX.RemoveKeyEventListener (this);
  ALT_LOG (status);
}

#endif

#endif // ALT_USE_DX