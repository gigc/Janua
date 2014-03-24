/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <d3d11.h>

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Renderer/TgcIndexBuffer.h"


namespace TgcViewer
{



/**
* DirectX 11 Index Buffer
*/
class TgcDX11IndexBuffer : public TgcIndexBuffer
{

public:

	//Virtual members
	bool internalCreate(const void* data);
	void internalDispose();

private:


public:

	/**
	* DirectX buffer
	*/
	ID3D11Buffer* buffer;

private:

	
};




}