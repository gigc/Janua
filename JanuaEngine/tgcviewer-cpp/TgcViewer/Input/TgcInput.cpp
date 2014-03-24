/*#############################################################
TgcViewer-cpp

Author: Matias Leone

#############################################################*/


#include "TgcViewer/Input/TgcInput.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcInput::TgcInput()
{
	//Init keyboard state
	for(int i = 0; i < KEYBOARD_KEYS_COUNT; i++) {
		eventKeyboardState[i] = false;
		previousKeyboardState[i] = false;
		currentKeyboardState[i] = false;
	}

	//Init mouse button state
	for(int i = 0; i < MOUSE_BUTTONS_COUNT; i++) {
		eventMouseButtonState[i] = false;
		previousMouseButtonState[i] = false;
		currentMouseButtonState[i] = false;
	}

	//Init mouse pos
	mouseX = 0;
	mouseY = 0;
	eventMouseX = 0;
	eventMouseY = 0;
	deltaMouseX = 0;
	deltaMouseY = 0;
	deltaMouseX = 0;
	deltaMouseY = 0;
	mouseWheel = 0;
	deltaMouseWheel = 0;
	eventMouseWheel = 0;
}


TgcInput::TgcInput(const TgcInput& other)
{
}


TgcInput::~TgcInput()
{
}

void TgcInput::update()
{
	//Backup current keyboard state
	for(int i = 0; i < KEYBOARD_KEYS_COUNT; i++) {
		previousKeyboardState[i] = currentKeyboardState[i];
	}
	
	//Update current keyboard state with events
	for(int i = 0; i < KEYBOARD_KEYS_COUNT; i++) {
		currentKeyboardState[i] = eventKeyboardState[i];
	}


	//Backup current mouse button state
	for(int i = 0; i < MOUSE_BUTTONS_COUNT; i++) {
		previousMouseButtonState[i] = currentMouseButtonState[i];
	}
	
	//Update current mouse button with events
	for(int i = 0; i < MOUSE_BUTTONS_COUNT; i++) {
		currentMouseButtonState[i] = eventMouseButtonState[i];
	}

	
	//Update mouse pos
	deltaMouseX = mouseX - eventMouseX;
	mouseX = eventMouseX;
	deltaMouseY = mouseY - eventMouseY;
	mouseY = eventMouseY;

	//Mouse wheel
	deltaMouseWheel = mouseWheel - eventMouseWheel;
	mouseWheel = eventMouseWheel;

	//Exit
	if(keyPress(K_ESCAPE))
	{
		GuiController::Instance->shutDown();
	}

}

void TgcInput::setKeyDown(TgcInput::Keys key)
{
	if(key < KEYBOARD_KEYS_COUNT )
		this->eventKeyboardState[key] = true;
}

void TgcInput::setKeyUp(TgcInput::Keys key)
{
	if(key < KEYBOARD_KEYS_COUNT )
		this->eventKeyboardState[key] = false;
}

void TgcInput::setMousePos(int x, int y)
{
	eventMouseX = x;
	eventMouseY = y;
}

void TgcInput::setButtonDown(TgcInput::MouseButtons b)
{
	this->eventMouseButtonState[b] = true;
}

void TgcInput::setButtonUp(TgcInput::MouseButtons b)
{
	this->eventMouseButtonState[b] = false;
}

void TgcInput::setMouseWheel(int zDelta)
{
	eventMouseWheel = (float)zDelta;
}




bool TgcInput::keyDown(unsigned int key)
{
	return this->currentKeyboardState[key];
}

bool TgcInput::keyUp(unsigned int key)
{
	return !this->currentKeyboardState[key];
}

bool TgcInput::keyPress(unsigned int key)
{
	return !this->previousKeyboardState[key] && this->currentKeyboardState[key];
}

bool TgcInput::buttonDown(TgcInput::MouseButtons b)
{
	return currentMouseButtonState[b];
}

bool TgcInput::buttonUp(TgcInput::MouseButtons b)
{
	return !currentMouseButtonState[b];
}

bool TgcInput::buttonPress(TgcInput::MouseButtons b)
{
	return !previousMouseButtonState[b] && currentMouseButtonState[b];
}

Vector2 TgcInput::mousePos() const
{
	return Vector2((float)mouseX, (float)mouseY);
}






