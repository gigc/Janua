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
#include "TgcViewer/Renderer/TgcRendererGlobals.h"


namespace TgcViewer
{

/**
* Vertex format description, with its components, sizes and offsets.
* Each renderer implements the concret class
*/
class TgcInputLayout
{

public:

	TgcInputLayout();
	TgcInputLayout(const TgcInputLayout&);
	~TgcInputLayout();

	/**
	* Create the input layout.
	* The elements array must be previously filled.
	*/
	void create();

	/**
	* Free resources
	*/
	virtual void dispose() = 0;


	/**
	* {Renderer-dependent}
	* Create the internal structures of the input layout required by the renderer.
	*/
	virtual void internalCreate() = 0;


private:

public:

	/**
	* Array of elements that must be filled
	*/
	vector<InputElement::Element> elements;

	/**
	* Total size of the vertex layout
	*/
	unsigned int size;

	/**
	* Offset for each element of the layout
	*/
	vector<unsigned int> offsets;

private:

	
};




}