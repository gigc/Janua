/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "Examples/ExampleOCEngine1/Voxel.h"
using namespace Examples;


///////////////////////////////////// Voxel /////////////////////////////////////////

Voxel::Voxel()
{
}

Voxel::Voxel(Vector3 center, Vector3 size)
{
	this->center = center;
	this->size = size;
}

void Voxel::setExtremes(Vector3 min, Vector3 max)
{
	this->size = max - min;
	this->center = min + this->size * 0.5f;
}

///////////////////////////////////// VoxelGroup /////////////////////////////////////////

VoxelGroup::VoxelGroup()
{
	drawVoxels = true;
	drawAABB = true;
	alphaBlendEnabled = true;
}

void VoxelGroup::create()
{
	//input layout
	TgcInputLayout* inputLayout = GuiController::Instance->renderer->createTgcInputLayoutInstance();
	inputLayout->elements.push_back(InputElement::Element(InputElement::Position, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Color, InputElement::Float4, 0));
	inputLayout->create();

	//Data for each voxel
	totalVertices = VERTEX_COUNT * voxels.size();
	totalIndices = INDEX_COUNT * voxels.size();
	totalBBIndices = BB_INDEX_COUNT * voxels.size();
	VertexFormat::PositionColor* vertices = new VertexFormat::PositionColor[totalVertices];
	VertexFormat::PositionColor* bbVertices = new VertexFormat::PositionColor[totalVertices];
	unsigned long* indexData = new unsigned long[totalIndices];
	unsigned long* bbIndexData = new unsigned long[totalBBIndices];
	int vIdx = 0;
	int iIdx = 0;
	int vBBIdx = 0;
	int iBBIdx = 0;
	int voxelIndex;
	for(unsigned int i = 0; i < voxels.size(); i++)
	{
		Voxel* v = voxels[i];
		Vector3 c = v->center;
		Vector3 e = v->size * 0.5f;
		voxelIndex = i * 8;
		
		//vertex data
		Color col = randomAdaptColor(color);
		vertices[vIdx++] = VertexFormat::PositionColor(Vector3(c.X - e.X, c.Y - e.Y, c.Z - e.Z), col);
		vertices[vIdx++] = VertexFormat::PositionColor(Vector3(c.X + e.X, c.Y - e.Y, c.Z - e.Z), col);
		vertices[vIdx++] = VertexFormat::PositionColor(Vector3(c.X - e.X, c.Y - e.Y, c.Z + e.Z), col);
		vertices[vIdx++] = VertexFormat::PositionColor(Vector3(c.X + e.X, c.Y - e.Y, c.Z + e.Z), col);

		vertices[vIdx++] = VertexFormat::PositionColor(Vector3(c.X - e.X, c.Y + e.Y, c.Z - e.Z), col);
		vertices[vIdx++] = VertexFormat::PositionColor(Vector3(c.X + e.X, c.Y + e.Y, c.Z - e.Z), col);
		vertices[vIdx++] = VertexFormat::PositionColor(Vector3(c.X - e.X, c.Y + e.Y, c.Z + e.Z), col);
		vertices[vIdx++] = VertexFormat::PositionColor(Vector3(c.X + e.X, c.Y + e.Y, c.Z + e.Z), col);


		//Index buffer data
		//Bottom face
		indexData[iIdx++] = 0 + voxelIndex;
		indexData[iIdx++] = 1 + voxelIndex;
		indexData[iIdx++] = 3 + voxelIndex;
		indexData[iIdx++] = 3 + voxelIndex;
		indexData[iIdx++] = 2 + voxelIndex;
		indexData[iIdx++] = 0 + voxelIndex;

		//Top face
		indexData[iIdx++] = 4 + voxelIndex;
		indexData[iIdx++] = 6 + voxelIndex;
		indexData[iIdx++] = 7 + voxelIndex;
		indexData[iIdx++] = 7 + voxelIndex;
		indexData[iIdx++] = 5 + voxelIndex;
		indexData[iIdx++] = 4 + voxelIndex;

		//Back face
		indexData[iIdx++] = 2 + voxelIndex;
		indexData[iIdx++] = 3 + voxelIndex;
		indexData[iIdx++] = 7 + voxelIndex;
		indexData[iIdx++] = 7 + voxelIndex;
		indexData[iIdx++] = 6 + voxelIndex;
		indexData[iIdx++] = 2 + voxelIndex;

		//Front face
		indexData[iIdx++] = 0 + voxelIndex;
		indexData[iIdx++] = 4 + voxelIndex;
		indexData[iIdx++] = 5 + voxelIndex;
		indexData[iIdx++] = 5 + voxelIndex;
		indexData[iIdx++] = 1 + voxelIndex;
		indexData[iIdx++] = 0 + voxelIndex;

		//Left face
		indexData[iIdx++] = 0 + voxelIndex;
		indexData[iIdx++] = 2 + voxelIndex;
		indexData[iIdx++] = 6 + voxelIndex;
		indexData[iIdx++] = 6 + voxelIndex;
		indexData[iIdx++] = 4 + voxelIndex;
		indexData[iIdx++] = 0 + voxelIndex;

		//Right face
		indexData[iIdx++] = 1 + voxelIndex;
		indexData[iIdx++] = 5 + voxelIndex;
		indexData[iIdx++] = 7 + voxelIndex;
		indexData[iIdx++] = 7 + voxelIndex;
		indexData[iIdx++] = 3 + voxelIndex;
		indexData[iIdx++] = 1 + voxelIndex;



		//vertex data for BB
		bbVertices[vBBIdx++] = VertexFormat::PositionColor(Vector3(c.X - e.X, c.Y - e.Y, c.Z - e.Z), bbColor);
		bbVertices[vBBIdx++] = VertexFormat::PositionColor(Vector3(c.X + e.X, c.Y - e.Y, c.Z - e.Z), bbColor);
		bbVertices[vBBIdx++] = VertexFormat::PositionColor(Vector3(c.X - e.X, c.Y - e.Y, c.Z + e.Z), bbColor);
		bbVertices[vBBIdx++] = VertexFormat::PositionColor(Vector3(c.X + e.X, c.Y - e.Y, c.Z + e.Z), bbColor);

		bbVertices[vBBIdx++] = VertexFormat::PositionColor(Vector3(c.X - e.X, c.Y + e.Y, c.Z - e.Z), bbColor);
		bbVertices[vBBIdx++] = VertexFormat::PositionColor(Vector3(c.X + e.X, c.Y + e.Y, c.Z - e.Z), bbColor);
		bbVertices[vBBIdx++] = VertexFormat::PositionColor(Vector3(c.X - e.X, c.Y + e.Y, c.Z + e.Z), bbColor);
		bbVertices[vBBIdx++] = VertexFormat::PositionColor(Vector3(c.X + e.X, c.Y + e.Y, c.Z + e.Z), bbColor);


		//Index buffer data for BB
		//Bottom face
		bbIndexData[iBBIdx++] = 0 + voxelIndex;
		bbIndexData[iBBIdx++] = 1 + voxelIndex;
		bbIndexData[iBBIdx++] = 1 + voxelIndex;
		bbIndexData[iBBIdx++] = 3 + voxelIndex;
		bbIndexData[iBBIdx++] = 3 + voxelIndex;
		bbIndexData[iBBIdx++] = 2 + voxelIndex;
		bbIndexData[iBBIdx++] = 2 + voxelIndex;
		bbIndexData[iBBIdx++] = 0 + voxelIndex;

		//Top face
		bbIndexData[iBBIdx++] = 4 + voxelIndex;
		bbIndexData[iBBIdx++] = 6 + voxelIndex;
		bbIndexData[iBBIdx++] = 6 + voxelIndex;
		bbIndexData[iBBIdx++] = 7 + voxelIndex;
		bbIndexData[iBBIdx++] = 7 + voxelIndex;
		bbIndexData[iBBIdx++] = 5 + voxelIndex;
		bbIndexData[iBBIdx++] = 5 + voxelIndex;
		bbIndexData[iBBIdx++] = 4 + voxelIndex;

		//Front face
		bbIndexData[iBBIdx++] = 0 + voxelIndex;
		bbIndexData[iBBIdx++] = 4 + voxelIndex;
		bbIndexData[iBBIdx++] = 1 + voxelIndex;
		bbIndexData[iBBIdx++] = 5 + voxelIndex;

		//Back face
		bbIndexData[iBBIdx++] = 2 + voxelIndex;
		bbIndexData[iBBIdx++] = 6 + voxelIndex;
		bbIndexData[iBBIdx++] = 3 + voxelIndex;
		bbIndexData[iBBIdx++] = 7 + voxelIndex;
	}

	//VertexBuffer
	vertexBuffer = GuiController::Instance->renderer->createTgcVertexBufferInstance();
	vertexBuffer->create(totalVertices, inputLayout, vertices, BufferUsage::Default);
	delete[] vertices;

	//VertexBuffer for BB
	bbVertexBuffer = GuiController::Instance->renderer->createTgcVertexBufferInstance();
	bbVertexBuffer->create(totalVertices, inputLayout, bbVertices, BufferUsage::Default);
	delete[] bbVertices;

	//IndexBuffer
	indexBuffer = GuiController::Instance->renderer->createTgcIndexBufferInstance();
	indexBuffer->create(totalIndices, indexData);
	delete[] indexData;

	//Index buffer for BB
	bbIndexBuffer = GuiController::Instance->renderer->createTgcIndexBufferInstance();
	bbIndexBuffer->create(totalBBIndices, bbIndexData);
	delete[] bbIndexData;

	//Shader
	this->effect = GuiController::Instance->shaders->generalPositionColor;
	this->effect->init(this->vertexBuffer);
}

