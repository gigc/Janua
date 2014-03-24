/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "TgcViewer/Windows/WindowHandler.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;



WindowHandler::WindowHandler()
{
	this->fullScreen = false;
	this->applicationName = "TgcViewer";
	this->initKeyboardMapping();

	this->initializeWindow();
}


WindowHandler::WindowHandler(const WindowHandler& other)
{
}


WindowHandler::~WindowHandler()
{
}


void WindowHandler::initializeWindow()
{
	running = true;

	// Get the instance of this application.
	hinstance = GetModuleHandle(NULL);

	// Setup the windows class with default settings.
	WNDCLASSEX wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hinstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm       = wc.hIcon;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = this->applicationName;
	wc.cbSize        = sizeof(WNDCLASSEX);
	
	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	this->screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	this->screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	int posX, posY;
	if(this->fullScreen)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)this->screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)this->screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = 0;
		posY = 0;
	}
	else
	{
		this->screenWidth  = 1024;
		this->screenHeight = 768;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - this->screenWidth)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - this->screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, this->applicationName, this->applicationName, 
						    WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
						    posX, posY, this->screenWidth, this->screenHeight, NULL, NULL, hinstance, NULL);

	// Get device context
	this->deviceContext = GetDC(this->hwnd);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);


	//Center mouse pose
	SetCursorPos(this->screenWidth / 2, this->screenHeight / 2);

	// Hide the mouse cursor.
	//ShowCursor(false);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		//Window destroyed
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		//Window close
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}
		//Mouse movment
		case WM_MOUSEMOVE:
		{
			int xPos = GET_X_LPARAM(lparam); 
			int yPos = GET_Y_LPARAM(lparam); 
			GuiController::Instance->input->setMousePos(xPos, yPos);
			return 0;
		}
		//Right mouse button down
		case WM_RBUTTONDOWN:
		{
			GuiController::Instance->input->setButtonDown(TgcInput::BUTTON_RIGHT);
			return 0;
		}
		//Left mouse button down
		case WM_LBUTTONDOWN:
		{
			GuiController::Instance->input->setButtonDown(TgcInput::BUTTON_LEFT);
			return 0;
		}
		//Middle mouse button down
		case WM_MBUTTONDOWN:
		{
			GuiController::Instance->input->setButtonDown(TgcInput::BUTTON_MIDDLE);
			return 0;
		}
		//Right mouse button up
		case WM_RBUTTONUP:
		{
			GuiController::Instance->input->setButtonUp(TgcInput::BUTTON_RIGHT);
			return 0;
		}
		//Left mouse button down
		case WM_LBUTTONUP:
		{
			GuiController::Instance->input->setButtonUp(TgcInput::BUTTON_LEFT);
			return 0;
		}
		//Middle mouse button down
		case WM_MBUTTONUP:
		{
			GuiController::Instance->input->setButtonUp(TgcInput::BUTTON_MIDDLE);
			return 0;
		}
		//Mouse wheel
		case WM_MOUSEWHEEL:
		{
			int zDelta = GET_WHEEL_DELTA_WPARAM(wparam);
			GuiController::Instance->input->setMouseWheel(zDelta);
			return 0;
		}
		//Keydown
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			GuiController::Instance->input->setKeyDown(GuiController::Instance->windowHandler->KEYBOARD_MAPPINGS[(unsigned int)wparam]);
			return 0;
		}
		//Keyup
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			GuiController::Instance->input->setKeyUp(GuiController::Instance->windowHandler->KEYBOARD_MAPPINGS[(unsigned int)wparam]);
			return 0;
		}
		// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umessage, wparam, lparam);
		}
	}
}


void WindowHandler::run()
{
	// Initialize the message structure.
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	
	// Loop until there is a quit message from the window or the user.
	while(running)
	{
		// Handle the windows messages.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if(msg.message == WM_QUIT)
		{
			running = false;
		}
		else
		{
			// Otherwise do render
			GuiController::Instance->render();
		}

	}

	closeWindow();
	GuiController::Instance->dispose();
	return;
}


void WindowHandler::closeWindow()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if(this->fullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	//Release device context
	ReleaseDC(hwnd, deviceContext);

	// Remove the window.
	DestroyWindow(hwnd);
	hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(this->applicationName, hinstance);
	hinstance = NULL;
}



