/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//Project Includes:
#include "Examples/TgcViewerIncludes.h"


namespace Examples
{



/**
* TgcVoxel
*/
class TgcVoxel
{

public:

	TgcVoxel();
	TgcVoxel(const TgcVoxel&);
	~TgcVoxel();

	void create();

	void render();
	void dispose();

private:
	

public:

	Vector3 size;
	Vector3 center;
	Color color;


	TgcVertexBuffer* vertexBuffer;
	TgcIndexBuffer* indexBuffer;
	TgcEffect* effect;
	Matrix4 transform;


private:

	
};




}