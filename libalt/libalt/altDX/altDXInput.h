#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.

#ifndef ALTDXINPUT_H
#define ALTDXINPUT_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altDXInput.h
 * \brief   DirectX Input class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>
#ifdef ALT_WIN
#include <altBase/altLog.h>
#include <altBase/altSingleton.h>
#include <dinput.h>

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
///
/// \brief  Get Instance
///
#define aiDXInput altDXInput::GetInstance()

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef std::vector<altUInt>  altKeyContainer;

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Event
///
class altDXInput : public altSingleton<altDXInput>
{
friend class altSingleton<altDXInput>;
private:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altDXInput();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API ~altDXInput();

  ///
  /// \brief  Clean up
  ///
  LIBALT_API void Cleanup();

public:
  ///
  /// \brief  Set keyboard
  ///
  /// \param  dwCooperativeLevel  [I ] Cooperative level
  ///
  /// \return ALT_S_SUCCESS success
  /// \return ALT_E_ERROR   error
  ///
  LIBALT_API alt_t SetKeyboard(DWORD dwCooperativeLevel = DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

  ///
  /// \brief  Get down key or not
  ///
  /// \param  nKey  [I ] Key
  ///
  /// \return true  down
  /// \return false not down
  ///
  LIBALT_API altBool DownKey(const altByte nKey);

  ///
  /// \brief  Get down key or not
  ///
  /// \return true  down
  /// \return false not down
  ///
  LIBALT_API altBool DownAnyKey();

  ///
  /// \brief  Get down keys
  ///
  /// \return Down keys
  ///
  LIBALT_API altKeyContainer GetDownKey();

  ///
  /// \brief  Get altDXInput Instance
  ///
  /// \return altDX Instance
  ///
  LIBALT_API static altDXInput & GetInstance();

  ///
  /// \brief  Delete Instance
  ///
  LIBALT_API static void DeleteInstance();

private:
  LPDIRECTINPUT8        m_pDinput;        ///< DirectX input
  LPDIRECTINPUTDEVICE8  m_pInputDevice;   ///< Input device
};

#endif
#endif

#endif // ALT_USE_DX