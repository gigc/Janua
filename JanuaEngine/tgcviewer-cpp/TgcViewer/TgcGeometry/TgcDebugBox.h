/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Math/FastMath.h"
#include "TgcViewer/Math/Vector3.h"
#include "TgcViewer/Math/Vector2.h"
#include "TgcViewer/Math/Color.h"
#include "TgcViewer/Math/Matrix4.h"
#include "TgcViewer/Renderer/TgcEffect.h"
#include "TgcViewer/Renderer/TgcVertexBuffer.h"
#include "TgcViewer/Renderer/TgcIndexBuffer.h"
#include "TgcViewer/Renderer/TgcInputLayout.h"
#include "TgcViewer/Renderer/TgcRendererGlobals.h"
#include "TgcViewer/TgcGeometry/TgcBoundingBox.h"


namespace TgcViewer
{



/**
* A 3D Box that only renders it edges with a custom thickness and color
*/
class TgcDebugBox
{

public:

	TgcDebugBox();
	TgcDebugBox(const TgcDebugBox&);
	~TgcDebugBox();

	void create();
	void updateValues();
	void render();
	void dispose();

	void setPositionSize(Vector3 position, Vector3 size);


private:
	
	void createLineX(VertexFormat::PositionColor* const vertices, int idx, Color c, Vector3 min, Vector3 max);
	void createLineY(VertexFormat::PositionColor* const vertices, int idx, Color c, Vector3 min, Vector3 max);
	void createLineZ(VertexFormat::PositionColor* const vertices, int idx, Color c, Vector3 min, Vector3 max);
	void createLineVertices(VertexFormat::PositionColor* const vertices, int idx, Vector3 min, Vector3 max, Color c);

	

public:

	static const int LINE_VERTICES_COUNT;
    static const int LINES_COUNT;
    static const int VERTICES_COUNT;
    static const int TRIANGLES_COUNT;

	Vector3 pMin;
	Vector3 pMax;
	Color color;
	float thickness;

	TgcVertexBuffer* vertexBuffer;
	TgcIndexBuffer* indexBuffer;
	TgcEffect* effect;

private:

	
	
};




}