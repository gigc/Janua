/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <string>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Math/Vector2.h"
#include "TgcViewer/Math/Color.h"
#include "TgcViewer/Renderer/TgcRendererGlobals.h"

//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;}


namespace TgcViewer
{



/**
* Tool to draw 2D text in screen
*/
class TgcText2d
{

public:

	TgcText2d();
	TgcText2d(const TgcText2d&);
	~TgcText2d();


	/**
	* Update text values when some property is changed
	*/
	void updateValues();

	/**
	* Render the text, if it is enabled
	*/
	void render();

	/**
	* Free resources
	*/ 
	void dispose();

private:

public:

	/**
	* The text to draw
	*/
	string text;

	/**
	* The font ID to use, located in Media\TgcViewer\Fonts
	* Example: times_new_roman_16
	*/
	string fontId;

	/**
	* Top-left position of the text
	*/
	Vector2 position;

	/**
	* Size of the text area
	*/
	Vector2 size;

	/**
	* Texto align.
	* Left by default
	*/
	TextAlign::Align align;

	/**
	* Enabled for render
	*/
	bool enabled;

	/**
	* Color to render the text
	*/
	Color color;

private:

	
};




}