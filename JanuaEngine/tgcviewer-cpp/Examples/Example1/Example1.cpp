/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "Examples/Example1/Example1.h"
using namespace Examples;


string Example1::getCategory()
{
	return "Category";
}

string Example1::getName()
{
	return "Example1";
}

string Example1::getDescription()
{
	return "Example1";
}

void Example1::init()
{
	camera = new TgcFpsCamera();

	TgcSceneLoader loader;
	scene = loader.loadSceneFromFile(GuiController::Instance->examplesMediaPath + "TgcModels\\Deposito\\Deposito-TgcScene.xml");
	//scene = loader.loadSceneFromFile(GuiController::Instance->examplesMediaPath + "TgcModels\\CamionCemento\\CamionCemento-TgcScene.xml");
	//scene = loader.loadSceneFromFile(GuiController::Instance->examplesMediaPath + "TgcModels\\Box\\Box-TgcScene.xml");
	//scene = loader.loadSceneFromFile(GuiController::Instance->examplesMediaPath + "TgcModels\\Triangle\\Triangle-TgcScene.xml");
}

void Example1::render(float elapsedTime)
{
	camera->updateCamera();
	camera->updateViewMatrix();

	scene->renderAll(true);
}

void Example1::close()
{
	scene->disposeAll();
	delete scene;
}

