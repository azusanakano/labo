#ifndef altSSLSyncThread_H
#define altSSLSyncThread_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSSLSyncThread.h
 * \brief   SSL synchronize thread class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altStatus.h>
#include <altBase/altSyncThread.h>
#include <vector>

//--------------------------------------------------------------------
// Type Definition
//--------------------------------------------------------------------
typedef std::vector<altSyncThread *> altSyncThreadContainer;

//--------------------------------------------------------------------
// Class Definition
//--------------------------------------------------------------------
///
/// \brief	 SSL Synchronize Class
///
class altSSLSyncThread
{
public:
	///
	/// \brief Constructor
	///
	altSSLSyncThread();

	///
	/// \brief Destructor
	///
	virtual ~altSSLSyncThread();

  ///
  /// \brief	Initialize
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
	static alt_t InitLock();

	///
	/// \brief	Lock Call Back Function
	///
	static void LockingCallback(altInt nMode, altInt nType, const altChar * pFile, altInt nLine);

	///
	/// \brief	end of using
	///
	/// \return ALT_S_SUCCESS	  Success
	///
	static alt_t End();

private:
  static altBool                bInitDone;
  static altSyncThreadContainer oSyncThreads;
};

#endif //altSSLSyncThread_H

