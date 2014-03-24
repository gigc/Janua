/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "TgcViewer/Renderer/TgcRendererFactory.h"
using namespace TgcViewer;


TgcRendererFactory::TgcRendererFactory()
{
}

TgcRenderer* TgcRendererFactory::createRenderer()
{
	//Creates a renderer instance based on TGC_CURRENT_RENDERER value
	return new TGC_CURRENT_RENDERER;
}


