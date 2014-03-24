/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once

//OCEngine includes
#include "JanuaEngine/Scene.h"
#include "JanuaEngine/SceneOptions.h"
#include "JanuaEngine/Model.h"
#include "JanuaEngine/SceneObjectType.h"
#include "JanuaEngine/PVSGenerator.h"
#include "JanuaEngine/PVSDatabase.h"
#include "Core/Matrix4x4.h"
#include "Core/Vector3f.h"
#include "Core/Point3i.h"


//Project Includes:
#include "Examples/TgcViewerIncludes.h"
#include "Examples/ExampleOCEngine1/Voxel.h"





namespace Examples
{


/**
* ExampleOCEngine1
*/
class ExampleOCEngine1 : public TgcExample
{


public:

	struct RenderPortal
	{
		Vector3 min;
		Vector3 max;
	};

	struct RenderCell
	{
		Vector3 min;
		Vector3 max;
		vector<RenderPortal*> portals;
	};


	//Virtual members
	string getCategory();
	string getName();
	string getDescription();
	void init();
	void render(float elapsedTime);
	void close();

	ExampleOCEngine1::RenderCell* getCurrentCell();

private:

public:

	const static int VOXEL_SIZE = 10;

	TgcFpsCamera* camera;
	TgcScene* scene;
	shared_ptr<PVSDatabase> ocDatabase;
	VoxelGroup* voxelGroup;
	VoxelGroup* cellGroup;

	bool renderScene;
	bool renderVoxels;
	bool renderCells;
	bool renderPortals;

	TgcDebugBox* currentCellBox;
	vector<TgcDebugBox*> currentPortalsBoxPool;

	vector<Model*> ocModels;

	vector<RenderCell*> cells;

private:


	
};




}