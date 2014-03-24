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
#include "TgcViewer/Renderer/TgcEffect.h"
#include "TgcViewer/Math/Matrix4.h"

//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;}



namespace TgcViewer
{
	
/**
* Common shader effects used by the engine
*/
class TgcShaders
{

public:

	TgcShaders();
	TgcShaders(const TgcShaders&);
	~TgcShaders();

	/**
	* Loads the common shader effects used by the engine
	*/
	virtual void loadCommonShaders() = 0;

	/**
	* Frees resources
	*/
	virtual void dispose() = 0;

	/**
	* Returns the suitable effect for a TgcMesh based on the MeshRenderType
	*/
	TgcEffect* getTgcMeshEffect(MeshValues::RenderType renderType);

	/**
	* Compute common matrix values and set the MatrixBuffer in the shader as a constant buffer
	* @param effect
	* @param world object world transform
	*/
	void setShaderMatrix(TgcEffect* effect, Matrix4 world);

	/**
	* Compute common matrix values and set the MatrixBuffer in the shader as a constant buffer.
	* The world matrix is considered the identity matrix.
	*/
	void setShaderMatrixIdentity(TgcEffect* effect);

	/**
	* Hook to make final adjustments to a matrix, before been send to the shader (for example transpose)
	*/
	virtual void adaptMatrix(Matrix4 &mat) = 0;


private:

public:
	
	/**
	* Default shader for TgcMesh - VertexColor
	*/
	TgcEffect* tgcMeshShaderVertexColor;

	/**
	* Default shader for TgcMesh - DiffuseMap
	*/
	TgcEffect* tgcMeshShaderDiffuseMap;

	/**
	* Default shader for TgcMesh - DiffuseMapAndLightmap
	*/
	TgcEffect* tgcMeshShaderDiffuseMapAndLightmap;



	/**
	* General shader for a Position + Color vertex
	*/
	TgcEffect* generalPositionColor;

	/**
	* General shader for a Position + Color + Texcoord vertex
	*/
	TgcEffect* generalPositionColorTexcoord;

	/**
	* General shader for a Position + Color + Texcoord vertex without using the texture in the pixel shader
	*/
	TgcEffect* generalPositionColorTexcoordNoTexture;

	/**
	* General shader for a Transformed Position + Texcoord vertex
	*/
	TgcEffect* generalTransformedPositionTexcoord;


	/**
	* Shader to draw 2D text
	*/
	TgcEffect* text2dShader;

	
private:

	
};




}