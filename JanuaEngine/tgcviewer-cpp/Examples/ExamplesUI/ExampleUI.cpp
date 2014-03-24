/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "Examples/ExamplesUI/ExampleUI.h"
using namespace Examples;


string ExampleUI::getCategory()
{
	return "ExamplesUI";
}

string ExampleUI::getName()
{
	return "ExampleUI";
}

string ExampleUI::getDescription()
{
	return "ExampleUI";
}

void ExampleUI::init()
{
	camera = new TgcFpsCamera();
	
	checkbox1 = new TgcGuiCheckBox("check1", "checkbox 1");
	checkbox1->position = Vector2(20, 100);
	GuiController::Instance->gui->add(checkbox1);

	checkbox2 = new TgcGuiCheckBox("check1", "checkbox 2");
	checkbox2->position = Vector2(20, 150);
	GuiController::Instance->gui->add(checkbox2);
	
	button1 = new TgcGuiButton("button1", "button 1");
	button1->position = Vector2(20, 200);
	GuiController::Instance->gui->add(button1);
	
	button2 = new TgcGuiButton("button2", "button 2 hello");
	button2->position = Vector2(20, 250);
	GuiController::Instance->gui->add(button2);
	
	slider1 = new TgcGuiSlider("slider1", "Slider 1");
	slider1->position = Vector2(20, 300);
	GuiController::Instance->gui->add(slider1);

	slider2 = new TgcGuiSlider("slider2", "Slider 2");
	slider2->position = Vector2(20, 350);
	slider2->setValues(128, 256, 256);
	GuiController::Instance->gui->add(slider2);
	
	slider3 = new TgcGuiSlider("slider3", "Slider 3");
	slider3->position = Vector2(20, 400);
	slider3->setValues(0.5f, 3.0f, 0.5f);
	GuiController::Instance->gui->add(slider3);
}

void ExampleUI::render(float elapsedTime)
{
	camera->updateCamera();
	camera->updateViewMatrix();

	TgcGui::Message m = GuiController::Instance->gui->update();
	GuiController::Instance->gui->render();

	GuiController::Instance->drawText("Current value: " + TgcParserUtils::toString(slider1->currentValue), (int)slider1->position.X + 300, (int)slider1->position.Y);
	GuiController::Instance->drawText("Current value: " + TgcParserUtils::toString(slider2->currentValue), (int)slider2->position.X + 300, (int)slider2->position.Y);
	GuiController::Instance->drawText("Current value: " + TgcParserUtils::toString(slider3->currentValue), (int)slider3->position.X + 300, (int)slider3->position.Y);
}

void ExampleUI::close()
{
	delete camera;
	GuiController::Instance->gui->reset();
}

