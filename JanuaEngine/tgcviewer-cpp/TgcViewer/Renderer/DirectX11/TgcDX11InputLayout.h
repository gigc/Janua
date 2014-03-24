/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <d3d11.h>

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Renderer/TgcInputLayout.h"
#include "TgcViewer/Renderer/DirectX11/TgcDX11Renderer.h"


namespace TgcViewer
{



/**
* DirectX 11 Input layout
*/
class TgcDX11InputLayout : public TgcInputLayout
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
	ID3D11InputLayout* layout;

	/**
	* Aux layout desc array used to create ID3D11InputLayout
	*/
	D3D11_INPUT_ELEMENT_DESC* layoutDesc;

private:

	
};




}