string WindowHandler::getCurrentDir()
{
	char buffer[4096];
	GetModuleFileName(NULL, buffer, 4096);
	
	string currentPath = string(buffer);
	return currentPath.substr(0, currentPath.find_last_of("\\"));
}

Vector2 WindowHandler::size() const
{
	return Vector2((float)screenWidth, (float)screenHeight);
}

void WindowHandler::initKeyboardMapping()
{
	KEYBOARD_MAPPINGS['0'] = TgcInput::K_0;
	KEYBOARD_MAPPINGS['1'] = TgcInput::K_1;
	KEYBOARD_MAPPINGS['2'] = TgcInput::K_2;
	KEYBOARD_MAPPINGS['3'] = TgcInput::K_3;
	KEYBOARD_MAPPINGS['4'] = TgcInput::K_4;
	KEYBOARD_MAPPINGS['5'] = TgcInput::K_5;
	KEYBOARD_MAPPINGS['6'] = TgcInput::K_6;
	KEYBOARD_MAPPINGS['7'] = TgcInput::K_7;
	KEYBOARD_MAPPINGS['8'] = TgcInput::K_8;
	KEYBOARD_MAPPINGS['9'] = TgcInput::K_9;

	KEYBOARD_MAPPINGS['A'] = TgcInput::K_A;
	KEYBOARD_MAPPINGS['B'] = TgcInput::K_B;
	KEYBOARD_MAPPINGS['C'] = TgcInput::K_C;
	KEYBOARD_MAPPINGS['D'] = TgcInput::K_D;
	KEYBOARD_MAPPINGS['E'] = TgcInput::K_E;
	KEYBOARD_MAPPINGS['F'] = TgcInput::K_F;
	KEYBOARD_MAPPINGS['G'] = TgcInput::K_G;
	KEYBOARD_MAPPINGS['H'] = TgcInput::K_H;
	KEYBOARD_MAPPINGS['I'] = TgcInput::K_I;
	KEYBOARD_MAPPINGS['J'] = TgcInput::K_J;
	KEYBOARD_MAPPINGS['K'] = TgcInput::K_K;
	KEYBOARD_MAPPINGS['L'] = TgcInput::K_L;
	KEYBOARD_MAPPINGS['M'] = TgcInput::K_M;
	KEYBOARD_MAPPINGS['N'] = TgcInput::K_N;
	KEYBOARD_MAPPINGS['O'] = TgcInput::K_O;
	KEYBOARD_MAPPINGS['P'] = TgcInput::K_P;
	KEYBOARD_MAPPINGS['Q'] = TgcInput::K_Q;
	KEYBOARD_MAPPINGS['R'] = TgcInput::K_R;
	KEYBOARD_MAPPINGS['S'] = TgcInput::K_S;
	KEYBOARD_MAPPINGS['T'] = TgcInput::K_T;
	KEYBOARD_MAPPINGS['U'] = TgcInput::K_U;
	KEYBOARD_MAPPINGS['V'] = TgcInput::K_V;
	KEYBOARD_MAPPINGS['W'] = TgcInput::K_W;
	KEYBOARD_MAPPINGS['X'] = TgcInput::K_X;
	KEYBOARD_MAPPINGS['Y'] = TgcInput::K_Y;
	KEYBOARD_MAPPINGS['Z'] = TgcInput::K_Z;

	KEYBOARD_MAPPINGS[VK_F1] = TgcInput::K_F1;
	KEYBOARD_MAPPINGS[VK_F2] = TgcInput::K_F2;
	KEYBOARD_MAPPINGS[VK_F3] = TgcInput::K_F3;
	KEYBOARD_MAPPINGS[VK_F4] = TgcInput::K_F4;
	KEYBOARD_MAPPINGS[VK_F5] = TgcInput::K_F5;
	KEYBOARD_MAPPINGS[VK_F6] = TgcInput::K_F6;
	KEYBOARD_MAPPINGS[VK_F7] = TgcInput::K_F7;
	KEYBOARD_MAPPINGS[VK_F8] = TgcInput::K_F8;
	KEYBOARD_MAPPINGS[VK_F9] = TgcInput::K_F9;
	KEYBOARD_MAPPINGS[VK_F10] = TgcInput::K_F10;
	KEYBOARD_MAPPINGS[VK_F11] = TgcInput::K_F11;
	KEYBOARD_MAPPINGS[VK_F11] = TgcInput::K_F12;

	KEYBOARD_MAPPINGS[VK_NUMPAD0] = TgcInput::K_NUMPAD0;
	KEYBOARD_MAPPINGS[VK_NUMPAD1] = TgcInput::K_NUMPAD1;
	KEYBOARD_MAPPINGS[VK_NUMPAD2] = TgcInput::K_NUMPAD2;
	KEYBOARD_MAPPINGS[VK_NUMPAD3] = TgcInput::K_NUMPAD3;
	KEYBOARD_MAPPINGS[VK_NUMPAD4] = TgcInput::K_NUMPAD4;
	KEYBOARD_MAPPINGS[VK_NUMPAD5] = TgcInput::K_NUMPAD5;
	KEYBOARD_MAPPINGS[VK_NUMPAD6] = TgcInput::K_NUMPAD6;
	KEYBOARD_MAPPINGS[VK_NUMPAD7] = TgcInput::K_NUMPAD7;
	KEYBOARD_MAPPINGS[VK_NUMPAD8] = TgcInput::K_NUMPAD8;
	KEYBOARD_MAPPINGS[VK_NUMPAD9] = TgcInput::K_NUMPAD9;

	KEYBOARD_MAPPINGS[VK_CLEAR] = TgcInput::K_CLEAR;
	KEYBOARD_MAPPINGS[VK_RETURN] = TgcInput::K_RETURN;
	KEYBOARD_MAPPINGS[VK_SHIFT] = TgcInput::K_SHIFT;
	KEYBOARD_MAPPINGS[VK_CONTROL] = TgcInput::K_CONTROL;
	KEYBOARD_MAPPINGS[VK_MENU] = TgcInput::K_MENU;
	KEYBOARD_MAPPINGS[VK_PAUSE] = TgcInput::K_PAUSE;
	KEYBOARD_MAPPINGS[VK_CAPITAL] = TgcInput::K_CAPITAL;
	KEYBOARD_MAPPINGS[VK_ESCAPE] = TgcInput::K_ESCAPE;
	KEYBOARD_MAPPINGS[VK_CONVERT] = TgcInput::K_CONVERT;
	KEYBOARD_MAPPINGS[VK_NONCONVERT] = TgcInput::K_NONCONVERT;
	KEYBOARD_MAPPINGS[VK_ACCEPT] = TgcInput::K_ACCEPT;
	KEYBOARD_MAPPINGS[VK_MODECHANGE] = TgcInput::K_MODECHANGE;
	KEYBOARD_MAPPINGS[VK_SPACE] = TgcInput::K_SPACE;
	KEYBOARD_MAPPINGS[VK_PRIOR] = TgcInput::K_PRIOR;
	KEYBOARD_MAPPINGS[VK_NEXT] = TgcInput::K_NEXT;
	KEYBOARD_MAPPINGS[VK_END] = TgcInput::K_END;
	KEYBOARD_MAPPINGS[VK_HOME] = TgcInput::K_HOME;
	KEYBOARD_MAPPINGS[VK_LEFT] = TgcInput::K_LEFT;
	KEYBOARD_MAPPINGS[VK_UP] = TgcInput::K_UP;
	KEYBOARD_MAPPINGS[VK_RIGHT] = TgcInput::K_RIGHT;
	KEYBOARD_MAPPINGS[VK_DOWN] = TgcInput::K_DOWN;
	KEYBOARD_MAPPINGS[VK_SELECT] = TgcInput::K_SELECT;
	KEYBOARD_MAPPINGS[VK_PRINT] = TgcInput::K_PRINT;
	KEYBOARD_MAPPINGS[VK_EXECUTE] = TgcInput::K_EXECUTE;
	KEYBOARD_MAPPINGS[VK_SNAPSHOT] = TgcInput::K_SNAPSHOT;
	KEYBOARD_MAPPINGS[VK_INSERT] = TgcInput::K_INSERT;
	KEYBOARD_MAPPINGS[VK_DELETE] = TgcInput::K_DELETE;
	KEYBOARD_MAPPINGS[VK_HELP] = TgcInput::K_HELP;
}

