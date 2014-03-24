/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "Examples/ExampleOCEngine1/ExampleOCEngine1.h"
using namespace Examples;


string ExampleOCEngine1::getCategory()
{
	return "Occlusion";
}

string ExampleOCEngine1::getName()
{
	return "Example1";
}

string ExampleOCEngine1::getDescription()
{
	return "Example1";
}


void ExampleOCEngine1::init()
{
	camera = new TgcFpsCamera();
	camera->movementSpeed *= 4;
	camera->jumpSpeed *= 4;

	//Load 3D scene
	//string filePath = GuiController::Instance->examplesMediaPath + "TgcModels\\Deposito\\Deposito-TgcScene.xml";
	string filePath = GuiController::Instance->examplesMediaPath + "TgcModels\\NormalMapRoom\\NormalMapRoom-TgcScene.xml";
	//string filePath = GuiController::Instance->examplesMediaPath + "TgcModels\\EscenarioPortal\\EscenarioPortal-TgcScene.xml";
	

	string mediaPath = filePath.substr(0, filePath.find_last_of('\\') + 1);
	TgcSceneParser parser;
	TgcSceneData* sceneData = parser.parseSceneFromFile(filePath);
	TgcSceneLoader loader;
	this->scene = loader.loadScene(sceneData, mediaPath);


	//Create occlusion data
	SceneOptions ocSceneOptions;
	ocSceneOptions.setVoxelSize((float)VOXEL_SIZE,(float)VOXEL_SIZE,(float)VOXEL_SIZE);
	//ocSceneOptions.setMaxCellSize(2,2,2); //Set scene max cell size
	Scene ocScene = Scene(ocSceneOptions, "test");

	//Model data for occlusion
	for(int i = 0; i < sceneData->meshCount; i++)
	{
		TgcMeshData* meshData = sceneData->meshesData[i];

		//vertex data
		int numVerts = meshData->verticesCoordinatesCount / 3;
		float* verts = new float[meshData->verticesCoordinatesCount];
		memcpy(verts, meshData->verticesCoordinates, meshData->verticesCoordinatesCount * sizeof(float));

		//index data
		int triangleCount = meshData->coordinatesIndicesCount / 3;
		int* indices = new int[meshData->coordinatesIndicesCount];
		memcpy(indices, meshData->coordinatesIndices, meshData->coordinatesIndicesCount * sizeof(int));
		
		//Add model to occlusion scene
		Model* ocModel = new Model(verts, numVerts, indices, triangleCount);
		ocModels.push_back(ocModel);
		ocScene.addModelInstance((*ocModel), i, Matrix4x4(), OCCLUDER);

		delete verts;
		delete indices;
	}
	delete sceneData;


	//Generate voxels from the scene
 	PVSGenerator gen = PVSGenerator(ocScene);
	this->ocDatabase = gen.generatePVSDatabase();


	

	
	//Create a box for each voxel
	this->voxelGroup = new VoxelGroup();
	this->voxelGroup->color = Color::Red;
	this->voxelGroup->bbColor = Color::Yellow;
	this->voxelGroup->drawAABB = false;
	this->voxelGroup->drawVoxels = true;
	vector<Vector3f> voxelsInWorldSpace = gen.getAllSolidVoxelPositionsInWorldSpace();
	Vector3 voxelExtents = Vector3((float)VOXEL_SIZE/2, (float)VOXEL_SIZE/2, (float)VOXEL_SIZE/2);
	for(unsigned int i = 0; i < voxelsInWorldSpace.size(); i++)
	{
		Vector3 voxelCenter = Vector3(voxelsInWorldSpace[i].x, voxelsInWorldSpace[i].y, voxelsInWorldSpace[i].z);
		Vector3 min = voxelCenter - voxelExtents; 
		Vector3 max = voxelCenter + voxelExtents; 
		
		//Add voxel to render group
		Voxel* v = new Voxel();
		v->setExtremes(min, max);
		this->voxelGroup->voxels.push_back(v);
	}
	this->voxelGroup->create();
	

	//Create a box for each cells
	this->cellGroup = new VoxelGroup();
	this->cellGroup->color = Color(0, 100/255.0f, 0, 1);
	this->cellGroup->bbColor = Color::Yellow;
	this->cellGroup->drawAABB = true;
	this->cellGroup->drawVoxels = false;
	this->cellGroup->alphaBlendEnabled = false;
	AABB sceneAABB = this->ocDatabase->getSceneAABB();
	float halfVoxel = (float)VOXEL_SIZE / 2;
	for(unsigned int i = 0; i < this->ocDatabase->m_cells.size(); i++)
	{
		Point3i minIndex = this->ocDatabase->m_cells[i]->minPoint;
		Point3i maxIndex = this->ocDatabase->m_cells[i]->maxPoint;

		Vector3 min = Vector3(
			minIndex.x * (float)VOXEL_SIZE + sceneAABB.minPoint.x,
			minIndex.y * (float)VOXEL_SIZE + sceneAABB.minPoint.y,
			minIndex.z * (float)VOXEL_SIZE + sceneAABB.minPoint.z
			);
		Vector3 max = Vector3(
			maxIndex.x * (float)VOXEL_SIZE + sceneAABB.minPoint.x + (float)VOXEL_SIZE,
			maxIndex.y * (float)VOXEL_SIZE + sceneAABB.minPoint.y + (float)VOXEL_SIZE,
			maxIndex.z * (float)VOXEL_SIZE + sceneAABB.minPoint.z + (float)VOXEL_SIZE
			);
		
		//Add voxel to render group
		Voxel* v = new Voxel();
		v->setExtremes(min, max);
		this->cellGroup->voxels.push_back(v);

		//Create renderCell
		RenderCell* renderCell = new RenderCell();
		renderCell->min = min;
		renderCell->max = max;
		cells.push_back(renderCell);

		//Create a box for each portal
		vector<shared_ptr<Portal>> portals = this->ocDatabase->m_cells[i]->getPortals();
		for(unsigned int j = 0; j < portals.size(); j++)
		{
			Point3i pMinIndex = portals[j]->minPoint;
			Point3i pMaxIndex = portals[j]->maxPoint;
			Point3i facingPlane = portals[j]->facingPlane;

			Vector3 pmin = Vector3(
				pMinIndex.x * (float)VOXEL_SIZE + sceneAABB.minPoint.x + halfVoxel,
				pMinIndex.y * (float)VOXEL_SIZE + sceneAABB.minPoint.y + halfVoxel,
				pMinIndex.z * (float)VOXEL_SIZE + sceneAABB.minPoint.z + halfVoxel
			);
			Vector3 pmax = Vector3(
				pMaxIndex.x * (float)VOXEL_SIZE + sceneAABB.minPoint.x + halfVoxel,
				pMaxIndex.y * (float)VOXEL_SIZE + sceneAABB.minPoint.y + halfVoxel,
				pMaxIndex.z * (float)VOXEL_SIZE + sceneAABB.minPoint.z + halfVoxel
			);


			Vector3 addVec;
			addVec.X = FastMath::abs((float)facingPlane.x) == 1 ? 0 : halfVoxel;
			addVec.Y = FastMath::abs((float)facingPlane.y) == 1 ? 0 : halfVoxel;
			addVec.Z = FastMath::abs((float)facingPlane.z) == 1 ? 0 : halfVoxel;

			pmin -= addVec;
			pmax += addVec;

			Vector3 vecAddDir;
			vecAddDir.X = facingPlane.x * halfVoxel;
			vecAddDir.Y = facingPlane.y * halfVoxel;
			vecAddDir.Z = facingPlane.z * halfVoxel;

			pmin += vecAddDir;
			pmax += vecAddDir;

			//Create renderPortal
			RenderPortal* renderPortal = new RenderPortal();
			renderPortal->min = pmin;
			renderPortal->max = pmax;
			renderCell->portals.push_back(renderPortal);
		}
	}
	this->cellGroup->create();



	//Current cell box
	currentCellBox = new TgcDebugBox();
	currentCellBox->color = Color::Red;
	currentCellBox->thickness = 2;
	currentCellBox->create();

	//Create pool of current portals box
	for(unsigned int i = 0; i < 100; i++)
	{
		TgcDebugBox* portalBox = new TgcDebugBox();
		portalBox->color = VoxelGroup::randomAdaptColor(Color::DarkGreen);
		portalBox->thickness = 1;
		portalBox->create();
		currentPortalsBoxPool.push_back(portalBox);
	}


	//Toogles
	renderScene = true;
	renderVoxels = false;
	renderCells = true;
	renderPortals = true;
}

