/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <vector>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Math/FastMath.h"
#include "TgcViewer/Math/Vector3.h"
#include "TgcViewer/Math/Color.h"
#include "TgcViewer/Renderer/TgcEffect.h"
#include "TgcViewer/Renderer/TgcVertexBuffer.h"
#include "TgcViewer/Renderer/TgcIndexBuffer.h"
#include "TgcViewer/Renderer/TgcInputLayout.h"
#include "TgcViewer/Renderer/TgcRendererGlobals.h"

//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;}


namespace TgcViewer
{



/**
* An Axis-aligned Bounding Box
*/
class TgcBoundingBox
{

public:

	/**
	* Creates an AABB from a group of AABBs
	*/
	static TgcBoundingBox* computeFromBoundingBoxes(const vector<TgcBoundingBox*> &boundingBoxes);

	/**
	* Creates an AABB from a set of points
	*/
	static TgcBoundingBox* TgcBoundingBox::computeFromPoints(const vector<Vector3> &points);


	TgcBoundingBox();
	TgcBoundingBox(const TgcBoundingBox&);
	~TgcBoundingBox();

	TgcBoundingBox(Vector3 pMin, Vector3 pMax);

	/**
	* Sets the extemes of the AABB
	*/
	void setExtremes(Vector3 pMin, Vector3 pMax);

	/**
	* Updates rendering data
	*/
	void updateValues();

	/**
	* Render the AABB
	*/
	void render();

	/**
	* Free resources
	*/
	void dispose();

	/**
	* Squared radius of the AABB
	*/
	float computeBoxRadiusSquare();

	/**
	* Radius of the AABB
	*/
	float computeBoxRadius();

	/**
	* Center of the AABB
	*/
	Vector3 computeBoxCenter();

	/**
	* Size of each AABB axis
	*/
	Vector3 computeSize();

	/**
	* Extents of each AABB axis
	*/
	Vector3 computeExtents();

	/**
	* Scales and translates the AABB
	*/
	void scaleTranslate(Vector3 position, Vector3 scale);

	/**
	* Moves the AABB
	*/
	void move(Vector3 movement);


private:

public:

	static const int VERTEX_COUNT = 8;
	static const int INDEX_COUNT = 24;


	Vector3 pMinOriginal;
    Vector3 pMaxOriginal;

	Vector3 pMin;
	Vector3 pMax;

	Color renderColor;

	VertexFormat::PositionColor vertices[VERTEX_COUNT];

	TgcVertexBuffer* vertexBuffer;
	TgcIndexBuffer* indexBuffer;

	TgcEffect* effect;

	bool dirtyValues;

private:


	
};


}