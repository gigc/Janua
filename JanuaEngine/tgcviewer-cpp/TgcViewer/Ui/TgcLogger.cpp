/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Ui/TgcLogger.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcLogger::TgcLogger()
{
}


TgcLogger::TgcLogger(const TgcLogger& other)
{
}


TgcLogger::~TgcLogger()
{
}

void TgcLogger::log(string txt)
{
	cout << txt;
}

void TgcLogger::logError(string txt)
{
	cerr << txt;
	MessageBox(GuiController::Instance->windowHandler->hwnd, txt.c_str(), "Error", MB_OK);
}

void TgcLogger::dispose()
{
}

