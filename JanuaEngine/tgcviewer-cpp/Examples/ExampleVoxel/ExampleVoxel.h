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
* ExampleVoxel
*/
class ExampleVoxel : public TgcExample
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

private:


	
};




}