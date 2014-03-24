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
* A GUI slider widget
*/
class TgcGuiSlider : public TgcGuiItem
{
public:

	TgcGuiSlider(const string id, string label);
	TgcGuiSlider(const TgcGuiSlider&);
	~TgcGuiSlider();

	/**
	* Set the extremes and current value
	*/
	void setValues(float minValue, float maxValue, float currentValue);


	//Virtual members
	void render();
	void dispose();
	virtual void onClick(int button, const Vector2 pos);
	virtual void onMouseDown(int button, const Vector2 pos);
	virtual void onMouseUp(int button, const Vector2 pos);
	virtual void onMouseOver();
	virtual void onMouseOut();
	virtual void onMouseMove(const Vector2 pos);
	

private:
	


public:

	/**
	* Minium value that can take the slider
	*/
	float minValue;

	/**
	* Maxium value that can take the slider
	*/
	float maxValue;

	/**
	* The current value of the slider
	*/
	float currentValue;

	/**
	* Text for the button
	*/
	string label;

	/**
	* Text element
	*/
	TgcText2d* labelText;

	/**
	* Sprite for the bar
	*/
	TgcSprite* barSprite;

	/**
	* Sprite for the slide button
	*/
	TgcSprite* sliderSprite;


	bool mouseOver;
	bool dragging;
	float sliderPixelWidth;

private:

};




}