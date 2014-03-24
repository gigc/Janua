/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "TgcViewer/Renderer/DirectX10/TgcDX10Renderer.h"
using namespace TgcViewer;


TgcDX10Renderer::TgcDX10Renderer() : TgcRenderer()
{
	this->vsync = true;
	this->screenFarDistance = 10000;
	this->screenNearDistance = 1;
}


TgcDX10Renderer::TgcDX10Renderer(const TgcDX10Renderer& other)
{
}


TgcDX10Renderer::~TgcDX10Renderer()
{
}

bool TgcDX10Renderer::init()
{
	HRESULT result;
	
	// Create a DirectX graphics interface factory.
	IDXGIFactory* factory;
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);

	// Use the factory to create an adapter for the primary graphics interface (video card).
	IDXGIAdapter* adapter;
	result = factory->EnumAdapters(0, &adapter);

	// Enumerate the primary adapter output (monitor).
	IDXGIOutput* adapterOutput;
	result = adapter->EnumOutputs(0, &adapterOutput);

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
	unsigned int numModes;
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);

	// Create a list to hold all the possible display modes for this monitor/video card combination.
	DXGI_MODE_DESC* displayModeList;
	displayModeList = new DXGI_MODE_DESC[numModes];

	// Now fill the display mode list structures.
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	int screenWidth = GuiController::Instance->windowHandler->screenWidth;
	int screenHeight = GuiController::Instance->windowHandler->screenHeight;
	unsigned int numerator, denominator;
	for(unsigned int i = 0; i < numModes; i++)
	{
		if(displayModeList[i].Width == (unsigned int)screenWidth)
		{
			if(displayModeList[i].Height == (unsigned int)screenHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	// Get the adapter (video card) description.
	DXGI_ADAPTER_DESC adapterDesc;
	result = adapter->GetDesc(&adapterDesc);

	// Store the dedicated video card memory in megabytes.
	this->videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// Convert the name of the video card to a character array and store it.
	unsigned int stringLength;
	char videoCardDescriptionArray[128];
	int error = wcstombs_s(&stringLength, videoCardDescriptionArray, 128, adapterDesc.Description, 128);
	this->videoCardDescription = videoCardDescriptionArray;

	// Release the display mode list.
	delete [] displayModeList;
	displayModeList = 0;

	// Release the adapter output.
	adapterOutput->Release();
	adapterOutput = 0;

	// Release the adapter.
	adapter->Release();
	adapter = 0;

	// Release the factory.
	factory->Release();
	factory = 0;
	
	// Initialize the swap chain description.
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Set to a single back buffer.
    swapChainDesc.BufferCount = 1;

	// Set the width and height of the back buffer.
    swapChainDesc.BufferDesc.Width = screenWidth;
    swapChainDesc.BufferDesc.Height = screenHeight;

	// Set regular 32-bit surface for the back buffer.
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Set the refresh rate of the back buffer.
	if(this->vsync)
	{
	    swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
	    swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	// Set the usage of the back buffer.
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to.
    swapChainDesc.OutputWindow = GuiController::Instance->windowHandler->hwnd;

	// Turn multisampling off.
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

	// Set to full screen or windowed mode.
	if(GuiController::Instance->windowHandler->fullScreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	// Set the scan line ordering and scaling to unspecified.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	swapChainDesc.Flags = 0;

	// Create the swap chain, Direct3D device, and Direct3D device context.
	result = D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0, D3D10_SDK_VERSION,
				&swapChainDesc, &(this->swapChain), &(this->device));
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("DirectX 10 creation error: D3D10CreateDeviceAndSwapChain()");
		return false;
	}

	// Get the pointer to the back buffer.
	ID3D10Texture2D* backBufferPtr;
	result = this->swapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&backBufferPtr);
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("DirectX 10 creation error: GetBuffer()");
		return false;
	}

	// Create the render target view with the back buffer pointer.
	result = this->device->CreateRenderTargetView(backBufferPtr, NULL, &(this->renderTargetView));
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("DirectX 10 creation error: CreateRenderTargetView()");
		return false;
	}

	// Release pointer to the back buffer as we no longer need it.
	backBufferPtr->Release();
	backBufferPtr = 0;

	// Initialize the description of the depth buffer.
	D3D10_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create the texture for the depth buffer using the filled out description.
	result = this->device->CreateTexture2D(&depthBufferDesc, NULL, &(this->depthStencilBuffer));
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("DirectX 10 creation error: CreateTexture2D()");
		return false;
	}
	
	// Initialize the description of the stencil state.
	D3D10_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D10_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	result = this->device->CreateDepthStencilState(&depthStencilDesc, &(this->depthStencilState));
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("DirectX 10 creation error: CreateDepthStencilState()");
		return false;
	}

	// Set the depth stencil state.
	this->device->OMSetDepthStencilState(this->depthStencilState, 1);



	// Clear the second depth stencil state before setting the parameters.
	D3D10_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
	ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));

	// Now create a second depth stencil state which turns off the Z buffer for 2D rendering.  The only difference is 
	// that DepthEnable is set to false, all other parameters are the same as the other depth stencil state.
	depthDisabledStencilDesc.DepthEnable = false;
	depthDisabledStencilDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;
	depthDisabledStencilDesc.DepthFunc = D3D10_COMPARISON_LESS;
	depthDisabledStencilDesc.StencilEnable = true;
	depthDisabledStencilDesc.StencilReadMask = 0xFF;
	depthDisabledStencilDesc.StencilWriteMask = 0xFF;
	depthDisabledStencilDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
	depthDisabledStencilDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;
	depthDisabledStencilDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
	depthDisabledStencilDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	// Create the state using the device.
	result = this->device->CreateDepthStencilState(&depthDisabledStencilDesc, &(this->depthDisabledStencilState));
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("DirectX 10 creation error: CreateDepthStencilState()");
		return false;
	}




	// Initialize the depth stencil view.
	D3D10_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	result = this->device->CreateDepthStencilView(this->depthStencilBuffer, &depthStencilViewDesc, &(this->depthStencilView));
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("DirectX 10 creation error: CreateDepthStencilView()");
		return false;
	}

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	this->device->OMSetRenderTargets(1, &(this->renderTargetView), this->depthStencilView);

	// Setup the raster description which will determine how and what polygons will be drawn.
	D3D10_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = /*D3D10_CULL_BACK*/D3D10_CULL_NONE;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D10_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	result = this->device->CreateRasterizerState(&rasterDesc, &(this->solidRasterState));
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("DirectX 10 creation error: CreateRasterizerState()");
		return false;
	}

	// Now set the rasterizer state.
	this->device->RSSetState(this->solidRasterState);

	//Create raster description for wireframe mode
	rasterDesc.FillMode = D3D10_FILL_WIREFRAME;
	result = this->device->CreateRasterizerState(&rasterDesc, &(this->wireframeRasterState));
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("DirectX 10 creation error: CreateRasterizerState()");
		return false;
	}


	// Clear the blend state description.
	D3D10_BLEND_DESC blendStateDescription;
	ZeroMemory(&blendStateDescription, sizeof(D3D10_BLEND_DESC));

	// Create an alpha enabled blend state description.
	blendStateDescription.BlendEnable[0] = TRUE;
	blendStateDescription.SrcBlend = D3D10_BLEND_SRC_ALPHA;
    blendStateDescription.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
    blendStateDescription.BlendOp = D3D10_BLEND_OP_ADD;
    blendStateDescription.SrcBlendAlpha = D3D10_BLEND_ONE;
    blendStateDescription.DestBlendAlpha = D3D10_BLEND_ZERO;
    blendStateDescription.BlendOpAlpha = D3D10_BLEND_OP_ADD;
    blendStateDescription.RenderTargetWriteMask[0] = 0x0f;

	// Create the blend state using the description.
	result = this->device->CreateBlendState(&blendStateDescription, &(this->alphaEnableBlendingState));
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("DirectX 10 creation error: CreateBlendState()");
		return false;
	}
	
	// Modify the description to create an alpha disabled blend state description.
	blendStateDescription.BlendEnable[0] = FALSE;

	// Create the blend state using the description.
	result = this->device->CreateBlendState(&blendStateDescription, &(this->alphaDisableBlendingState));
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("DirectX 10 creation error: CreateBlendState()");
		return false;
	}
	
	// Setup the viewport for rendering.
    this->viewport.Width = (unsigned int)screenWidth;
    this->viewport.Height = (unsigned int)screenHeight;
    this->viewport.MinDepth = 0.0f;
    this->viewport.MaxDepth = 1.0f;
    this->viewport.TopLeftX = 0;
    this->viewport.TopLeftY = 0;

	// Create the viewport.
    this->device->RSSetViewports(1, &(this->viewport));
	if(FAILED(result))
	{
		GuiController::Instance->logger->logError("DirectX 10 creation error: RSSetViewports()");
		return false;
	}
	
	// Setup the projection matrix.
	this->fieldOfView = FastMath::PI / 4.0f;
	this->screenAspect = (float)screenWidth / (float)screenHeight;
	this->projectionMatrix = Matrix4::PerspectiveFovLH(this->fieldOfView, this->screenAspect, this->screenNearDistance, this->screenFarDistance);

	//View matrix
	this->viewMatrix = Matrix4::Identity();

	/*
	// Create an orthographic projection matrix for 2D rendering.
	D3DXMatrixOrthoLH(&(this->orthoMatrix), (float)screenWidth, (float)screenHeight, this->screenNearDistance, this->screenFarDistance);
	*/

    return true;
}


