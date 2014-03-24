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
* Voxel
*/
class Voxel
{

public:

	Voxel();
	Voxel(Vector3 center, Vector3 size);

	void setExtremes(Vector3 min, Vector3 max);

private:
	

public:

	Vector3 center;
	Vector3 size;

private:

	
};



/**
* VoxelGroup
*/
class VoxelGroup
{

public:

	VoxelGroup();
	void create();
	void render();
	void dispose();

	static Color randomAdaptColor(const Color &c);

private:
	
public:

	static const int VERTEX_COUNT = 8;
	static const int INDEX_COUNT = 36;

	//Voxel list
	vector<Voxel*> voxels;

	//Things to render
	bool drawVoxels;
	bool alphaBlendEnabled;
	Color color;
	TgcVertexBuffer* vertexBuffer;
	TgcIndexBuffer* indexBuffer;
	TgcEffect* effect;
	
	int totalVertices;
	int totalIndices;
	int totalBBIndices;

	//Things to render AABB
	static const int BB_INDEX_COUNT = 24;
	bool drawAABB;
	Color bbColor;
	TgcVertexBuffer* bbVertexBuffer;
	TgcIndexBuffer* bbIndexBuffer;


private:

	
};




}