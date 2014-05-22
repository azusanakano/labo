/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altSSLSyncThread.cpp
 * \brief   SSL synchronize thread class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altSSLSyncThread.h"
#include "openssl/ssl.h"
#include "altBase/altLog.h"

/*----------------------------------------------------------------*
 * Static variables
 *----------------------------------------------------------------*/
altBool                 altSSLSyncThread::bInitDone = false;   ///< 初期化フラグ
altSyncThreadContainer  altSSLSyncThread::oSyncThreads;        ///< 同期オブジェクトの入れ物

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief Constructor
///
altSSLSyncThread::altSSLSyncThread()
{
}

///
/// \brief Destructor
///
altSSLSyncThread::~altSSLSyncThread()
{
  alt_t status = End();
  ALT_LOG (status);
}

///
/// \brief	Initialize
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
alt_t altSSLSyncThread::InitLock()
{
	if (! bInitDone) {
		for (altInt i = 0; i < CRYPTO_num_locks(); i++) {
      try {
			  altSyncThread * pSyncThread = new altSyncThread ();
        oSyncThreads.push_back (pSyncThread);
      }
      catch (std::exception & e) {
        ALT_RET_P (ALT_E_ERROR, e.what());
      }
      catch (...) {
        ALT_RET (ALT_E_ERROR);
      }
		}
		CRYPTO_set_locking_callback (LockingCallback);
		bInitDone =  true;
	}
	ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief	Lock Call Back Function
///
void altSSLSyncThread::LockingCallback(altInt nMode, altInt nType, const altChar * pFile, altInt nLine)
{
	if (nMode & CRYPTO_LOCK) {
		oSyncThreads[nType]->BeginLock ();
	}
	else {
		oSyncThreads[nType]->EndLock ();
	}
}

///
/// \brief	end of using
///
/// \return ALT_S_SUCCESS	  Success
///
alt_t altSSLSyncThread::End()
{
	for (altSyncThreadContainer::iterator i = oSyncThreads.begin (); i != oSyncThreads.end (); i++) {
		delete (* i);
		(* i) = NULL;
	}
	oSyncThreads.clear ();
	ALT_RET (ALT_S_SUCCESS);
}

