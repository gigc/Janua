/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "Examples/ExampleEditor/BorderBox.h"
using namespace Examples;

const int BorderBox::LINE_VERTICES_COUNT = 36;
const int BorderBox::LINES_COUNT = 12;
const int BorderBox::VERTICES_COUNT = LINES_COUNT * LINE_VERTICES_COUNT;
const int BorderBox::TRIANGLES_COUNT = LINES_COUNT * 12;


BorderBox::BorderBox()
{
	thickness = 1;
}


BorderBox::BorderBox(const BorderBox& other)
{
}


BorderBox::~BorderBox()
{
}

void BorderBox::create()
{
	//input layout
	TgcInputLayout* inputLayout = GuiController::Instance->renderer->createTgcInputLayoutInstance();
	inputLayout->elements.push_back(InputElement::Element(InputElement::Position, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Normal, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Color, InputElement::Float4, 0));
	inputLayout->create();

	//Vertex buffer
	vertexBuffer = GuiController::Instance->renderer->createTgcVertexBufferInstance();
	VertexType::VertexColor* vertexData = new VertexType::VertexColor[VERTICES_COUNT];
	vertexBuffer->create(VERTICES_COUNT, inputLayout, vertexData, BufferUsage::Dynamic);
	delete[] vertexData;
	updateValues();


	//Index buffer
	indexBuffer = GuiController::Instance->renderer->createTgcIndexBufferInstance();
	unsigned int* indexData = new unsigned int[VERTICES_COUNT];
	for(int i = 0; i < VERTICES_COUNT; i++)
	{
		indexData[i] = i;
	}
	indexBuffer->create(VERTICES_COUNT, indexData);
	delete[] indexData;

	//Effect
	effect = GuiController::Instance->shaders->tgcMeshShaderVertexColor;
	effect->init(vertexBuffer);
}

void BorderBox::updateValues()
{
	VertexType::VertexColor* vertices = (VertexType::VertexColor*)this->vertexBuffer->map(BufferMap::WriteDiscard);
	int idx;
	Color c = this->color;

	//Botton Face
    idx = 0;
    createLineZ(vertices, idx, c, 
        pMin, Vector3(pMin.X, pMin.Y, pMax.Z));

    idx += LINE_VERTICES_COUNT;
    createLineX(vertices, idx, c,
        Vector3(pMin.X, pMin.Y, pMax.Z), Vector3(pMax.X, pMin.Y, pMax.Z));

    idx += LINE_VERTICES_COUNT;
    createLineZ(vertices, idx, c,
        Vector3(pMax.X, pMin.Y, pMax.Z), Vector3(pMax.X, pMin.Y, pMin.Z));

    idx += LINE_VERTICES_COUNT;
    createLineX(vertices, idx, c,
        Vector3(pMax.X, pMin.Y, pMin.Z), pMin);


    //Top Face
    idx += LINE_VERTICES_COUNT;
    createLineZ(vertices, idx, c,
        Vector3(pMin.X, pMax.Y, pMin.Z), Vector3(pMin.X, pMax.Y, pMax.Z));

    idx += LINE_VERTICES_COUNT;
    createLineX(vertices, idx, c,
        Vector3(pMin.X, pMax.Y, pMax.Z), pMax);

    idx += LINE_VERTICES_COUNT;
    createLineZ(vertices, idx, c,
        pMax, Vector3(pMax.X, pMax.Y, pMin.Z));

    idx += LINE_VERTICES_COUNT;
    createLineX(vertices, idx, c,
        Vector3(pMax.X, pMax.Y, pMin.Z), Vector3(pMin.X, pMax.Y, pMin.Z));


    //Conexión Bottom-Top
    idx += LINE_VERTICES_COUNT;
    createLineY(vertices, idx, c,
        pMin, Vector3(pMin.X, pMax.Y, pMin.Z));

    idx += LINE_VERTICES_COUNT;
    createLineY(vertices, idx, c,
        Vector3(pMin.X, pMin.Y, pMax.Z), Vector3(pMin.X, pMax.Y, pMax.Z));

    idx += LINE_VERTICES_COUNT;
    createLineY(vertices, idx, c,
        Vector3(pMax.X, pMin.Y, pMax.Z), pMax);

    idx += LINE_VERTICES_COUNT;
    createLineY(vertices, idx, c,
        Vector3(pMax.X, pMin.Y, pMin.Z), Vector3(pMax.X, pMax.Y, pMin.Z));

	this->vertexBuffer->unmap();
}


void BorderBox::render()
{
	TgcRenderer* renderer = GuiController::Instance->renderer;

	GuiController::Instance->shaders->setShaderMatrix(this->effect, Matrix4::Identity());

	renderer->setVertexBuffer(this->vertexBuffer);
	renderer->setIndexBuffer(this->indexBuffer);

	effect->begin();
	renderer->drawIndexed(PrimitiveTopology::TriangleList, VERTICES_COUNT);
	effect->end();
}

void BorderBox::createLineX(VertexType::VertexColor* const vertices, int idx, Color c, Vector3 min, Vector3 max)
{
    Vector3 min2 = Vector3(min.X, min.Y - thickness, min.Z - thickness);
	Vector3 max2 = Vector3(max.X, max.Y + thickness, max.Z + thickness);
    createLineVertices(vertices, idx, min2, max2, c);
}

void BorderBox::createLineY(VertexType::VertexColor* const vertices, int idx, Color c, Vector3 min, Vector3 max)
{
    Vector3 min2 = Vector3(min.X - thickness, min.Y, min.Z - thickness);
    Vector3 max2 = Vector3(max.X + thickness, max.Y, max.Z + thickness);
    createLineVertices(vertices, idx, min2, max2, c);
}

