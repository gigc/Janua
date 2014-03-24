/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Ui/TgcUserVars.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcUserVars::TgcUserVars()
{
	this->position = Vector2(5, 200);
	this->enabled = true;
	this->enableKey = TgcInput::K_V;
	this->color = Color::Yellow;
}


TgcUserVars::TgcUserVars(const TgcUserVars& other)
{
}


TgcUserVars::~TgcUserVars()
{
}

void TgcUserVars::addVar(const string name)
{
	map<string, TgcText2d*>::iterator  it = this->uiTexts.find(name);
	if (it == this->uiTexts.end() )
	{
		TgcText2d* text = new TgcText2d();
		text->position = Vector2(position.X, position.Y + TEXT_Y_DISTANCE * this->uiTexts.size());
		text->color = color;
		text->updateValues();
		this->uiTexts[name] = text;
	}
}

void TgcUserVars::setVar(const string name, const string value)
{
	this->addVar(name);
	this->uiTexts[name]->text = name + ": " + value;
}

void TgcUserVars::setVar(const string name, const int value)
{
	TgcUserVars::setVar(name, TgcParserUtils::toString(value));
}

void TgcUserVars::setVar(const string name, const int long value)
{
	TgcUserVars::setVar(name, TgcParserUtils::toString(value));
}

void TgcUserVars::setVar(const string name, const unsigned int value)
{
	TgcUserVars::setVar(name, TgcParserUtils::toString(value));
}

void TgcUserVars::setVar(const string name, const float value)
{
	TgcUserVars::setVar(name, TgcParserUtils::toString(value));
}

void TgcUserVars::setVar(const string name, const Vector2& value)
{
	TgcUserVars::setVar(name, TgcParserUtils::toString(value));
}

void TgcUserVars::setVar(const string name, const Vector3& value)
{
	TgcUserVars::setVar(name, TgcParserUtils::toString(value));
}

void TgcUserVars::setVar(const string name, const Vector4& value)
{
	TgcUserVars::setVar(name, TgcParserUtils::toString(value));
}

void TgcUserVars::setVar(const string name, const Color& value)
{
	TgcUserVars::setVar(name, TgcParserUtils::toString(value));
}

void TgcUserVars::render()
{
	//Auto show/hide
	if(GuiController::Instance->input->keyPress(this->enableKey))
	{
		enabled = !enabled;
	}

	if(!enabled)
		return;

	//Render all
	for (map<string, TgcText2d*>::iterator it = this->uiTexts.begin(); it != this->uiTexts.end(); ++it) 
	{
		TgcText2d* text = it->second;
		text->render();

		//GuiController::Instance->drawText(text->text, text->position.X, text->position.Y);
	}
}

void TgcUserVars::dispose()
{
	for (map<string, TgcText2d*>::iterator it = this->uiTexts.begin(); it != this->uiTexts.end(); ++it) 
	{
		TgcText2d* text = it->second;
		text->dispose();
		delete text;
	}
}
