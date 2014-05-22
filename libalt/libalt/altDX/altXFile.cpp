#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altXFile.cpp
 * \brief   DirectX X file class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altXFile.h"
#include "altBase/altStatus.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altXFile::altXFile() :
m_pXFile (NULL)
{
}

///
/// \brief  Destructor
///
LIBALT_API altXFile::~altXFile()
{
  Release();
}

///
/// \brief  Load X File
///
/// \param  sFileName   [I ] File Name
/// \param  dwOptions   [I ] Options
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altXFile::Load(const altStr & sFileName, const DWORD dwOptions)
{
	LPD3DXBUFFER lpD3DXBuffer;

  m_pXFile = new XFILE();
  HRESULT hRet = D3DXLoadMeshFromXA (sFileName.GetCStr(), dwOptions, aiDX.GetDevice(), NULL, & lpD3DXBuffer, NULL, &(m_pXFile->NumMaterial), &(m_pXFile->lpMesh));
  if (hRet != D3D_OK) {
    ALT_RET_P (ALT_E_ERROR, sFileName.GetCStr());
  }

	m_pXFile->Mat = new D3DMATERIAL9[m_pXFile->NumMaterial];
	m_pXFile->Tex = new LPDIRECT3DTEXTURE9[m_pXFile->NumMaterial];

	D3DXMATERIAL* D3DXMat = (D3DXMATERIAL *)lpD3DXBuffer->GetBufferPointer();

	DWORD i;
	for (i = 0; i < m_pXFile->NumMaterial; i++) {
		m_pXFile->Mat[i] = D3DXMat[i].MatD3D;
		m_pXFile->Mat[i].Ambient = m_pXFile->Mat[i].Diffuse;

    altStr  sTextureFileName;
    altStr  sDirName;
    altInt  nIndex = sFileName.FindLastOfChar ("\\/");
    if (nIndex >= 0) {
      sDirName = sFileName.SubStr (0, nIndex);
    }
    sTextureFileName = sDirName + D3DXMat[i].pTextureFilename;

    if (FAILED (D3DXCreateTextureFromFileA (aiDX.GetDevice(), sTextureFileName.GetCStr(), &(m_pXFile->Tex[i])))) {
			m_pXFile->Tex[i] = NULL;
		}
	}

	lpD3DXBuffer->Release();

  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Release X File
///
LIBALT_API void altXFile::Release()
{
	DWORD i;

  if (m_pXFile != NULL) {
	  delete[] m_pXFile->Mat;
	  for (i = 0; i < m_pXFile->NumMaterial; i++) {
		  if (m_pXFile->Tex[i] != NULL) {
			  m_pXFile->Tex[i]->Release();
		  }
	  }
	  delete[] m_pXFile->Tex;
	  m_pXFile->lpMesh->Release();
    delete m_pXFile;
    m_pXFile = NULL;
  }
}

///
/// \brief  Draw X File
///
LIBALT_API void altXFile::Draw()
{
	for (DWORD i = 0; i < m_pXFile->NumMaterial; i++){
		aiDX.GetDevice()->SetMaterial (& (m_pXFile->Mat[i]));
		aiDX.GetDevice()->SetTexture (0, m_pXFile->Tex[i]);
		m_pXFile->lpMesh->DrawSubset(i);
	}
}

///
/// \brief  Draw X File Color
///
LIBALT_API void altXFile::DrawColor(int ColorNo)
{
	D3DMATERIAL9 Mat;
	for (DWORD i = 0; i < m_pXFile->NumMaterial; i++) {
		Mat = m_pXFile->Mat[i];
		//1番目のマテリアルなら
		if(i == 1){
			//ColorNoによって、マテリアル色変更

      //1ビット目が1なら赤を含める
			if(ColorNo & 0x01){
				Mat.Diffuse.r = 1.0f;
			}
      else{
				Mat.Diffuse.r = 0.0f;
			}
     
      //2ビット目が1なら緑を含める
			if(ColorNo & 0x02){
				Mat.Diffuse.g = 1.0f;
			}
      else{
				Mat.Diffuse.g = 0.0f;
			}

      //3ビット目が1なら青を含める
			if(ColorNo & 0x04){
				Mat.Diffuse.b = 1.0f;
			}else{
				Mat.Diffuse.b = 0.0f;
			}

			//EmissiveはDiffuseを元に、やや暗めに設定
			Mat.Emissive.r = Mat.Diffuse.r * 0.4f;
			Mat.Emissive.g = Mat.Diffuse.g * 0.4f;
			Mat.Emissive.b = Mat.Diffuse.b * 0.4f;
		}

		aiDX.GetDevice()->SetMaterial (& Mat);
		aiDX.GetDevice()->SetTexture (0, m_pXFile->Tex[i]);
		m_pXFile->lpMesh->DrawSubset(i);
	}
}

#endif // ALT_USE_DX
