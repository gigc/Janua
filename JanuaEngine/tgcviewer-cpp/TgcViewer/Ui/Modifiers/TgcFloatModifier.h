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
#include "TgcViewer/Ui/Modifiers/TgcModifierItem.h"
#include "TgcViewer/Ui/Gui/TgcGuiSlider.h"
#include "TgcViewer/TgcSceneLoader/TgcParserUtils.h"

//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;}


namespace TgcViewer
{



/**
* A float or numeric modifier with a slider
*/
class TgcFloatModifier : public TgcModifierItem
{

public:

	TgcFloatModifier(const string id, const string label, float minValue, float maxValue, float currentValue);
	TgcFloatModifier(const TgcFloatModifier&);
	~TgcFloatModifier();


	//Virtual members
	virtual void update();
	virtual void dispose();
	virtual float getFloat() const;
	virtual int getInt() const;
	virtual string getString() const;
	virtual void setPosition(const Vector2 pos);
	


private:
	
public:

	/**
	* slider widget
	*/
	TgcGuiSlider* slider;

private:

	
};




}