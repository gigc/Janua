/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <d3d10_1.h>

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Renderer/TgcInputLayout.h"
#include "TgcViewer/Renderer/DirectX10/TgcDX10Renderer.h"


namespace TgcViewer
{



/**
* DirectX 10 Input layout
*/
class TgcDX10InputLayout : public TgcInputLayout
{

public:

	//Virtual members
	void internalCreate();
	void dispose();

private:

	LPCSTR getSemantic(InputElement::Semantic semantic);
	DXGI_FORMAT getFormat(InputElement::Type type);


public:

	/**
	* Input layout
	*/
	ID3D10InputLayout* layout;

	/**
	* Aux layout desc array used to create ID3D11InputLayout
	*/
	D3D10_INPUT_ELEMENT_DESC* layoutDesc;

private:

	
};




}