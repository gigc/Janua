/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "TgcViewer/TgcSceneLoader/TgcSceneLoader.h"
using namespace TgcViewer;


TgcSceneLoader::TgcSceneLoader()
{

}


TgcSceneLoader::TgcSceneLoader(const TgcSceneLoader& other)
{
}


TgcSceneLoader::~TgcSceneLoader()
{
}

TgcScene* TgcSceneLoader::loadSceneFromFile(string filePath)
{
	string mediaPath = filePath.substr(0, filePath.find_last_of('\\') + 1);
	return this->loadSceneFromFile(filePath, mediaPath);
}

TgcScene* TgcSceneLoader::loadSceneFromFile(string filePath, string mediaPath)
{
	TgcSceneParser parser;
	TgcSceneData* sceneData = parser.parseSceneFromFile(filePath);
	TgcScene* scene = this->loadScene(sceneData, mediaPath);
	delete sceneData;

	return scene;
}


TgcScene* TgcSceneLoader::loadScene(const TgcSceneData* sceneData, string mediaPath)
{
	texturesMap.clear();

	TgcScene* tgcScene = new TgcScene(sceneData->name, mediaPath);

	//Load textures
	vector<TgcSceneLoaderMaterialAux*> materialsArray;
    for (int i = 0; i < sceneData->materialCount; i++)
    {
        TgcMaterialData* materialData = sceneData->materialsData[i];
        string texturesPath = mediaPath + sceneData->texturesDir + "\\";

        //Create StandardMaterial
        if (materialData->type.compare(TgcMaterialData::StandardMaterial) == 0)
        {
			materialsArray.push_back(createTextureAndMaterial(materialData, texturesPath));
        }

        //Crear MultiMaterial
        else if (materialData->type.compare(TgcMaterialData::MultiMaterial) == 0)
        {
            TgcSceneLoaderMaterialAux* matAux = new TgcSceneLoaderMaterialAux();
            for (int j = 0; j < materialData->subMaterialsCount; j++)
            {
				matAux->subMaterials.push_back(createTextureAndMaterial(materialData->subMaterials[j], texturesPath));
            }
			materialsArray.push_back(matAux);
        }
    }


	//Load Meshes
	for (int i = 0; i < sceneData->meshCount; i++)
    {
        TgcMeshData* meshData = sceneData->meshesData[i];
        TgcMesh* tgcMesh = NULL;

        //Mesh with only vertexColor
        if (meshData->materialId == -1)
        {
            tgcMesh = createMeshVertexColor(meshData);
        }

        //With material
        else
        {
            //With lightmap
            if (meshData->lightmapEnabled)
            {
                tgcMesh = createMeshDiffuseMapLightmap(sceneData, mediaPath, materialsArray, meshData);
            }

            //With texture but without lightmap
            else
            {
                tgcMesh = createMeshDiffuseMap(materialsArray, meshData);
            }
        }

        //Create BoundingBox if it is not provided
		if (meshData->boundingBox)
        {
            tgcMesh->boundingBox = new TgcBoundingBox(Vector3(meshData->pMin), Vector3(meshData->pMax));
        }
        else
        {
            tgcMesh->createBoundingBox(meshData);
        }

        //layer
        tgcMesh->layer = meshData->layerName;
                
        //AlphaBlending
        tgcMesh->alphaBlendEnable = meshData->alphaBlending;

        //add mesh to scene
        tgcMesh->enabled = true;
		tgcScene->meshes.push_back(tgcMesh);

        //userProperties
        tgcMesh->userProperties = meshData->userProperties;
    }


    //BoundingBox del escenario, utilizar el que viene del XML o crearlo nosotros
	if (sceneData->boundingBox)
    {
        tgcScene->boundingBox = new TgcBoundingBox(Vector3(sceneData->pMin), Vector3(sceneData->pMax));
    }
    else
    {
        vector<TgcBoundingBox*> boundingBoxes;
		for (int j = 0; j < sceneData->meshCount; j++)
		{
			boundingBoxes.push_back(tgcScene->meshes[j]->boundingBox);
		}
        tgcScene->boundingBox = TgcBoundingBox::computeFromBoundingBoxes(boundingBoxes);
    }




	return tgcScene;
}


TgcSceneLoader::TgcSceneLoaderMaterialAux* TgcSceneLoader::createTextureAndMaterial(const TgcMaterialData* materialData, string texturesPath)
{
	TgcSceneLoaderMaterialAux* matAux = new TgcSceneLoaderMaterialAux();
	matAux->texturePath = texturesPath + materialData->fileName;
	return matAux;
}

