/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/DirectX11/TgcDX11Shaders.h"
using namespace TgcViewer;



void TgcDX11Shaders::loadCommonShaders()
{
	string shadersPath = GuiController::Instance->engineMediaPath + "Shaders\\DirectX11\\";
	TgcEffectValues::Description desc;

	//tgcMeshShaderVertexColor
	this->tgcMeshShaderVertexColor = TgcEffect::createFromFile(shadersPath + "TgcMeshShader.hlsl", "vs_VertexColor", "ps_VertexColor");
	this->tgcMeshShaderVertexColor->addConstantBuffer(TgcEffectValues::ConstantBuffer("MatrixBuffer", TgcEffectValues::VS_AND_PS, sizeof(TgcShadersCommon::MatrixBuffer), 0));

	//tgcMeshShaderDiffuseMap
	this->tgcMeshShaderDiffuseMap = TgcEffect::createFromFile(shadersPath + "TgcMeshShader.hlsl", "vs_DiffuseMap", "ps_DiffuseMap");
	this->tgcMeshShaderDiffuseMap->addConstantBuffer(TgcEffectValues::ConstantBuffer("MatrixBuffer", TgcEffectValues::VS_AND_PS, sizeof(TgcShadersCommon::MatrixBuffer), 0));
	this->tgcMeshShaderDiffuseMap->addSampler(TgcEffectValues::Sampler("diffuseMap", "texDiffuseMap",TgcEffectValues::PS, 0));

	//tgcMeshShaderDiffuseMap
	this->tgcMeshShaderDiffuseMapAndLightmap = TgcEffect::createFromFile(shadersPath + "TgcMeshShader.hlsl", "vs_diffuseMapAndLightmap", "ps_diffuseMapAndLightmap");
	this->tgcMeshShaderDiffuseMapAndLightmap->addConstantBuffer(TgcEffectValues::ConstantBuffer("MatrixBuffer", TgcEffectValues::VS_AND_PS, sizeof(TgcShadersCommon::MatrixBuffer), 0));
	this->tgcMeshShaderDiffuseMapAndLightmap->addSampler(TgcEffectValues::Sampler("diffuseMap", "texDiffuseMap",TgcEffectValues::PS, 0));
	this->tgcMeshShaderDiffuseMapAndLightmap->addSampler(TgcEffectValues::Sampler("lightMap", "texLightMap",TgcEffectValues::PS, 1));


	//generalPositionColor
	this->generalPositionColor = TgcEffect::createFromFile(shadersPath + "GeneralShaders.hlsl", "vs_positionColor", "ps_positionColor");
	this->generalPositionColor->addConstantBuffer(TgcEffectValues::ConstantBuffer("MatrixBuffer", TgcEffectValues::VS_AND_PS, sizeof(TgcShadersCommon::MatrixBuffer), 0));

	//generalPositionColorTexcoord
	this->generalPositionColorTexcoord = TgcEffect::createFromFile(shadersPath + "GeneralShaders.hlsl", "vs_positionColorTexcoord", "ps_positionColorTexcoord");
	this->generalPositionColorTexcoord->addConstantBuffer(TgcEffectValues::ConstantBuffer("MatrixBuffer", TgcEffectValues::VS_AND_PS, sizeof(TgcShadersCommon::MatrixBuffer), 0));
	this->generalPositionColorTexcoord->addSampler(TgcEffectValues::Sampler("diffuseMap", "texDiffuseMap",TgcEffectValues::PS, 0));

	//generalPositionColorTexcoordNoTexture
	this->generalPositionColorTexcoordNoTexture = TgcEffect::createFromFile(shadersPath + "GeneralShaders.hlsl", "vs_positionColorTexcoordNoTexture", "ps_positionColorTexcoordNoTexture");
	this->generalPositionColorTexcoordNoTexture->addConstantBuffer(TgcEffectValues::ConstantBuffer("MatrixBuffer", TgcEffectValues::VS_AND_PS, sizeof(TgcShadersCommon::MatrixBuffer), 0));
	this->generalPositionColorTexcoordNoTexture->addSampler(TgcEffectValues::Sampler("diffuseMap", "texDiffuseMap",TgcEffectValues::PS, 0));

	//generalTransformedPositionTexcoord
	this->generalTransformedPositionTexcoord = TgcEffect::createFromFile(shadersPath + "GeneralShaders.hlsl", "vs_transformedPositionTexcoord", "ps_transformedPositionTexcoord");
	this->generalTransformedPositionTexcoord->addConstantBuffer(TgcEffectValues::ConstantBuffer("InputColorBuffer", TgcEffectValues::PS, sizeof(TgcShadersCommon::InputColorBuffer), 1));
	this->generalTransformedPositionTexcoord->addSampler(TgcEffectValues::Sampler("diffuseMap", "texDiffuseMap",TgcEffectValues::PS, 0));


	//text2dShader
	this->text2dShader = TgcEffect::createFromFile(shadersPath + "Text2dShader.hlsl", "vs_text2d", "ps_text2d");
	this->text2dShader->addConstantBuffer(TgcEffectValues::ConstantBuffer("TextBuffer", TgcEffectValues::PS, sizeof(TgcShadersCommon::TextBuffer), 0));
	this->text2dShader->addSampler(TgcEffectValues::Sampler("diffuseMap", "texDiffuseMap",TgcEffectValues::PS, 0));
}

void TgcDX11Shaders::dispose()
{
	if(this->tgcMeshShaderVertexColor)
	{
		this->tgcMeshShaderVertexColor->dispose();
		this->tgcMeshShaderVertexColor = 0;
	}
	if(this->tgcMeshShaderDiffuseMap)
	{
		this->tgcMeshShaderDiffuseMap->dispose();
		this->tgcMeshShaderDiffuseMap = 0;
	}
	if(this->tgcMeshShaderDiffuseMapAndLightmap)
	{
		this->tgcMeshShaderDiffuseMapAndLightmap->dispose();
		this->tgcMeshShaderDiffuseMapAndLightmap = 0;
	}
	if(this->generalPositionColor)
	{
		this->generalPositionColor->dispose();
		this->generalPositionColor = 0;
	}
	if(this->generalPositionColorTexcoord)
	{
		this->generalPositionColorTexcoord->dispose();
		this->generalPositionColorTexcoord = 0;
	}
	if(this->generalTransformedPositionTexcoord)
	{
		this->generalTransformedPositionTexcoord->dispose();
		this->generalTransformedPositionTexcoord = 0;
	}
}

void TgcDX11Shaders::adaptMatrix(Matrix4 &mat)
{
	//Do nothing
}