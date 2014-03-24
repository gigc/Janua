/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/TgcGeometry/TgcBox.h"
using namespace TgcViewer;

TgcBox* TgcBox::fromSize(Vector3 center, Vector3 size)
{
	TgcBox* box = new TgcBox();
    box->setPositionSize(center, size);
    box->updateValues();
    return box;
}

TgcBox* TgcBox::fromSize(Vector3 center, Vector3 size, Color color)
{
	TgcBox* box = new TgcBox();
    box->setPositionSize(center, size);
    box->color = color;
    box->updateValues();
    return box;
}

TgcBox* TgcBox::fromSize(Vector3 center, Vector3 size, TgcTexture* texture)
{
	TgcBox* box = TgcBox::fromSize(center, size);
    box->setTexture(texture);
    return box;
}

TgcBox* TgcBox::fromSize(Vector3 size)
{
	return TgcBox::fromSize(Vector3(0, 0, 0), size);
}

TgcBox* TgcBox::fromSize(Vector3 size, Color color)
{
	return TgcBox::fromSize(Vector3(0, 0, 0), size, color);
}

TgcBox* TgcBox::fromSize(Vector3 size, TgcTexture* texture)
{
	return TgcBox::fromSize(Vector3(0, 0, 0), size, texture);
}

TgcBox* TgcBox::fromExtremes(Vector3 pMin, Vector3 pMax)
{
	Vector3 size = pMax - pMin;
	Vector3 midSize = size * 0.5f;
	Vector3 center = pMin + midSize;
	return TgcBox::fromSize(center, size);
}

TgcBox* TgcBox::fromExtremes(Vector3 pMin, Vector3 pMax, Color color)
{
	TgcBox* box = TgcBox::fromExtremes(pMin, pMax);
	box->color = color;
	box->updateValues();
	return box;
}
TgcBox* TgcBox::fromExtremes(Vector3 pMin, Vector3 pMax, TgcTexture* texture)
{
	TgcBox* box = TgcBox::fromExtremes(pMin, pMax);
	box->setTexture(texture);
	return box;
}




TgcBox::TgcBox()
{
	this->autoTransformEnable = true;
    this->transform = Matrix4::Identity();
    this->position = Vector3(0,0,0);
    this->rotation = Vector3(0,0,0);
	this->size = Vector3(1,1,1);
    this->enabled = true;
    this->color = Color::White;
    this->alphaBlendEnable = false;
    this->uvOffset = Vector2(0, 0);
    this->uvTiling = Vector2(1, 1);
	this->texture = NULL;
	this->autoUpdateBoundingBox = true;

    //BoundingBox
    this->boundingBox = new TgcBoundingBox();

	//input layout
	TgcInputLayout* inputLayout = GuiController::Instance->renderer->createTgcInputLayoutInstance();
	inputLayout->elements.push_back(InputElement::Element(InputElement::Position, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Color, InputElement::Float4, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Texcoord, InputElement::Float2, 0));
	inputLayout->create();

	//Vertex buffer
	VertexFormat::PositionColorTexcoord vertices[VERTEX_COUNT];
	vertexBuffer = GuiController::Instance->renderer->createTgcVertexBufferInstance();
	vertexBuffer->create(VERTEX_COUNT, inputLayout, vertices, BufferUsage::Dynamic);

	//Index buffer
	unsigned long indexData[VERTEX_COUNT];
    for (int i = 0; i < VERTEX_COUNT; i++)
    {
        indexData[i] = i;
    }
	indexBuffer = GuiController::Instance->renderer->createTgcIndexBufferInstance();
	indexBuffer->create(VERTEX_COUNT, indexData);

	//Shader
	this->effect = GuiController::Instance->shaders->generalPositionColorTexcoordNoTexture;
	this->effect->init(this->vertexBuffer);
}


TgcBox::TgcBox(const TgcBox& other)
{
}


TgcBox::~TgcBox()
{
}


