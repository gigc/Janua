/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <d3d10_1.h>


//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Renderer/TgcVertexBuffer.h"


namespace TgcViewer
{



/**
* A DirectX 10 vertex buffer
*/
class TgcDX10VertexBuffer : public TgcVertexBuffer
{

public:

	//Virtual members
	bool internalCreate(const void* data);
	void internalDispose();
	void* map(BufferMap::Map mapOption);
	void unmap();
	void update(const void* data);

private:
	

public:

	/**
	* DirectX buffer
	*/
	ID3D10Buffer* buffer;

private:

	

};




}