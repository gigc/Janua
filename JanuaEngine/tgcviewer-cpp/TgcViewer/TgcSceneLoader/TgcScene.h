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
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/TgcSceneLoader/TgcMesh.h"
#include "TgcViewer/TgcGeometry/TgcBoundingBox.h"


namespace TgcViewer
{



/**
* Scene composed of many static meshes
*/
class TgcScene
{

public:

	/**
	* Creates a new scene
	*/
	TgcScene(string sceneName, string filePath);

	TgcScene(const TgcScene&);
	~TgcScene();

	/**
	* Render all meshes of the scene
	*/
	void renderAll();

	/**
	* Render all meshes of the scene
	* @param showBoundingBox true to show the boundingBox of each mesh
	*/
	void renderAll(bool showBoundingBox);

	/**
	* Free all meshes
	*/
	void disposeAll();

	/**
	* Enable or disable all meshes
	*/
	void setMeshesEnabled(bool flag);

private:

public:

	string sceneName;
	string filePath;
	vector<TgcMesh*> meshes;
	TgcBoundingBox* boundingBox;

private:


	
};




}