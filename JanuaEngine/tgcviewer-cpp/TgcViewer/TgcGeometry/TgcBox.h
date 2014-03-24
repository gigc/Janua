/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <string>

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
#include "TgcViewer/TgcSceneLoader/TgcTexture.h"


namespace TgcViewer
{



/**
* An editable 3D box
*/
class TgcBox
{

public:

	/*
	* Helpers to create a new TgcBox
	*/
	static TgcBox* fromSize(Vector3 center, Vector3 size);
	static TgcBox* fromSize(Vector3 center, Vector3 size, Color color);
	static TgcBox* fromSize(Vector3 center, Vector3 size, TgcTexture* texture);
	static TgcBox* fromSize(Vector3 size);
	static TgcBox* fromSize(Vector3 size, Color color);
	static TgcBox* fromSize(Vector3 size, TgcTexture* texture);
	static TgcBox* fromExtremes(Vector3 pMin, Vector3 pMax);
	static TgcBox* fromExtremes(Vector3 pMin, Vector3 pMax, Color color);
	static TgcBox* fromExtremes(Vector3 pMin, Vector3 pMax, TgcTexture* texture);

	TgcBox();
	TgcBox(const TgcBox&);
	~TgcBox();

	void updateValues();
	void render();
	void dispose();
	void updateBoundingBox();
	void setTexture(TgcTexture* texture);
	void setPositionSize(Vector3 position, Vector3 size);
	void setExtremes(Vector3 min, Vector3 max);


	/**
	* Set absolute position and calls updateBoundingBox()
	*/
	void setPosition(float x, float y, float z);

	/**
	* Set absolute position and calls updateBoundingBox()
	*/
	void setPosition(Vector3 pos);

	/**
	* Moves the position and calls updateBoundingBox()
	*/
	void move(float x, float y, float z);

	/**
	* Moves the position and calls updateBoundingBox()
	*/
	void move(Vector3 movement);

	/**
	* Moves the mesh based on the current Y rotation.
	* It also calls updateBoundingBox()
	*/
	void moveOrientedY(float movement);

	/**
	* Set absolute rotation (in radians) and calls updateBoundingBox()
	*/
	void setRotation(float x, float y, float z);

	/**
	* Set absolute rotation (in radians) and calls updateBoundingBox()
	*/
	void setRotation(Vector3 rot);

	/**
	* Relative rotation in X (in radians) and calls updateBoundingBox()
	*/
	void rotateX(float angle);

	/**
	* Relative rotation in Y (in radians) and calls updateBoundingBox()
	*/
	void rotateY(float angle);

	/**
	* Relative rotation in Z(in radians) and calls updateBoundingBox()
	*/
	void rotateZ(float angle);

	/**
	* Relative rotation (in radians) and calls updateBoundingBox()
	*/
	void rotate(Vector3 rot);


private:
	


public:

	static const int VERTEX_COUNT = 36;

	Vector3 size;
	Color color;
	TgcTexture* texture;
	TgcEffect* effect;
	TgcVertexBuffer* vertexBuffer;
	TgcIndexBuffer* indexBuffer;

	Matrix4 transform;
	bool autoTransformEnable;
	Vector3 position;
	Vector3 rotation;
	bool enabled;
	TgcBoundingBox* boundingBox;
	bool alphaBlendEnable;
	bool autoUpdateBoundingBox;

	Vector2 uvOffset;
	Vector2 uvTiling;

private:

	
};




}