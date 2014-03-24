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
* BorderBox
*/
class BorderBox
{

public:

	BorderBox();
	BorderBox(const BorderBox&);
	~BorderBox();

	void create();
	void updateValues();
	void render();
	void dispose();


	Vector3 pMin;
	Vector3 pMax;
	Color color;
	float thickness;

private:
	
	void createLineX(VertexType::VertexColor* const vertices, int idx, Color c, Vector3 min, Vector3 max);
	void createLineY(VertexType::VertexColor* const vertices, int idx, Color c, Vector3 min, Vector3 max);
	void createLineZ(VertexType::VertexColor* const vertices, int idx, Color c, Vector3 min, Vector3 max);
	void createLineVertices(VertexType::VertexColor* const vertices, int idx, Vector3 min, Vector3 max, Color c);

	void setPositionSize(Vector3 position, Vector3 size);

public:

	static const int LINE_VERTICES_COUNT;
    static const int LINES_COUNT;
    static const int VERTICES_COUNT;
    static const int TRIANGLES_COUNT;

private:

	TgcVertexBuffer* vertexBuffer;
	TgcIndexBuffer* indexBuffer;
	TgcEffect* effect;
	
};




}