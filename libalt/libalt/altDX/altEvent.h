#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef ALTEVENT_H
#define ALTEVENT_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altEvent.h
 * \brief   Event class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN
#include <altDX/altComponent.h>
#include <altBase/altLog.h>

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Event
///
class altEvent : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altEvent(const altUInt nType, altComponent * pSource);

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altEvent();

  ///
  /// \brief  Get event type
  ///
  /// \return Event type
  ///
  LIBALT_API altUInt GetType() const;

  ///
  /// \brief  Get event source
  ///
  /// \return Evnet source
  ///
  LIBALT_API altComponent * GetEventSource() const;

private:
  altUInt         m_nType;
  altComponent *  m_pSource;
};

#endif
#endif

#endif // ALT_USE_DX