void TgcBox::updateValues()
{
	float x = size.X / 2;
    float y = size.Y / 2;
    float z = size.Z / 2;
	float u = uvTiling.X;
    float v = uvTiling.Y;
    float offsetU = uvOffset.X;
    float offsetV = uvOffset.Y;

	VertexFormat::PositionColorTexcoord* vertexData = (VertexFormat::PositionColorTexcoord*)this->vertexBuffer->map(BufferMap::WriteDiscard);

	// Front face
	vertexData[0] = VertexFormat::PositionColorTexcoord(Vector3(-x, y, z), color, Vector2(offsetU, offsetV));
	vertexData[1] = VertexFormat::PositionColorTexcoord(Vector3(-x, -y, z), color, Vector2(offsetU, offsetV + v));
	vertexData[2] = VertexFormat::PositionColorTexcoord(Vector3(x, y, z), color, Vector2(offsetU + u, offsetV));
	vertexData[3] = VertexFormat::PositionColorTexcoord(Vector3(-x, -y, z), color, Vector2(offsetU, offsetV + v));
	vertexData[4] = VertexFormat::PositionColorTexcoord(Vector3(x, -y, z), color, Vector2(offsetU + u, offsetV + v));
	vertexData[5] = VertexFormat::PositionColorTexcoord(Vector3(x, y, z), color, Vector2(offsetU + u, offsetV));
	
	// Back face (remember this is facing *away* from the camera, so vertices should be clockwise order)
	vertexData[6] = VertexFormat::PositionColorTexcoord(Vector3(-x, y, -z), color, Vector2(offsetU, offsetV));
	vertexData[7] = VertexFormat::PositionColorTexcoord(Vector3(x, y, -z), color, Vector2(offsetU + u, offsetV));
	vertexData[8] = VertexFormat::PositionColorTexcoord(Vector3(-x, -y, -z), color, Vector2(offsetU, offsetV + v));
	vertexData[9] = VertexFormat::PositionColorTexcoord(Vector3(-x, -y, -z), color, Vector2(offsetU, offsetV + v));
	vertexData[10] = VertexFormat::PositionColorTexcoord(Vector3(x, y, -z), color, Vector2(offsetU + u, offsetV));
	vertexData[11] = VertexFormat::PositionColorTexcoord(Vector3(x, -y, -z), color, Vector2(offsetU + u, offsetV + v));
	
	// Top face
	vertexData[12] = VertexFormat::PositionColorTexcoord(Vector3(-x, y, z), color, Vector2(offsetU, offsetV));
	vertexData[13] = VertexFormat::PositionColorTexcoord(Vector3(x, y, -z), color, Vector2(offsetU + u, offsetV + v));
	vertexData[14] = VertexFormat::PositionColorTexcoord(Vector3(-x, y, -z), color, Vector2(offsetU, offsetV + v));
	vertexData[15] = VertexFormat::PositionColorTexcoord(Vector3(-x, y, z), color, Vector2(offsetU, offsetV));
	vertexData[16] = VertexFormat::PositionColorTexcoord(Vector3(x, y, z), color, Vector2(offsetU + u, offsetV));
	vertexData[17] = VertexFormat::PositionColorTexcoord(Vector3(x, y, -z), color, Vector2(offsetU + u, offsetV + v));

	// Bottom face (remember this is facing *away* from the camera, so vertices should be clockwise order)
	vertexData[18] = VertexFormat::PositionColorTexcoord(Vector3(-x, -y, z), color, Vector2(offsetU, offsetV));
	vertexData[19] = VertexFormat::PositionColorTexcoord(Vector3(-x, -y, -z), color, Vector2(offsetU, offsetV + v));
	vertexData[20] = VertexFormat::PositionColorTexcoord(Vector3(x, -y, -z), color, Vector2(offsetU + u, offsetV + v));
	vertexData[21] = VertexFormat::PositionColorTexcoord(Vector3(-x, -y, z), color, Vector2(offsetU, offsetV));
	vertexData[22] = VertexFormat::PositionColorTexcoord(Vector3(x, -y, -z), color, Vector2(offsetU + u, offsetV + v));
	vertexData[23] = VertexFormat::PositionColorTexcoord(Vector3(x, -y, z), color, Vector2(offsetU + u, offsetV));

	// Left face
	vertexData[24] = VertexFormat::PositionColorTexcoord(Vector3(-x, y, z), color, Vector2(offsetU, offsetV));
	vertexData[25] = VertexFormat::PositionColorTexcoord(Vector3(-x, -y, -z), color, Vector2(offsetU + u, offsetV + v));
	vertexData[26] = VertexFormat::PositionColorTexcoord(Vector3(-x, -y, z), color, Vector2(offsetU, offsetV + v));
	vertexData[27] = VertexFormat::PositionColorTexcoord(Vector3(-x, y, -z), color, Vector2(offsetU + u, offsetV));
	vertexData[28] = VertexFormat::PositionColorTexcoord(Vector3(-x, -y, -z), color, Vector2(offsetU + u, offsetV + v));
	vertexData[29] = VertexFormat::PositionColorTexcoord(Vector3(-x, y, z), color, Vector2(offsetU, offsetV));

	// Right face (remember this is facing *away* from the camera, so vertices should be clockwise order)
	vertexData[30] = VertexFormat::PositionColorTexcoord(Vector3(x, y, z), color, Vector2(offsetU, offsetV));
	vertexData[31] = VertexFormat::PositionColorTexcoord(Vector3(x, -y, z), color, Vector2(offsetU, offsetV + v));
	vertexData[32] = VertexFormat::PositionColorTexcoord(Vector3(x, -y, -z), color, Vector2(offsetU + u, offsetV + v));
	vertexData[33] = VertexFormat::PositionColorTexcoord(Vector3(x, y, -z), color, Vector2(offsetU + u, offsetV));
	vertexData[34] = VertexFormat::PositionColorTexcoord(Vector3(x, y, z), color, Vector2(offsetU, offsetV));
	vertexData[35] = VertexFormat::PositionColorTexcoord(Vector3(x, -y, -z), color, Vector2(offsetU + u, offsetV + v));


	this->vertexBuffer->unmap();
}


