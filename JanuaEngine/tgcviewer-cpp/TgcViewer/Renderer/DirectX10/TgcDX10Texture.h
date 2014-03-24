/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <d3d10_1.h>
#include <d3dx10tex.h>

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/TgcSceneLoader/TgcTexture.h"


namespace TgcViewer
{



/**
* A DirectX 10 Texture
*/
class TgcDX10Texture : public TgcTexture
{

public:

	//Virtual members
	void internalCreateFromFile();
	void internalDispose();



private:


public:

	/**
	* DirectX texture
	*/
	ID3D10ShaderResourceView* dxTexture;

private:

	TextureFormat::Format getTextureFormat(DXGI_FORMAT dxFormat);
	
};




}