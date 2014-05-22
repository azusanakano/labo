#ifndef ALTSINGLETON_H
#define ALTSINGLETON_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSingleton.h
 * \brief   Singleton Base Class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altBase.h>
#include <altBase/altSyncThread.h>
#include <altBase/altUncopyable.h>

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
/// \brief  Singleton Base
///
template <typename T>
class altSingleton : public altBase, private altUncopyable
{
protected:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altSingleton(){};
  
  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altSingleton(){};

public:
  ///
  /// \brief	Get instance
  ///
  /// \return instance
  ///
	LIBALT_API static T & GetInstance()
  {
    if (pInstance == NULL) {
      oSyncThread.BeginLock();
      if (pInstance == NULL) {
        pInstance = new T();
      }
      oSyncThread.EndLock();
    }
    return (* pInstance);
  };

  ///
  /// \brief  Delete instance
  ///
  LIBALT_API static void DeleteInstance()
  {
    if (pInstance != NULL) {
      delete pInstance;
      pInstance = NULL;
    }
  };

protected:
	static T *		          pInstance;	    ///< instance
  static altSyncThread    oSyncThread;    ///< sync thread
};

template<typename T> T *           altSingleton<T>::pInstance = NULL;  ///< instance
template<typename T> altSyncThread altSingleton<T>::oSyncThread;       ///< sync thread

#endif  // ALTSINGLETON_H

