/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:


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
* A GUI checkbox widget
*/
class TgcGuiCheckBox : public TgcGuiItem
{

public:

	TgcGuiCheckBox(const string id, const string label);
	TgcGuiCheckBox(const TgcGuiCheckBox&);
	~TgcGuiCheckBox();

	//Virtual members
	void render();
	void dispose();
	virtual void onClick(int button, const Vector2 pos);
	virtual void onMouseOver();
	virtual void onMouseOut();

private:


public:

	/**
	* True if the widget is checked
	*/
	bool checked;

	/**
	* Text for the label of the checkbox
	*/
	string label;


	/**
	* Text element
	*/
	TgcText2d* labelText;

	/**
	* Checkbox sprite
	*/
	TgcSprite* sprite;


	bool mouseOver;


private:

	
};




}