void TgcBox::render()
{
	if (!enabled)
		return;

	TgcRenderer* renderer = GuiController::Instance->renderer;

    if (autoTransformEnable)
    {
		this->transform = Matrix4::RotationYawPitchRoll(rotation.Y, rotation.X, rotation.Z) * Matrix4::Translation(position);
    }
	GuiController::Instance->shaders->setShaderMatrix(this->effect, this->transform);
	
	//activateAlphaBlend();

	renderer->setVertexBuffer(this->vertexBuffer);
	renderer->setIndexBuffer(this->indexBuffer);

	if(texture != NULL)
	{
		effect->setTexture("texDiffuseMap", texture);
	}

	effect->begin();
	renderer->drawIndexed(PrimitiveTopology::TriangleList, VERTEX_COUNT);
	effect->end();

	//resetAlphaBlend();
}


void TgcBox::dispose()
{
	vertexBuffer->dispose();
	indexBuffer->dispose();
	if(texture != NULL)
	{
		texture->dispose();
	}
}


void TgcBox::updateBoundingBox()
{
	Vector3 extents = this->size * 0.5f;
	this->boundingBox->setExtremes(this->position - extents, this->position + extents);
}

void TgcBox::setTexture(TgcTexture* texture)
{
	if(this->texture != NULL)
	{
		this->texture->dispose();
	}
	this->texture = texture;
	if(texture == NULL)
	{
		this->effect = GuiController::Instance->shaders->generalPositionColorTexcoordNoTexture;
	} 
	else 
	{
		this->effect = GuiController::Instance->shaders->generalPositionColorTexcoord;
	}
}

void TgcBox::setExtremes(Vector3 min, Vector3 max)
{
	Vector3 size = max - min;
    Vector3 midSize = size * 0.5f;
    Vector3 center = min + midSize;
    setPositionSize(center, size);
}

void TgcBox::setPositionSize(Vector3 position, Vector3 size)
{
	this->position = position;
	this->size = size;
	if(autoUpdateBoundingBox) this->updateBoundingBox();
}



void TgcBox::setPosition(float x, float y, float z)
{
	this->setPosition(Vector3(x, y, z));
}

void TgcBox::setPosition(Vector3 pos)
{
	this->position = pos;
	if(autoUpdateBoundingBox) this->updateBoundingBox();
}

void TgcBox::move(float x, float y, float z)
{
	this->move(Vector3(x, y, z));
}

void TgcBox::move(Vector3 movement)
{
	this->position += movement;
	if(autoUpdateBoundingBox) this->updateBoundingBox();
}

void TgcBox::moveOrientedY(float movement)
{
	float z = FastMath::cos(this->rotation.Y) * movement;
	float x = FastMath::sin(this->rotation.Y) * movement;
	this->move(x, 0, z);
}

void TgcBox::setRotation(float x, float y, float z)
{
	this->setRotation(Vector3(x, y, z));
}

void TgcBox::setRotation(Vector3 rot)
{
	this->rotation = rot;
	if(autoUpdateBoundingBox) this->updateBoundingBox();
}

void TgcBox::rotateX(float angle)
{
	this->rotate(Vector3(angle, 0, 0));
}

void TgcBox::rotateY(float angle)
{
	this->rotate(Vector3(0, angle, 0));
}

void TgcBox::rotateZ(float angle)
{
	this->rotate(Vector3(0, 0, angle));
}

void TgcBox::rotate(Vector3 rot)
{
	this->rotation += rot;
	if(autoUpdateBoundingBox) this->updateBoundingBox();
}