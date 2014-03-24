/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <string>

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Ui/Gui/TgcGuiItem.h"
#include "TgcViewer/2D/TgcSprite.h"
#include "TgcViewer/2D/TgcText2d.h"
#include "TgcViewer/TgcSceneLoader/TgcTexture.h"
#include "TgcViewer/Math/Color.h"

//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;}


namespace TgcViewer
{



/**
* A GUI button widget
*/
class TgcGuiButton : public TgcGuiItem
{
public:

	TgcGuiButton(const string id, string label);
	TgcGuiButton(const TgcGuiButton&);
	~TgcGuiButton();

	//Virtual members
	void render();
	void dispose();
	virtual void onClick(int button, const Vector2 pos);
	virtual void onMouseDown(int button, const Vector2 pos);
	virtual void onMouseUp(int button, const Vector2 pos);
	virtual void onMouseOver();
	virtual void onMouseOut();
	

private:
	


public:

	/**
	* Text for the button
	*/
	string label;


	/**
	* Text element
	*/
	TgcText2d* labelText;

	/**
	* Button sprite
	*/
	TgcSprite* sprite;


	bool mouseOver;
	bool pressed;

private:

	
	
};




}