void BorderBox::createLineZ(VertexType::VertexColor* const vertices, int idx, Color c, Vector3 min, Vector3 max)
{
    Vector3 min2 = Vector3(min.X - thickness, min.Y - thickness, min.Z);
    Vector3 max2 = Vector3(max.X + thickness, max.Y + thickness, max.Z);
    createLineVertices(vertices, idx, min2, max2, c);
}


void BorderBox::createLineVertices(VertexType::VertexColor* const vertices, int idx, Vector3 min, Vector3 max, Color c)
{
	Vector3 n;

    // Front face
	n = Vector3(0, 0, 1);
    vertices[idx] = VertexType::VertexColor(Vector3(min.X, max.Y, max.Z), n, c);
    vertices[idx + 1] = VertexType::VertexColor(Vector3(min.X, min.Y, max.Z), n, c);
    vertices[idx + 2] = VertexType::VertexColor(Vector3(max.X, max.Y, max.Z), n, c);
    vertices[idx + 3] = VertexType::VertexColor(Vector3(min.X, min.Y, max.Z), n, c);
    vertices[idx + 4] = VertexType::VertexColor(Vector3(max.X, min.Y, max.Z), n, c);
    vertices[idx + 5] = VertexType::VertexColor(Vector3(max.X, max.Y, max.Z), n, c);

    // Back face (remember this is facing *away* from the camera, so vertices should be clockwise order)
	n = Vector3(0, 0, -1);
    vertices[idx + 6] = VertexType::VertexColor(Vector3(min.X, max.Y, min.Z), n, c);
    vertices[idx + 7] = VertexType::VertexColor(Vector3(max.X, max.Y, min.Z), n, c);
    vertices[idx + 8] = VertexType::VertexColor(Vector3(min.X, min.Y, min.Z), n, c);
    vertices[idx + 9] = VertexType::VertexColor(Vector3(min.X, min.Y, min.Z), n, c);
    vertices[idx + 10] = VertexType::VertexColor(Vector3(max.X, max.Y, min.Z), n, c);
    vertices[idx + 11] = VertexType::VertexColor(Vector3(max.X, min.Y, min.Z), n, c);

    // Top face
	n = Vector3(0, 1, 0);
    vertices[idx + 12] = VertexType::VertexColor(Vector3(min.X, max.Y, max.Z), n, c);
    vertices[idx + 13] = VertexType::VertexColor(Vector3(max.X, max.Y, min.Z), n, c);
    vertices[idx + 14] = VertexType::VertexColor(Vector3(min.X, max.Y, min.Z), n, c);
    vertices[idx + 15] = VertexType::VertexColor(Vector3(min.X, max.Y, max.Z), n, c);
    vertices[idx + 16] = VertexType::VertexColor(Vector3(max.X, max.Y, max.Z), n, c);
    vertices[idx + 17] = VertexType::VertexColor(Vector3(max.X, max.Y, min.Z), n, c);

    // Bottom face (remember this is facing *away* from the camera, so vertices should be clockwise order)
	n = Vector3(0, -1, 0);
    vertices[idx + 18] = VertexType::VertexColor(Vector3(min.X, min.Y, max.Z), n, c);
    vertices[idx + 19] = VertexType::VertexColor(Vector3(min.X, min.Y, min.Z), n, c);
    vertices[idx + 20] = VertexType::VertexColor(Vector3(max.X, min.Y, min.Z), n, c);
    vertices[idx + 21] = VertexType::VertexColor(Vector3(min.X, min.Y, max.Z), n, c);
    vertices[idx + 22] = VertexType::VertexColor(Vector3(max.X, min.Y, min.Z), n, c);
    vertices[idx + 23] = VertexType::VertexColor(Vector3(max.X, min.Y, max.Z), n, c);

    // Left face
	n = Vector3(-1, 0, 0);
    vertices[idx + 24] = VertexType::VertexColor(Vector3(min.X, max.Y, max.Z), n, c);
    vertices[idx + 25] = VertexType::VertexColor(Vector3(min.X, min.Y, min.Z), n, c);
    vertices[idx + 26] = VertexType::VertexColor(Vector3(min.X, min.Y, max.Z), n, c);
    vertices[idx + 27] = VertexType::VertexColor(Vector3(min.X, max.Y, min.Z), n, c);
    vertices[idx + 28] = VertexType::VertexColor(Vector3(min.X, min.Y, min.Z), n, c);
    vertices[idx + 29] = VertexType::VertexColor(Vector3(min.X, max.Y, max.Z), n, c);

    // Right face (remember this is facing *away* from the camera, so vertices should be clockwise order)
	n = Vector3(1, 0, 0);
    vertices[idx + 30] = VertexType::VertexColor(Vector3(max.X, max.Y, max.Z), n, c);
    vertices[idx + 31] = VertexType::VertexColor(Vector3(max.X, min.Y, max.Z), n, c);
    vertices[idx + 32] = VertexType::VertexColor(Vector3(max.X, min.Y, min.Z), n, c);
    vertices[idx + 33] = VertexType::VertexColor(Vector3(max.X, max.Y, min.Z), n, c);
    vertices[idx + 34] = VertexType::VertexColor(Vector3(max.X, max.Y, max.Z), n, c);
    vertices[idx + 35] = VertexType::VertexColor(Vector3(max.X, min.Y, min.Z), n, c);
}

void BorderBox::dispose()
{
	vertexBuffer->dispose();
	indexBuffer->dispose();
}

void BorderBox::setPositionSize(Vector3 position, Vector3 size)
{
	Vector3 radius = size * 0.5f;
    pMin = position - radius;
    pMax = position + radius;
}

