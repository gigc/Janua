/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/DirectX11/TgcDX11Effect.h"
using namespace TgcViewer;

const LPCSTR TgcDX11Effect::VS_SHADER_TARGET = "vs_5_0";
const LPCSTR TgcDX11Effect::PS_SHADER_TARGET = "ps_5_0";


void TgcDX11Effect::internalCreate()
{
	ID3D11Device* device = ((TgcDX11Renderer*)GuiController::Instance->renderer)->device;

	HRESULT result;
	ID3D10Blob* errorMessage = NULL;
	D3D_SHADER_MACRO* pDefines = NULL;
	ID3DInclude* pInclude = NULL;
	UINT flags2 = 0;

	//Compile vertex shader
	this->vertexShaderBuffer = NULL;
	result = D3DX11CompileFromFile(this->filePath.c_str(), pDefines, pInclude, this->description.vsFunctionName.c_str(), 
		TgcDX11Effect::VS_SHADER_TARGET, D3D10_SHADER_PACK_MATRIX_ROW_MAJOR | D3D10_SHADER_ENABLE_STRICTNESS, flags2, NULL, 
		&(this->vertexShaderBuffer), &errorMessage, NULL);
	if(FAILED(result))
	{
		if(errorMessage)
		{
			GuiController::Instance->logger->logError("Error loading DX11 vertex shader: " + this->description.vsFunctionName 
				+ ", Path: " + this->filePath + ", Error: " + getErrorMessage(errorMessage));
		}
		else
		{
			GuiController::Instance->logger->logError("Error loading DX11 vertex shader. Could not find file: " + this->filePath);
		}
		return;
	}


	//Compile pixel shader
	ID3D10Blob* pixelShaderBuffer = NULL;
	result = D3DX11CompileFromFile(this->filePath.c_str(), pDefines, pInclude, this->description.psFunctionName.c_str(), 
		TgcDX11Effect::PS_SHADER_TARGET, D3D10_SHADER_PACK_MATRIX_ROW_MAJOR | D3D10_SHADER_ENABLE_STRICTNESS, flags2, NULL, 
		&pixelShaderBuffer, &errorMessage, NULL);
	if(FAILED(result))
	{
		if(errorMessage)
		{
			GuiController::Instance->logger->logError("Error loading DX11 pixel shader: " + this->description.psFunctionName 
				+ ", Path: " + this->filePath + ", Error: " + getErrorMessage(errorMessage));
		}
		else
		{
			GuiController::Instance->logger->logError("Error loading DX11 pixel shader. Could not find file: " + this->filePath);
		}
		return;
	}

	//Create the vertex shader from the buffer.
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), this->vertexShaderBuffer->GetBufferSize(), NULL, &(this->vertexShader));
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("Error creating DX11 vertex shader: " + this->description.vsFunctionName + ", Path: " + this->filePath);
	}

    //Create the pixel shader from the buffer.
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &(this->pixelShader));
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("Error creating DX11 pixel shader: " + this->description.psFunctionName + ", Path: " + this->filePath);
	}

	//Release pixelShaderBuffer (vertexShaderBuffer no because is used later to create the InputLayout)
	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;
}


void TgcDX11Effect::init(const TgcVertexBuffer* vertexBuffer)
{
	ID3D11Device* device = ((TgcDX11Renderer*)GuiController::Instance->renderer)->device;
	TgcDX11InputLayout* inputLayout = ((TgcDX11InputLayout*)((TgcDX11VertexBuffer*)vertexBuffer)->inputLayout);

	//Create the input layout
	if(inputLayout->layout == NULL)
	{
		HRESULT result = device->CreateInputLayout(inputLayout->layoutDesc, inputLayout->elements.size(), 
		this->vertexShaderBuffer->GetBufferPointer(), this->vertexShaderBuffer->GetBufferSize(), &(inputLayout->layout));
		if(FAILED(result))
		{
			GuiController::Instance->logger->logError("Could not create InputLayout");
		}
	}
}


