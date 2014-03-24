/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <string>
#include <map>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Math/Vector2.h"
#include "TgcViewer/Math/Vector3.h"
#include "TgcViewer/Math/Vector4.h"
#include "TgcViewer/Math/Color.h"
#include "TgcViewer/2D/TgcText2d.h"
#include "TgcViewer/Input/TgcInput.h"
#include "TgcViewer/TgcSceneLoader/TgcParserUtils.h"

//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;}

namespace TgcViewer
{



/**
* Tool to draw debug text variables to screen
*/
class TgcUserVars
{

public:

	TgcUserVars();
	TgcUserVars(const TgcUserVars&);
	~TgcUserVars();

	/**
	* Creates a new variable with the specified name.
	* @param name unique identifier of the variable
	*/
	void addVar(const string name);

	/**
	* Set the value of a variable.
	* If the variable does not exist then it is created.
	* @param name unique identifier of the variable
	* @param value
	*/
	void setVar(const string name, const string value);
	void setVar(const string name, const int value);
	void setVar(const string name, const int long value);
	void setVar(const string name, const unsigned int value);
	void setVar(const string name, const float value);
	void setVar(const string name, const Vector2& value);
	void setVar(const string name, const Vector3& value);
	void setVar(const string name, const Vector4& value);
	void setVar(const string name, const Color& value);


	/**
	* Draws all the variables
	*/
	void render();

	/**
	* Free resources
	*/
	void dispose();

private:

public:

	static const int TEXT_Y_DISTANCE = 25;

	/**
	* Top-left position
	*/
	Vector2 position;

	/**
	* Font color
	*/
	Color color;

	/**
	* True to render the variables
	*/
	bool enabled;

	/**
	* Key to show or hide the variables
	*/
	TgcInput::Keys enableKey;

	/**
	* Text elements
	*/
	map<string, TgcText2d*> uiTexts;

private:

	
};




}