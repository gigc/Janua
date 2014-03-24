/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "Examples/ExampleTgcBox/ExampleTgcBox.h"
using namespace Examples;


string ExampleTgcBox::getCategory()
{
	return "Category";
}

string ExampleTgcBox::getName()
{
	return "Example1";
}

string ExampleTgcBox::getDescription()
{
	return "Example1";
}

void ExampleTgcBox::init()
{
	camera = new TgcFpsCamera();

	box = TgcBox::fromSize(Vector3(10, 10, 10), TgcTexture::createTexture(GuiController::Instance->examplesMediaPath + "TgcModels\\Deposito\\Textures\\box1.jpg"));
	//box = TgcBox::fromSize(Vector3(10, 10, 10), Color::Red);
}

void ExampleTgcBox::render(float elapsedTime)
{
	camera->updateCamera();
	camera->updateViewMatrix();

	box->render();
}

void ExampleTgcBox::close()
{
	box->dispose();
	delete box;
}

