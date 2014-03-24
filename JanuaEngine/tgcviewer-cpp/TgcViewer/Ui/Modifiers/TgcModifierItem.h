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

//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;}


namespace TgcViewer
{



/**
* An abstract modifier item
*/
class TgcModifierItem
{

public:

	TgcModifierItem();
	TgcModifierItem(const TgcModifierItem&);
	~TgcModifierItem();

	/**
	* Init the modifier
	*/
	void init(const string id);

	/**
	* Updates the modifier
	*/
	virtual void update() = 0;

	/**
	* Free resources
	*/
	virtual void dispose() = 0;


	/**
	* Modifier data accesors
	*/
	virtual float getFloat() const;
	virtual int getInt() const;
	virtual bool getBool() const;
	virtual string getString() const;
	

	/**
	* {Internal}
	* Sets the modifier position
	*/
	virtual void setPosition(const Vector2 pos) = 0;


private:
	
public:

	/**
	* Unique identifier for the modifier
	*/
	string id;

	/**
	* Size of the modifier
	*/
	Vector2 size;

private:

	
};




}