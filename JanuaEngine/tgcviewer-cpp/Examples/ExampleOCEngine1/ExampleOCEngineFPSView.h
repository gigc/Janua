/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once

//General includes
#include <iostream>
#include <fstream>
#include <set>

//OCEngine includes
#include "JanuaEngine/Scene.h"
#include "JanuaEngine/SceneOptions.h"
#include "JanuaEngine/Model.h"
#include "JanuaEngine/SceneObjectType.h"
#include "JanuaEngine/PVSGenerator.h"
#include "JanuaEngine/PVSDatabase.h"
#include "JanuaEngine/Query.h"
#include "JanuaEngine/QueryResult.h"
#include "JanuaEngine/PVSDatabaseExporter.h"
#include "JanuaEngine/PVSDatabaseImporter.h"
#include "Core/Matrix4x4.h"
#include "Core/Vector3f.h"
#include "Core/Point3i.h"
#include "Core/PortalQuad.h"


//UTNOCRuntime includes
#include "JanuaRuntime/JanuaRuntime.h"


//Project Includes:
#include "Examples/TgcViewerIncludes.h"
#include "Examples/ExampleOCEngine1/Voxel.h"





namespace Examples
{


/**
* ExampleOCEngineFPSView
*/
class ExampleOCEngineFPSView : public TgcExample
{


public:


	struct RenderPortal
	{
		Vector3 min;
		Vector3 max;
		Vector3 cellMin;
		Vector3 cellMax;
	};

	struct VisibleCell
	{
		Vector3 min;
		Vector3 max;
	};

	struct RenderCell
	{
		Vector3 min;
		Vector3 max;
		vector<RenderPortal*> portals;
		vector<VisibleCell*> visibleCells;
	};


	//Virtual members
	string getCategory();
	string getName();
	string getDescription();
	void init();
	void render(float elapsedTime);
	void close();

	RenderCell* getCurrentCell(int& cellIndex);
	Vector3 toVector3(const Vector3f &v) const;
	void writePVSDumpFile();

private:

public:

	const static int VOXEL_SIZE = 20;

	//Escena
	TgcFpsCamera* camera;
	TgcScene* scene;

	//Occlusion engine
	shared_ptr<PVSDatabase> ocDatabase;
	vector<Model*> ocModels;

	//Render-debug
	VoxelGroup* voxelGroup;
	VoxelGroup* cellGroup;
	vector<RenderCell*> cells;
	TgcDebugBox* currentCellBox;
	vector<TgcBox*> currentPortalsBoxPool;
	vector<TgcBox*> currentNeighbourBoxPool;
	vector<TgcBox*> currentVisibleCellsBoxPool;
	Vector3 cameraFreezePos;
	TgcBox* cameraBox;
	bool freezeCameraFlag;

	//Runtime
	janua_handler handler;
	bool loadedfromfile;
	float queryTime;

	vector<int> visibleModelIds;

private:


	
};




}