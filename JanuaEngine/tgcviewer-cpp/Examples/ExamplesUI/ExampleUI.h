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
* ExampleUI
*/
class ExampleUI : public TgcExample
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

	TgcGuiCheckBox* checkbox1;
	TgcGuiCheckBox* checkbox2;
	TgcGuiButton* button1;
	TgcGuiButton* button2;
	TgcGuiSlider* slider1;
	TgcGuiSlider* slider2;
	TgcGuiSlider* slider3;


private:


	
};




}