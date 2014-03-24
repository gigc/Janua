/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:


//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Renderer/TgcRendererGlobals.h"
#include "TgcViewer/Renderer/TgcInputLayout.h"


namespace TgcViewer
{



/**
* An abstract Vertex Buffer.
* Each renderer implement the concrete class
*/
class TgcVertexBuffer
{

public:

	TgcVertexBuffer();
	TgcVertexBuffer(const TgcVertexBuffer&);
	~TgcVertexBuffer();

	/**
	* Creates a new vertex buffer and fills its data
	* @param numVertices the number of vertices in the buffer
	* @param inputLayout Input layout of the buffer
	* @param data the vertices array to fill in the vertex buffer
	* @param usage the usage mode of the vertex buffer
	*/
	void create(int numVertices, TgcInputLayout* inputLayout, const void* data, BufferUsage::Usage usage = BufferUsage::Default);

	/**
	* Destroy the vertex buffer
	*/
	void dispose();

	/**
	* Map the vertexBuffer to cpu data.
	* The BufferUsage must be Dynamic to write the data
	*/
	virtual void* map(BufferMap::Map mapOption) = 0;

	/**
	* Unmap the previously mapped buffer
	*/
	virtual void unmap() = 0;

	/**
	* Updates the content of the vertex buffer.
	* It overrides the existing content.
	* It is usually faster than using map() and unmap()
	*/
	virtual void update(const void* data) = 0;

	/**
	* {Renderer-dependent}
	* Creates a new vertex buffer
	* @param the vertices array to fill in the vertex buffer
	*/
	virtual bool internalCreate(const void* data) = 0;

	/**
	* {Renderer-dependent}
	* Destroys the vertex buffer
	*/
	virtual void internalDispose() = 0;

private:
	

public:

	/**
	* Number of vertices
	*/
	int numVertices;

	/**
	* Size in bytes of one vertex
	*/
	unsigned int vertexSize;

	/**
	* Usage of the buffer
	*/
	BufferUsage::Usage usage;

	/**
	* Input layout of the buffer
	*/
	TgcInputLayout* inputLayout;

private:


};




}