void TgcDX11Effect::internalAddSampler(TgcEffectValues::Sampler sampler)
{
	ID3D11Device* device = ((TgcDX11Renderer*)GuiController::Instance->renderer)->device;

	//Create a texture sampler state description.
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = this->getFilter(sampler.filter);
	samplerDesc.AddressU = this->getAddressMode(sampler.addressU);
	samplerDesc.AddressV = this->getAddressMode(sampler.addressV);
	samplerDesc.AddressW = this->getAddressMode(sampler.addressW);
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = sampler.borderColor.R;
	samplerDesc.BorderColor[1] = sampler.borderColor.G;
	samplerDesc.BorderColor[2] = sampler.borderColor.B;
	samplerDesc.BorderColor[3] = sampler.borderColor.A;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//Create the texture sampler state.
	ID3D11SamplerState* samplerState = NULL;
	HRESULT result = device->CreateSamplerState(&samplerDesc, &samplerState);
	this->dxSampleStates[sampler.textureName] = samplerState;
}


void TgcDX11Effect::internalAddConstantBuffer(TgcEffectValues::ConstantBuffer constantBuffer)
{
	ID3D11Device* device = ((TgcDX11Renderer*)GuiController::Instance->renderer)->device;

	//Set buffer desc
	D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = constantBuffer.size;
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// Create the constant buffer
	ID3D11Buffer* cBuffer = NULL;
	HRESULT result = device->CreateBuffer(&bufferDesc, NULL, &cBuffer);
	this->dxConstantBuffers[constantBuffer.name] = cBuffer;
}


string TgcDX11Effect::getErrorMessage(ID3D10Blob* dxErrorMessage)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	string errorMessage = "";

	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(dxErrorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = dxErrorMessage->GetBufferSize();

	// Write out the error message.
	for(i=0; i<bufferSize; i++)
	{
		errorMessage += compileErrors[i];
	}

	// Release the error message.
	dxErrorMessage->Release();
	dxErrorMessage = 0;

	return errorMessage;
}

D3D11_FILTER TgcDX11Effect::getFilter(TgcEffectValues::Filter filter)
{
	switch(filter)
	{
	case TgcEffectValues::MinMagMipPoint:
		return D3D11_FILTER_MIN_MAG_MIP_POINT;
	case TgcEffectValues::MinMagMipLinear:
		return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	case TgcEffectValues::Anisotropic:
		return D3D11_FILTER_ANISOTROPIC;
	}

	return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
}

D3D11_TEXTURE_ADDRESS_MODE TgcDX11Effect::getAddressMode(TgcEffectValues::AddressMode addressMode)
{
	switch(addressMode)
	{
	case TgcEffectValues::Wrap:
		return D3D11_TEXTURE_ADDRESS_WRAP;
	case TgcEffectValues::Mirror:
		return D3D11_TEXTURE_ADDRESS_MIRROR;
	case TgcEffectValues::Border:
		return D3D11_TEXTURE_ADDRESS_BORDER;
	case TgcEffectValues::Clamp:
		return D3D11_TEXTURE_ADDRESS_CLAMP;
	case TgcEffectValues::MirrorOnce:
		return D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
	}

	return D3D11_TEXTURE_ADDRESS_WRAP;
}


void TgcDX11Effect::begin()
{
	ID3D11DeviceContext* deviceContext = ((TgcDX11Renderer*)GuiController::Instance->renderer)->deviceContext;

	//Set the vertex and pixel shaders that will be used to render
    deviceContext->VSSetShader(this->vertexShader, NULL, 0);
    deviceContext->PSSetShader(this->pixelShader, NULL, 0);
}

void TgcDX11Effect::end()
{
	//TODO: ver si hay que quitar los shaders y los sampler states
}


