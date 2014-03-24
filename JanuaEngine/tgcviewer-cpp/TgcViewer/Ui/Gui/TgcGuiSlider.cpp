/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Ui/Gui/TgcGuiSlider.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcGuiSlider::TgcGuiSlider(const string id, string label)
{
	this->init(id);
	this->label = label;
	this->mouseOver = false;
	this->dragging = false;
	this->setValues(0, 100, 50);

	this->barSprite = new TgcSprite();
	this->barSprite->texture = TgcTexture::createTexture(GuiController::Instance->engineMediaPath + "Ui\\gui_palette.png");
	this->barSprite->size = Vector2(128, 32);
	this->barSprite->srcRect.x = 0;
	this->barSprite->srcRect.width = this->barSprite->size.Width;
	this->barSprite->srcRect.height = this->barSprite->size.Height;
	this->barSprite->init();

	this->sliderSprite = new TgcSprite();
	this->sliderSprite->texture = TgcTexture::createTexture(GuiController::Instance->engineMediaPath + "Ui\\gui_palette.png");
	this->sliderSprite->size = Vector2(8, 32);
	this->sliderSprite->srcRect.y = 64;
	this->sliderSprite->srcRect.width = this->sliderSprite->size.Width;
	this->sliderSprite->srcRect.height = this->sliderSprite->size.Height;
	this->sliderSprite->init();

	this->size = this->barSprite->size;
	this->sliderPixelWidth = this->barSprite->size.Width - this->sliderSprite->size.Width;

	this->labelText = new TgcText2d();
	this->labelText->color = Color::White;
	this->labelText->updateValues();
}

TgcGuiSlider::TgcGuiSlider(const TgcGuiSlider& other)
{
}

TgcGuiSlider::~TgcGuiSlider()
{
}

void TgcGuiSlider::render()
{
	this->barSprite->position = this->position;
	this->barSprite->srcRect.y = this->dragging ? 64.0f : 32.0f;
	this->barSprite->color = this->mouseOver ? Color::Gold : Color::White;
	this->barSprite->updateValues();
	this->barSprite->render();

	const float slideDiffX = 32 / 2 - sliderSprite->size.Width / 2;
	this->sliderSprite->srcRect.x = this->dragging ? 160.0f + slideDiffX : 128.0f + slideDiffX;
	this->sliderSprite->position.X = this->position.X + (currentValue - minValue) * (sliderPixelWidth / (maxValue - minValue));
	this->sliderSprite->position.Y = this->position.Y;
	this->sliderSprite->color = this->mouseOver ? Color::Orange : Color::White;
	this->sliderSprite->updateValues();
	this->sliderSprite->render();

	this->labelText->position = this->position + Vector2(this->size.X + 4, this->size.Y / 2 - this->labelText->size.Y / 2);
	this->labelText->text = this->label;
	this->labelText->render();
}

void TgcGuiSlider::dispose()
{
	this->barSprite->dispose();
	delete this->barSprite;

	this->sliderSprite->dispose();
	delete this->sliderSprite;
}

void TgcGuiSlider::onClick(int button, const Vector2 pos)
{

}

void TgcGuiSlider::onMouseDown(int button, const Vector2 pos)
{
	if(button == 0 /*&& sliderSprite->inside(pos)*/)
	{
		dragging = true;
	}
}

void TgcGuiSlider::onMouseUp(int button, const Vector2 pos)
{
	if(button == 0 && dragging)
	{
		dragging = false;
	}
}

void TgcGuiSlider::onMouseOver()
{
	this->mouseOver = true;
}

void TgcGuiSlider::onMouseOut()
{
	this->mouseOver = false;
}

void TgcGuiSlider::onMouseMove(const Vector2 pos)
{
	if(dragging)
	{
		if(pos.X < position.X)
		{
			currentValue = minValue;
		}
		else if(pos.X > position.X + sliderPixelWidth)
		{
			currentValue = maxValue;
		}
		else
		{
			currentValue = minValue + (pos.X - position.X) * ((maxValue - minValue) / sliderPixelWidth);
		}
	}
}

void TgcGuiSlider::setValues(float minValue, float maxValue, float currentValue)
{
	this->minValue = minValue;
	this->maxValue = maxValue;
	this->currentValue = currentValue;
}