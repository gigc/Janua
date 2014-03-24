/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "Examples/ExampleSprite/ExampleSprite.h"
using namespace Examples;


string ExampleSprite::getCategory()
{
	return "Category";
}

string ExampleSprite::getName()
{
	return "ExampleSprite";
}

string ExampleSprite::getDescription()
{
	return "ExampleSprite";
}

void ExampleSprite::init()
{
	camera = new TgcFpsCamera();


	sprite = new TgcSprite();
	sprite->texture = TgcTexture::createTexture(GuiController::Instance->examplesMediaPath + "TgcModels\\Deposito\\Textures\\boxMetal.jpg");
	sprite->position = Vector2(50, 100);
	sprite->size = Vector2((float)sprite->texture->width * 2, (float)sprite->texture->height * 2);
	sprite->srcRect = ScreenSpace::ScreenRect(30, 30, 200, 200);
	sprite->init();


	box = TgcBox::fromSize(Vector3(10, 10, 10), Color::Brown);


	animSprite = new TgcAnimatedSprite();
	animSprite->init(GuiController::Instance->examplesMediaPath + "Sprites\\Explosion.png", Vector2(64, 64), 16, 10, Vector2(600, 50));
	//animSprite->init(GuiController::Instance->examplesMediaPath + "Sprites\\rotation_cube.png", Vector2(64, 64), 16, 10, Vector2(600, 50));
	animSprite->sprite->size *= 2;
	animSprite->updateValues();


	text = new TgcText2d();
	text->text = "Hello world. Hello world. Hello world. Hello world. Hello world.";
	text->position = Vector2(100, 200);
	text->updateValues();

	text2 = new TgcText2d();
	text2->text = "After three years this \"wonderful all-around resource\" of computer graphics, \"indispensable for every serious graphics programmer\", is available in a completely revised and updated edition";
	text2->position = Vector2(100, 400);
	text2->color = Color::Magenta;
	text2->fontId = TgcFont::MICROSOFT_SANS_SERIF_26;
	text2->size = Vector2(300, 1000);
	text2->align = TextAlign::Center;
	text2->updateValues();
}

void ExampleSprite::render(float elapsedTime)
{
	camera->updateCamera();
	camera->updateViewMatrix();

	
	box->render();

	sprite->render();

	animSprite->render();

	text->render();
	text2->render();
	
	GuiController::Instance->userVars->setVar("var1", "value");
	GuiController::Instance->userVars->setVar("var2", 159.0f);
	GuiController::Instance->userVars->setVar("position", camera->position);
	GuiController::Instance->userVars->setVar("windows size", GuiController::Instance->windowHandler->size());
	GuiController::Instance->userVars->setVar("vector4", Vector4(-1, 0.15f, -4.0f, 1000));
	GuiController::Instance->userVars->setVar("color", box->color);
}

void ExampleSprite::close()
{
	delete camera;

	sprite->dispose();
	delete sprite;

	box->dispose();
	delete box;

	animSprite->dispose();
	delete animSprite;

	text->dispose();
	delete text;

	text2->dispose();
	delete text2;
}

