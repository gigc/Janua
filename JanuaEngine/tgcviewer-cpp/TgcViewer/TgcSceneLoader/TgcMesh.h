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
#include <unordered_map>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/TgcSceneLoader/TgcSceneData.h"
#include "TgcViewer/TgcSceneLoader/TgcTexture.h"
#include "TgcViewer/TgcGeometry/TgcBoundingBox.h"
#include "TgcViewer/Renderer/TgcRenderer.h"
#include "TgcViewer/Renderer/TgcRendererGlobals.h"
#include "TgcViewer/Renderer/TgcVertexBuffer.h"
#include "TgcViewer/Renderer/TgcIndexBuffer.h"
#include "TgcViewer/Renderer/TgcEffect.h"
#include "TgcViewer/Math/Vector3.h"
#include "TgcViewer/Math/Matrix4.h"


namespace TgcViewer
{



/**
* A static mesh
* It can be moved, scaled and rotated but it has not animations
* The mesh may have vertex-colors, textures and lightmaps.
*/
class TgcMesh
{

public:


	TgcMesh();
	TgcMesh(const TgcMesh&);
	~TgcMesh();

	/**
	* Init a new mesh
	* @param name mesh name
	* @param vertexBuffer the vertex buffer of the mesh
	* @param indexBuffer the index buffer of the mesh
	* @param subGroupsVertexCount how many vertices are for each sub-group
	* @param renderType the type of the mesh
	*/
	void initData(string name, TgcVertexBuffer* vertexBuffer, TgcIndexBuffer* indexBuffer, vector<int> subGroupsVertexCount, MeshValues::RenderType renderType);

	/**
	* Draw the mesh with the current effect, if it is enabled
	*/
	void render();

	/**
	* Free the resources of the mesh
	*/
	void dispose();

	/**
	* Creates a BoundingBox for the mesh based on the meshData
	*/
	void createBoundingBox(const TgcMeshData* meshData);

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




	/**
	* Updates mesh transform matrix
	*/
	void updateMeshTransform();

	/**
	* Updates the mesh AABB
	*/
	void updateBoundingBox();


private:
	
protected:

public:

	/**
	* Name of the mesh
	*/
	string name;

	/**
	* Layer of the mesh
	*/
	string layer;

	/**
	* User properties of the mesh
	*/
	unordered_map<string, string> userProperties;

	/**
	* Vertex buffer
	*/
	TgcVertexBuffer* vertexBuffer;

	/**
	* Index buffer
	*/
	TgcIndexBuffer* indexBuffer;

	/**
	* How many vertices are for each sub-group
	*/
	vector<int> subGroupsVertexCount;

	/**
	* Offset of vertices for each sub-group
	*/
	vector<int>subGroupsVertexOffset;

	/**
	* Type of mesh
	*/
	MeshValues::RenderType renderType;

	/**
	* Shader effect of the mesh
	*/
	TgcEffect* effect;

	/**
	* DiffuseMap array of the mesh
	*/
	vector<TgcTexture*> diffuseMaps;

	/**
	* Lightmap of the mesh
	*/
	TgcTexture* lightMap;

	/**
	* Mesh avaliable to be rendered
	*/
	bool enabled;

	/**
	* Matrix used to appliy the final world transform of the mesh.
	* If autoTransformEnable is true then the matrix is automatically computed in each frame
	* from the values of position, rotation, scale.
	* If autoTransformEnable is false the mesh uses the value of transform directly.
	*/
	Matrix4 transform;

	/**
	* If true then transform is automatically computed in each frame from the values of position, rotation, scale.
	* Otherwise the mesh uses the value of transform directly.
	*/
	bool autoTransformEnable;

	/**
	* Absolute position of the mesh
	*/
	Vector3 position;

	/**
	* Absolute rotation of the mesh
	*/
	Vector3 rotation;

	/**
	* Absolute scale of the mesh
	*/
	Vector3 scale;

	/**
	* BoundingBox of the msh
	*/
	TgcBoundingBox* boundingBox;

	/**
	* If true then the mesh automatically updates the BoundingBox when its position or scale is changed.
	*/
	bool autoUpdateBoundingBox;

	/**
	* Enables to render with alpha blend activated.
	* It is false by default
	*/
	bool alphaBlendEnable;

private:

	
};




}