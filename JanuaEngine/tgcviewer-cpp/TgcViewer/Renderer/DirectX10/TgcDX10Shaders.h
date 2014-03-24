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
#include "TgcViewer/Shaders/TgcShaders.h"
#include "TgcViewer/GuiController.h"


namespace TgcViewer
{



/**
* DirectX 10 common engine shader effects
*/
class TgcDX10Shaders : public TgcShaders
{

public:


	//Virtual members
	void loadCommonShaders();
	void dispose();
	void adaptMatrix(Matrix4 &mat);


private:
	
public:


private:

	
};




}