void TgcDX11Effect::setTexture(string name, const TgcTexture* texture)
{
	ID3D11DeviceContext* deviceContext = ((TgcDX11Renderer*)GuiController::Instance->renderer)->deviceContext;

	TgcEffectValues::Sampler sampler = this->samplers[name];
	ID3D11SamplerState* dxSampler = this->dxSampleStates[name];
	TgcDX11Texture* dxTexture = (TgcDX11Texture*)texture;

	//Set the sampler and texture for pixel shader
	if(sampler.shaderType == TgcEffectValues::PS)
	{
		deviceContext->PSSetSamplers(sampler.slot, 1, &dxSampler);
		deviceContext->PSSetShaderResources(sampler.slot, 1, &(dxTexture->dxTexture));
	}
	//Set the sampler and texture for vertex shader
	else if(sampler.shaderType == TgcEffectValues::VS)
	{
		deviceContext->VSSetSamplers(sampler.slot, 1, &dxSampler);
		deviceContext->VSSetShaderResources(sampler.slot, 1, &(dxTexture->dxTexture));
	}
	else if(sampler.shaderType == TgcEffectValues::VS_AND_PS)
	{
		deviceContext->VSSetSamplers(sampler.slot, 1, &dxSampler);
		deviceContext->PSSetSamplers(sampler.slot, 1, &dxSampler);

		deviceContext->VSSetShaderResources(sampler.slot, 1, &(dxTexture->dxTexture));
		deviceContext->PSSetShaderResources(sampler.slot, 1, &(dxTexture->dxTexture));
	}
	
}

void TgcDX11Effect::setConstantBuffer(string name, const void* bufferData)
{
	ID3D11DeviceContext* deviceContext = ((TgcDX11Renderer*)GuiController::Instance->renderer)->deviceContext;

	TgcEffectValues::ConstantBuffer cBuffer = this->constantBuffers[name];
	ID3D11Buffer* dxCbuffer = this->dxConstantBuffers[name];

	//Map
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT result = deviceContext->Map(dxCbuffer, cBuffer.slot, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	//Copy values
	memcpy(mappedResource.pData, bufferData, cBuffer.size);

	//Unmap
	deviceContext->Unmap(dxCbuffer, cBuffer.slot);

	//Set buffer in VS o PS
	if(cBuffer.shaderType == TgcEffectValues::VS)
	{
		deviceContext->VSSetConstantBuffers(cBuffer.slot, 1, &dxCbuffer);
	}
	else if(cBuffer.shaderType == TgcEffectValues::PS)
	{
		deviceContext->PSSetConstantBuffers(cBuffer.slot, 1, &dxCbuffer);
	}
	else if(cBuffer.shaderType == TgcEffectValues::VS_AND_PS)
	{
		deviceContext->VSSetConstantBuffers(cBuffer.slot, 1, &dxCbuffer);
		deviceContext->PSSetConstantBuffers(cBuffer.slot, 1, &dxCbuffer);
	}
}



void TgcDX11Effect::dispose()
{
	//Constant buffers
	for (unordered_map<string, ID3D11Buffer*>::iterator it = this->dxConstantBuffers.begin(); it != this->dxConstantBuffers.end(); ++it) 
	{
		ID3D11Buffer* cBuffer = it->second;
		if(cBuffer)
		{
			cBuffer->Release();
			cBuffer = 0;
		}
	}

	//Sampler states
	for (unordered_map<string, ID3D11SamplerState*>::iterator it = this->dxSampleStates.begin(); it != this->dxSampleStates.end(); ++it) 
	{
		ID3D11SamplerState* sampler = it->second;
		if(sampler)
		{
			sampler->Release();
			sampler = 0;
		}
	}

	//vertexShaderBuffer
	if(this->vertexShaderBuffer)
	{
		this->vertexShaderBuffer->Release();
		this->vertexShaderBuffer = 0;
	}

	//vertexShader
	if(this->vertexShader)
	{
		this->vertexShader->Release();
		this->vertexShader = 0;
	}

	//pixelShader
	if(this->pixelShader)
	{
		this->pixelShader->Release();
		this->pixelShader = 0;
	}
}


