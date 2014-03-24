/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/DirectX10/TgcDX10Texture.h"
using namespace TgcViewer;


void TgcDX10Texture::internalCreateFromFile()
{
	//Create texture from file
	ID3D10Device* device = ((TgcDX10Renderer*)GuiController::Instance->renderer)->device;
	HRESULT result = D3DX10CreateShaderResourceViewFromFile(device, this->filePath.c_str(), NULL, NULL, &(this->dxTexture), NULL);
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("Could not load texture: " + this->fileName + ", Path: " + this->filePath);
		return;
	}

	//Get width and height
	ID3D10Resource* resource;
	this->dxTexture->GetResource(&resource);
	D3D10_TEXTURE2D_DESC desc2D;
	((ID3D10Texture2D*)resource)->GetDesc(&desc2D);

	this->width = desc2D.Width;
	this->height = desc2D.Height;
	this->format = getTextureFormat(desc2D.Format);

	resource->Release();
}


void TgcDX10Texture::internalDispose()
{
	if(this->dxTexture)
	{
		this->dxTexture->Release();
		this->dxTexture = 0;
	}
}

TextureFormat::Format TgcDX10Texture::getTextureFormat(DXGI_FORMAT dxFormat)
{
	switch(dxFormat)
	{
	//Common case
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		return TextureFormat::R8G8B8A8_UNORM;

	case DXGI_FORMAT_R8_UINT:
		return TextureFormat::R8_UINT;
	case DXGI_FORMAT_R8_SINT:
		return TextureFormat::R8_SINT;
	case DXGI_FORMAT_R8_UNORM:
		return TextureFormat::R8_UNORM;
	case DXGI_FORMAT_R16_UINT:
		return TextureFormat::R16_UINT;
	case DXGI_FORMAT_R16_SINT:
		return TextureFormat::R16_SINT;
	case DXGI_FORMAT_R16_UNORM:
		return TextureFormat::R16_UNORM;
	case DXGI_FORMAT_R16_FLOAT:
		return TextureFormat::R16_FLOAT;
	case DXGI_FORMAT_R8G8_UINT:
		return TextureFormat::R8G8_UINT;
	case DXGI_FORMAT_R8G8_SINT:
		return TextureFormat::R8G8_SINT;
	case DXGI_FORMAT_R8G8_UNORM:
		return TextureFormat::R8G8_UNORM;
	case DXGI_FORMAT_R32_UINT:
		return TextureFormat::R32_UINT;
	case DXGI_FORMAT_R32_SINT:
		return TextureFormat::R32_SINT;
	case DXGI_FORMAT_R32_FLOAT:
		return TextureFormat::R32_FLOAT;
	case DXGI_FORMAT_R16G16_UINT:
		return TextureFormat::R16G16_UINT;
	case DXGI_FORMAT_R16G16_SINT:
		return TextureFormat::R16G16_SINT;
	case DXGI_FORMAT_R16G16_UNORM:
		return TextureFormat::R16G16_UNORM;
	case DXGI_FORMAT_R16G16_FLOAT:
		return TextureFormat::R16G16_FLOAT;
	case DXGI_FORMAT_R8G8B8A8_UINT:
		return TextureFormat::R8G8B8A8_UINT;
	case DXGI_FORMAT_R8G8B8A8_SINT:
		return TextureFormat::R8G8B8A8_SINT;
	case DXGI_FORMAT_R32G32_UINT:
		return TextureFormat::R32G32_UINT;
	case DXGI_FORMAT_R32G32_SINT:
		return TextureFormat::R32G32_SINT;
	case DXGI_FORMAT_R32G32_FLOAT:
		return TextureFormat::R32G32_FLOAT;
	case DXGI_FORMAT_R32G32B32_UINT:
		return TextureFormat::R32G32B32_UINT;
	case DXGI_FORMAT_R32G32B32_SINT:
		return TextureFormat::R32G32B32_SINT;
	case DXGI_FORMAT_R32G32B32_FLOAT:
		return TextureFormat::R32G32B32_FLOAT;
	case DXGI_FORMAT_R16G16B16A16_UINT:
		return TextureFormat::R16G16B16A16_UINT;
	case DXGI_FORMAT_R16G16B16A16_SINT:
		return TextureFormat::R16G16B16A16_SINT;
	case DXGI_FORMAT_R16G16B16A16_UNORM:
		return TextureFormat::R16G16B16A16_UNORM;
	case DXGI_FORMAT_R16G16B16A16_FLOAT:
		return TextureFormat::R16G16B16A16_FLOAT;
	case DXGI_FORMAT_R32G32B32A32_UINT:
		return TextureFormat::R32G32B32A32_UINT;
	case DXGI_FORMAT_R32G32B32A32_SINT:
		return TextureFormat::R32G32B32A32_SINT;
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
		return TextureFormat::R32G32B32A32_FLOAT;
	}
	return TextureFormat::R8G8B8A8_UNORM;
}

