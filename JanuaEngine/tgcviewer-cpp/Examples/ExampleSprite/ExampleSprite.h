/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//Project Includes:
#include "Examples/TgcViewerIncludes.h"



namespace Examples
{


/**
* Example Sprite
*/
class ExampleSprite : public TgcExample
{

public:

	//Virtual members
	string getCategory();
	string getName();
	string getDescription();
	void init();
	void render(float elapsedTime);
	void close();

private:

public:

	TgcFpsCamera* camera;
	TgcSprite* sprite;
	TgcBox* box;
	TgcAnimatedSprite* animSprite;
	TgcText2d* text;
	TgcText2d* text2;

private:


	
};




}