/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "Examples/ExampleOCEngine1/ExampleOCEngineFPSView.h"
using namespace Examples;
HighResolutionTimer timer;


string ExampleOCEngineFPSView::getCategory()
{
	return "Occlusion";
}

string ExampleOCEngineFPSView::getName()
{
	return "Example2";
}

string ExampleOCEngineFPSView::getDescription()
{
	return "Example2";
}


void ExampleOCEngineFPSView::init()
{

	camera = new TgcFpsCamera();
	camera->position = Vector3(0, 60, 20);
	camera->movementSpeed *= 4;
	camera->jumpSpeed *= 4;

	//Load 3D scene
	//string filePath = GuiController::Instance->examplesMediaPath + "TgcModels\\Deposito\\Deposito-TgcScene.xml";
	//string filePath = GuiController::Instance->examplesMediaPath + "TgcModels\\NormalMapRoom\\NormalMapRoom-TgcScene.xml";
	//string filePath = GuiController::Instance->examplesMediaPath + "TgcModels\\EscenarioPortal\\EscenarioPortal-TgcScene.xml";
	//string filePath = GuiController::Instance->examplesMediaPath + "TgcModels\\NormalMapRoomSimple\\NormalMapRoomSimple-TgcScene.xml";
	//string filePath = GuiController::Instance->examplesMediaPath + "TgcModels\\NormalMapRoomObstaculos\\NormalMapRoomObstaculos-TgcScene.xml";
	//string filePath = GuiController::Instance->examplesMediaPath + "TgcModels\\NormalMapRoom2\\NormalMapRoom2-TgcScene.xml";
	string filePath = GuiController::Instance->examplesMediaPath + "TgcModels\\QuakeRoom1\\QuakeMap-TgcScene.xml";

	string mediaPath = filePath.substr(0, filePath.find_last_of('\\') + 1);
	TgcSceneParser parser;
	TgcSceneData* sceneData = parser.parseSceneFromFile(filePath);
	TgcSceneLoader loader;
	this->scene = loader.loadScene(sceneData, mediaPath);

	


	//Generate voxels from the scene
	Vector3f voxelSize = Vector3f((float)VOXEL_SIZE, (float)VOXEL_SIZE, (float)VOXEL_SIZE);
	//Create occlusion data
	SceneOptions ocSceneOptions;
	ocSceneOptions.setSceneTileSize(20,20,20);
	ocSceneOptions.setMaxCellSize(100,100,100); //Set scene max cell size
	ocSceneOptions.setVoxelSize(voxelSize.x, voxelSize.y, voxelSize.z);
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
		SceneObjectType type = meshData->layerName == "Obstaculos" ? OCCLUDEE : OCCLUDER;
			
		Model* ocModel = new Model(verts, numVerts, indices, triangleCount);
		
		ocModels.push_back(ocModel);
		ocScene.addModelInstance((*ocModel), i, Matrix4x4(), type);


		
		delete[] verts;
		delete[] indices;
	}
	delete sceneData;

 	PVSGenerator gen = PVSGenerator(ocScene);
	

	//Poner esto para leer la PVS ya guardada.
	loadedfromfile = false;
	FILE *file = fopen("pvs.lrb", "rb");
	if( file != NULL )
	{
		fseek(file, 0L, SEEK_END);
		int bufferSize = ftell(file);
		fseek(file, 0L, SEEK_SET);
		char *readBuffer = new char[bufferSize];
		fread( readBuffer, 1, bufferSize, file);
		fclose( file );
		PVSDatabaseImporter dbImporter;
		this->ocDatabase = dbImporter.load(readBuffer);

		janua_handler_load_database(&handler, readBuffer);

		loadedfromfile =true;
	}
	else
	{
		this->ocDatabase = gen.generatePVSDatabase();
		PVSDatabaseExporter dbExporter(*(this->ocDatabase));
		int allocatedSize = dbExporter.getBufferSize();
			
		//TODO: create buffer internally.
		char *buffer = new char[allocatedSize];
		dbExporter.saveToBuffer(buffer);

		//Save the buffer to a file.
		FILE *file = fopen("pvs.lrb", "wb");
		fwrite( buffer, 1, allocatedSize, file);
		fclose(file);

		janua_handler_load_database(&handler, buffer);
//		delete [] buffer;
	}

	
	
	//Create a box for each voxel
	this->voxelGroup = new VoxelGroup();
	this->voxelGroup->color = Color::Red;
	this->voxelGroup->bbColor = Color::Yellow;
	this->voxelGroup->drawAABB = false;
	this->voxelGroup->drawVoxels = true;

	vector<Vector3f> voxelsInWorldSpace;

	//PORK:
	if( loadedfromfile )
		voxelsInWorldSpace.push_back(Vector3f(0,0,0)); //El archivo no carga voxeles, y pongo esto para que no se cague el vertex buffer.
	else
		voxelsInWorldSpace = gen.getAllSolidVoxelPositionsInWorldSpace(); //Los voxels recien generados.


	if( voxelsInWorldSpace.empty() )
		voxelsInWorldSpace.push_back(Vector3f(0,0,0)); 

	//Voxels para dibujar
	Vector3 voxelExtents = Vector3((float)VOXEL_SIZE/2, (float)VOXEL_SIZE/2, (float)VOXEL_SIZE/2);
	for(unsigned int i = 0; i < voxelsInWorldSpace.size(); i++)
	{
		Vector3 voxelCenter = toVector3(voxelsInWorldSpace[i]);
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

		//Store visible cells data
		vector<shared_ptr<Cell>> visibleCells = this->ocDatabase->m_cells[i]->getVisibleCells();
		for(unsigned int j = 0; j < visibleCells.size(); j++)
		{
			VisibleCell* visCell = new VisibleCell();
			Point3i visMinIndex = visibleCells[j]->minPoint;
			Point3i visMaxIndex = visibleCells[j]->maxPoint;

			visCell->min = Vector3(
				visMinIndex.x * (float)VOXEL_SIZE + sceneAABB.minPoint.x,
				visMinIndex.y * (float)VOXEL_SIZE + sceneAABB.minPoint.y,
				visMinIndex.z * (float)VOXEL_SIZE + sceneAABB.minPoint.z
			);
			visCell->max = Vector3(
				visMaxIndex.x * (float)VOXEL_SIZE + sceneAABB.minPoint.x + (float)VOXEL_SIZE,
				visMaxIndex.y * (float)VOXEL_SIZE + sceneAABB.minPoint.y + (float)VOXEL_SIZE,
				visMaxIndex.z * (float)VOXEL_SIZE + sceneAABB.minPoint.z + (float)VOXEL_SIZE
			);
			renderCell->visibleCells.push_back(visCell);
		}

		//Create a box for each portal
		vector<shared_ptr<Portal>> portals = this->ocDatabase->m_cells[i]->getPortals();
		for(unsigned int j = 0; j < portals.size(); j++)
		{
			//Get Quad 4 points
			PortalQuad quad = gen.getPortalRectangle(*(portals[j]), voxelSize);
			vector<Vector3> quadPoints;
			quadPoints.push_back(toVector3(quad.points[0]));
			quadPoints.push_back(toVector3(quad.points[1]));
			quadPoints.push_back(toVector3(quad.points[2]));
			quadPoints.push_back(toVector3(quad.points[3]));
			
			//AABB from quad?
			TgcBoundingBox* aabb = TgcBoundingBox::computeFromPoints(quadPoints);
			
			//Create renderPortal
			RenderPortal* renderPortal = new RenderPortal();
			renderPortal->min = aabb->pMin + toVector3(sceneAABB.minPoint);
			renderPortal->max = aabb->pMax + toVector3(sceneAABB.minPoint);
			renderCell->portals.push_back(renderPortal);

			//Data for neighbour
			shared_ptr<Cell> cell = portals[j]->toCell;
			Point3i minIndexN = cell->minPoint;
			Point3i maxIndexN = cell->maxPoint;
			renderPortal->cellMin = Vector3(
				minIndexN.x * (float)VOXEL_SIZE + sceneAABB.minPoint.x,
				minIndexN.y * (float)VOXEL_SIZE + sceneAABB.minPoint.y,
				minIndexN.z * (float)VOXEL_SIZE + sceneAABB.minPoint.z
				);
			renderPortal->cellMax = Vector3(
				maxIndexN.x * (float)VOXEL_SIZE + sceneAABB.minPoint.x + (float)VOXEL_SIZE,
				maxIndexN.y * (float)VOXEL_SIZE + sceneAABB.minPoint.y + (float)VOXEL_SIZE,
				maxIndexN.z * (float)VOXEL_SIZE + sceneAABB.minPoint.z + (float)VOXEL_SIZE
				);

			delete aabb;
		}
	}
	this->cellGroup->create();



	//Current cell box
	currentCellBox = new TgcDebugBox();
	currentCellBox->color = Color::Red;
	currentCellBox->thickness = 2;
	currentCellBox->create();

	//Create pool of current portals box
	for(unsigned int i = 0; i < 1000; i++)
	{
		TgcBox* portalBox = new TgcBox();
		portalBox->color = VoxelGroup::randomAdaptColor(Color::DarkGreen);
		//portalBox->color.A = 0.3f;
		currentPortalsBoxPool.push_back(portalBox);
	}

	//Create pool of current cell neighbours box
	for(unsigned int i = 0; i < 1000; i++)
	{
		TgcBox* box = new TgcBox();
		box->color = VoxelGroup::randomAdaptColor(Color::Magenta);
		//box->color.A = 0.3f;
		currentNeighbourBoxPool.push_back(box);
	}

	//Create pool of current visible cells box
	for(unsigned int i = 0; i < 1000; i++)
	{
		TgcBox* box = new TgcBox();
		box->color = VoxelGroup::randomAdaptColor(Color::Violet);
		//box->color.A = 0.3f;
		currentVisibleCellsBoxPool.push_back(box);
	}


	
	//Camera box
	cameraBox = TgcBox::fromSize(Vector3(50, 50, 50), Color::Red);


	//Modifiers
	GuiController::Instance->modifiers->addBool("renderVoxels", "renderVoxels", false);
	GuiController::Instance->modifiers->addBool("renderCells", "renderCells", true);
	GuiController::Instance->modifiers->addBool("wireframe", "wireframe", false);
	GuiController::Instance->modifiers->addBool("doOcclusion", "doOcclusion", true);
	GuiController::Instance->modifiers->addBool("renderPortals", "renderPortals", false);
	GuiController::Instance->modifiers->addBool("freezeCamera", "freezeCamera", false);
	GuiController::Instance->modifiers->addBool("renderNeighbours", "renderNeighbours", false);
	GuiController::Instance->modifiers->addBool("renderVisibleCells", "renderVisibleCells", false);
	GuiController::Instance->modifiers->addBool("renderOccluders", "renderOccluders", true);
	GuiController::Instance->modifiers->addBool("renderOccludees", "renderOccludees", true);
	freezeCameraFlag = false;

	//Debug text
	GuiController::Instance->userVars->color = Color::White;

}

