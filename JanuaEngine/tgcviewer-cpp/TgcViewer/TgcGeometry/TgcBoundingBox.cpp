/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/TgcGeometry/TgcBoundingBox.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcBoundingBox* TgcBoundingBox::computeFromBoundingBoxes(const vector<TgcBoundingBox*> &boundingBoxes)
{
	vector<Vector3> points;
    for (unsigned int i = 0; i < boundingBoxes.size(); i++)
	{
		points.push_back(boundingBoxes[i]->pMin);
		points.push_back(boundingBoxes[i]->pMax);
	}
    return computeFromPoints(points);
}

TgcBoundingBox* TgcBoundingBox::computeFromPoints(const vector<Vector3> &points)
{
	Vector3 min = Vector3(FastMath::MAX_FLOAT, FastMath::MAX_FLOAT, FastMath::MAX_FLOAT);
    Vector3 max = Vector3(FastMath::MIN_FLOAT, FastMath::MIN_FLOAT, FastMath::MIN_FLOAT);

	for(unsigned int i = 0; i < points.size(); i++)
	{
		Vector3 p = points[i];

		//min
        if (p.X < min.X)
        {
            min.X = p.X;
        }
        if (p.Y < min.Y)
        {
            min.Y = p.Y;
        }
        if (p.Z < min.Z)
        {
            min.Z = p.Z;
        }
                
        //max
        if (p.X > max.X)
        {
            max.X = p.X;
        }
        if (p.Y > max.Y)
        {
            max.Y = p.Y;
        }
        if (p.Z > max.Z)
        {
            max.Z = p.Z;
        }
	}

    return new TgcBoundingBox(min, max);
}

TgcBoundingBox::TgcBoundingBox()
{
	this->renderColor = Color::Yellow;
	this->dirtyValues = true;
	this->vertexBuffer = NULL;
}

TgcBoundingBox::TgcBoundingBox(Vector3 pMin, Vector3 pMax)
{
	this->renderColor = Color::Yellow;
	this->dirtyValues = true;
	this->vertexBuffer = NULL;
	this->setExtremes(pMin, pMax);
}

TgcBoundingBox::TgcBoundingBox(const TgcBoundingBox& other)
{
}


TgcBoundingBox::~TgcBoundingBox()
{
}

void TgcBoundingBox::setExtremes(Vector3 pMin, Vector3 pMax)
{
	this->pMin = pMin;
    this->pMax = pMax;
    this->pMinOriginal = pMin;
    this->pMaxOriginal = pMax;

    this->dirtyValues = true;
}

void TgcBoundingBox::updateValues()
{
	//Create renderer data
	if(this->vertexBuffer == NULL)
	{
		//input layout
		TgcInputLayout* inputLayout = GuiController::Instance->renderer->createTgcInputLayoutInstance();
		inputLayout->elements.push_back(InputElement::Element(InputElement::Position, InputElement::Float3, 0));
		inputLayout->elements.push_back(InputElement::Element(InputElement::Color, InputElement::Float4, 0));
		inputLayout->create();

		//Vertex buffer
		vertexBuffer = GuiController::Instance->renderer->createTgcVertexBufferInstance();
		vertexBuffer->create(VERTEX_COUNT, inputLayout, this->vertices, BufferUsage::Dynamic);

		//Index data
		unsigned int indexData[INDEX_COUNT];
		
		//Bottom face
		indexData[0] = 0;
		indexData[1] = 1;
		indexData[2] = 1;
		indexData[3] = 3;
		indexData[4] = 3;
		indexData[5] = 2;
		indexData[6] = 2;
		indexData[7] = 0;

		//Top face
		indexData[8] = 4;
		indexData[9] = 6;
		indexData[10] = 6;
		indexData[11] = 7;
		indexData[12] = 7;
		indexData[13] = 5;
		indexData[14] = 5;
		indexData[15] = 4;

		//Front face
		indexData[16] = 0;
		indexData[17] = 4;
		indexData[18] = 1;
		indexData[19] = 5;

		//Back face
		indexData[20] = 2;
		indexData[21] = 6;
		indexData[22] = 3;
		indexData[23] = 7;

		//Index buffer
		indexBuffer = GuiController::Instance->renderer->createTgcIndexBufferInstance();
		indexBuffer->create(INDEX_COUNT, indexData);

		//Effect
		effect = GuiController::Instance->shaders->generalPositionColor;
		effect->init(vertexBuffer);
	}
	
	//Update vertex values
	this->vertices[0] = VertexFormat::PositionColor(pMin, renderColor);
	this->vertices[1] = VertexFormat::PositionColor(Vector3(pMax.X, pMin.Y, pMin.Z), renderColor);
	this->vertices[2] = VertexFormat::PositionColor(Vector3(pMin.X, pMin.Y, pMax.Z), renderColor);
	this->vertices[3] = VertexFormat::PositionColor(Vector3(pMax.X, pMin.Y, pMax.Z), renderColor);
	this->vertices[4] = VertexFormat::PositionColor(Vector3(pMin.X, pMax.Y, pMin.Z), renderColor);
	this->vertices[5] = VertexFormat::PositionColor(Vector3(pMax.X, pMax.Y, pMin.Z), renderColor);
	this->vertices[6] = VertexFormat::PositionColor(Vector3(pMin.X, pMax.Y, pMax.Z), renderColor);
	this->vertices[7] = VertexFormat::PositionColor(pMax, renderColor);
	this->vertexBuffer->update(this->vertices);
	

	this->dirtyValues = false;
}

void TgcBoundingBox::render()
{
	TgcRenderer* renderer = GuiController::Instance->renderer;

	//Auto update values
	if (dirtyValues)
    {
        updateValues();
    }

	GuiController::Instance->shaders->setShaderMatrixIdentity(this->effect);

	renderer->setVertexBuffer(this->vertexBuffer);
	renderer->setIndexBuffer(this->indexBuffer);

	effect->begin();
	renderer->drawIndexed(PrimitiveTopology::LineList, INDEX_COUNT);
	effect->end();
}

void TgcBoundingBox::dispose()
{
	if(this->vertexBuffer != NULL)
	{
		this->vertexBuffer->dispose();
		this->indexBuffer->dispose();
	}
}

void TgcBoundingBox::scaleTranslate(Vector3 position, Vector3 scale)
{
    pMin.X = pMinOriginal.X * scale.X + position.X;
    pMin.Y = pMinOriginal.Y * scale.Y + position.Y;
    pMin.Z = pMinOriginal.Z * scale.Z + position.Z;

    pMax.X = pMaxOriginal.X * scale.X + position.X;
    pMax.Y = pMaxOriginal.Y * scale.Y + position.Y;
    pMax.Z = pMaxOriginal.Z * scale.Z + position.Z;

    dirtyValues = true;
}

float TgcBoundingBox::computeBoxRadiusSquare()
{
	return Vector3((pMax - pMin) * 0.5f).lengthSq();
}

float TgcBoundingBox::computeBoxRadius()
{
	return FastMath::sqrt(this->computeBoxRadiusSquare());
}

Vector3 TgcBoundingBox::computeBoxCenter()
{
    return pMin + computeExtents();
}

Vector3 TgcBoundingBox::computeSize()
{
    return pMax - pMin;
}

Vector3 TgcBoundingBox::computeExtents()
{
    return computeSize() * 0.5f;
}

void TgcBoundingBox::move(Vector3 movement)
{
    pMin += movement;
    pMax += movement;

    dirtyValues = true;
}