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
#include "TgcViewer/Ui/Gui/TgcGuiCheckBox.h"

//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;}


namespace TgcViewer
{



/**
* A Boolean modifier with a checkbox
*/
class TgcBoolModifier : public TgcModifierItem
{

public:

	TgcBoolModifier(const string id, const string label, bool value);
	TgcBoolModifier(const TgcBoolModifier&);
	~TgcBoolModifier();


	//Virtual members
	virtual void update();
	virtual void dispose();
	virtual bool getBool() const;
	virtual string getString() const;
	virtual void setPosition(const Vector2 pos);
	


private:
	
public:

	/**
	* Checkbox widget
	*/
	TgcGuiCheckBox* checkbox;

private:

	
};




}