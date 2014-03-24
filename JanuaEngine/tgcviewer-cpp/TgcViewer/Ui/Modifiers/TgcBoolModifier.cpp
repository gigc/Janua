/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Ui/Modifiers/TgcBoolModifier.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcBoolModifier::TgcBoolModifier(const string id, const string label, bool value)
{
	this->init(id);
	
	checkbox = new TgcGuiCheckBox(id, label);
	checkbox->checked = value;
	GuiController::Instance->gui->add(checkbox);

	this->size = checkbox->size;
}

TgcBoolModifier::TgcBoolModifier(const TgcBoolModifier& other)
{
}

TgcBoolModifier::~TgcBoolModifier()
{
}

void TgcBoolModifier::update()
{
}

void TgcBoolModifier::dispose()
{
}

bool TgcBoolModifier::getBool() const
{
	return checkbox->checked;
}

string TgcBoolModifier::getString() const
{
	return checkbox->checked ? "true" : "false";
}

void TgcBoolModifier::setPosition(const Vector2 pos)
{
	checkbox->position = pos;
}


