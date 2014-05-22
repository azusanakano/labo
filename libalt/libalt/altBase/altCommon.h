#ifndef ALTCOMMON_H
#define ALTCOMMON_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altCommon.h
 * \brief   Alternative Library Common Header
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
#ifdef __cplusplus
#  define  ALT_BEGIN_C_DECLS extern "C" {
#  define  ALT_END_C_DECLS }
#else  /* __cplusplus */
#  define  ALT_BEGIN_C_DECLS
#  define  ALT_END_C_DECLS
#endif  /* __cplus_plus */

#ifdef WIN32
  #define ALT_WIN
  #define alloca _alloca

  #ifdef LIBALT_EXPORTS
    #define LIBALT_API __declspec(dllexport)
  #else
    #define LIBALT_API __declspec(dllimport)
  #endif
#else
  #define ALT_LINUX
  #define LIBALT_API
#endif

///
/// \brief  Get array size
///
/// \param  p [I ] array
///
/// \return array size
///
#define ALT_ARRAY_SIZE(p) (sizeof (p) / sizeof (p[0]))

#define ALT_BUFSIZ    2048    ///< Buffer Size

/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <stdio.h>
#ifdef _DEBUG
  #include <assert.h>
#endif

#ifdef ALT_WIN
  #include <winsock2.h>
  #include <windows.h>
  #include <tchar.h>
#else
  #include <sys/types.h>
  #include <unistd.h>
  #include <string.h>
#endif

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
typedef char                altChar;
typedef unsigned char       altUChar;
typedef unsigned char       altByte;
typedef bool                altBool;

typedef short               altShort;
typedef unsigned short      altUShort;

typedef int                 altInt;
typedef unsigned int        altUInt;

typedef long                altLong;
typedef unsigned long       altULong;

typedef long long           altLongLong;
typedef unsigned long long  altULongLong;

#ifdef ALT_LINUX
  typedef unsigned short    WORD;
  typedef unsigned long     DWORD;
  typedef unsigned char     BYTE;
  typedef long int          errno_t;
#endif

typedef float               altFloat;
typedef double              altDouble;

typedef altUShort           altWChar;


/*----------------------------------------------------------------*
 * Define
 *----------------------------------------------------------------*/
#ifdef _DEBUG
  #define ALT_BASE_ASSERT(cond) assert (cond)
#else
  #define ALT_BASE_ASSERT(cond)
#endif

#ifdef ALT_LINUX
  #define INFINITE  0xFFFFFFFF
#endif

#ifdef ALT_WIN
  #define ALT_THROWS(exception) 
#endif
#ifdef ALT_LINUX
  #define ALT_THROWS(exception) throw (exception)
#endif

#ifdef _DEBUG
#define USE_MEM_MANAGER_FULL
#endif

#endif  // ALTCOMMON_H
