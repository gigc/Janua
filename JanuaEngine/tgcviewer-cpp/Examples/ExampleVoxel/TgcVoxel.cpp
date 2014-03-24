/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "Examples/ExampleVoxel/TgcVoxel.h"
using namespace Examples;


TgcVoxel::TgcVoxel()
{
}


TgcVoxel::TgcVoxel(const TgcVoxel& other)
{
}


TgcVoxel::~TgcVoxel()
{
}


void TgcVoxel::create()
{
	//input layout
	TgcInputLayout* inputLayout = GuiController::Instance->renderer->createTgcInputLayoutInstance();
	inputLayout->elements.push_back(InputElement::Element(InputElement::Position, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Normal, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Color, InputElement::Float4, 0));
	inputLayout->create();

	//Vertex data
	int vertexCount = 8;
	VertexType::DiffuseMap* vertexData = new VertexType::DiffuseMap[vertexCount];

	Vector3 min = Vector3(-0.5f, -0.5f, -0.5f);
	Vector3 max = Vector3(0.5f, 0.5f, 0.5f);

	vertexData[0].position = Vector3(min.X, min.Y, min.Z);
	vertexData[0].normal = Vector3(0, -1, 0);
	vertexData[0].color = color;

	vertexData[1].position = Vector3(min.X, min.Y, max.Z);
	vertexData[1].normal = Vector3(0, -1, 0);
	vertexData[1].color = color;

	vertexData[2].position = Vector3(max.X, min.Y, min.Z);
	vertexData[2].normal = Vector3(0, -1, 0);
	vertexData[2].color = color;

	vertexData[3].position = Vector3(max.X, min.Y, max.Z);
	vertexData[3].normal = Vector3(0, -1, 0);
	vertexData[3].color = color;

	vertexData[4].position = Vector3(min.X, max.Y, min.Z);
	vertexData[4].normal = Vector3(0, -1, 0);
	vertexData[4].color = color;

	vertexData[5].position = Vector3(min.X, max.Y, max.Z);
	vertexData[5].normal = Vector3(0, -1, 0);
	vertexData[5].color = color;

	vertexData[6].position = Vector3(max.X, max.Y, min.Z);
	vertexData[6].normal = Vector3(0, -1, 0);
	vertexData[6].color = color;

	vertexData[7].position = Vector3(max.X, max.Y, max.Z);
	vertexData[7].normal = Vector3(0, -1, 0);
	vertexData[7].color = color;

	//Vertex buffer
	vertexBuffer = GuiController::Instance->renderer->createTgcVertexBufferInstance();
	vertexBuffer->create(vertexCount, inputLayout, vertexData);
	delete[] vertexData;

	//Index buffer
	unsigned long* indexData = new unsigned long[36];
	int i = 0;

	//Bottom
	indexData[i++] = 0;
	indexData[i++] = 1;
	indexData[i++] = 3;
	indexData[i++] = 3;
	indexData[i++] = 2;
	indexData[i++] = 0;

	//Top
	indexData[i++] = 4;
	indexData[i++] = 5;
	indexData[i++] = 7;
	indexData[i++] = 7;
	indexData[i++] = 6;
	indexData[i++] = 4;

	//Left
	indexData[i++] = 0;
	indexData[i++] = 2;
	indexData[i++] = 6;
	indexData[i++] = 6;
	indexData[i++] = 4;
	indexData[i++] = 0;

	//Right
	indexData[i++] = 1;
	indexData[i++] = 5;
	indexData[i++] = 7;
	indexData[i++] = 7;
	indexData[i++] = 3;
	indexData[i++] = 1;

	//Front
	indexData[i++] = 0;
	indexData[i++] = 4;
	indexData[i++] = 5;
	indexData[i++] = 5;
	indexData[i++] = 1;
	indexData[i++] = 0;

	//Back
	indexData[i++] = 3;
	indexData[i++] = 7;
	indexData[i++] = 6;
	indexData[i++] = 6;
	indexData[i++] = 2;
	indexData[i++] = 3;

	indexBuffer = GuiController::Instance->renderer->createTgcIndexBufferInstance();
	indexBuffer->create(vertexCount, indexData);
	delete[] indexData;


	//Effect
	effect = GuiController::Instance->shaders->tgcMeshShaderDiffuseMap;
	effect->init(vertexBuffer);
}

