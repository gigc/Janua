/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Ui/Modifiers/TgcFloatModifier.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcFloatModifier::TgcFloatModifier(const string id, const string label, float minValue, float maxValue, float currentValue)
{
	this->init(id);
	
	slider = new TgcGuiSlider(id, label);
	slider->setValues(minValue, maxValue, currentValue);
	GuiController::Instance->gui->add(slider);

	this->size = slider->size;
}

TgcFloatModifier::TgcFloatModifier(const TgcFloatModifier& other)
{
}

TgcFloatModifier::~TgcFloatModifier()
{
}

void TgcFloatModifier::update()
{
}

void TgcFloatModifier::dispose()
{
}

float TgcFloatModifier::getFloat() const
{
	return slider->currentValue;
}

int TgcFloatModifier::getInt() const
{
	return (int)slider->currentValue;
}

string TgcFloatModifier::getString() const
{
	return TgcParserUtils::toString(slider->currentValue);
}

void TgcFloatModifier::setPosition(const Vector2 pos)
{
	slider->position = pos;
}


