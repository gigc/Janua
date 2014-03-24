/*#############################################################
TgcViewer-cpp

Author: Matias Leone

Application entry point
#############################################################*/

#include "TgcViewer/GuiController.h"
#include "TgcViewer/Example/TgcExample.h"
using namespace TgcViewer; 


//Concret example to be used
#include "Examples/Example1/Example1.h"
#include "Examples/ExampleVB/ExampleVB.h"
#include "Examples/ExampleEditor/ExampleEditor.h"
#include "Examples/ExampleTgcBox/ExampleTgcBox.h"
#include "Examples/ExampleOCEngine1/ExampleOCEngine1.h"
#include "Examples/ExampleOCEngine1/ExampleOCEngineFPSView.h"
#include "Examples/ExampleOCEngine1/ExampleCreateRawSceneXML.h"
using namespace Examples; 


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	//Create GuiController
	GuiController::newInstance();

	
	//Create concret example
	//TgcExample* example = new Example1();
	//TgcExample* example = new ExampleVB();
	//TgcExample* example = new ExampleEditor();
	//TgcExample* example = new ExampleTgcBox();
	//TgcExample* example = new ExampleOCEngine1();
	TgcExample* example = new ExampleOCEngineFPSView();
	//TgcExample* example = new ExampleCreateRawSceneXML();
	
	
	//Init graphics
	GuiController::Instance->initGraphics(example);

	//Shutdown
	//GuiController::Instance->dispose();

	return 0;
}