/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/TgcIndexBuffer.h"
using namespace TgcViewer;


TgcIndexBuffer::TgcIndexBuffer()
{
	
}


TgcIndexBuffer::TgcIndexBuffer(const TgcIndexBuffer& other)
{
}


TgcIndexBuffer::~TgcIndexBuffer()
{
}


void TgcIndexBuffer::create(int numIndices, const void* data, BufferUsage::Usage usage)
{
	this->numIndices = numIndices;
	this->usage = usage;

	this->internalCreate(data);
}

void TgcIndexBuffer::dispose()
{
	this->internalDispose();
}


