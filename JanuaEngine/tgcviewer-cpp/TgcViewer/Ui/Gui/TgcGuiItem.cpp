/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Ui/Gui/TgcGuiItem.h"
using namespace TgcViewer;


TgcGuiItem::TgcGuiItem()
{
}


TgcGuiItem::TgcGuiItem(const TgcGuiItem& other)
{
}


TgcGuiItem::~TgcGuiItem()
{
}

void TgcGuiItem::init(const string id)
{
	this->id = id;
	this->position = Vector2(0, 0);
	this->size = Vector2(0, 0);
	this->visible = true;
}

bool TgcGuiItem::inside(const Vector2 pos) const
{
	return pos.X >= position.X && pos.X <= position.X + size.Width &&
		pos.Y >= position.Y && pos.Y <= position.Y + size.Height;
}

void TgcGuiItem::onFocus()
{
}

void TgcGuiItem::onFocusLost()
{
}

void TgcGuiItem::onMouseOver()
{
}

void TgcGuiItem::onMouseOut()
{
}

void TgcGuiItem::onClick(int button, const Vector2 pos)
{
}

void TgcGuiItem::onMouseDown(int button, const Vector2 pos)
{
}

void TgcGuiItem::onMouseUp(int button, const Vector2 pos)
{
}

void TgcGuiItem::onMouseMove(const Vector2 pos)
{
}