TgcMesh* TgcSceneLoader::createMeshVertexColor(TgcMeshData* meshData)
{
	//Define input layout
	TgcInputLayout* inputLayout = GuiController::Instance->renderer->createTgcInputLayoutInstance();
	inputLayout->elements.push_back(InputElement::Element(InputElement::Position, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Normal, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Color, InputElement::Float4, 0));
	inputLayout->create();

	//Create vertexBuffer
	TgcVertexBuffer* vertexBuffer = GuiController::Instance->renderer->createTgcVertexBufferInstance();
	VertexType::VertexColor* vertexData = new VertexType::VertexColor[meshData->coordinatesIndicesCount];
	vector<int> subGroupsVertexCount;
	subGroupsVertexCount.push_back(meshData->coordinatesIndicesCount);
	for (int j = 0; j < meshData->coordinatesIndicesCount; j++)
	{
		VertexType::VertexColor v;

        //vertices
        int coordIdx = meshData->coordinatesIndices[j] * 3;
        v.position = Vector3(
            meshData->verticesCoordinates[coordIdx],
            meshData->verticesCoordinates[coordIdx + 1],
            meshData->verticesCoordinates[coordIdx + 2]
            );

        //normals
        //there may be one normal shared for each unique vertex of the mesh (old version)
        if (meshData->verticesNormalsCount == meshData->verticesCoordinatesCount)
        {
            v.normal = Vector3(
                meshData->verticesNormals[coordIdx],
                meshData->verticesNormals[coordIdx + 1],
                meshData->verticesNormals[coordIdx + 2]
                );
        }
        //or one normal for each vertex of each individual face (updated version of the exporter)
        else
        {
            int normalIdx = j * 3;
            v.normal = Vector3(
                meshData->verticesNormals[normalIdx],
                meshData->verticesNormals[normalIdx + 1],
                meshData->verticesNormals[normalIdx + 2]
                );
        }

        //color
        int colorIdx = meshData->colorIndices[j] * 4;
        v.color = Color(
			meshData->verticesColors[colorIdx],
			meshData->verticesColors[colorIdx + 1],
			meshData->verticesColors[colorIdx + 2],
			meshData->verticesColors[colorIdx + 3]
		);

		vertexData[j] = v;
	}
	vertexBuffer->create(meshData->coordinatesIndicesCount, inputLayout, vertexData);
	delete[] vertexData;

	//Create indexBuffer
	TgcIndexBuffer* indexBuffer = GuiController::Instance->renderer->createTgcIndexBufferInstance();
	unsigned long* indexData = new unsigned long[meshData->coordinatesIndicesCount];
    for (int i = 0; i < meshData->coordinatesIndicesCount; i++)
    {
        indexData[i] = i;
    }
	indexBuffer->create(meshData->coordinatesIndicesCount, indexData);
	delete[] indexData;


	//Create mesh
	TgcMesh* tgcMesh = new TgcMesh();
	tgcMesh->initData(meshData->name, vertexBuffer, indexBuffer, subGroupsVertexCount, MeshValues::VertexColor);
	
	return tgcMesh;
}


