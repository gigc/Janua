/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/TgcSceneLoader/TgcScene.h"
using namespace TgcViewer;


TgcScene::TgcScene(string sceneName, string filePath)
{
	this->sceneName = sceneName;
	this->filePath = filePath;
}


TgcScene::TgcScene(const TgcScene& other)
{
}


TgcScene::~TgcScene()
{
}

void TgcScene::renderAll()
{
	for(unsigned int i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i]->render();
	}
}

void TgcScene::renderAll(bool showBoundingBox)
{
	for(unsigned int i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i]->render();
		this->meshes[i]->boundingBox->render();
	}
}

void TgcScene::disposeAll()
{
	for(unsigned int i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i]->dispose();
	}
}

void TgcScene::setMeshesEnabled(bool flag)
{
	for(unsigned int i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i]->enabled = flag;
	}
}

