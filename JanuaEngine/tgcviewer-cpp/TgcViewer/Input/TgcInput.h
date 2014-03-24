/*#############################################################
TgcViewer-cpp

Author: Matias Leone

#############################################################*/


#pragma once


//General Includes:
//#include <windows.h>

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Math/Vector2.h"


//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;};


namespace TgcViewer
{

/*////////////////////////////////////////////////////////////////////////////////
Class name: TgcInput
////////////////////////////////////////////////////////////////////////////////*/
class TgcInput
{


public:

	/**
	* Mouse Buttons
	*/ 
	enum MouseButtons
	{
		BUTTON_LEFT,
		BUTTON_RIGHT,
		BUTTON_MIDDLE
	};

	/**
	* Keyboard keys
	*/ 
	enum Keys
	{
		K_BACK,
		K_TAB,
		K_CLEAR,
		K_RETURN,
		K_SHIFT,
		K_CONTROL,
		K_MENU,
		K_PAUSE,
		K_CAPITAL,
		K_ESCAPE,
		K_CONVERT,
		K_NONCONVERT,
		K_ACCEPT,
		K_MODECHANGE,
		K_SPACE,
		K_PRIOR,
		K_NEXT,
		K_END,
		K_HOME,
		K_LEFT,
		K_UP,
		K_RIGHT,
		K_DOWN,
		K_SELECT,
		K_PRINT,
		K_EXECUTE,
		K_SNAPSHOT,
		K_INSERT,
		K_DELETE,
		K_HELP,
		K_0,
		K_1,
		K_2,
		K_3,
		K_4,
		K_5,
		K_6,
		K_7,
		K_8,
		K_9,
		K_A,
		K_B,
		K_C,
		K_D,
		K_E,
		K_F,
		K_G,
		K_H,
		K_I,
		K_J,
		K_K,
		K_L,
		K_M,
		K_N,
		K_O,
		K_P,
		K_Q,
		K_R,
		K_S,
		K_T,
		K_U,
		K_V,
		K_W,
		K_X,
		K_Y,
		K_Z,
		K_LWIN,
		K_RWIN,
		K_APPS,
		K_SLEEP,
		K_NUMPAD0,
		K_NUMPAD1,
		K_NUMPAD2,
		K_NUMPAD3,
		K_NUMPAD4,
		K_NUMPAD5,
		K_NUMPAD6,
		K_NUMPAD7,
		K_NUMPAD8,
		K_NUMPAD9,
		K_MULTIPLY,
		K_ADD,
		K_SEPARATOR,
		K_SUBTRACT,
		K_DECIMAL,
		K_DIVIDE,
		K_F1,
		K_F2,
		K_F3,
		K_F4,
		K_F5,
		K_F6,
		K_F7,
		K_F8,
		K_F9,
		K_F10,
		K_F11,
		K_F12,
		K_F13,
		K_F14,
		K_F15,
		K_F16,
		K_F17,
		K_F18,
		K_F19,
		K_F20,
		K_F21,
		K_F22,
		K_F23,
		K_F24,
		K_NUMLOCK,
		K_SCROLL,
		K_LSHIFT,
		K_RSHIFT,
		K_LCONTROL,
		K_RCONTROL,
		K_LMENU,
		K_RMENU
	};



	TgcInput();
	TgcInput(const TgcInput&);
	~TgcInput();
	
	/**
	* Update input status
	*/
	void update();


	/**
	* Check keyboard events
	*/
	bool keyDown(unsigned int key);
	bool keyUp(unsigned int key);
	bool keyPress(unsigned int key);


	/**
	* Check mouse buttons
	*/
	bool TgcInput::buttonDown(TgcInput::MouseButtons b);
	bool TgcInput::buttonUp(TgcInput::MouseButtons b);
	bool TgcInput::buttonPress(TgcInput::MouseButtons b);

	/**
	* Mouse cursor pos
	*/
	Vector2 mousePos() const;

	/**
	* {Internal}
	* Values set by WindowHandler
	*/
	void setKeyDown(TgcInput::Keys key);
	void setKeyUp(TgcInput::Keys key);
	void setMousePos(int x, int y);
	void setButtonDown(TgcInput::MouseButtons b);
	void setButtonUp(TgcInput::MouseButtons b);
	void setMouseWheel(int zDelta);

private:
	
	
public:

	static const unsigned int KEYBOARD_KEYS_COUNT = 256;
	static const unsigned int MOUSE_BUTTONS_COUNT = 3;


	/**
	* Mouse cursor position
	*/
	int mouseX;
	int mouseY;

	/**
	* Relative mouse cursor movement between frames
	*/
	int deltaMouseX;
	int deltaMouseY;

	/**
	* Mouse wheel
	*/
	float eventMouseWheel;
	float mouseWheel;
	float deltaMouseWheel;



	/**
	* {Internal}
	* Evento mouse pos
	*/
	int eventMouseX;
	int eventMouseY;

	/**
	* {Internal}
	* Keyboard states
	*/
	bool eventKeyboardState[KEYBOARD_KEYS_COUNT];
	bool previousKeyboardState[KEYBOARD_KEYS_COUNT];
    bool currentKeyboardState[KEYBOARD_KEYS_COUNT];

	/**
	* {Internal}
	* Mouse buttons states
	*/
	bool eventMouseButtonState[MOUSE_BUTTONS_COUNT];
	bool previousMouseButtonState[MOUSE_BUTTONS_COUNT];
    bool currentMouseButtonState[MOUSE_BUTTONS_COUNT];

private:


};




}