#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
#ifndef ALTXFILE_H
#define ALTXFILE_H
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altXFile.h
 * \brief   DirectX X file class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include <altBase/altLog.h>
#include <altBase/altBase.h>

#ifdef ALT_WIN
#include <altDX/altDX.h>

/*----------------------------------------------------------------*
 * Type Definition
 *----------------------------------------------------------------*/
struct XFILE
{
	LPD3DXMESH            lpMesh;
	DWORD                 NumMaterial;
	D3DMATERIAL9 *        Mat;
	LPDIRECT3DTEXTURE9 *  Tex;
};

/*----------------------------------------------------------------*
 * Class Definition
 *----------------------------------------------------------------*/
class altXFile : public altBase
{
public:
  ///
  /// \brief  Constructor
  ///
  LIBALT_API altXFile();

  ///
  /// \brief  Destructor
  ///
  LIBALT_API virtual ~altXFile();

  ///
  /// \brief  Load X File
  ///
  /// \param  sFileName   [I ] File Name
  /// \param  dwOptions   [I ] Options
  ///
  /// \return ALT_S_SUCCESS   success
  /// \return ALT_E_ERROR     error
  ///
  LIBALT_API alt_t Load(const altStr & sFileName, const DWORD dwOptions = D3DXMESH_MANAGED);

  ///
  /// \brief  Release X File
  ///
  LIBALT_API void Release();
  
  ///
  /// \brief  Draw X File
  ///
  LIBALT_API void Draw();

  ///
  /// \brief  Draw X File Color
  ///
  LIBALT_API void DrawColor(int ColorNo);

private:
  struct XFILE *      m_pXFile;
};

#endif
#endif

#endif // ALT_USE_DX