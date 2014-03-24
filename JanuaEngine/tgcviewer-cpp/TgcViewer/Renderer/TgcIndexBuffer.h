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


namespace TgcViewer
{



/**
* An abstract Index Buffer.
* Each renderer implement the concrete class
*/
class TgcIndexBuffer
{

public:

	TgcIndexBuffer();
	TgcIndexBuffer(const TgcIndexBuffer&);
	~TgcIndexBuffer();

	/**
	* Creates a new vertex buffer and fills its data
	* @param numIndices the number of indices in the buffer
	* @param data the index array to fill in the index buffer
	* @param usage the usage mode of the index buffer
	*/
	void create(int numIndices, const void* data, BufferUsage::Usage usage = BufferUsage::Default);

	/**
	* Destroy the index buffer
	*/
	void dispose();

	/**
	* {Renderer-dependent}
	* Creates a new index buffer
	* @param the index array to fill in the index buffer
	*/
	virtual bool internalCreate(const void* data) = 0;

	/**
	* {Renderer-dependent}
	* Destroys the index buffer
	*/
	virtual void internalDispose() = 0;

private:
	

public:

	/**
	* Number of indices
	*/
	int numIndices;

	/**
	* Usage of the buffer
	*/
	BufferUsage::Usage usage;


private:

	
};




}