void TgcDX10Renderer::shutdown()
{
	// Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
	if(this->swapChain)
	{
		this->swapChain->SetFullscreenState(false, NULL);
	}

	if(this->solidRasterState)
	{
		this->solidRasterState->Release();
		this->solidRasterState = 0;
	}
	if(this->wireframeRasterState)
	{
		this->wireframeRasterState->Release();
		this->wireframeRasterState = 0;
	}

	if(this->depthStencilView)
	{
		this->depthStencilView->Release();
		this->depthStencilView = 0;
	}

	if(this->depthStencilState)
	{
		this->depthStencilState->Release();
		this->depthStencilState = 0;
	}

	if(this->depthDisabledStencilState)
	{
		this->depthDisabledStencilState->Release();
		this->depthDisabledStencilState = 0;
	}

	if(this->depthStencilBuffer)
	{
		this->depthStencilBuffer->Release();
		this->depthStencilBuffer = 0;
	}

	if(this->renderTargetView)
	{
		this->renderTargetView->Release();
		this->renderTargetView = 0;
	}

	if(this->device)
	{
		this->device->Release();
		this->device = 0;
	}

	if(this->swapChain)
	{
		this->swapChain->Release();
		this->swapChain = 0;
	}

	if(this->alphaEnableBlendingState)
	{
		this->alphaEnableBlendingState->Release();
		this->alphaEnableBlendingState = 0;
	}

	if(this->alphaDisableBlendingState)
	{
		this->alphaDisableBlendingState->Release();
		this->alphaDisableBlendingState = 0;
	}
}


