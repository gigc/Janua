/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Ui/Gui/TgcGuiButton.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcGuiButton::TgcGuiButton(const string id, string label)
{
	this->init(id);
	this->label = label;
	this->mouseOver = false;
	this->pressed = false;

	this->sprite = new TgcSprite();
	this->sprite->texture = TgcTexture::createTexture(GuiController::Instance->engineMediaPath + "Ui\\gui_palette.png");
	this->sprite->size = Vector2(128, 32);
	this->sprite->srcRect.x = 128;
	this->sprite->srcRect.width = this->sprite->size.Width;
	this->sprite->srcRect.height = this->sprite->size.Height;
	this->sprite->init();

	this->size = this->sprite->size;

	this->labelText = new TgcText2d();
	this->labelText->size.Width = this->sprite->size.Width - 4;
	this->labelText->color = Color::White;
	this->labelText->align = TextAlign::Center;
	this->labelText->updateValues();
}

TgcGuiButton::TgcGuiButton(const TgcGuiButton& other)
{
}

TgcGuiButton::~TgcGuiButton()
{
}

void TgcGuiButton::render()
{
	const float imgY = this->pressed ? 32.0f : 0.0f;
	const Color color = this->mouseOver ? Color::Gold : Color::White;

	this->sprite->position = this->position;
	this->sprite->srcRect.y = imgY;
	this->sprite->color = color;
	this->sprite->updateValues();
	this->sprite->render();

	this->labelText->position = this->position + Vector2(this->size.X / 2 - this->labelText->size.X / 2, this->size.Y / 2 - this->labelText->size.Y / 2);
	this->labelText->text = this->label;
	this->labelText->render();
}

void TgcGuiButton::dispose()
{
	this->sprite->dispose();
	delete this->sprite;
}

void TgcGuiButton::onClick(int button, const Vector2 pos)
{

}

void TgcGuiButton::onMouseDown(int button, const Vector2 pos)
{
	if(button == 0)
	{
		pressed = true;
	}
}

void TgcGuiButton::onMouseUp(int button, const Vector2 pos)
{
	if(button == 0)
	{
		pressed = false;
	}
}

void TgcGuiButton::onMouseOver()
{
	this->mouseOver = true;
}

void TgcGuiButton::onMouseOut()
{
	this->mouseOver = false;
}

