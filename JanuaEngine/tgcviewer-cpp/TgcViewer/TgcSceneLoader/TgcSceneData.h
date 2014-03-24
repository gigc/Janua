/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////

#pragma once

//General Includes:
#include <string>
#include <unordered_map>
using namespace std;


namespace TgcViewer
{


/**
* Data for a material of the scene
*/
struct TgcMaterialData
{
	//Material Types
	static const string StandardMaterial;
	static const string MultiMaterial;

    string name;
    string type;

    //Submaterials
    TgcMaterialData** subMaterials;
	int subMaterialsCount;
            
    //Material
    float ambientColor[4];
    float diffuseColor[4];
    float specularColor[4];
    float opacity;
    bool alphaBlendEnable;

    //Bitmap
    string fileName;
    float uvTiling[2];
    float uvOffset[2];

	~TgcMaterialData()
	{
		if(subMaterialsCount > 0)
		{
			for(int i = 0; i < subMaterialsCount; i++)
			{
				delete subMaterials[i];
			}
			delete[] subMaterials;
		}
	}

};



/**
* Data for a mesh of the scene
*/
struct TgcMeshData
{
    string name;
    string layerName;

	//UserProperties
	unordered_map<string, string> userProperties;

    //Global material
    int materialId;

    //LightMap filename
    string lightmap;
    bool lightmapEnabled;

    //Global color if it doen't have Material
    float color[3];

    //Triangles data
    int* coordinatesIndices;
	int coordinatesIndicesCount;

    int* texCoordinatesIndices;
	int texCoordinatesIndicesCount;

    int* colorIndices;
	int colorIndicesCount;

    int* texCoordinatesIndicesLightMap;
	int texCoordinatesIndicesLightMapCount;


    //SubMaterials for each triangle
    int* materialsIds;
	int materialsIdsCount;


    //Vertices values
    float* verticesCoordinates;
	int verticesCoordinatesCount;

    float* textureCoordinates;
	int textureCoordinatesCount;

    float* verticesNormals;
	int verticesNormalsCount;

    float* verticesColors;
	int verticesColorsCount;

    float* textureCoordinatesLightMap;
	int textureCoordinatesLightMapCount;

    float* verticesTangents;
	int verticesTangentsCount;

    float* verticesBinormals;
	int verticesBinormalsCount;


    //BoundingBox
    float pMin[3];
    float pMax[3];
	bool boundingBox;

    //AlphaBlending
    bool alphaBlending;


	~TgcMeshData()
	{
		delete[] coordinatesIndices;
		delete[] texCoordinatesIndices;
		delete[] colorIndices;
		if(texCoordinatesIndicesLightMapCount > 0) delete[] texCoordinatesIndicesLightMap;

		if(materialsIdsCount > 0) delete[] materialsIds;

		delete[] verticesCoordinates;
		delete[] textureCoordinates;
		delete[] verticesNormals;
		delete[] verticesColors;
		if(textureCoordinatesLightMapCount > 0) delete[] textureCoordinatesLightMap;
		if(verticesTangentsCount > 0) delete[] verticesTangents;
		if(verticesBinormalsCount > 0) delete[] verticesBinormals;
	}
};


/**
* Complete data for a scene
*/
struct TgcSceneData 
{
	string name;
    string texturesDir;
        
    //LightMap data
    string lightmapsDir;
    bool lightmapsEnabled;

	//Data for each mesh of the scene
    TgcMeshData** meshesData;
	int meshCount;

	//Data for each material of the scene
    TgcMaterialData** materialsData;
	int materialCount;

    //Scene BoundingBox
    float pMin[3];
    float pMax[3];
	bool boundingBox;

	~TgcSceneData()
	{
		if(meshCount > 0)
		{
			for(int i = 0; i < meshCount; i++)
			{
				delete meshesData[i];
			}
			delete[] meshesData;
		}
		
		if(materialCount > 0)
		{
			for(int i = 0; i < materialCount; i++)
			{
				delete materialsData[i];
			}
			delete[] materialsData;
		}
	}
};




}
