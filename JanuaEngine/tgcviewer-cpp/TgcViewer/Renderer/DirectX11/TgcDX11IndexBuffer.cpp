/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/DirectX11/TgcDX11IndexBuffer.h"
using namespace TgcViewer;



bool TgcDX11IndexBuffer::internalCreate(const void* data)
{
	ID3D11Device* device = ((TgcDX11Renderer*)GuiController::Instance->renderer)->device;

	//DX11 usage
	D3D11_USAGE d3dUsage;
	switch(this->usage)
	{
		case BufferUsage::Default:
			d3dUsage = D3D11_USAGE_DEFAULT;
			break;
		case BufferUsage::Dynamic:
			d3dUsage = D3D11_USAGE_DYNAMIC;
			break;
		case BufferUsage::Immutable:
			d3dUsage = D3D11_USAGE_IMMUTABLE;
			break;
		case BufferUsage::Staging:
			d3dUsage = D3D11_USAGE_STAGING;
			break;
	}

	//Buffer description
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = d3dUsage;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * this->numIndices;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	//Buffer data
	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = data;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	//Create buffer
	HRESULT result = device->CreateBuffer(&indexBufferDesc, &indexData, &this->buffer);
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("Could not create IndexBuffer");
	}

	return !FAILED(result);
}


void TgcDX11IndexBuffer::internalDispose()
{
	// Release the vertex buffer.
	if(this->buffer)
	{
		this->buffer->Release();
		this->buffer = NULL;
	}
}