TgcMesh* TgcSceneLoader::createMeshDiffuseMap(const vector<TgcSceneLoaderMaterialAux*> &materialsArray, TgcMeshData* meshData)
{
	//Define input layout
	TgcInputLayout* inputLayout = GuiController::Instance->renderer->createTgcInputLayoutInstance();
	inputLayout->elements.push_back(InputElement::Element(InputElement::Position, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Normal, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Color, InputElement::Float4, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Texcoord, InputElement::Float2, 0));
	inputLayout->create();

	//Set texture for a mesh with one sub-group
    TgcSceneLoaderMaterialAux* matAux = materialsArray[meshData->materialId];
    vector<TgcTexture*> meshTextures;
	int subGroups = 1;
	if (matAux->subMaterials.size() == 0)
    {
		meshTextures.push_back(TgcTexture::createTexture(matAux->texturePath));
    }
    //Set texture for many sub-group
    else
    {
		subGroups = matAux->subMaterials.size();
        for (int m = 0; m < subGroups; m++)
        {
			meshTextures.push_back(TgcTexture::createTexture(matAux->subMaterials[m]->texturePath));
        }
    }

	//Create vertexBuffer
	TgcVertexBuffer* vertexBuffer = GuiController::Instance->renderer->createTgcVertexBufferInstance();
	VertexType::DiffuseMap* vertexData = new VertexType::DiffuseMap[meshData->coordinatesIndicesCount];
	vector<int> subGroupsVertexCount;
	int vertexCount = 0;
	for (int g = 0; g < subGroups && vertexCount < meshData->coordinatesIndicesCount; g++) 
	{
		//Iterate many times over the same array to store the vertex sorted by sub-group
		subGroupsVertexCount.push_back(0);
		for (int j = 0; j < meshData->coordinatesIndicesCount; j++)
		{
			//We only take the vertex that belongs to the current group
            int triIndex = (int)floor((float)j / 3);
            if(subGroups == 1 || meshData->materialsIds[triIndex] == g) 
			{
				//Increment the vertex count for this group
                subGroupsVertexCount[g]++;
                vertexCount++;

				VertexType::DiffuseMap v;

				//vertices
				int coordIdx = meshData->coordinatesIndices[j] * 3;
				v.position = Vector3(
					meshData->verticesCoordinates[coordIdx],
					meshData->verticesCoordinates[coordIdx + 1],
					meshData->verticesCoordinates[coordIdx + 2]
					);

				//normals
				//there may be one normal shared for each unique vertex of the mesh (old version)
				if (meshData->verticesNormalsCount == meshData->verticesCoordinatesCount)
				{
					v.normal = Vector3(
						meshData->verticesNormals[coordIdx],
						meshData->verticesNormals[coordIdx + 1],
						meshData->verticesNormals[coordIdx + 2]
						);
				}
				//or one normal for each vertex of each individual face (updated version of the exporter)
				else
				{
					int normalIdx = j * 3;
					v.normal = Vector3(
						meshData->verticesNormals[normalIdx],
						meshData->verticesNormals[normalIdx + 1],
						meshData->verticesNormals[normalIdx + 2]
						);
				}

				//color
				int colorIdx = meshData->colorIndices[j] * 4;
				v.color = Color(
					meshData->verticesColors[colorIdx],
					meshData->verticesColors[colorIdx + 1],
					meshData->verticesColors[colorIdx + 2],
					meshData->verticesColors[colorIdx + 3]
				);

				//texture coordinates diffuseMap
				int texCoordIdx = meshData->texCoordinatesIndices[j] * 2;
				v.texCoord = Vector2(
					meshData->textureCoordinates[texCoordIdx],
					meshData->textureCoordinates[texCoordIdx + 1]
				);

				vertexData[j] = v;
			}
		}
	}
	vertexBuffer->create(meshData->coordinatesIndicesCount, inputLayout, vertexData);
	delete[] vertexData;

	//Create indexBuffer
	TgcIndexBuffer* indexBuffer = GuiController::Instance->renderer->createTgcIndexBufferInstance();
	unsigned long* indexData = new unsigned long[meshData->coordinatesIndicesCount];
    for (int i = 0; i < meshData->coordinatesIndicesCount; i++)
    {
        indexData[i] = i;
    }
	indexBuffer->create(meshData->coordinatesIndicesCount, indexData);
	delete[] indexData;


	//Create mesh
	TgcMesh* tgcMesh = new TgcMesh();
	tgcMesh->initData(meshData->name, vertexBuffer, indexBuffer, subGroupsVertexCount, MeshValues::DiffuseMap);
	tgcMesh->diffuseMaps = meshTextures;

	return tgcMesh;
}

