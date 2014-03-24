/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "Examples/ExampleEditor/Grid.h"
using namespace Examples;


const float Grid::GRID_RADIUS = 100.0f;
const int Grid::VERTEX_COUNT = 21 * 2 * 2;
const float Grid::LINE_SEPARATION = 10.0f;


Grid::Grid()
{
}


Grid::Grid(const Grid& other)
{
}


Grid::~Grid()
{
}

void Grid::create()
{
	aabb = AABB();
	aabb.min = Vector3(-100000, -0.1f, -100000);
	aabb.max = Vector3(100000, 0, 100000);

	//input layout
	TgcInputLayout* inputLayout = GuiController::Instance->renderer->createTgcInputLayoutInstance();
	inputLayout->elements.push_back(InputElement::Element(InputElement::Position, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Normal, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Color, InputElement::Float4, 0));
	inputLayout->create();

	//Vertex buffer
	VertexType::VertexColor* vertices = new VertexType::VertexColor[VERTEX_COUNT];
	Color color = Color::fromRGB(139, 139, 131);
	Vector3 n = Vector3(0, 1, 0);

    //20 lineas horizontales en X
    for (int i = 0; i < 21; i++)
    {
        vertices[i * 2] = VertexType::VertexColor(Vector3(-GRID_RADIUS, 0, -GRID_RADIUS + LINE_SEPARATION * i), n, color);
        vertices[i * 2 + 1] = VertexType::VertexColor(Vector3(GRID_RADIUS, 0, -GRID_RADIUS + LINE_SEPARATION * i), n, color);
    }

    //20 lineas horizontales en Z
    for (int i = 21; i < 42; i++)
    {
        vertices[i * 2] = VertexType::VertexColor(Vector3(-GRID_RADIUS * 3 + LINE_SEPARATION * i - LINE_SEPARATION, 0, -GRID_RADIUS), n, color);
        vertices[i * 2 + 1] = VertexType::VertexColor(Vector3(-GRID_RADIUS * 3 + LINE_SEPARATION * i - LINE_SEPARATION, 0, GRID_RADIUS), n, color);
    }

	vertexBuffer = GuiController::Instance->renderer->createTgcVertexBufferInstance();
	vertexBuffer->create(VERTEX_COUNT, inputLayout, vertices);
	delete[] vertices;


	//Index buffer
	indexBuffer = GuiController::Instance->renderer->createTgcIndexBufferInstance();
	unsigned int* indexData = new unsigned int[VERTEX_COUNT];
	for(int i = 0; i < VERTEX_COUNT; i++)
	{
		indexData[i] = i;
	}
	indexBuffer->create(VERTEX_COUNT, indexData);
	delete[] indexData;

	//Effect
	effect = GuiController::Instance->shaders->tgcMeshShaderVertexColor;
	effect->init(vertexBuffer);
}

void Grid::render()
{
	TgcRenderer* renderer = GuiController::Instance->renderer;

	GuiController::Instance->shaders->setShaderMatrix(this->effect, Matrix4::Identity());

	renderer->setVertexBuffer(this->vertexBuffer);
	renderer->setIndexBuffer(this->indexBuffer);

	effect->begin();
	renderer->drawIndexed(PrimitiveTopology::LineList, VERTEX_COUNT);
	effect->end();
}

void Grid::dispose()
{
	vertexBuffer->dispose();
	indexBuffer->dispose();
}


