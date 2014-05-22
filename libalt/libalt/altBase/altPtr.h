#ifndef ALTPTR_H
#define ALTPTR_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altPtr.h
 * \brief   Pointer template class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altBase.h>
#include <altBase/altBaseMem.h>
#include <altBase/altSyncThread.h>

#include <map>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
///
/// \brief  Pointer Class
///
template <typename T>
class altPtr : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altPtr()
  {
    m_pPtr = NULL;
    m_bInherited = false;
  };

  ///
  /// \brief  Constructor
  ///
  /// \param  pPtr  [I ] pointer
  ///
  LIBALT_API altPtr(T * pPtr)
  {
    oSync.BeginLock();
    m_pPtr = pPtr;
    oPtrMap[m_pPtr] = oPtrMap[m_pPtr] + 1;
    oSync.EndLock();
    m_bInherited = false;
  };

  ///
  /// \brief  Copy Constructor
  ///
  /// \param  oPtr  [I ] pointer object
  ///
  LIBALT_API altPtr(const altPtr<T> & oPtr)
  {
    oSync.BeginLock();
    m_pPtr = oPtr.m_pPtr;
    oPtrMap[m_pPtr] = oPtrMap[m_pPtr] + 1;
    oSync.EndLock();
    m_bInherited = false;
  };

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altPtr()
  {
    if (! m_bInherited) {
      oSync.BeginLock();
      oPtrMap[m_pPtr] = oPtrMap[m_pPtr] - 1;
      if (oPtrMap[m_pPtr] == 0) {
        delete m_pPtr;
        m_pPtr = NULL;
      }
      oSync.EndLock();
    }
  };

  ///
  /// \brief  Get raw pointer
  ///
  /// \return raw pointer
  ///
  LIBALT_API T * get_ptr() const
  {
    return (m_pPtr);
  }

  ///
  /// \brief  operator = 
  ///
  /// \param  oPtr  [I ] object
  ///
  /// \return this object
  ///
  LIBALT_API altPtr & operator = (const altPtr<T> & oPtr)
  {
    (* this) = oPtr.m_pPtr;
    return (* this);
  }

  ///
  /// \brief  operator = 
  ///
  /// \param  pPtr  [I ] pointer
  ///
  LIBALT_API T * operator = (T * pPtr)
  {
    oSync.BeginLock();
    if (m_pPtr != NULL) {
      oPtrMap[m_pPtr] = oPtrMap[m_pPtr] - 1;
      if (oPtrMap[m_pPtr] == 0) {
        delete m_pPtr;
      }
    }
    m_pPtr = pPtr;
    if (pPtr != NULL) {
      oPtrMap[m_pPtr] = oPtrMap[m_pPtr] + 1;
    }
    oSync.EndLock();
    return (pPtr);
  }

  ///
  /// \brief  operator -> 
  ///
  /// \return pointer
  ///
  LIBALT_API  T * operator -> () const
  {
    return (m_pPtr);
  }

  ///
  /// \brief  operator *
  ///
  /// \return object
  ///
  LIBALT_API T & operator * () const
  {
    return (* m_pPtr);
  }

  ///
  /// \brief  operator ==
  ///
  /// \param  pPtr  [I ] pointer
  ///
  LIBALT_API altBool operator == (const T * pPtr) const
  {
    return (m_pPtr == pPtr);
  }

  ///
  /// \brief  operator ==
  ///
  /// \param  pPtr  [I ] pointer
  ///
  LIBALT_API altBool operator == (const altPtr<T> oPtr) const
  {
    return (m_pPtr == oPtr.m_pPtr);
  }

  ///
  /// \brief  operator !=
  ///
  /// \param  pPtr  [I ] pointer
  ///
  LIBALT_API altBool operator != (const T * pPtr) const
  {
    return (m_pPtr != pPtr);
  }

  ///
  /// \brief  operator !=
  ///
  /// \param  pPtr  [I ] pointer
  ///
  LIBALT_API altBool operator != (const altPtr<T> oPtr) const
  {
    return (m_pPtr != oPtr.m_pPtr);
  }

  ///
  /// \brief  operator <
  ///
  /// \param  pPtr  [I ] pointer
  ///
  LIBALT_API altBool operator < (const altPtr<T> oPtr) const
  {
    return (m_pPtr < oPtr.m_pPtr);
  }

  ///
  /// \brief  operator  []
  ///
  /// \param  nIndex  [i ] nIndex
  ///
  /// \return index element
  ///
  LIBALT_API T & operator [] (const altUInt nIndex) const
  {
    return (m_pPtr[nIndex]);
  }

  ///
  /// \brief  operator  []
  ///
  /// \param  nIndex  [i ] nIndex
  ///
  /// \return index element
  ///
  LIBALT_API T & operator [] (const altInt nIndex) const
  {
    return (m_pPtr[nIndex]);
  }

protected:
  static std::map<T *, altUInt> oPtrMap;      ///< pointer and reference count map
  static altSyncThread          oSync;        ///< thread syncronize object
  T *                           m_pPtr;       ///< pointer
  altBool                       m_bInherited; ///< inherited or not
};

template<typename T> std::map<T *, altUInt> altPtr<T>::oPtrMap; ///< pointer and reference count map
template<typename T> altSyncThread          altPtr<T>::oSync;   ///< thread syncronize object

#endif  // ALTPTR_H

