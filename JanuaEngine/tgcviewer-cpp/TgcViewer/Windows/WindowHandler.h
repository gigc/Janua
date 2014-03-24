/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <windows.h>
#include <windowsx.h>
#include <string>
using namespace std;

//Project Includes:
#include "TgcViewer/Input/TgcInput.h"
#include "TgcViewer/Math/Vector2.h"

//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;};




namespace TgcViewer
{

/*////////////////////////////////////////////////////////////////////////////////
Class name: WindowHandler
////////////////////////////////////////////////////////////////////////////////*/
class WindowHandler
{

public:

	WindowHandler();
	WindowHandler(const WindowHandler&);
	~WindowHandler();
	
	/**
	* Create window
	*/
	void initializeWindow();

	/**
	* Run events
	*/
	void run();
	
	/**
	* Close window
	*/
	void closeWindow();


	/**
	* Returns the directory of the exe file of the application
	*/
	string getCurrentDir();

	/**
	* Window size
	*/
	Vector2 size() const;

private:

	void initKeyboardMapping();

public:

	/**
	* Window handler
	*/
	HWND hwnd;

	/**
	* Application name
	*/
	LPCSTR applicationName;

	/**
	* Application instance
	*/
	HINSTANCE hinstance;

	/**
	* GDI device context
	*/
	HDC deviceContext;

	/**
	* Screen width
	*/
	int screenWidth;

	/**
	* Screen height
	*/
	int screenHeight;


	bool fullScreen;
	bool running;
	
	
	/**
	* Mapping for windows keyboard
	*/
	TgcInput::Keys KEYBOARD_MAPPINGS[255];

private:

	

};

}


//Handler de eventos de windows
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);




