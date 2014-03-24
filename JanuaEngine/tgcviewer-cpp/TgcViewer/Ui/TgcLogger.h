/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <string>
#include <iostream>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"

//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;}


namespace TgcViewer
{



/**
* Tools for message logging
*/
class TgcLogger
{

public:

	TgcLogger();
	TgcLogger(const TgcLogger&);
	~TgcLogger();


	/**
	* Log message
	*/
	void log(string txt);

	/**
	* Log error message
	*/
	void logError(string error);

	/**
	* Free resources
	*/
	void dispose();

private:

public:

private:
	
};




}