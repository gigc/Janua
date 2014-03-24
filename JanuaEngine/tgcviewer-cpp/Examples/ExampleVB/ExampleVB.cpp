/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "Examples/ExampleVB/ExampleVB.h"
using namespace Examples;


string ExampleVB::getCategory()
{
	return "Category";
}

string ExampleVB::getName()
{
	return "ExampleVB";
}

string ExampleVB::getDescription()
{
	return "ExampleVB";
}

void ExampleVB::init()
{
	//camera
	camera = new TgcFpsCamera();
	/*
	camera->position = Vector3(-5, 0, 0);
	camera->lookAt = Vector3(1, 0, 0);
	camera->movementSpeed = 1;
	camera->jumpSpeed = 1;
	camera->currentRotY = 6.0325036f;
	camera->currentRotXZ = 0.79224771f;
	*/
	camera->position = Vector3(0, 0, -5);
	camera->lookAt = Vector3(0, 0, 1);
	camera->movementSpeed = 1;
	camera->jumpSpeed = 1;

	


	//input layout
	TgcInputLayout* inputLayout = GuiController::Instance->renderer->createTgcInputLayoutInstance();
	inputLayout->elements.push_back(InputElement::Element(InputElement::Position, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Normal, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Color, InputElement::Float4, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Texcoord, InputElement::Float2, 0));
	inputLayout->create();

	//Texture
	texture = TgcTexture::createTexture(GuiController::Instance->examplesMediaPath + "TgcModels\\Deposito\\Textures\\box1.jpg");

	//Vertex data
	int vertexCount = 3;
	VertexType::DiffuseMap* vertexData = new VertexType::DiffuseMap[vertexCount];

	/*
	vertexData[0].position = Vector3(0, 0, 0);
	vertexData[0].normal = Vector3(0, 1, 0);
	vertexData[0].color = Color::Blue;
	vertexData[0].texCoord = Vector2(0, 0);

	vertexData[1].position = Vector3(100, 0, 0);
	vertexData[1].normal = Vector3(0, 1, 0);
	vertexData[1].color = Color::Red;
	vertexData[1].texCoord = Vector2(1, 0);

	vertexData[2].position = Vector3(0, 0, 100);
	vertexData[2].normal = Vector3(0, 1, 0);
	vertexData[2].color = Color::Green;
	vertexData[2].texCoord = Vector2(0, 1);
	*/
	vertexData[0].position = Vector3(0, 0, 0);
	vertexData[0].normal = Vector3(0, 1, 0);
	vertexData[0].color = Color::Blue;
	vertexData[0].texCoord = Vector2(0, 0);

	vertexData[1].position = Vector3(200, 0, 0);
	vertexData[1].normal = Vector3(0, 1, 0);
	vertexData[1].color = Color::Red;
	vertexData[1].texCoord = Vector2(1, 0);

	vertexData[2].position = Vector3(0, 100, 200);
	vertexData[2].normal = Vector3(0, 1, 0);
	vertexData[2].color = Color::Green;
	vertexData[2].texCoord = Vector2(0, 1);

	//Vertex buffer
	vertexBuffer = GuiController::Instance->renderer->createTgcVertexBufferInstance();
	vertexBuffer->create(vertexCount, inputLayout, vertexData);
	delete[] vertexData;

	//Index buffer
	unsigned long* indexData = new unsigned long[vertexCount];
	indexData[0] = 0;
	indexData[1] = 1;
	indexData[2] = 2;
	indexBuffer = GuiController::Instance->renderer->createTgcIndexBufferInstance();
	indexBuffer->create(vertexCount, indexData);
	delete[] indexData;


	//Effect
	effect = GuiController::Instance->shaders->tgcMeshShaderDiffuseMap;
	effect->init(vertexBuffer);


}

void ExampleVB::render(float elapsedTime)
{
	TgcRenderer* renderer = GuiController::Instance->renderer;


	//Update camera
	camera->updateCamera();
	camera->updateViewMatrix();

	//Set world matrix
	Matrix4 world = Matrix4::Identity();
	GuiController::Instance->shaders->setShaderMatrix(effect, world);

	//Set buffers
	renderer->setVertexBuffer(this->vertexBuffer);
	renderer->setIndexBuffer(this->indexBuffer);

	//Init shader
	effect->begin();

	//Set texture
	effect->setTexture("texDiffuseMap", this->texture);

	//Draw
	renderer->drawIndexed(PrimitiveTopology::TriangleList, 3, 0);


	//End shader
	effect->end();
}

void ExampleVB::close()
{

}

