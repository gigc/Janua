/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//Project Includes:
#include "Examples/TgcViewerIncludes.h"
#include "Examples/ExampleEditor/EditorBox.h"


namespace Examples
{



/**
* Grid
*/
class Grid
{

public:

	Grid();
	Grid(const Grid&);
	~Grid();

	void create();
	void render();
	void dispose();


private:
	
public:

	static const int VERTEX_COUNT;
	static const int LINES_COUNT;
	static const float GRID_RADIUS;
    static const float LINE_SEPARATION;

	AABB aabb;

private:

	TgcVertexBuffer* vertexBuffer;
	TgcIndexBuffer* indexBuffer;
	TgcEffect* effect;
	
};




}