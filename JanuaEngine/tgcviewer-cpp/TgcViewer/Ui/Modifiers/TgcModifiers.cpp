/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Ui/Modifiers/TgcModifiers.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
#include "TgcViewer/Ui/Modifiers/TgcBoolModifier.h" //required by forward declaration
#include "TgcViewer/Ui/Modifiers/TgcFloatModifier.h" //required by forward declaration
using namespace TgcViewer;


TgcModifiers::TgcModifiers()
{
	currentHeight = 5;
}

TgcModifiers::TgcModifiers(const TgcModifiers& other)
{
}

TgcModifiers::~TgcModifiers()
{
}

void TgcModifiers::add(TgcModifierItem* modifier)
{
	this->modifiers.push_back(modifier);
	modifier->setPosition(Vector2((float)GuiController::Instance->windowHandler->screenWidth - 300, currentHeight));
	currentHeight += modifier->size.Y + 10;
}

void TgcModifiers::addBool(const string id, const string label, bool value)
{
	add(new TgcBoolModifier(id, label, value));
}

void TgcModifiers::addFloat(const string id, const string label, float minValue, float maxValue, float currentValue)
{
	add(new TgcFloatModifier(id, label, minValue, maxValue, currentValue));
}

TgcModifierItem* TgcModifiers::get(const string id) const
{
	return modifiers[getModifierIndex(id)];
}

/*
TgcModifierItem* TgcModifiers::operator[] (const string id) const
{
	return get(id);
}
*/

void TgcModifiers::update()
{
	GuiController::Instance->gui->update();
	for(unsigned int i = 0; i < this->modifiers.size(); i++)
	{
		modifiers[i]->update();
	}
}

void TgcModifiers::render()
{
	GuiController::Instance->gui->render();
}

void TgcModifiers::dispose()
{
	for(unsigned int i = 0; i < this->modifiers.size(); i++)
	{
		modifiers[i]->dispose();
		delete modifiers[i];
	}
	this->modifiers.clear();
	GuiController::Instance->gui->reset();
}

int TgcModifiers::getModifierIndex(const string id) const
{
	for(unsigned int i = 0; i < this->modifiers.size(); i++)
	{
		if(modifiers[i]->id == id)
		{
			return i;
		}
	}
	return -1;
}


