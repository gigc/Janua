/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/TgcEffect.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcEffect::TgcEffect()
{
}


TgcEffect::TgcEffect(const TgcEffect& other)
{
}


TgcEffect::~TgcEffect()
{
}


TgcEffect* TgcEffect::createFromFile(string filePath, string vsFunctionName, string psFunctionName)
{
	TgcEffect* effect = GuiController::Instance->renderer->createTgcEffectInstance();
	TgcEffectValues::Description desc;
	desc.vsFunctionName = vsFunctionName;
	desc.psFunctionName = psFunctionName;
	effect->create(filePath, desc);
	return effect;
	return NULL;
}


void TgcEffect::create(string filePath, TgcEffectValues::Description desc)
{
	this->filePath = filePath;
	this->description = desc;
	this->internalCreate();
}

void TgcEffect::addSampler(TgcEffectValues::Sampler sampler)
{
	this->samplers[sampler.textureName] = sampler;
	this->internalAddSampler(sampler);
}

void TgcEffect::addConstantBuffer(TgcEffectValues::ConstantBuffer constantBuffer)
{
	this->constantBuffers[constantBuffer.name] = constantBuffer;
	this->internalAddConstantBuffer(constantBuffer);
}

