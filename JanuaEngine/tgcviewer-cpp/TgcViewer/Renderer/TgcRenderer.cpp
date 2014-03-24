/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/TgcRenderer.h"
using namespace TgcViewer;


TgcRenderer::TgcRenderer()
{
	this->vsync = true;
	this->screenFarDistance = 1000.0f;
	this->screenNearDistance = 0.1f;
	this->backgroundColor = Color::Blue;
}


TgcRenderer::TgcRenderer(const TgcRenderer& other)
{
}


TgcRenderer::~TgcRenderer()
{
}



