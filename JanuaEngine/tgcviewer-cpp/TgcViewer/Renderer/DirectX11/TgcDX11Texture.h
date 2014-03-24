/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <d3d11.h>
#include <d3dx11tex.h>

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/TgcSceneLoader/TgcTexture.h"


namespace TgcViewer
{



/**
* A DirectX 11 Texture
*/
class TgcDX11Texture : public TgcTexture
{

public:

	//Virtual members
	void internalCreateFromFile();
	void internalDispose();



private:

	TextureFormat::Format getTextureFormat(DXGI_FORMAT dxFormat);

public:

	/**
	* DirectX texture
	*/
	ID3D11ShaderResourceView* dxTexture;

private:


	
};




}