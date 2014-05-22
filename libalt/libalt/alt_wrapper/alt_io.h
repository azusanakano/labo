#ifndef ALT_IO_H
#define ALT_IO_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    alt_io.h
 * \brief   IO wrapper functions
 * \date    2013
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altCommon.h>

#ifdef ALT_WIN
  #include <io.h>
  #include <direct.h>   // for _mkdir
#else
  #include <sys/stat.h> // for mkdir
#endif
#include <stdio.h>
#include <errno.h>


/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
#ifdef ALT_WIN
  typedef altInt  mode_t;   // for alt_mkdir
#endif

/*----------------------------------------------------------------*
 * Function Declare
 *----------------------------------------------------------------*/

/**
 * \brief Open file
 *
 * \param ppfile    [IO] FILE pointer container
 * \param filename  [I ] file name
 * \param mode      [I ] open mode
 *
 * \return error number
 */
LIBALT_API inline errno_t alt_fopen (
  FILE ** ppFile,
  const char *  filename,
  const char *  mode
)
{
#ifdef ALT_WIN
  return fopen_s (ppFile, filename, mode);
#else
  if (ppFile == NULL) {
    return -1;
  }
  *ppFile = fopen (filename, mode);
  if (*ppFile == NULL) {
    return errno;
  }
  return 0;
#endif
}


/**
 * \brief Open file by file descripter
 *
 * \param filename  [I ] file name
 * \param mode      [I ] open mode
 *
 * \return FILE pointer
 */
LIBALT_API inline FILE * alt_fdopen (
  const int     fd,
  const char *  mode
)
{
#ifdef ALT_WIN
  return _fdopen (fd, mode);
#else
  return fdopen (fd, mode);
#endif
}


/**
 * \brief create directory
 *
 * \param szDirName [I ] directory name
 * \param mode      [I ] directory permission
 *
 * \return true   success
 * \return false  error
 */
LIBALT_API inline const altBool alt_mkdir (
  const altChar * szDirName,
  mode_t          mode = 0777
)
{
#ifdef ALT_WIN
   return (_mkdir (szDirName) == 0);
#endif

#ifdef ALT_LINUX
  return (mkdir (szDirName, mode) == 0);
#endif
}

#endif  // ALT_IO_H


