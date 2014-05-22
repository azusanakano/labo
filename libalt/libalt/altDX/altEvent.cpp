#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altEvent.cpp
 * \brief   Event class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altEvent.h"
#ifdef ALT_WIN

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altEvent::altEvent(const altUInt nType, altComponent * pSource) :
m_nType (nType),
m_pSource (pSource)
{
}

///
/// \brief  Destructor
///
LIBALT_API altEvent::~altEvent()
{
}

///
/// \brief  Get event type
///
/// \return Event type
///
LIBALT_API altUInt altEvent::GetType() const
{
  return (m_nType);
}

///
/// \brief  Get event source
///
/// \return Evnet source
///
LIBALT_API altComponent * altEvent::GetEventSource() const
{
  return (m_pSource);
}

#endif

#endif // ALT_USE_DX