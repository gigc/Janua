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
#include <d3d11.h>
#include <d3dx11.h>


//Linking
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")


//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Renderer/TgcRenderer.h"
#include "TgcViewer/Renderer/DirectX11/TgcDX11Texture.h"
#include "TgcViewer/Renderer/DirectX11/TgcDX11VertexBuffer.h"
#include "TgcViewer/Renderer/DirectX11/TgcDX11IndexBuffer.h"
#include "TgcViewer/Renderer/DirectX11/TgcDX11InputLayout.h"
#include "TgcViewer/Renderer/DirectX11/TgcDX11Effect.h"
#include "TgcViewer/Renderer/DirectX11/TgcDX11Shaders.h"


namespace TgcViewer
{


/**
* Renderer for DirectX 11
*/
class TgcDX11Renderer : public TgcRenderer
{

public:

	TgcDX11Renderer();
	TgcDX11Renderer(const TgcDX11Renderer&);
	~TgcDX11Renderer();


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
	
	D3D11_PRIMITIVE_TOPOLOGY getPrimitiveTopology(PrimitiveTopology::Topology topology);

public:

	/**
	* DX11 device
	*/
	ID3D11Device* device;

	/**
	* DX11 device context
	*/
	ID3D11DeviceContext* deviceContext;

	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilView* depthStencilView;
	D3D11_VIEWPORT viewport;

	/**
	* Raster states
	*/
	ID3D11RasterizerState* solidRasterState;
	ID3D11RasterizerState* wireframeRasterState;

	/**
	* Depth states
	*/
	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilState* depthDisabledStencilState;

	/**
	* Blend states
	*/
	ID3D11BlendState* alphaEnableBlendingState;
	ID3D11BlendState* alphaDisableBlendingState;
	
private:

	
};




}