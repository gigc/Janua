/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/TgcGeometry/TgcDebugBox.h"
using namespace TgcViewer;

const int TgcDebugBox::LINE_VERTICES_COUNT = 36;
const int TgcDebugBox::LINES_COUNT = 12;
const int TgcDebugBox::VERTICES_COUNT = LINES_COUNT * LINE_VERTICES_COUNT;
const int TgcDebugBox::TRIANGLES_COUNT = LINES_COUNT * 12;


TgcDebugBox::TgcDebugBox()
{
	thickness = 1;
}


TgcDebugBox::TgcDebugBox(const TgcDebugBox& other)
{
}


TgcDebugBox::~TgcDebugBox()
{
}

void TgcDebugBox::create()
{
	//input layout
	TgcInputLayout* inputLayout = GuiController::Instance->renderer->createTgcInputLayoutInstance();
	inputLayout->elements.push_back(InputElement::Element(InputElement::Position, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Color, InputElement::Float4, 0));
	inputLayout->create();

	//Vertex buffer
	vertexBuffer = GuiController::Instance->renderer->createTgcVertexBufferInstance();
	VertexFormat::PositionColor* vertexData = new VertexFormat::PositionColor[VERTICES_COUNT];
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
	effect = GuiController::Instance->shaders->generalPositionColor;
	effect->init(vertexBuffer);
}

