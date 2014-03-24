/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/DirectX10/TgcDX10VertexBuffer.h"
using namespace TgcViewer;



bool TgcDX10VertexBuffer::internalCreate(const void* data)
{
	ID3D10Device* device = ((TgcDX10Renderer*)GuiController::Instance->renderer)->device;

	//DX10 usage
	D3D10_USAGE d3dUsage;
	switch(this->usage)
	{
		case BufferUsage::Default:
			d3dUsage = D3D10_USAGE_DEFAULT;
			break;
		case BufferUsage::Dynamic:
			d3dUsage = D3D10_USAGE_DYNAMIC;
			break;
		case BufferUsage::Immutable:
			d3dUsage = D3D10_USAGE_IMMUTABLE;
			break;
		case BufferUsage::Staging:
			d3dUsage = D3D10_USAGE_STAGING;
			break;
	}

	//Buffer description
	D3D10_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = d3dUsage;;
	vertexBufferDesc.ByteWidth = this->vertexSize * this->numVertices;
    vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;

	if(this->usage == BufferUsage::Dynamic)
	{
		vertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	}

	//Buffer data
	D3D10_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = data;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	//Create buffer
	HRESULT result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &this->buffer);
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("Could not create VertexBuffer");
	}

	return !FAILED(result);
}

void TgcDX10VertexBuffer::internalDispose()
{
	// Release the vertex buffer.
	if(this->buffer)
	{
		this->buffer->Release();
		this->buffer = NULL;
	}
}


void* TgcDX10VertexBuffer::map(BufferMap::Map mapOption)
{
	if(this->usage != BufferUsage::Dynamic)
	{
		GuiController::Instance->logger->logError("The vertexBuffer is not dynamic and cannot be mapped");
		return NULL;
	}

	//DX10 map
	D3D10_MAP d3dMap;
	switch(mapOption)
	{
		case BufferMap::Read:
			d3dMap = D3D10_MAP_READ;
			break;
		case BufferMap::Write:
			d3dMap = D3D10_MAP_WRITE;
			break;
		case BufferMap::ReadWrite:
			d3dMap = D3D10_MAP_READ_WRITE;
			break;
		case BufferMap::WriteDiscard:
			d3dMap = D3D10_MAP_WRITE_DISCARD;
			break;
		case BufferMap::WriteNoOverwrite:
			d3dMap = D3D10_MAP_WRITE_NO_OVERWRITE;
			break;
	}

	void* data;
	HRESULT hResult = this->buffer->Map(d3dMap, 0, &data);
	if(FAILED(hResult))
	{
		GuiController::Instance->logger->logError("Could not map vertexBuffer");
		return NULL;
	}

	return data;
}


void TgcDX10VertexBuffer::unmap()
{
	this->buffer->Unmap();
}

void TgcDX10VertexBuffer::update(const void* data)
{
	/*
	if(this->usage != BufferUsage::Dynamic)
	{
		GuiController::Instance->logger->logError("The vertexBuffer is not dynamic and cannot be update");
		return;
	}

	ID3D10Device* device = ((TgcDX10Renderer*)GuiController::Instance->renderer)->device;

	//D3D10_BOX box;
	device->UpdateSubresource(this->buffer, 0, NULL, data, this->vertexSize, this->vertexSize * this->numVertices);
	*/

	//TODO: check why UpdateSubresource() doesn't work
	void* data2 = this->map(BufferMap::WriteDiscard);
	memcpy(data2, data, this->vertexSize * this->numVertices);
	this->unmap();
}