void TgcDX10Renderer::beginScene()
{
	// Clear the back buffer.
	this->device->ClearRenderTargetView(this->renderTargetView, this->backgroundColor.v);
    
	// Clear the depth buffer.
	this->device->ClearDepthStencilView(this->depthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);
}


void TgcDX10Renderer::endScene()
{
	// Present the back buffer to the screen since rendering is complete.
	if(this->vsync)
	{
		// Lock to screen refresh rate.
		this->swapChain->Present(1, 0);
	}
	else
	{
		// Present as fast as possible.
		this->swapChain->Present(0, 0);
	}
}


void TgcDX10Renderer::setVertexBuffer(const TgcVertexBuffer* vbuffer, unsigned int slot, unsigned int offset)
{
	TgcDX10VertexBuffer* dxVbuffer = (TgcDX10VertexBuffer*)vbuffer;
	this->device->IASetVertexBuffers(slot, 1, &((dxVbuffer)->buffer), &(vbuffer->vertexSize), &offset);
	
	TgcDX10InputLayout* dxInlayout = (TgcDX10InputLayout*)dxVbuffer->inputLayout;
	this->device->IASetInputLayout(dxInlayout->layout);
}

void TgcDX10Renderer::setIndexBuffer(const TgcIndexBuffer* ibuffer, unsigned int offset)
{
	this->device->IASetIndexBuffer(((TgcDX10IndexBuffer*)ibuffer)->buffer, DXGI_FORMAT_R32_UINT, offset);
}