void ExampleOCEngineFPSView::render(float elapsedTime)
{
	TgcRenderer* renderer = GuiController::Instance->renderer;


	//toogle freezeCamera
	bool freezeCamera = GuiController::Instance->modifiers->get("freezeCamera")->getBool();
	if(freezeCamera != freezeCameraFlag)
	{
		freezeCameraFlag = freezeCamera;
		if(freezeCameraFlag)
		{
			cameraFreezePos = camera->position;
			
		} else
		{
			camera->position = cameraFreezePos;
		}
	}


	//Camera
	camera->updateCamera();
	camera->updateViewMatrix();
	if(freezeCameraFlag)
	{
		//Remote move of camera box
		const float speed = 1000;
		if(GuiController::Instance->input->keyDown(TgcInput::K_UP))
		{
			cameraFreezePos.Z += speed * elapsedTime;
		}
		else if(GuiController::Instance->input->keyDown(TgcInput::K_DOWN))
		{
			cameraFreezePos.Z -= speed * elapsedTime;
		}
		if(GuiController::Instance->input->keyDown(TgcInput::K_RIGHT))
		{
			cameraFreezePos.X += speed * elapsedTime;
		}
		else if(GuiController::Instance->input->keyDown(TgcInput::K_LEFT))
		{
			cameraFreezePos.X -= speed * elapsedTime;
		}
		cameraBox->position = cameraFreezePos;
		cameraBox->updateValues();
	}
	else
	{
		cameraFreezePos = camera->position;
	}



	//Save file
	if(GuiController::Instance->input->keyPress(TgcInput::K_P))
	{
		PVSDatabaseExporter dbExporter(*(this->ocDatabase));
		int allocatedSize = dbExporter.getBufferSize();
		char *buffer = new char[allocatedSize];
		dbExporter.saveToBuffer(buffer);

		//Save the buffer to a file.
		FILE *file = fopen("pvs.lrb", "wb");
		fwrite( buffer, 1, allocatedSize, file);
		fclose(file);
	}


	//Render voxels
	if(GuiController::Instance->modifiers->get("renderVoxels")->getBool())
	{
		voxelGroup->render();
	}

	//Render cells
	if(GuiController::Instance->modifiers->get("renderCells")->getBool())
	{
		cellGroup->render();
	}

	//Render current cell
	int currentCellId = -1;
	int currentCellPortalsCount = -1;
	RenderCell* currentCell = getCurrentCell(currentCellId);
	if(currentCell != NULL)
	{
		//Render current cell
		currentCellBox->pMin = currentCell->min;
		currentCellBox->pMax = currentCell->max;
		currentCellBox->updateValues();
		currentCellBox->render();

		currentCellPortalsCount = (int)currentCell->portals.size();

		//Render current portals
		if(GuiController::Instance->modifiers->get("renderPortals")->getBool())
		{
			renderer->enableAlphaBlending(true);
			for(unsigned int i = 0; i < currentCell->portals.size(); i++)
			{
				RenderPortal* p = currentCell->portals[i];
				TgcBox* pBox = currentPortalsBoxPool[i];
				pBox->setExtremes(p->min, p->max);
				pBox->updateValues();
				pBox->render();
			}
			renderer->enableAlphaBlending(false);
		}

		//Render current cell neighbours
		if(GuiController::Instance->modifiers->get("renderNeighbours")->getBool())
		{
			renderer->enableAlphaBlending(true);
			for(unsigned int i = 0; i < currentCell->portals.size(); i++)
			{
				RenderPortal* p = currentCell->portals[i];
				TgcBox* pBox = currentNeighbourBoxPool[i];
				pBox->setExtremes(p->cellMin, p->cellMax);
				pBox->updateValues();
				pBox->render();
			}
			renderer->enableAlphaBlending(false);
		}

		//Render current cell visible cells
		if(GuiController::Instance->modifiers->get("renderVisibleCells")->getBool())
		{
			renderer->enableAlphaBlending(true);
			for(unsigned int i = 0; i < currentCell->visibleCells.size(); i++)
			{
				VisibleCell* v = currentCell->visibleCells[i];
				TgcBox* pBox = currentVisibleCellsBoxPool[i];
				pBox->setExtremes(v->min, v->max);
				pBox->updateValues();
				pBox->render();
			}
			renderer->enableAlphaBlending(false);
		}
		
	}

	
	//Wireframe
	bool wireframe = GuiController::Instance->modifiers->get("wireframe")->getBool();
	if(wireframe)
	{
		GuiController::Instance->renderer->setFillMode(FillMode::WireFrame);
	}

	//Render scene with occlusion
	unsigned int visibleModels = this->scene->meshes.size();
	unsigned int occludedObjects = 0;
	bool renderOccludees = GuiController::Instance->modifiers->get("renderOccludees")->getBool();
	bool renderOccluders = GuiController::Instance->modifiers->get("renderOccluders")->getBool();
	janua_get_cells_data_result cells_result;
	cells_result.current_cell_index = -1;
	if(GuiController::Instance->modifiers->get("doOcclusion")->getBool())
	{
		Query q = Query(*this->ocDatabase);
		Vector3 pos = cameraFreezePos;
		//if(currentCell != NULL)
		{

			timer.reset();

			janua_query_result result;
			int queryreturncode = janua_query_visibility_from_position( &handler, pos.X, pos.Y, pos.Z, &result );
			if( loadedfromfile == true && (queryreturncode == JANUA_RETURN_CODE_OK ||  queryreturncode == JANUA_RETURN_CODE_OUT_OF_SCENE_BOUNDS) )
			{
				
				timer.set();
				queryTime = timer.frameTime * 1000;

				//If runtime query worked, use it.
				//visibleModelIds.reserve(result.model_ids_count);
				visibleModelIds.clear();
				for(unsigned int c = 0; c < result.model_ids_count ; ++c)
				{
					visibleModelIds.push_back( result.model_ids[c] );
				} 

				//Get cells debug data
				janua_get_cells_data_from_position(&handler, pos.X, pos.Y, pos.Z, &cells_result);
				

			}
			else
			{
				QueryResult qRes = q.getPotentiallyVisibleObjectsFromRegion(Vector3f(pos.X, pos.Y, pos.Z));
				//Use the engine one.
				visibleModelIds = qRes.getVisibleModelIds();
			}
			
			visibleModels = visibleModelIds.size();
			occludedObjects = this->scene->meshes.size() - visibleModelIds.size();
			for(unsigned int i = 0; i < visibleModelIds.size(); i++)
			{
				TgcMesh* mesh = this->scene->meshes[visibleModelIds[i]];
				if(mesh->layer == "Obstaculos" && renderOccludees)
				{
					mesh->render();
				}
				else if(mesh->layer != "Obstaculos" && renderOccluders)
				{
					mesh->render();
				}
			}
		}
	}
	else
	{
		//Render all
		for(unsigned int i = 0; i < scene->meshes.size(); i++)
		{
			TgcMesh* mesh = this->scene->meshes[i];
			if(mesh->layer == "Obstaculos" && renderOccludees)
			{
				mesh->render();
			}
			else if(mesh->layer != "Obstaculos" && renderOccluders)
			{
				mesh->render();
			}
		}
	}
	

	if(wireframe)
	{
		GuiController::Instance->renderer->setFillMode(FillMode::Solid);
	}


	//Render cameraBox
	if(freezeCameraFlag)
	{
		renderer->enableDepthTest(false);
		cameraBox->render();
		renderer->enableDepthTest(true);
	}


	//Debug text
	GuiController::Instance->userVars->setVar("Mostrar/Ocultar", "V");
	GuiController::Instance->userVars->setVar("Generate debug file", "P");
	GuiController::Instance->userVars->setVar("Visible models", TgcParserUtils::toString(visibleModels) + "/" + TgcParserUtils::toString(this->scene->meshes.size()));
	GuiController::Instance->userVars->setVar("Occluded models", occludedObjects);
	GuiController::Instance->userVars->setVar("Current cell index", currentCellId);
	GuiController::Instance->userVars->setVar("Current cell portals", currentCellPortalsCount);
	GuiController::Instance->userVars->setVar("Total cells", TgcParserUtils::toString(cells.size()));
	GuiController::Instance->userVars->setVar("Query time ms", TgcParserUtils::toString(queryTime));
	if(cells_result.current_cell_index != -1)
	{
		GuiController::Instance->userVars->setVar("Janua current cell index", TgcParserUtils::toString(cells_result.current_cell_index));
		GuiController::Instance->userVars->setVar("Janua neigbour count", TgcParserUtils::toString(cells_result.neighbour_cells_count));
		string neigbourIds = "";
		unsigned int maxCount = 100;
		for(unsigned int i = 0; i < cells_result.neighbour_cells_count && i < maxCount; i++)
		{
			neigbourIds += TgcParserUtils::toString(cells_result.neighbour_cells_index[i]) + ", ";
		}
		if(cells_result.neighbour_cells_count >= maxCount)
		{
			neigbourIds += "...";
		}
		GuiController::Instance->userVars->setVar("Janua neigbour ids", neigbourIds);
	}
	else
	{
		GuiController::Instance->userVars->setVar("Janua current cell index", "off");
		GuiController::Instance->userVars->setVar("Janua neigbour count", "off");
		GuiController::Instance->userVars->setVar("Janua neigbour ids", "off");
	}
	
	
	//Debug file
	if(GuiController::Instance->input->keyPress(TgcInput::K_P))
	{
		writePVSDumpFile();
	}

}