void ExampleOCEngine1::render(float elapsedTime)
{
	camera->updateCamera();
	camera->updateViewMatrix();

	//toogle renderScene
	if(GuiController::Instance->input->keyPress(TgcInput::K_1))
	{
		renderScene = !renderScene;
	}

	//toogle renderVoxels
	if(GuiController::Instance->input->keyPress(TgcInput::K_2))
	{
		renderVoxels = !renderVoxels;
	}

	//toogle renderCells
	if(GuiController::Instance->input->keyPress(TgcInput::K_3))
	{
		renderCells = !renderCells;
	}

	//toogle renderPortals
	if(GuiController::Instance->input->keyPress(TgcInput::K_4))
	{
		renderPortals = !renderPortals;
	}





	if(renderScene)
	{
		scene->renderAll();
	}
	if(renderVoxels)
	{
		voxelGroup->render();
	}
	if(renderCells)
	{
		cellGroup->render();
	}


	//Render current cell and its portals
	RenderCell* currentCell = getCurrentCell();
	if(currentCell != NULL)
	{
		//Render current cell
		currentCellBox->pMin = currentCell->min;
		currentCellBox->pMax = currentCell->max;
		currentCellBox->updateValues();
		currentCellBox->render();

		//Render current portals
		if(renderPortals)
		{
			for(unsigned int i = 0; i < currentCell->portals.size(); i++)
			{
				RenderPortal* p = currentCell->portals[i];
				TgcDebugBox* pBox = currentPortalsBoxPool[i];

				//Achicar un poco para que se vea
				Vector3 smaller = Vector3(5, 5, 5);
				Vector3 diff = p->max - p->min;
				if(diff.X < 0.1f) smaller.X = 0;
				if(diff.Y < 0.1f) smaller.Y = 0;
				if(diff.Z < 0.1f) smaller.Z = 0;

				pBox->pMin = p->min + smaller;
				pBox->pMax = p->max - smaller;
				pBox->updateValues();
				pBox->render();
			}
		}
		
	}

	
}


