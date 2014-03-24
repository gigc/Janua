/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "Examples/ExampleVoxel/ExampleVoxel.h"
using namespace Examples;


string ExampleVoxel::getCategory()
{
	return "Category";
}

string ExampleVoxel::getName()
{
	return "ExampleVoxel";
}

string ExampleVoxel::getDescription()
{
	return "ExampleVoxel";
}

void ExampleVoxel::init()
{
	camera = new TgcFpsCamera();

	
}

void ExampleVoxel::render(float elapsedTime)
{
	camera->updateCamera();
	camera->updateViewMatrix();

}

void ExampleVoxel::close()
{

}