void VoxelGroup::render()
{
	TgcRenderer* renderer = GuiController::Instance->renderer;


	if(alphaBlendEnabled)
	{
		renderer->enableAlphaBlending(true);
	}

	effect->begin();

	GuiController::Instance->shaders->setShaderMatrixIdentity(this->effect);

	//Draw group of voxels
	if(drawVoxels)
	{
		renderer->setVertexBuffer(this->vertexBuffer);
		renderer->setIndexBuffer(this->indexBuffer);
		renderer->drawIndexed(PrimitiveTopology::TriangleList, totalIndices);
	}
	

	//Draw group of bounding boxes
	if(drawAABB)
	{
		renderer->setVertexBuffer(this->bbVertexBuffer);
		renderer->setIndexBuffer(this->bbIndexBuffer);
		renderer->drawIndexed(PrimitiveTopology::LineList, totalBBIndices);
	}
	
	effect->end();

	if(alphaBlendEnabled)
	{
		renderer->enableAlphaBlending(false);
	}
}

void VoxelGroup::dispose()
{
	for(unsigned int i = 0; i < voxels.size(); i++)
	{
		delete voxels[i];
	}

	vertexBuffer->dispose();
	indexBuffer->dispose();
	bbVertexBuffer->dispose();
	bbIndexBuffer->dispose();
}

Color VoxelGroup::randomAdaptColor(const Color &c)
{
	float r = FastMath::random(1, 150) / 255.0f;
	return Color(
		FastMath::minf(c.R + r, 1), 
		FastMath::minf(c.G + r, 1), 
		FastMath::minf(c.B + r, 1), 
		c.A);
}