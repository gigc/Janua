/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Shaders/TgcShaders.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcShaders::TgcShaders()
{
}


TgcShaders::TgcShaders(const TgcShaders& other)
{
}


TgcShaders::~TgcShaders()
{
}


TgcEffect* TgcShaders::getTgcMeshEffect(MeshValues::RenderType renderType)
{
	switch(renderType)
	{
	case MeshValues::VertexColor:
		return this->tgcMeshShaderVertexColor;
	case MeshValues::DiffuseMap:
		return this->tgcMeshShaderDiffuseMap;
	case MeshValues::DiffuseMapAndLightmap:
		return this->tgcMeshShaderDiffuseMapAndLightmap;
	}
	return NULL;
}


void TgcShaders::setShaderMatrix(TgcEffect* effect, Matrix4 world)
{
	//Fill constant buffer
	TgcShadersCommon::MatrixBuffer c;
	c.matWorld = world;
	c.matWorldView = world * GuiController::Instance->renderer->viewMatrix;
	c.matWorldViewProj = c.matWorldView * GuiController::Instance->renderer->projectionMatrix;
	c.matInverseTransposeWorld = Matrix4::Transpose(world);

	//Adapt matrices
	this->adaptMatrix(c.matWorld);
	this->adaptMatrix(c.matWorldView);
	this->adaptMatrix(c.matWorldViewProj);
	this->adaptMatrix(c.matInverseTransposeWorld);

	//Set constant buffer in shader
	effect->setConstantBuffer("MatrixBuffer", &c);
}


void TgcShaders::setShaderMatrixIdentity(TgcEffect* effect)
{
	//Fill constant buffer
	TgcShadersCommon::MatrixBuffer c;
	c.matWorld = Matrix4::Identity();
	c.matWorldView = GuiController::Instance->renderer->viewMatrix;
	c.matWorldViewProj = c.matWorldView * GuiController::Instance->renderer->projectionMatrix;
	c.matInverseTransposeWorld = Matrix4::Transpose(c.matWorld);

	//Adapt matrices
	this->adaptMatrix(c.matWorld);
	this->adaptMatrix(c.matWorldView);
	this->adaptMatrix(c.matWorldViewProj);
	this->adaptMatrix(c.matInverseTransposeWorld);

	//Set constant buffer in shader
	effect->setConstantBuffer("MatrixBuffer", &c);
}


