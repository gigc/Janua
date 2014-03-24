/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#pragma once


//General Includes:
#include <string>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Renderer/TgcRendererGlobals.h"
#include "TgcViewer/TgcSceneLoader/TgcTexture.h"
#include "TgcViewer/Renderer/TgcVertexBuffer.h"
#include "TgcViewer/Renderer/TgcIndexBuffer.h"
#include "TgcViewer/Renderer/TgcInputLayout.h"
#include "TgcViewer/Renderer/TgcEffect.h"
#include "TgcViewer/Math/FastMath.h"
#include "TgcViewer/Math/Matrix4.h"
#include "TgcViewer/Math/Color.h"
#include "TgcViewer/Shaders/TgcShaders.h"

namespace TgcViewer
{


/**
* Abstraction of a Renderer technology (DirectX9, DirectX11, etc)
*/
class TgcRenderer
{

public:

	TgcRenderer();
	TgcRenderer(const TgcRenderer&);
	~TgcRenderer();
	
	/**
	* Creates all the data required by the renderer and starts the graphics device
	*/
	virtual bool init() = 0;

	/**
	* Destroys the graphics device
	*/
	virtual void shutdown() = 0;

	/**
	* Starts the scene
	*/
	virtual void beginScene() = 0;

	/**
	* Ends the scene
	*/
	virtual void endScene() = 0;

	/**
	* Bind a vertex buffer to the renderer
	* @param vbuffer
	* @param slot
	* @param offset
	*/
	virtual void setVertexBuffer(const TgcVertexBuffer* vbuffer, unsigned int slot = 0, unsigned int offset = 0) = 0;

	/**
	* Bind an index buffer to the renderer
	* @param ibuffer
	* @param offset
	*/
	virtual void setIndexBuffer(const TgcIndexBuffer* ibuffer, unsigned int offset = 0) = 0;

	/**
	* Draw indexed primitives
	* @param topology
	* @param indexCount
	* @param startIndexLocation
	*/
	virtual void drawIndexed(PrimitiveTopology::Topology topology, unsigned int indexCount, unsigned int startIndexLocation = 0) = 0;

	/**
	* Draw non-indexed primitives
	* @param topology
	* @param vertexCount
	* @param startIndexLocation
	*/
	virtual void draw(PrimitiveTopology::Topology topology, unsigned int vertexCount, unsigned int startIndexLocation = 0) = 0;

	/**
	* Enables or disables Alpha Blending
	*/
	virtual void enableAlphaBlending(bool enable) = 0;

	/**
	* Enables or disables Depth test
	*/
	virtual void enableDepthTest(bool enable) = 0;

	/**
	* Sets the fill mode
	*/
	virtual void setFillMode(FillMode::Mode mode) = 0;


	/////////////////////////// Renderer-dependent instance creation members //////////////////////////////


	/**
	* Creates a new TgcTexture instance
	*/
	virtual TgcTexture* createTgcTextureInstance() = 0;

	/**
	* Creates a new TgcVertexBuffer instance
	*/
	virtual TgcVertexBuffer* createTgcVertexBufferInstance() = 0;

	/**
	* Creates a new TgcIndexBuffer instance
	*/
	virtual TgcIndexBuffer* createTgcIndexBufferInstance() = 0;

	/**
	* Creates a new TgcInputLayout instance
	*/
	virtual TgcInputLayout* createTgcInputLayoutInstance() = 0;

	/**
	* Creates a new TgcEffect instance
	*/
	virtual TgcEffect* createTgcEffectInstance() = 0;

	/**
	* Creates a new TgcShaders instance
	*/
	virtual TgcShaders* createTgcShadersInstance() = 0;


private:
	


public:

	/**
	* Vertical sync enabled flag
	*/
	bool vsync;

	/**
	* Frustum far distance
	*/
	float screenFarDistance;

	/**
	* Frustum near distance
	*/
	float screenNearDistance;

	/**
	* Video card memory
	*/
	int videoCardMemory;

	/**
	* Video card description
	*/
	string videoCardDescription;

	/**
	* Field of view
	*/
	float fieldOfView;

	/**
	* Aspect ratio
	*/
	float screenAspect;

	/**
	* Projection matrix
	*/
	Matrix4 projectionMatrix;

	/**
	* View matrix
	*/
	Matrix4 viewMatrix;

	/**
	* Color for screen cleanning
	*/
	Color backgroundColor;




	/**
	* Orthogonal matrix
	*/
	//Matrix4 orthoMatrix;

	
private:

	
};




}