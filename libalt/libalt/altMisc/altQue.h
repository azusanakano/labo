#ifndef ALTQUE_H
#define ALTQUE_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altQue.h
 * \brief   Queue data structure class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altLog.h>
#include <altBase/altStatus.h>
#include <altBase/altUncopyable.h>
#include <altBase/altSyncThread.h>

#include <vector>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Que Class
///
template <class T>
class altQue : public altBase, private altUncopyable, public altSyncThread
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altQue()
  {
  }

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altQue()
  {
  }

  ///
  /// \brief  Push to first position
  ///
  /// \param  oData [I ] Data
  ///
  /// \return ALT_S_SUCCESS success
  ///
  LIBALT_API alt_t Push(const T & oData)
  {
    BeginLock();
    m_oContainer.insert (m_oContainer.begin(), oData);
    EndLock();
    ALT_RET (ALT_S_SUCCESS);
  }

  ///
  /// \brief  Pop from last position
  ///
  /// \param  oData [ O] Data
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_S_NOT_FOUND no data
  ///
  LIBALT_API alt_t Pop(T & oData)
  {
    BeginLock();
    alt_t status = ALT_S_SUCCESS;
    if (! m_oContainer.empty()) {
      oData = m_oContainer.back();
      m_oContainer.pop_back();
    }
    else {
      status = ALT_S_NOT_FOUND;
    }
    EndLock();
    ALT_RET (status);
  }

  ///
  /// \brief  Check Is empty or not
  ///
  /// \return true  empty
  /// \return false not empty
  ///
  LIBALT_API altBool Empty()
  {
    BeginLock();
    altBool bEmpty = m_oContainer.empty();
    EndLock();
    return bEmpty;
  }

  ///
  /// \brief Get Size
  ///
  /// \return size
  ///
  LIBALT_API altUInt Size()
  {
    return static_cast<altUInt>(m_oContainer.size());
  }

protected:
  std::vector<T> m_oContainer;
};
#endif  //ALTQUE_H