TgcMesh* TgcSceneLoader::createMeshDiffuseMapLightmap(const TgcSceneData* sceneData, string mediaPath, const vector<TgcSceneLoaderMaterialAux*> &materialsArray, 
	TgcMeshData* meshData)
{
	//Define input layout
	TgcInputLayout* inputLayout = GuiController::Instance->renderer->createTgcInputLayoutInstance();
	inputLayout->elements.push_back(InputElement::Element(InputElement::Position, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Normal, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Color, InputElement::Float4, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Texcoord, InputElement::Float2, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Texcoord, InputElement::Float2, 1, "TexcoordLightmap"));
	inputLayout->create();

	//Set texture for a mesh with one sub-group
    TgcSceneLoaderMaterialAux* matAux = materialsArray[meshData->materialId];
    vector<TgcTexture*> meshTextures;
	int subGroups = 1;
	if (matAux->subMaterials.size() == 0)
    {
		meshTextures.push_back(TgcTexture::createTexture(matAux->texturePath));
    }
    //Set texture for many sub-group
    else
    {
		subGroups = matAux->subMaterials.size();
        for (int m = 0; m < subGroups; m++)
        {
			meshTextures.push_back(TgcTexture::createTexture(matAux->subMaterials[m]->texturePath));
        }
    }

	//Create vertexBuffer
	TgcVertexBuffer* vertexBuffer = GuiController::Instance->renderer->createTgcVertexBufferInstance();
	VertexType::DiffuseMapAndLightmap* vertexData = new VertexType::DiffuseMapAndLightmap[meshData->coordinatesIndicesCount];
	vector<int> subGroupsVertexCount;
	int vertexCount = 0;
	for (int g = 0; g < subGroups && vertexCount < meshData->coordinatesIndicesCount; g++) 
	{
		//Iterate many times over the same array to store the vertex sorted by sub-group
		subGroupsVertexCount.push_back(0);
		for (int j = 0; j < meshData->coordinatesIndicesCount; j++)
		{
			//We only take the vertex that belongs to the current group
            int triIndex = (int)floor((float)j / 3);
            if(subGroups == 1 || meshData->materialsIds[triIndex] == g) 
			{
				//Increment the vertex count for this group
                subGroupsVertexCount[g]++;
                vertexCount++;

				VertexType::DiffuseMapAndLightmap v;

				//vertices
				int coordIdx = meshData->coordinatesIndices[j] * 3;
				v.position = Vector3(
					meshData->verticesCoordinates[coordIdx],
					meshData->verticesCoordinates[coordIdx + 1],
					meshData->verticesCoordinates[coordIdx + 2]
					);

				//normals
				//there may be one normal shared for each unique vertex of the mesh (old version)
				if (meshData->verticesNormalsCount == meshData->verticesCoordinatesCount)
				{
					v.normal = Vector3(
						meshData->verticesNormals[coordIdx],
						meshData->verticesNormals[coordIdx + 1],
						meshData->verticesNormals[coordIdx + 2]
						);
				}
				//or one normal for each vertex of each individual face (updated version of the exporter)
				else
				{
					int normalIdx = j * 3;
					v.normal = Vector3(
						meshData->verticesNormals[normalIdx],
						meshData->verticesNormals[normalIdx + 1],
						meshData->verticesNormals[normalIdx + 2]
						);
				}

				//color
				int colorIdx = meshData->colorIndices[j] * 4;
				v.color = Color(
					meshData->verticesColors[colorIdx],
					meshData->verticesColors[colorIdx + 1],
					meshData->verticesColors[colorIdx + 2],
					meshData->verticesColors[colorIdx + 3]
				);

				//texture coordinates diffuseMap
				int texCoordIdx = meshData->texCoordinatesIndices[j] * 2;
				v.texCoord0 = Vector2(
					meshData->textureCoordinates[texCoordIdx],
					meshData->textureCoordinates[texCoordIdx + 1]
				);

				//texture coordinates LightMap
                int texCoordIdxLM = meshData->texCoordinatesIndicesLightMap[j] * 2;
				v.texCoord0 = Vector2(
					meshData->textureCoordinatesLightMap[texCoordIdxLM],
					meshData->textureCoordinatesLightMap[texCoordIdxLM + 1]
				);

				vertexData[j] = v;
			}
		}
	}
	vertexBuffer->create(meshData->coordinatesIndicesCount, inputLayout, vertexData);
	delete[] vertexData;

	//Create indexBuffer
	TgcIndexBuffer* indexBuffer = GuiController::Instance->renderer->createTgcIndexBufferInstance();
	unsigned long* indexData = new unsigned long[meshData->coordinatesIndicesCount];
    for (int i = 0; i < meshData->coordinatesIndicesCount; i++)
    {
        indexData[i] = i;
    }
	indexBuffer->create(meshData->coordinatesIndicesCount, indexData);
	delete[] indexData;


	//Load lightMap
    TgcTexture* lightMap = TgcTexture::createTexture(mediaPath + sceneData->lightmapsDir + "\\" + meshData->lightmap);


	//Create mesh
	TgcMesh* tgcMesh = new TgcMesh();
	tgcMesh->initData(meshData->name, vertexBuffer, indexBuffer, subGroupsVertexCount, MeshValues::DiffuseMapAndLightmap);
	tgcMesh->diffuseMaps = meshTextures;
	tgcMesh->lightMap = lightMap;

	return tgcMesh;
}
