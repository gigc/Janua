/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <string>
#include <vector>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Ui/Modifiers/TgcModifierItem.h"

//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;}
//Forward declaration for "TgcViewer/Ui/Modifiers/TgcBoolModifier.h"
namespace TgcViewer {class TgcBoolModifier;}
//Forward declaration for "TgcViewer/Ui/Modifiers/TgcFloatModifier.h"
namespace TgcViewer {class TgcFloatModifier;}


namespace TgcViewer
{



/**
* Tool to create fast debug widgets, like checkbox, buttons and sliders
*/
class TgcModifiers
{

public:

	TgcModifiers();
	TgcModifiers(const TgcModifiers&);
	~TgcModifiers();

	/**
	* Add a new modifier
	* @param modifier
	*/
	void add(TgcModifierItem* modifier);

	/**
	* Add a new Boolean modifier
	* @param id
	* @param label
	* @param value
	*/
	void addBool(const string id, const string label, bool value);

	/**
	* Add a new Float modifier
	* @param id
	* @param label
	* @param minValue
	* @param maxValue
	* @param currentValue
	*/
	void addFloat(const string id, const string label, float minValue, float maxValue, float currentValue);


	/**
	* Returns the specified modifier
	* @param id
	* @return TgcModifierItem*
	*/
	TgcModifierItem* get(const string id) const;
	//TgcModifierItem* operator[] (const string id) const;

	/**
	* Updates all the modifiers
	*/
	void update();

	/**
	* Render all the modifiers
	*/
	void render();

	/**
	* Free resources
	*/
	void dispose();


	/**
	* {Internal}
	* Returns the index of the modifier, or -1 if it is not found
	*/
	int getModifierIndex(const string id) const;

private:

public:

	/**
	* List of modifiers
	*/
	vector<TgcModifierItem*> modifiers;


	float currentHeight;

private:

	
};




}