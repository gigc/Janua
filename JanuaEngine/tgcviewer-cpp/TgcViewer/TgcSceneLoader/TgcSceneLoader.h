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
#include <math.h>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/TgcSceneLoader/TgcSceneParser.h"
#include "TgcViewer/TgcSceneLoader/TgcSceneData.h"
#include "TgcViewer/TgcSceneLoader/TgcScene.h"
#include "TgcViewer/TgcSceneLoader/TgcTexture.h"
#include "TgcViewer/TgcSceneLoader/TgcMesh.h"
#include "TgcViewer/Math/Vector2.h"
#include "TgcViewer/Math/Vector3.h"
#include "TgcViewer/Math/Color.h"
#include "TgcViewer/Renderer/TgcRendererGlobals.h"
#include "TgcViewer/Renderer/TgcInputLayout.h"




namespace TgcViewer
{


/**
* Loader of a static tgcScene.xml file
*/
class TgcSceneLoader
{

public:

	TgcSceneLoader();
	TgcSceneLoader(const TgcSceneLoader&);
	~TgcSceneLoader();

	/**
	* Load a TgcScene from a tgcScene.xml file.
	* It uses a mediaPath relative to filePath
	* @param filePath absolute path of the xml file
	* @return a TgcScene loaded
	*/
	TgcScene* loadSceneFromFile(string filePath);

	/**
	* Load a TgcScene from a tgcScene.xml file
	* @param filePath absolute path of the xml file
	* @param mediaPath absolute path of the media directory for the scene resources
	* @return a TgcScene loaded
	*/
	TgcScene* loadSceneFromFile(string filePath, string mediaPath);

	/**
	* Load a TgcScene from a parsed TgcSceneData structure
	* @param sceneData the scene data structure
	* @param mediaPath absolute path of the media directory for the scene resources
	* @return a TgcScene loaded
	*/
	TgcScene* loadScene(const TgcSceneData* sceneData, string mediaPath);




private:
	
	/**
	* Aux structure to store Textures and SubMaterials
	*/
	struct TgcSceneLoaderMaterialAux
	{
		string texturePath;
		vector<TgcSceneLoaderMaterialAux*> subMaterials;

		~TgcSceneLoaderMaterialAux()
		{
			for(unsigned int i = 0; i < subMaterials.size(); i++)
			{
				delete subMaterials[i];
			}
		}
	};

	TgcSceneLoader::TgcSceneLoaderMaterialAux* TgcSceneLoader::createTextureAndMaterial(const TgcMaterialData* materialData, string texturesPath);

	TgcMesh* createMeshVertexColor(TgcMeshData* meshData);

	TgcMesh* createMeshDiffuseMap(const vector<TgcSceneLoaderMaterialAux*> &materialsArray, TgcMeshData* meshData);

	TgcMesh* createMeshDiffuseMapLightmap(const TgcSceneData* sceneData, string mediaPath, const vector<TgcSceneLoaderMaterialAux*> &materialsArray, TgcMeshData* meshData);


public:

private:

	unordered_map<string, TgcTexture*> texturesMap;

};

	/**
	* Vertex types
	*/
	namespace VertexType
	{
		/**
		* Vertex type for TgcMesh.VertexColor
		*/
		struct VertexColor
		{
			Vector3 position;
			Vector3 normal;
			Color color;

			VertexColor()
			{
			}

			VertexColor(Vector3 position, Vector3 normal, Color color)
			{
				this->position = position;
				this->normal = normal;
				this->color = color;
			}
		};

		/**
		* Vertex type for TgcMesh.DiffuseMap
		*/
		struct DiffuseMap
		{
			Vector3 position;
			Vector3 normal;
			Color color;
			Vector2 texCoord;
		};

		/**
		* Vertex type for TgcMesh.DiffuseMapAndLightmap
		*/
		struct DiffuseMapAndLightmap
		{
			Vector3 position;
			Vector3 normal;
			Color color;
			Vector2 texCoord0;
			Vector2 texCoord1;
		};

	}



}