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


namespace TgcViewer
{



/**
* Abstract GUI element
*/
class TgcGuiItem
{

public:

	TgcGuiItem();
	TgcGuiItem(const TgcGuiItem&);
	~TgcGuiItem();

	/**
	* Init the item
	*/
	void init(const string id);

	/**
	* Draws the item
	*/
	virtual void render() = 0;

	/**
	* Free resources
	*/
	virtual void dispose() = 0;

	/**
	* Check if the specified position is inside the item
	*/
	bool inside(const Vector2 pos) const;



	////////////////// Events ///////////////////

	/**
	* When the item is selected
	*/
	virtual void onFocus();

	/**
	* Whe the item is unselected
	*/
	virtual void onFocusLost();

	/**
	* When the mouse pointer moves over the item
	*/
	virtual void onMouseOver();

	/**
	* When the mouse pointer moves out the item
	*/
	virtual void onMouseOut();

	/**
	* When the item is clicked
	* @param button 0: left, 1: right: 2: middle
	* @param pos mouse pos
	*/
	virtual void onClick(int button, const Vector2 pos);

	/**
	* When a mouse button is pressed down on the item
	* @param button 0: left, 1: right: 2: middle
	* @param pos mouse pos
	*/
	virtual void onMouseDown(int button, const Vector2 pos);

	/**
	* When a mouse button is released on the item
	* @param button 0: left, 1: right: 2: middle
	* @param pos mouse pos
	*/
	virtual void onMouseUp(int button, const Vector2 pos);

	/**
	* When the mouse pointer moves over the item
	* @param pos mouse pos
	*/
	virtual void onMouseMove(const Vector2 pos);


private:
	

public:

	/**
	* Item unique identifier
	*/
	string id;

	/**
	* Shows or hide the item. If it is hidden
	*/
	bool visible;

	/**
	* Screen position
	*/
	Vector2 position;

	/**
	* Item size
	*/
	Vector2 size;

private:

	
};




}