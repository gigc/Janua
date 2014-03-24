/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Ui/Gui/TgcGuiCheckBox.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcGuiCheckBox::TgcGuiCheckBox(const string id, const string label)
{
	this->init(id);
	this->checked = false;
	this->label = label;
	this->mouseOver = false;

	this->sprite = new TgcSprite();
	this->sprite->texture = TgcTexture::createTexture(GuiController::Instance->engineMediaPath + "Ui\\gui_palette.png");
	this->sprite->size = Vector2(32, 32);
	this->sprite->srcRect.y = 0;
	this->sprite->srcRect.width = this->sprite->size.Width;
	this->sprite->srcRect.height = this->sprite->size.Height;
	this->sprite->init();

	this->size = this->sprite->size;

	this->labelText = new TgcText2d();
	this->labelText->color = Color::White;
	this->labelText->updateValues();
}


TgcGuiCheckBox::TgcGuiCheckBox(const TgcGuiCheckBox& other)
{
}


TgcGuiCheckBox::~TgcGuiCheckBox()
{
}

void TgcGuiCheckBox::render()
{
	float imgX = this->checked ? 0.0f : 64.0f;
	const Color color = this->mouseOver ? Color::Gold : Color::White;

	this->sprite->position = this->position;
	this->sprite->srcRect.x = imgX;
	this->sprite->color = color;
	this->sprite->updateValues();
	this->sprite->render();

	this->labelText->position = this->position + Vector2(this->size.X + 4, this->size.Y / 2 - this->labelText->size.Y / 2);
	this->labelText->text = this->label;
	this->labelText->render();
}

void TgcGuiCheckBox::dispose()
{
	this->sprite->dispose();
	delete this->sprite;
}

void TgcGuiCheckBox::onClick(int button, const Vector2 pos)
{
	if(button == 0)
	{
		this->checked = !this->checked;
	}
}

void TgcGuiCheckBox::onMouseOver()
{
	this->mouseOver = true;
}

void TgcGuiCheckBox::onMouseOut()
{
	this->mouseOver = false;
}
