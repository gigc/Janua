/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#pragma once


//General Includes:
#include <string>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Example/TgcExample.h"
#include "TgcViewer/Windows/WindowHandler.h"
#include "TgcViewer/Windows/HighResolutionTimer.h"
#include "TgcViewer/Renderer/TgcRendererFactory.h"
#include "TgcViewer/Renderer/TgcRenderer.h"
#include "TgcViewer/Input/TgcInput.h"
#include "TgcViewer/TgcSceneLoader/TgcTexture.h"
#include "TgcViewer/TgcSceneLoader/TgcParserUtils.h"
#include "TgcViewer/Ui/TgcLogger.h"
#include "TgcViewer/Ui/TgcUserVars.h"
#include "TgcViewer/Ui/Gui/TgcGui.h"
#include "TgcViewer/Ui/Modifiers/TgcModifiers.h"
#include "TgcViewer/Shaders/TgcShaders.h"
#include "TgcViewer/2D/TgcFontRenderer.h"
#include "TgcViewer/Math/Color.h"



namespace TgcViewer
{



/**
* Main class of the framework
*/
class GuiController
{

public:

	/**
	* Creates a new instance of GuiController
	*/
	static void newInstance();
	
	void initGraphics(TgcExample* example);
	void render();
	void shutDown();
	void dispose();

	/**
	* Draw debug text in the screen
	* @param text
	* @param x
	* @param y
	* @param color
	*/
	void drawText(string text, int x, int y, Color color = Color::Yellow);


private:
	
	GuiController();
	~GuiController();

	
public:

	/**
	* Singleton instance
	*/
	static GuiController* Instance;
	
	/**
	* The current example of the application
	*/
	TgcExample* currentExample;

	/**
	* Window handler
	*/
	WindowHandler* windowHandler;

	/**
	* Renderer
	*/
	TgcRenderer* renderer;

	/**
	* HighResolutionTimer
	*/
	HighResolutionTimer* highResolutionTimer;

	/**
	* Keyboard and mouse input
	*/
	TgcInput* input;

	/**
	* Textures pool
	*/
	TgcTexturePool* texturesPool;

	/**
	* Logger
	*/
	TgcLogger* logger;
	
	/**
	* Media path of all examples
	* .../Media/Examples/
	*/
	string examplesMediaPath;

	/**
	* Media path for the engine resources
	* .../Media/TgcViewer/
	*/
	string engineMediaPath;

	/**
	* Common engine shaders
	*/
	TgcShaders* shaders;

	/**
	* Elapsed seconds between frames
	*/
	float elapsedTime;

	/**
	* For rendering bitmap fonts
	*/
	TgcFontRenderer* fontRenderer;

	/**
	* Text-area used for debug info
	*/
	TgcText2d* debugText;

	/**
	* For rendering debug variables
	*/
	TgcUserVars* userVars;

	/**
	* 2D User interface manager
	*/
	TgcGui* gui;

	/**
	* For creating fast debug widgets
	*/
	TgcModifiers* modifiers;
	
private:

	
	
};




}