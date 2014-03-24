/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once

//General includes
#include <sstream>

//Project Includes:
#include "Examples/TgcViewerIncludes.h"
#include "Examples/ExampleOCEngine1/Voxel.h"
#include "TgcViewer/Xml/pugixml.hpp"
using namespace pugi;




namespace Examples
{


/**
* ExampleCreateRawSceneXML
*/
class ExampleCreateRawSceneXML : public TgcExample
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

private:


	
};




}