void TgcDebugBox::updateValues()
{
	VertexFormat::PositionColor* vertices = (VertexFormat::PositionColor*)this->vertexBuffer->map(BufferMap::WriteDiscard);
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


void TgcDebugBox::render()
{
	TgcRenderer* renderer = GuiController::Instance->renderer;

	GuiController::Instance->shaders->setShaderMatrixIdentity(this->effect);

	renderer->setVertexBuffer(this->vertexBuffer);
	renderer->setIndexBuffer(this->indexBuffer);

	effect->begin();
	renderer->drawIndexed(PrimitiveTopology::TriangleList, VERTICES_COUNT);
	effect->end();
}

void TgcDebugBox::createLineX(VertexFormat::PositionColor* const vertices, int idx, Color c, Vector3 min, Vector3 max)
{
    Vector3 min2 = Vector3(min.X, min.Y - thickness, min.Z - thickness);
	Vector3 max2 = Vector3(max.X, max.Y + thickness, max.Z + thickness);
    createLineVertices(vertices, idx, min2, max2, c);
}

void TgcDebugBox::createLineY(VertexFormat::PositionColor* const vertices, int idx, Color c, Vector3 min, Vector3 max)
{
    Vector3 min2 = Vector3(min.X - thickness, min.Y, min.Z - thickness);
    Vector3 max2 = Vector3(max.X + thickness, max.Y, max.Z + thickness);
    createLineVertices(vertices, idx, min2, max2, c);
}

void TgcDebugBox::createLineZ(VertexFormat::PositionColor* const vertices, int idx, Color c, Vector3 min, Vector3 max)
{
    Vector3 min2 = Vector3(min.X - thickness, min.Y - thickness, min.Z);
    Vector3 max2 = Vector3(max.X + thickness, max.Y + thickness, max.Z);
    createLineVertices(vertices, idx, min2, max2, c);
}


void TgcDebugBox::createLineVertices(VertexFormat::PositionColor* const vertices, int idx, Vector3 min, Vector3 max, Color c)
{
	Vector3 n;

    // Front face
    vertices[idx] = VertexFormat::PositionColor(Vector3(min.X, max.Y, max.Z), c);
    vertices[idx + 1] = VertexFormat::PositionColor(Vector3(min.X, min.Y, max.Z), c);
    vertices[idx + 2] = VertexFormat::PositionColor(Vector3(max.X, max.Y, max.Z), c);
    vertices[idx + 3] = VertexFormat::PositionColor(Vector3(min.X, min.Y, max.Z), c);
    vertices[idx + 4] = VertexFormat::PositionColor(Vector3(max.X, min.Y, max.Z), c);
    vertices[idx + 5] = VertexFormat::PositionColor(Vector3(max.X, max.Y, max.Z), c);

    // Back face (remember this is facing *away* from the camera, so vertices should be clockwise order)
    vertices[idx + 6] = VertexFormat::PositionColor(Vector3(min.X, max.Y, min.Z), c);
    vertices[idx + 7] = VertexFormat::PositionColor(Vector3(max.X, max.Y, min.Z), c);
    vertices[idx + 8] = VertexFormat::PositionColor(Vector3(min.X, min.Y, min.Z), c);
    vertices[idx + 9] = VertexFormat::PositionColor(Vector3(min.X, min.Y, min.Z), c);
    vertices[idx + 10] = VertexFormat::PositionColor(Vector3(max.X, max.Y, min.Z), c);
    vertices[idx + 11] = VertexFormat::PositionColor(Vector3(max.X, min.Y, min.Z), c);

    // Top face
    vertices[idx + 12] = VertexFormat::PositionColor(Vector3(min.X, max.Y, max.Z), c);
    vertices[idx + 13] = VertexFormat::PositionColor(Vector3(max.X, max.Y, min.Z), c);
    vertices[idx + 14] = VertexFormat::PositionColor(Vector3(min.X, max.Y, min.Z), c);
    vertices[idx + 15] = VertexFormat::PositionColor(Vector3(min.X, max.Y, max.Z), c);
    vertices[idx + 16] = VertexFormat::PositionColor(Vector3(max.X, max.Y, max.Z), c);
    vertices[idx + 17] = VertexFormat::PositionColor(Vector3(max.X, max.Y, min.Z), c);

    // Bottom face (remember this is facing *away* from the camera, so vertices should be clockwise order)
    vertices[idx + 18] = VertexFormat::PositionColor(Vector3(min.X, min.Y, max.Z), c);
    vertices[idx + 19] = VertexFormat::PositionColor(Vector3(min.X, min.Y, min.Z), c);
    vertices[idx + 20] = VertexFormat::PositionColor(Vector3(max.X, min.Y, min.Z), c);
    vertices[idx + 21] = VertexFormat::PositionColor(Vector3(min.X, min.Y, max.Z), c);
    vertices[idx + 22] = VertexFormat::PositionColor(Vector3(max.X, min.Y, min.Z), c);
    vertices[idx + 23] = VertexFormat::PositionColor(Vector3(max.X, min.Y, max.Z), c);

    // Left face
    vertices[idx + 24] = VertexFormat::PositionColor(Vector3(min.X, max.Y, max.Z), c);
    vertices[idx + 25] = VertexFormat::PositionColor(Vector3(min.X, min.Y, min.Z), c);
    vertices[idx + 26] = VertexFormat::PositionColor(Vector3(min.X, min.Y, max.Z), c);
    vertices[idx + 27] = VertexFormat::PositionColor(Vector3(min.X, max.Y, min.Z), c);
    vertices[idx + 28] = VertexFormat::PositionColor(Vector3(min.X, min.Y, min.Z), c);
    vertices[idx + 29] = VertexFormat::PositionColor(Vector3(min.X, max.Y, max.Z), c);

    // Right face (remember this is facing *away* from the camera, so vertices should be clockwise order)
    vertices[idx + 30] = VertexFormat::PositionColor(Vector3(max.X, max.Y, max.Z), c);
    vertices[idx + 31] = VertexFormat::PositionColor(Vector3(max.X, min.Y, max.Z), c);
    vertices[idx + 32] = VertexFormat::PositionColor(Vector3(max.X, min.Y, min.Z), c);
    vertices[idx + 33] = VertexFormat::PositionColor(Vector3(max.X, max.Y, min.Z), c);
    vertices[idx + 34] = VertexFormat::PositionColor(Vector3(max.X, max.Y, max.Z), c);
    vertices[idx + 35] = VertexFormat::PositionColor(Vector3(max.X, min.Y, min.Z), c);
}

void TgcDebugBox::dispose()
{
	vertexBuffer->dispose();
	indexBuffer->dispose();
}

void TgcDebugBox::setPositionSize(Vector3 position, Vector3 size)
{
	Vector3 radius = size * 0.5f;
    pMin = position - radius;
    pMax = position + radius;
}

