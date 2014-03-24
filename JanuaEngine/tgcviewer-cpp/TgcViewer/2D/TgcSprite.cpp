/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer\2D\TgcSprite.h"
using namespace TgcViewer;


TgcSprite::TgcSprite()
{
	this->enabled = true;
	this->position = Vector2(0, 0);
	this->size = Vector2(0, 0);
	this->texture = NULL;
	this->enabled = true;
	this->color = Color::White;
}


TgcSprite::TgcSprite(const TgcSprite& other)
{
}


TgcSprite::~TgcSprite()
{
}

TgcSprite* create(string texturePath, Vector2 position)
{
	TgcSprite* sprite = new TgcSprite();
	sprite->texture = TgcTexture::createTexture(texturePath);
	sprite->position = position;
	sprite->size = sprite->texture->size();
	sprite->init();
	return sprite;
}

void TgcSprite::init()
{
	//input layout
	TgcInputLayout* inputLayout = GuiController::Instance->renderer->createTgcInputLayoutInstance();
	inputLayout->elements.push_back(InputElement::Element(InputElement::Position, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Texcoord, InputElement::Float2, 0));
	inputLayout->create();

	//Vertex buffer
	VertexFormat::PositionTexcoord vertices[4];
	vertexBuffer = GuiController::Instance->renderer->createTgcVertexBufferInstance();
	vertexBuffer->create(4, inputLayout, vertices, BufferUsage::Dynamic);

	//Index buffer
	unsigned long indexData[6];
    indexData[0] = 3;
	indexData[1] = 0;
	indexData[2] = 1;
	indexData[3] = 1;
	indexData[4] = 2;
	indexData[5] = 3;
	indexBuffer = GuiController::Instance->renderer->createTgcIndexBufferInstance();
	indexBuffer->create(6, indexData);

	//Shader
	this->effect = GuiController::Instance->shaders->generalTransformedPositionTexcoord;
	this->effect->init(this->vertexBuffer);

	//Update the first time
	this->updateValues();
}

void TgcSprite::updateValues()
{
	const int w = GuiController::Instance->windowHandler->screenWidth;
	const int h = GuiController::Instance->windowHandler->screenHeight;

	//The 4 corners
	float left = this->position.X;
	float right = left + this->size.X;
	float top = this->position.Y; 
	float bottom = top + this->size.Y;

	//UV coords
	Vector2 uvMin, uvMax;
	if(srcRect.empty())
	{
		uvMin = Vector2(0, 0);
		uvMax = Vector2(1, 1);
	}
	else
	{
		uvMin = Vector2(srcRect.x / this->texture->width, srcRect.y / this->texture->height);
		uvMax = Vector2((srcRect.x + srcRect.width) / this->texture->width, (srcRect.y + srcRect.height) / this->texture->height);
	}

	//Normalize to projected values: X left/right: [-1, 1], Y top/bottom: [1, -1]
	left = -1 + left * 2 / w;
	right = -1 + right * 2 / w;
	top = 1 - top * 2 / h;
	bottom = 1 - bottom * 2 / h;


	//Updates vertexBuffer data
	VertexFormat::PositionTexcoord* vertexData = (VertexFormat::PositionTexcoord*)this->vertexBuffer->map(BufferMap::WriteDiscard);
	vertexData[0] = VertexFormat::PositionTexcoord(Vector3(left, top, 1), uvMin);
	vertexData[1] = VertexFormat::PositionTexcoord(Vector3(right, top, 1), Vector2(uvMax.U, uvMin.V));
	vertexData[2] = VertexFormat::PositionTexcoord(Vector3(right, bottom, 1), uvMax);
	vertexData[3] = VertexFormat::PositionTexcoord(Vector3(left, bottom, 1), Vector2(uvMin.U, uvMax.V));
	this->vertexBuffer->unmap();
}

void TgcSprite::render()
{
	if (!enabled)
		return;

	TgcRenderer* renderer = GuiController::Instance->renderer;
	
	renderer->enableAlphaBlending(true);
	renderer->enableDepthTest(false);

	renderer->setVertexBuffer(this->vertexBuffer);
	renderer->setIndexBuffer(this->indexBuffer);
	effect->setTexture("texDiffuseMap", texture);
	TgcShadersCommon::InputColorBuffer inputColorBuffer;
	inputColorBuffer.inputColor = this->color;
	effect->setConstantBuffer("InputColorBuffer", &inputColorBuffer);

	effect->begin();
	renderer->drawIndexed(PrimitiveTopology::TriangleList, 6);
	effect->end();

	renderer->enableAlphaBlending(false);
	renderer->enableDepthTest(true);
}

void TgcSprite::dispose()
{
	vertexBuffer->dispose();
	indexBuffer->dispose();
	if(texture != NULL)
	{
		texture->dispose();
	}
}

void TgcSprite::setSrcRectFromTileIndex(int tileIndex, Vector2 tileSize)
{
	this->srcRect.x = (float)(tileIndex % (int)(this->texture->width / tileSize.X));
	this->srcRect.y = (float)(tileIndex / (int)(this->texture->height / tileSize.Y));
	this->srcRect.width = tileSize.X;
	this->srcRect.height = tileSize.Y;
}

bool TgcSprite::inside(const Vector2 p)
{
	return p.X >= position.X && p.X <= position.X + size.Width &&
		p.Y >= position.Y && p.Y <= position.Y + size.Height;
}