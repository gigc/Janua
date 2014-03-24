/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#pragma once



//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Renderer/TgcRenderer.h"



//All avaliable renderers
#define TGC_DX11_RENDERER TgcDX11Renderer
#define TGC_DX10_RENDERER TgcDX10Renderer
#define TGC_OPENGL_RENDERER TgcOpenGLRenderer
#define TGC_DX9_RENDERER TgcDX9Renderer


//Renderer to be used by the engine (change this to select another renderer)
//#define TGC_CURRENT_RENDERER TGC_DX11_RENDERER
#define TGC_CURRENT_RENDERER TGC_DX10_RENDERER


//DX11 Renderer conditional include
#if TGC_CURRENT_RENDERER == TGC_DX11_RENDERER
#include "TgcViewer/Renderer/DirectX11/TgcDX11Renderer.h"
#endif


//DX10 Renderer conditional include
#if TGC_CURRENT_RENDERER == TGC_DX10_RENDERER
#include "TgcViewer/Renderer/DirectX10/TgcDX10Renderer.h"
#endif

/*
//OpenGL Renderer conditional include
#if TGC_CURRENT_RENDERER == TGC_OPENGL_RENDERER
#include "TgcViewer/Renderer/OpenGL/TgcOpenGLRenderer.h"
#endif
*/

/*
//DX9 Renderer conditional include
#if TGC_CURRENT_RENDERER == TGC_DX9_RENDERER
#include "TgcViewer/Renderer/DirectX9/TgcDX9Renderer.h"
#endif
*/



namespace TgcViewer
{


/**
* Factory for instancing all renderer-dependent objects
*/
class TgcRendererFactory
{

public:

	/**
	* Creates a new TgcRenderer using the value set in TGC_CURRENT_RENDERER
	*/
	static TgcRenderer* createRenderer();

private:

	TgcRendererFactory();
	
};




}