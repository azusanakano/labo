#ifndef LIBALT_H
#define LIBALT_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    libalt.h
 * \brief   Alternative Library Header
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <alt_wrapper/alt_cast.h>
#include <alt_wrapper/alt_io.h>
#include <alt_wrapper/alt_string.h>

#include <altBase/altRuntime.h>
#include <altBase/altSignal.h>
#include <altBase/altCharPtr.h>
#include <altBase/altMemManager.h>
#include <altBase/altMem.h>
#include <altBase/altLog.h>
#include <altBase/altStr.h>
#include <altBase/altLoopThread.h>
#include <altBase/altThread.h>
#include <altBase/altBaseMem.h>
#include <altBase/altSingleton.h>
#include <altBase/altUncopyable.h>
#include <altBase/altSyncThread.h>
#include <altBase/altUtil.h>
#include <altBase/altBase.h>

#include <altMisc/altTimer.h>
#include <altMisc/altMiscUtil.h>
#include <altMisc/altBlowFish.h>
#include <altMisc/altBzip2.h>
#include <altMisc/altProperty.h>
#include <altMisc/altSHA1.h>
#include <altMisc/altMD5.h>
#include <altMisc/altMemLogger.h>
#include <altMisc/altFile.h>
#include <altMisc/altQue.h>

#include <altNet/altTCPServer.h>
#include <altNet/altTCPClient.h>
#include <altNet/altSSLServer.h>
#include <altNet/altSSLClient.h>

#include <altDB/altDBConnection.h>
#include <altDB/altDBConnectionPtr.h>
#include <altDB/altDBManager.h>
#include <altDB/altDBResultSet.h>
#include <altDB/altPreparedStatement.h>
#include <altDB/altSQL.h>
#include <altDB/altSQLLoader.h>

#include <altDB/altMySQL.h>

#ifdef ALT_WIN
#ifdef ALT_USE_DX
  #include <altDX/altDX.h>
  #include <altDX/altDXInput.h>
  #include <altDX/alt2DQuad.h>
  #include <altDX/altComponent.h>
  #include <altDX/altIME.h>
  #include <altDX/altIMEComponent.h>
  #include <altDX/altMouse.h>
  #include <altDX/altPolygon.h>
  #include <altDX/altXFile.h>
  #include <altDX/altLight.h>
  #include <altDX/altFontManager.h>
  #include <altDX/Component/altLabel.h>
  #include <altDX/Component/altTextBox.h>
#endif  // ALT_USE_DX
#endif  // ALT_WIN

#endif  //LIBALT_H
