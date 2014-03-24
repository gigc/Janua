/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/2D/TgcText2d.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcText2d::TgcText2d()
{
	this->enabled = true;
	this->fontId = TgcFont::MICROSOFT_SANS_SERIF_16;
	this->align = TextAlign::Left;
	this->position = Vector2(0, 0);
	this->size = Vector2(1000, 20);
	this->color = Color::Yellow;
}


TgcText2d::TgcText2d(const TgcText2d& other)
{
}


TgcText2d::~TgcText2d()
{
}

void TgcText2d::updateValues()
{
	GuiController::Instance->fontRenderer->loadFont(this->fontId);
}

void TgcText2d::render()
{
	if(!enabled)
		return;

	GuiController::Instance->fontRenderer->render(this);
}

void TgcText2d::dispose()
{

}