ExampleOCEngine1::RenderCell* ExampleOCEngine1::getCurrentCell()
{
	Vector3 cameraPos = this->camera->position;
	for(unsigned int i = 0; i < cells.size(); i++)
	{
		RenderCell* v = cells[i];
		Vector3 size = v->max - v->min;
		Vector3 e = size * 0.5f;
		Vector3 center = v->min + e;

		Vector3 diff = center - cameraPos;
		if(FastMath::abs(diff.X) <= e.X && FastMath::abs(diff.Y) <= e.Y && FastMath::abs(diff.Z) <= e.Z)
		{
			return v;
		}
	}
	return NULL;
}


void ExampleOCEngine1::close()
{
	scene->disposeAll();
	delete scene;

	voxelGroup->dispose();
	delete voxelGroup;

	cellGroup->dispose();
	delete cellGroup;

	for(unsigned int i = 0; i < ocModels.size(); i++)
	{
		delete ocModels[i];
	}

	for(unsigned int i = 0; i < cells.size(); i++)
	{
		for(unsigned int j = 0; j < cells[i]->portals.size(); j++)
		{
			delete cells[i]->portals[j];
		}
		delete cells[i];
	}

	currentCellBox->dispose();
	delete currentCellBox;

	for(unsigned int i = 0; i < currentPortalsBoxPool.size(); i++)
	{
		currentPortalsBoxPool[i]->dispose();
		delete currentPortalsBoxPool[i];
	}
}

