/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Ui/Modifiers/TgcModifierItem.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcModifierItem::TgcModifierItem()
{
}


TgcModifierItem::TgcModifierItem(const TgcModifierItem& other)
{
}

TgcModifierItem::~TgcModifierItem()
{
}

void TgcModifierItem::init(const string id)
{
	this->id = id;
	this->size = Vector2(0, 0);
}

float TgcModifierItem::getFloat() const
{
	return 0;
}

int TgcModifierItem::getInt() const
{
	return 0;
}

bool TgcModifierItem::getBool() const
{
	return false;
}

string TgcModifierItem::getString() const
{
	return "";
}


