/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <d3d11.h>
#include <d3dx11async.h>
#include <unordered_map>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Renderer/TgcEffect.h"


namespace TgcViewer
{



/**
* DirectX 11 Effect
*/
class TgcDX11Effect : public TgcEffect
{

public:


	//Virtual members
	void internalCreate();
	void internalAddSampler(TgcEffectValues::Sampler sampler);
	void internalAddConstantBuffer(TgcEffectValues::ConstantBuffer constantBuffer);
	void init(const TgcVertexBuffer* vertexBuffer);
	void begin();
	void setTexture(string name, const TgcTexture* texture);
	void setConstantBuffer(string name, const void* bufferData);
	void end();
	void dispose();



	string getErrorMessage(ID3D10Blob* dxErrorMessage);
	D3D11_FILTER TgcDX11Effect::getFilter(TgcEffectValues::Filter filter);
	D3D11_TEXTURE_ADDRESS_MODE TgcDX11Effect::getAddressMode(TgcEffectValues::AddressMode addressMode);


private:


public:

	/**
	* Shader targets to compile
	*/
	static const LPCSTR VS_SHADER_TARGET;
	static const LPCSTR PS_SHADER_TARGET;


	/**
	* Buffer to the vertex shader
	*/
	ID3D10Blob* vertexShaderBuffer;

	/**
	* Vertex shader program
	*/
	ID3D11VertexShader* vertexShader;

	/**
	* Pixel shader program
	*/
	ID3D11PixelShader* pixelShader;

	/**
	* Sampler states map
	*/
	unordered_map<string, ID3D11SamplerState*> dxSampleStates;

	/**
	* Constant buffers map
	*/
	unordered_map<string, ID3D11Buffer*> dxConstantBuffers;

private:

	
};




}