void TgcDX10Renderer::drawIndexed(PrimitiveTopology::Topology topology, unsigned int indexCount, unsigned int startIndexLocation)
{
	this->device->IASetPrimitiveTopology(this->getPrimitiveTopology(topology));
	this->device->DrawIndexed(indexCount, startIndexLocation, 0);
}

D3D10_PRIMITIVE_TOPOLOGY TgcDX10Renderer::getPrimitiveTopology(PrimitiveTopology::Topology topology)
{
	D3D10_PRIMITIVE_TOPOLOGY d3dTopology;
	switch(topology)
	{
		case PrimitiveTopology::TriangleList:
			d3dTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;
		case PrimitiveTopology::TriangleStrip:
			d3dTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
			break;
		case PrimitiveTopology::LineList:
			d3dTopology = D3D10_PRIMITIVE_TOPOLOGY_LINELIST;
			break;
		case PrimitiveTopology::LineStrip:
			d3dTopology = D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP;
			break;
		case PrimitiveTopology::PointList:
			d3dTopology = D3D10_PRIMITIVE_TOPOLOGY_POINTLIST;
			break;
	}
	return d3dTopology;
}

void TgcDX10Renderer::draw(PrimitiveTopology::Topology topology, unsigned int vertexCount, unsigned int startVertexLocation)
{
	this->device->IASetPrimitiveTopology(this->getPrimitiveTopology(topology));
	this->device->Draw(vertexCount, startVertexLocation);
}


void TgcDX10Renderer::enableAlphaBlending(bool enable)
{
	ID3D10BlendState* blendState = enable ? this->alphaEnableBlendingState : this->alphaDisableBlendingState;
	float blendFactor[] = {0.0f, 0.0f, 0.0f, 0.0f};
	this->device->OMSetBlendState(blendState, blendFactor, 0xffffffff);
}

void TgcDX10Renderer::enableDepthTest(bool enable)
{
	ID3D10DepthStencilState* depthState = enable ? this->depthStencilState : this->depthDisabledStencilState;
	this->device->OMSetDepthStencilState(depthState, 1);
}

void TgcDX10Renderer::setFillMode(FillMode::Mode mode)
{
	ID3D10RasterizerState* dxState = mode == FillMode::Solid ? this->solidRasterState : this->wireframeRasterState;
	this->device->RSSetState(dxState);
}




TgcTexture* TgcDX10Renderer::createTgcTextureInstance()
{
	return new TgcDX10Texture();
}

TgcVertexBuffer* TgcDX10Renderer::createTgcVertexBufferInstance()
{
	return new TgcDX10VertexBuffer();
}

TgcIndexBuffer* TgcDX10Renderer::createTgcIndexBufferInstance()
{
	return new TgcDX10IndexBuffer();
}

TgcInputLayout* TgcDX10Renderer::createTgcInputLayoutInstance()
{
	return new TgcDX10InputLayout();
}

TgcEffect* TgcDX10Renderer::createTgcEffectInstance()
{
	return new TgcDX10Effect();
}

TgcShaders* TgcDX10Renderer::createTgcShadersInstance()
{
	return new TgcDX10Shaders();
}
