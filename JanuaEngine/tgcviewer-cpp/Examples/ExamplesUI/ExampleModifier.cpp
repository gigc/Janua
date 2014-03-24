/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "Examples/ExamplesUI/ExampleModifier.h"
using namespace Examples;


string ExampleModifier::getCategory()
{
	return "ExamplesUI";
}

string ExampleModifier::getName()
{
	return "ExampleModifier";
}

string ExampleModifier::getDescription()
{
	return "ExampleModifier";
}

void ExampleModifier::init()
{
	camera = new TgcFpsCamera();
	
	GuiController::Instance->modifiers->addBool("bool1", "boolean modifier 1", false);
	GuiController::Instance->modifiers->addFloat("float1", "float modifier 1", -10, 10, 5);
	GuiController::Instance->modifiers->addBool("bool2", "boolean modifier 2", true);
	GuiController::Instance->modifiers->addFloat("float2", "float modifier 2", 0, 100, 25);
	GuiController::Instance->modifiers->addBool("bool3", "boolean modifier 3", false);
	GuiController::Instance->modifiers->addBool("bool4", "boolean modifier 4", true);
	GuiController::Instance->modifiers->addFloat("float2", "float modifier 2", 0, 100, 25);
	GuiController::Instance->modifiers->addBool("bool5", "boolean modifier 5", false);
}

void ExampleModifier::render(float elapsedTime)
{
	camera->updateCamera();
	camera->updateViewMatrix();

	GuiController::Instance->drawText("bool1: " + GuiController::Instance->modifiers->get("bool1")->getString(), 300, 300);
	GuiController::Instance->drawText("float1: " + GuiController::Instance->modifiers->get("float1")->getString(), 300, 350);

}

void ExampleModifier::close()
{
	delete camera;
}

