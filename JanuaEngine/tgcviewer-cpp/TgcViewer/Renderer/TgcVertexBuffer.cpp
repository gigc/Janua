/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/TgcVertexBuffer.h"
using namespace TgcViewer;


TgcVertexBuffer::TgcVertexBuffer()
{
	
}


TgcVertexBuffer::TgcVertexBuffer(const TgcVertexBuffer& other)
{
}


TgcVertexBuffer::~TgcVertexBuffer()
{
}


void TgcVertexBuffer::create(int numVertices, TgcInputLayout* inputLayout, const void* data, BufferUsage::Usage usage)
{
	this->numVertices = numVertices;
	this->inputLayout = inputLayout;
	this->vertexSize = inputLayout->size;;
	this->usage = usage;

	this->internalCreate(data);
}

void TgcVertexBuffer::dispose()
{
	this->inputLayout->dispose();
	this->internalDispose();
}


