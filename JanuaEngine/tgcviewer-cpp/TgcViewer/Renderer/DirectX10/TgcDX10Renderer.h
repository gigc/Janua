/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d10_1.h>
#include <d3dx10.h>


//Linking
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10.lib")


//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Renderer/TgcRenderer.h"
#include "TgcViewer/Renderer/DirectX10/TgcDX10Texture.h"
#include "TgcViewer/Renderer/DirectX10/TgcDX10VertexBuffer.h"
#include "TgcViewer/Renderer/DirectX10/TgcDX10IndexBuffer.h"
#include "TgcViewer/Renderer/DirectX10/TgcDX10InputLayout.h"
#include "TgcViewer/Renderer/DirectX10/TgcDX10Effect.h"
#include "TgcViewer/Renderer/DirectX10/TgcDX10Shaders.h"


namespace TgcViewer
{


/**
* Renderer for DirectX 10
*/
class TgcDX10Renderer : public TgcRenderer
{

public:

	TgcDX10Renderer();
	TgcDX10Renderer(const TgcDX10Renderer&);
	~TgcDX10Renderer();


	//Virtual members
	bool init();
	void shutdown();
	void beginScene();
	void endScene();
	void setVertexBuffer(const TgcVertexBuffer* vbuffer, unsigned int slot = 0, unsigned int offset = 0);
	void setIndexBuffer(const TgcIndexBuffer* ibuffer, unsigned int offset = 0);
	void drawIndexed(PrimitiveTopology::Topology topology, unsigned int indexCount, unsigned int startIndexLocation = 0);
	void draw(PrimitiveTopology::Topology topology, unsigned int vertexCount, unsigned int startVertexLocation= 0);
	void enableAlphaBlending(bool enable);
	void enableDepthTest(bool enable);
	void setFillMode(FillMode::Mode mode);

	TgcTexture* createTgcTextureInstance();
	TgcVertexBuffer* createTgcVertexBufferInstance();
	TgcIndexBuffer* createTgcIndexBufferInstance();
	TgcInputLayout* createTgcInputLayoutInstance() ;
	TgcEffect* createTgcEffectInstance();
	TgcShaders* createTgcShadersInstance();



private:
	
	D3D10_PRIMITIVE_TOPOLOGY getPrimitiveTopology(PrimitiveTopology::Topology topology);

public:

	/**
	* DX10 device
	*/
	ID3D10Device* device;

	IDXGISwapChain* swapChain;
	ID3D10RenderTargetView* renderTargetView;
	ID3D10Texture2D* depthStencilBuffer;
	
	ID3D10DepthStencilView* depthStencilView;
	D3D10_VIEWPORT viewport;

	/**
	* Raster states
	*/
	ID3D10RasterizerState* solidRasterState;
	ID3D10RasterizerState* wireframeRasterState;

	/**
	* Depth states
	*/
	ID3D10DepthStencilState* depthStencilState;
	ID3D10DepthStencilState* depthDisabledStencilState;

	/**
	* Blend states
	*/
	ID3D10BlendState* alphaEnableBlendingState;
	ID3D10BlendState* alphaDisableBlendingState;
	
private:

	
};




}