ExampleOCEngineFPSView::RenderCell* ExampleOCEngineFPSView::getCurrentCell(int& cellIndex)
{
	Vector3 cameraPos = cameraFreezePos;
	for(unsigned int i = 0; i < cells.size(); i++)
	{
		RenderCell* v = cells[i];
		Vector3 size = v->max - v->min;
		Vector3 e = size * 0.5f;
		Vector3 center = v->min + e;

		Vector3 diff = center - cameraPos;
		if(FastMath::abs(diff.X) <= e.X && FastMath::abs(diff.Y) <= e.Y && FastMath::abs(diff.Z) <= e.Z)
		{
			cellIndex = i;
			return v;
		}
	}
	return NULL;
}

Vector3 ExampleOCEngineFPSView::toVector3(const Vector3f &v) const
{
	return Vector3(v.x, v.y, v.z);
}

void ExampleOCEngineFPSView::writePVSDumpFile()
{
	janua_dump_debug_result result;
	janua_dump_debug(&handler, &result);

	ofstream myfile;
	myfile.open ("pvs_dump.txt");
	myfile << "PVS Dump:\n";
	myfile << "Cells count: " + TgcParserUtils::toString(result.cells_count) + "\n";

	set<int> modelsId;
	for(unsigned int i = 0; i < result.cells_count; i++)
	{
		janua_dump_debug_cell cell = result.cells[i];
		for(unsigned int j = 0; j < cell.models_count; j++)
		{
			modelsId.insert(cell.models[j]);
		}
	}
	myfile << "Models count: " + TgcParserUtils::toString(modelsId.size()) + "\n";
	
	for(unsigned int i = 0; i < result.cells_count; i++)
	{
		myfile << "-----------------------------------------------------------------\n";
		janua_dump_debug_cell cell = result.cells[i];
		myfile << "Cell id: " + TgcParserUtils::toString(cell.cell_id) + "\n";
		myfile << "Models count: " + TgcParserUtils::toString(cell.models_count) + "\n";
		myfile << "Models id: [";
		for(unsigned int j = 0; j < cell.models_count; j++)
		{
			myfile << TgcParserUtils::toString(cell.models[j]) + ", ";
		}
		myfile << "]\n";
	}
	
	myfile.close();
}

void ExampleOCEngineFPSView::close()
{
	delete camera;

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
		for(unsigned int j = 0; j < cells[i]->visibleCells.size(); j++)
		{
			delete cells[i]->visibleCells[j];
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
	currentPortalsBoxPool.clear();

	for(unsigned int i = 0; i < currentNeighbourBoxPool.size(); i++)
	{
		currentNeighbourBoxPool[i]->dispose();
		delete currentNeighbourBoxPool[i];
	}
	currentNeighbourBoxPool.clear();

	for(unsigned int i = 0; i < currentVisibleCellsBoxPool.size(); i++)
	{
		currentVisibleCellsBoxPool[i]->dispose();
		delete currentVisibleCellsBoxPool[i];
	}
	currentVisibleCellsBoxPool.clear();

	delete cameraBox;
}



