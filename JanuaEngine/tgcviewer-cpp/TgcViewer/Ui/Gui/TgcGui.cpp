/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Ui/Gui/TgcGui.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcGui::TgcGui()
{
	this->selectedItem = NULL;
	this->lastMouseOverItem = NULL;
	this->isMouseLeftDown = false;
}


TgcGui::TgcGui(const TgcGui& other)
{
}


TgcGui::~TgcGui()
{
}


TgcGui::Message TgcGui::update()
{
	Message message;
	message.type = MessageType_None;

	//Mouse input
	const Vector2 mousePos = GuiController::Instance->input->mousePos();
	const bool mouseLeftPressed = GuiController::Instance->input->buttonPress(TgcInput::BUTTON_LEFT);
	const bool mouseLeftDown = GuiController::Instance->input->buttonDown(TgcInput::BUTTON_LEFT);
	const bool mouseLeftUp = GuiController::Instance->input->buttonUp(TgcInput::BUTTON_LEFT);
	const bool mouseRightPressed = GuiController::Instance->input->buttonPress(TgcInput::BUTTON_RIGHT);
	const int mouseButtonIdx = mouseLeftPressed ? 0 : (mouseRightPressed ? 1 : -1);

	//Check mouse over item
	TgcGuiItem* itemWithMouse = getItemInPos(mousePos);

	//Mouse out
	if(this->lastMouseOverItem != NULL && (itemWithMouse == NULL || this->lastMouseOverItem != itemWithMouse))
	{
		this->lastMouseOverItem->onMouseOut();
		this->lastMouseOverItem = NULL;
	}

	//Mouse over and mouse move
	if(itemWithMouse != NULL)
	{
		this->lastMouseOverItem = itemWithMouse;
		this->lastMouseOverItem->onMouseOver();
		this->lastMouseOverItem->onMouseMove(mousePos);
	}

	//Mouse clic
	if(mouseLeftPressed || mouseRightPressed)
	{
		//Unselect and Lost focus
		if(itemWithMouse == NULL)
		{
			if(this->selectedItem != NULL)
			{
				this->selectedItem->onFocusLost();
			}
			this->selectedItem = NULL;
		}
		//Select item and focus
		else
		{
			TgcGuiItem* previousItem = this->selectedItem;

			//Previous lost focus
			if(previousItem != NULL && itemWithMouse != previousItem)
			{
				this->selectedItem->onFocusLost();
			}
			this->selectedItem = itemWithMouse;

			//Focus
			if(this->selectedItem != previousItem)
			{
				this->selectedItem->onFocus();
			}

			//Clic
			this->selectedItem->onClick(mouseButtonIdx, mousePos);

			//Generate Command message
			message.type = MessageType_Command;
			message.id = this->selectedItem->id;
		}
	}
	//Mouse down
	else if(mouseLeftDown && !this->isMouseLeftDown)
	{
		this->isMouseLeftDown = true;
		if(itemWithMouse != NULL)
		{
			TgcGuiItem* previousItem = this->selectedItem;

			//Previous lost focus
			if(previousItem != NULL && itemWithMouse != previousItem)
			{
				this->selectedItem->onFocusLost();
			}
			this->selectedItem = itemWithMouse;

			//Focus
			if(this->selectedItem != previousItem)
			{
				this->selectedItem->onFocus();
			}

			//Mouse move
			this->selectedItem->onMouseDown(0, mousePos);
		}
	}
	//Mouse up
	else if(mouseLeftUp)
	{
		this->isMouseLeftDown = false;
		if(this->selectedItem != NULL)
		{
			this->selectedItem->onMouseUp(0, mousePos);
		}
	}


	return message;
}

void TgcGui::render()
{
	GuiController::Instance->renderer->enableAlphaBlending(true);

	for(unsigned int i = 0; i < guiItems.size(); i++)
	{
		TgcGuiItem* item = guiItems[i];
		if(item->visible)
		{
			guiItems[i]->render();
		}
	}

	GuiController::Instance->renderer->enableAlphaBlending(false);
}

void TgcGui::reset()
{
	this->selectedItem = NULL;
	this->lastMouseOverItem = NULL;

	for(unsigned int i = 0; i < guiItems.size(); i++)
	{
		if(guiItems[i] != NULL)
		{
			guiItems[i]->dispose();
			delete guiItems[i];
		}
	}
	guiItems.clear();
}

void TgcGui::dispose()
{
	reset();
}

TgcGuiItem* TgcGui::getItemInPos(const Vector2 pos) const
{
	for(unsigned int i = 0; i < guiItems.size(); i++)
	{
		TgcGuiItem* item = guiItems[i];
		if(item->visible && item->inside(pos))
		{
			return item;
		}
	}
	return NULL;
}

TgcGuiItem* TgcGui::get(const string id) const
{
	int index = getItemIndex(id);
	return index >= 0 ? this->guiItems[index] : NULL;
}

/*
TgcGuiItem* TgcGui::operator[] (const string id) const
{
	return this->get(id);
}
*/

void TgcGui::add(TgcGuiItem* item)
{
	this->guiItems.push_back(item);
}

void TgcGui::remove(const string id)
{
	int index = getItemIndex(id);
	if(index >= 0)
	{
		this->guiItems.erase(this->guiItems.begin() + index); 
	}
}


int TgcGui::getItemIndex(const string id) const
{
	for(unsigned int i = 0; i < guiItems.size(); i++)
	{
		if(guiItems[i]->id == id)
		{
			return i;
		}
	}
	return -1;
}
