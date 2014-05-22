#ifdef ALT_USE_DX   // If you use DirectX, define ALT_USE_DX.
/*--------------------------------------------------------------------------*

  Alternative Llibrary


  Copyright (C) 2007-2013 Azusa Nakano All Rights Reserved.
 
  This program is released under term of the Apache License 2.0.
  See details for http://www.apache.org/licenses/LICENSE-2.0

 *---------------------------------------------------------------------------*/
/**
 * \file    altTexture.h
 * \brief   DirectX texture class
 * \date    2007
 * \author  Azusa Nakano
 */
/*----------------------------------------------------------------*
 * Include
 *----------------------------------------------------------------*/
#include "altTexture.h"
#include "altBase/altStatus.h"

/*----------------------------------------------------------------*
 * Function Implements
 *----------------------------------------------------------------*/
///
/// \brief  Constructor
///
LIBALT_API altTexture::altTexture() :
m_lpTexture (NULL)
{
}

///
/// \brief  Destructor
///
LIBALT_API altTexture::~altTexture()
{
  if (m_lpTexture != NULL) {
    m_lpTexture->Release();
    m_lpTexture = NULL;
  }
}

///
/// \brief  Load Texture
///
/// \param  sFileName [I ] File name
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altTexture::Load(const altStr & sFileName)
{
  HRESULT hr = D3DXCreateTextureFromFileA (aiDX.GetDevice(), sFileName.GetCStr(), & m_lpTexture);
  if (hr != D3D_OK) {
    altStr  sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("sFileName=%s (%s)", sFileName.GetCStr(), DXGetErrorDescription9 (hr)));
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Load Texture
///
/// \param  sFileName   [I ] File Name
/// \param  nWidth      [I ] Width
/// \param  nHeight     [I ] Heigth
/// \param  dwColor     [I ] Color
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
alt_t altTexture::Load(const altStr & sFileName, altUInt nWidth, altUInt nHeight, D3DCOLOR dwColor)
{
  alt_t status;
  status = Load (sFileName, nWidth, nHeight, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, dwColor);
  ALT_ERR_RET (status);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Load Texture
///
/// \param  sFileName   [I ] File Name
/// \param  nWidth      [I ] Width
/// \param  nHeight     [I ] Heigth
/// \param  nMipLevels  [I ] Number of mip levels requested. If this value is zero or D3DX_DEFAULT, a complete mipmap chain is created. If D3DX_FROM_FILE, the size will be taken exactly as it is in the file, and the call will fail if this violates device capabilities. 
/// \param  dwUsage     [I ] 0, D3DUSAGE_RENDERTARGET, or D3DUSAGE_DYNAMIC. Setting this flag to D3DUSAGE_RENDERTARGET indicates that the surface is to be used as a render target. The resource can then be passed to the pNewRenderTarget parameter of the IDirect3DDevice9::SetRenderTarget method. If either D3DUSAGE_RENDERTARGET or D3DUSAGE_DYNAMIC is specified, Pool must be set to D3DPOOL_DEFAULT, and the application should check that the device supports this operation by calling IDirect3D9::CheckDeviceFormat. D3DUSAGE_DYNAMIC indicates that the surface should be handled dynamically. See Using Dynamic Textures. 
/// \param  nFormat     [I ] Member of the D3DFORMAT enumerated type, describing the requested pixel format for the texture. The returned texture might have a different format from that specified by Format. Applications should check the format of the returned texture. If D3DFMT_UNKNOWN, the format is taken from the file. If D3DFMT_FROM_FILE, the format is taken exactly as it is in the file, and the call will fail if this violates device capabilities.
/// \param  nPool       [I ] Member of the D3DPOOL enumerated type, describing the memory class into which the texture should be placed. 
/// \param  dwFilter    [I ] A combination of one or more D3DX_FILTER constants controlling how the image is filtered. Specifying D3DX_DEFAULT for this parameter is the equivalent of specifying D3DX_FILTER_TRIANGLE | D3DX_FILTER_DITHER. 
/// \param  dwMipFilter [I ] A combination of one or more D3DX_FILTER constants controlling how the image is filtered. Specifying D3DX_DEFAULT for this parameter is the equivalent of specifying D3DX_FILTER_BOX. In addition, use bits 27-31 to specify the number of mip levels to be skipped (from the top of the mipmap chain) when a .dds texture is loaded into memory; this allows you to skip up to 32 levels.
/// \param  dwColor     [I ] Color
/// \param  pSrcInfo    [IO] Pointer to a D3DXIMAGE_INFO structure to be filled in with a description of the data in the source image file, or NULL. 
/// \param  pPalette    [ O] Pointer to a PALETTEENTRY structure, representing a 256-color palette to fill in, or NULL.
///
/// \return ALT_S_SUCCESS   success
/// \return ALT_E_ERROR     error
///
LIBALT_API alt_t altTexture::Load(const altStr & sFileName, altUInt nWidth, altUInt nHeight, altUInt nMipLevels, DWORD dwUsage, D3DFORMAT nFormat, D3DPOOL nPool, DWORD dwFilter, DWORD dwMipFilter, D3DCOLOR dwColor, D3DXIMAGE_INFO * pSrcInfo, PALETTEENTRY * pPalette)
{
  if (nWidth == 0) {
    nWidth = D3DX_DEFAULT;
  }

  if (nHeight == 0) {
    nHeight = D3DX_DEFAULT;
  }
  
  HRESULT hr = D3DXCreateTextureFromFileExA (aiDX.GetDevice(), sFileName.GetCStr(), nWidth, nHeight, nMipLevels, dwUsage, nFormat, nPool, dwFilter, dwMipFilter, dwColor, pSrcInfo, pPalette, & m_lpTexture);
  if (hr != D3D_OK) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, sBuf.Format ("sFileName=%s (%s)", sFileName.GetCStr(), DXGetErrorDescription9 (hr)));
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Set texture
///
/// \param  dwStage [I ] stage
///
/// \return ALT_S_SUCCESS   success
///
LIBALT_API alt_t altTexture::SetTexture(const DWORD dwStage)
{
  aiDX.GetDevice()->SetTexture (dwStage, m_lpTexture);
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Draw
///
/// \param  pRect         [I ] Pointer to a RECT structure that indicates the portion of the source texture to use for the sprite. If this parameter is NULL, then the entire source image is used for the sprite.
/// \param  pVec3Center   [I ] Pointer to a D3DXVECTOR3 vector that identifies the center of the sprite. If this argument is NULL, the point (0,0,0) is used, which is the upper-left corner.
/// \param  pVec3Position [I ] Pointer to a D3DXVECTOR3 vector that identifies the position of the sprite. If this argument is NULL, the point (0,0,0) is used, which is the upper-left corner.
/// \param  dwColor       [I ] D3DCOLOR type. The color and alpha channels are modulated by this value. A value of 0xFFFFFFFF maintains the original source color and alpha data. Use the D3DCOLOR_RGBA macro to help generate this color.
///
/// \return ALT_S_SUCCESS success
/// \return ALT_E_ERROR   error
///
LIBALT_API alt_t altTexture::Draw(const RECT * pRect, const D3DXVECTOR3 * pVec3Center, const D3DXVECTOR3 * pVec3Position, D3DCOLOR dwColor)
{
  if (m_lpTexture == NULL) {
    ALT_RET_P (ALT_E_ERROR, "m_lpTexture is NULL");
  }
  HRESULT hr = aiDX.GetSprite()->Draw (m_lpTexture, pRect, pVec3Center, pVec3Position, dwColor);
  if (hr != S_OK) {
    altStr sBuf;
    ALT_RET_P (ALT_E_ERROR, DXGetErrorDescription9A (hr));
  }
  ALT_RET (ALT_S_SUCCESS);
}

///
/// \brief  Get raw pointer of texture
///
/// \return raw pointer of texture
///
LIBALT_API LPDIRECT3DTEXTURE9 altTexture::GetRawTexture()
{
  return (m_lpTexture);
}

#endif // ALT_USE_DX
