#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef ALTROOTCOMPONENT_H
#define ALTROOTCOMPONENT_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altComponent.h
 * \brief   DirectX root component class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN
#include <altDX/altEvent.h>
#include <altDX/altKeyEventListener.h>
#include <altDX/altComponent.h>
#include <altDX/altDXInput.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef std::vector<altKeyEventListener *>  altKeyEventListenerConatiner;

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  DirectX Root Component
///
class altRootComponent : public altComponent
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altRootComponent();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altRootComponent();

  ///
  /// \brief  Add key event listener
  ///
  /// \param  pKeyEventListener [I ] Key event listener
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_INVAL   invalid paramter
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t AddKeyEventListener(altKeyEventListener * pKeyEventListener);

  ///
  /// \brief  Remove key event listener
  ///
  /// \param  pKeyEventListener [I ] Key event listener
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_INVAL   invalid paramter
  ///
  LIBALT_API alt_t RemoveKeyEventListener(altKeyEventListener * pKeyEventListener);

  ///
  /// \brief  Listen key event
  ///
  /// \param  oEvent  [I ] Event
  /// \param  oKey    [I ] Key
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t OnKeyEvent(const altEvent & oEvent, altKeyContainer oKey);

  ///
  /// \brief  Set focus
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t SetFocus();

  ///
  /// \brief  Off focus
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t OffFocus();

private:
  altKeyEventListenerConatiner  m_oKeyEventListnerCotainer; ///< Key event listner container
};

#endif
#endif

#endif  // ALT_USE_DX
