/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/TgcSceneLoader/TgcMesh.h"
using namespace TgcViewer;


TgcMesh::TgcMesh()
{
}

TgcMesh::TgcMesh(const TgcMesh& other)
{
}

TgcMesh::~TgcMesh()
{
}

void TgcMesh::initData(string name, TgcVertexBuffer* vertexBuffer, TgcIndexBuffer* indexBuffer, vector<int> subGroupsVertexCount, MeshValues::RenderType renderType)
{
    this->name = name;
    this->renderType = renderType;
    this->enabled = false;
    this->alphaBlendEnable = false;

	this->vertexBuffer = vertexBuffer;
	this->indexBuffer = indexBuffer;
	this->subGroupsVertexCount = subGroupsVertexCount;

    this->autoTransformEnable = true;
    this->autoUpdateBoundingBox = true;
    this->position = Vector3(0, 0, 0);
    this->rotation = Vector3(0, 0, 0);
    this->scale = Vector3(1, 1, 1);
	this->transform.Identity();

	//Comput sub-groups offsets
    this->subGroupsVertexOffset.push_back(0);
    for (unsigned int i = 1; i < this->subGroupsVertexCount.size(); i++) {
            this->subGroupsVertexOffset.push_back(this->subGroupsVertexOffset[i - 1] + this->subGroupsVertexCount[i - 1]);
    }

    //Default Shader
	this->effect = GuiController::Instance->shaders->getTgcMeshEffect(this->renderType);
	this->effect->init(this->vertexBuffer);
}


void TgcMesh::render()
{
	if (!enabled)
		return;

	TgcRenderer* renderer = GuiController::Instance->renderer;

	//Apply transforms
	updateMeshTransform();

	//Activate AlphaBlending
	//activateAlphaBlend();

	//Set common matrices for shader
	GuiController::Instance->shaders->setShaderMatrix(this->effect, this->transform);

	renderer->setVertexBuffer(this->vertexBuffer);
	renderer->setIndexBuffer(this->indexBuffer);

	effect->begin();
	switch (renderType)
    {
	case MeshValues::VertexColor:
			renderer->drawIndexed(PrimitiveTopology::TriangleList, subGroupsVertexCount[0], 0);
			break;

		case MeshValues::DiffuseMap:
			for(unsigned int i = 0; i < diffuseMaps.size(); i++)
			{
				effect->setTexture("texDiffuseMap", this->diffuseMaps[i]);
				renderer->drawIndexed(PrimitiveTopology::TriangleList, subGroupsVertexCount[i], subGroupsVertexOffset[i]);
			}
			break;

		case MeshValues::DiffuseMapAndLightmap:
			effect->setTexture("texLightMap", this->lightMap);
			for(unsigned int i = 0; i < diffuseMaps.size(); i++)
			{
				effect->setTexture("texDiffuseMap", this->diffuseMaps[i]);
				renderer->drawIndexed(PrimitiveTopology::TriangleList, subGroupsVertexCount[i], subGroupsVertexOffset[i]);
			}
			break;
	}
	effect->end();


	//Reset alphaBlend
	//activateAlphaBlend();
}

void TgcMesh::updateMeshTransform()
{
	//Compute mesh transform
    if (autoTransformEnable)
    {
		this->transform = Matrix4::Scale(scale.X, scale.Y, scale.Z)
            * Matrix4::RotationYawPitchRoll(rotation.Y, rotation.X, rotation.Z)
			* Matrix4::Translation(position.X, position.Y, position.Z);
    }
}

void TgcMesh::createBoundingBox(const TgcMeshData* meshData)
{
	vector<Vector3> points;
	int vertexCount = meshData->verticesCoordinatesCount / 3;
	for(int i = 0; i < vertexCount; i++)
	{
		points.push_back(Vector3(
			meshData->verticesCoordinates[i * 3], 
			meshData->verticesCoordinates[i * 3 + 1], 
			meshData->verticesCoordinates[i * 3 + 2]));
	}
	this->boundingBox = TgcBoundingBox::computeFromPoints(points);
}

void TgcMesh::dispose()
{
	vertexBuffer->dispose();
	delete vertexBuffer;

	indexBuffer->dispose();
	delete indexBuffer;

	for(unsigned int i = 0; i < diffuseMaps.size(); i++)
	{
		diffuseMaps[i]->dispose();
	}
}

void TgcMesh::updateBoundingBox()
{
	this->boundingBox->scaleTranslate(this->position, this->scale);
}

void TgcMesh::setPosition(float x, float y, float z)
{
	this->setPosition(Vector3(x, y, z));
}

void TgcMesh::setPosition(Vector3 pos)
{
	this->position = pos;
	if(autoUpdateBoundingBox) this->updateBoundingBox();
}

void TgcMesh::move(float x, float y, float z)
{
	this->move(Vector3(x, y, z));
}

void TgcMesh::move(Vector3 movement)
{
	this->position += movement;
	if(autoUpdateBoundingBox) this->updateBoundingBox();
}

void TgcMesh::moveOrientedY(float movement)
{
	float z = FastMath::cos(this->rotation.Y) * movement;
	float x = FastMath::sin(this->rotation.Y) * movement;
	this->move(x, 0, z);
}

void TgcMesh::setRotation(float x, float y, float z)
{
	this->setRotation(Vector3(x, y, z));
}

void TgcMesh::setRotation(Vector3 rot)
{
	this->rotation = rot;
	if(autoUpdateBoundingBox) this->updateBoundingBox();
}

void TgcMesh::rotateX(float angle)
{
	this->rotate(Vector3(angle, 0, 0));
}

void TgcMesh::rotateY(float angle)
{
	this->rotate(Vector3(0, angle, 0));
}

void TgcMesh::rotateZ(float angle)
{
	this->rotate(Vector3(0, 0, angle));
}

void TgcMesh::rotate(Vector3 rot)
{
	this->rotation += rot;
	if(autoUpdateBoundingBox) this->updateBoundingBox();
}


