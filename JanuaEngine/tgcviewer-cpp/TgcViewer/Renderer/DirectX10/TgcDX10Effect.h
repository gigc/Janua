/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <d3d10_1.h>
#include <d3dx10async.h>
#include <unordered_map>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Renderer/TgcEffect.h"


namespace TgcViewer
{



/**
* DirectX 10 Effect
*/
class TgcDX10Effect : public TgcEffect
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
	D3D10_FILTER TgcDX10Effect::getFilter(TgcEffectValues::Filter filter);
	D3D10_TEXTURE_ADDRESS_MODE TgcDX10Effect::getAddressMode(TgcEffectValues::AddressMode addressMode);


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
	ID3D10VertexShader* vertexShader;

	/**
	* Pixel shader program
	*/
	ID3D10PixelShader* pixelShader;

	/**
	* Sampler states map
	*/
	unordered_map<string, ID3D10SamplerState*> dxSampleStates;

	/**
	* Constant buffers map
	*/
	unordered_map<string, ID3D10Buffer*> dxConstantBuffers;

private:

	
};




}