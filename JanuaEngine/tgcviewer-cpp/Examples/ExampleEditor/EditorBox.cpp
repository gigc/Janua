/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "Examples/ExampleEditor/EditorBox.h"
#include "Examples/ExampleEditor/BorderBox.h"
using namespace TgcViewer;
using namespace Examples;


EditorBox::EditorBox()
{
}


EditorBox::EditorBox(const EditorBox& other)
{
}


EditorBox::~EditorBox()
{
}

void EditorBox::create()
{
	selectedFace = EditorBox::None;
	selected = false;

	border = new BorderBox();
	border->create();

	//input layout
	TgcInputLayout* inputLayout = GuiController::Instance->renderer->createTgcInputLayoutInstance();
	inputLayout->elements.push_back(InputElement::Element(InputElement::Position, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Normal, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Color, InputElement::Float4, 0));
	inputLayout->create();

	//Vertex buffer
	vertexBuffer = GuiController::Instance->renderer->createTgcVertexBufferInstance();
	VertexType::VertexColor* vertexData = new VertexType::VertexColor[VERTEX_COUNT];
	vertexBuffer->create(VERTEX_COUNT, inputLayout, vertexData, BufferUsage::Dynamic);
	delete[] vertexData;
	updateValues();


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

void EditorBox::setExtremes(Vector3 min, Vector3 max)
{
	this->size = max - min;
	Vector3 extents = size / 2;
	this->position = min + extents;
}

void EditorBox::updateValues()
{
    float x = size.X / 2;
    float y = size.Y / 2;
    float z = size.Z / 2;
	Color faceColor;

	aabb.min = Vector3(position.X - x, position.Y - y, position.Z - z);
	aabb.max = Vector3(position.X + x, position.Y + y, position.Z + z);

	border->pMin = aabb.min;
	border->pMax = aabb.max;
	border->color = selected ? Color::fromRGB(255, 165, 0) : Color::fromRGB(139, 139, 131);
	border->thickness = 0.2f;
	border->updateValues();

	VertexType::VertexColor* vertexData = (VertexType::VertexColor*)this->vertexBuffer->map(BufferMap::WriteDiscard);


	// Front face
	faceColor = selectedFace == EditorBox::Front ? this->selectedColor : this->commonColor;
	vertexData[0] = VertexType::VertexColor(Vector3(-x, y, z), Vector3(0, 0, 1), faceColor);
	vertexData[1] = VertexType::VertexColor(Vector3(-x, -y, z), Vector3(0, 0, 1), faceColor);
	vertexData[2] = VertexType::VertexColor(Vector3(x, y, z), Vector3(0, 0, 1), faceColor);
	vertexData[3] = VertexType::VertexColor(Vector3(-x, -y, z), Vector3(0, 0, 1), faceColor);
	vertexData[4] = VertexType::VertexColor(Vector3(x, -y, z), Vector3(0, 0, 1), faceColor);
	vertexData[5] = VertexType::VertexColor(Vector3(x, y, z), Vector3(0, 0, 1), faceColor);
	
	// Back face (remember this is facing *away* from the camera, so vertices should be clockwise order)
	faceColor = selectedFace == EditorBox::Back ? this->selectedColor : this->commonColor;
	vertexData[6] = VertexType::VertexColor(Vector3(-x, y, -z), Vector3(0, 0, -1), faceColor);
	vertexData[7] = VertexType::VertexColor(Vector3(x, y, -z), Vector3(0, 0, -1), faceColor);
	vertexData[8] = VertexType::VertexColor(Vector3(-x, -y, -z), Vector3(0, 0, -1), faceColor);
	vertexData[9] = VertexType::VertexColor(Vector3(-x, -y, -z), Vector3(0, 0, -1), faceColor);
	vertexData[10] = VertexType::VertexColor(Vector3(x, y, -z), Vector3(0, 0, -1), faceColor);
	vertexData[11] = VertexType::VertexColor(Vector3(x, -y, -z), Vector3(0, 0, -1), faceColor);
	
	// Top face
	faceColor = selectedFace == EditorBox::Top ? this->selectedColor : this->commonColor;
	vertexData[12] = VertexType::VertexColor(Vector3(-x, y, z), Vector3(0, 1, 0), faceColor);
	vertexData[13] = VertexType::VertexColor(Vector3(x, y, -z), Vector3(0, 1, 0), faceColor);
	vertexData[14] = VertexType::VertexColor(Vector3(-x, y, -z), Vector3(0, 1, 0), faceColor);
	vertexData[15] = VertexType::VertexColor(Vector3(-x, y, z), Vector3(0, 1, 0), faceColor);
	vertexData[16] = VertexType::VertexColor(Vector3(x, y, z), Vector3(0, 1, 0), faceColor);
	vertexData[17] = VertexType::VertexColor(Vector3(x, y, -z), Vector3(0, 1, 0), faceColor);

	// Bottom face (remember this is facing *away* from the camera, so vertices should be clockwise order)
	faceColor = selectedFace == EditorBox::Bottom ? this->selectedColor : this->commonColor;
	vertexData[18] = VertexType::VertexColor(Vector3(-x, -y, z), Vector3(0, -1, 0), faceColor);
	vertexData[19] = VertexType::VertexColor(Vector3(-x, -y, -z), Vector3(0, -1, 0), faceColor);
	vertexData[20] = VertexType::VertexColor(Vector3(x, -y, -z), Vector3(0, -1, 0), faceColor);
	vertexData[21] = VertexType::VertexColor(Vector3(-x, -y, z), Vector3(0, -1, 0), faceColor);
	vertexData[22] = VertexType::VertexColor(Vector3(x, -y, -z), Vector3(0, -1, 0), faceColor);
	vertexData[23] = VertexType::VertexColor(Vector3(x, -y, z), Vector3(0, -1, 0), faceColor);

	// Left face
	faceColor = selectedFace == EditorBox::Left ? this->selectedColor : this->commonColor;
	vertexData[24] = VertexType::VertexColor(Vector3(-x, y, z), Vector3(-1, 0, 0), faceColor);
	vertexData[25] = VertexType::VertexColor(Vector3(-x, -y, -z), Vector3(-1, 0, 0), faceColor);
	vertexData[26] = VertexType::VertexColor(Vector3(-x, -y, z), Vector3(-1, 0, 0), faceColor);
	vertexData[27] = VertexType::VertexColor(Vector3(-x, y, -z), Vector3(-1, 0, 0), faceColor);
	vertexData[28] = VertexType::VertexColor(Vector3(-x, -y, -z), Vector3(-1, 0, 0), faceColor);
	vertexData[29] = VertexType::VertexColor(Vector3(-x, y, z), Vector3(-1, 0, 0), faceColor);

	// Right face (remember this is facing *away* from the camera, so vertices should be clockwise order)
	faceColor = selectedFace == EditorBox::Right ? this->selectedColor : this->commonColor;
	vertexData[30] = VertexType::VertexColor(Vector3(x, y, z), Vector3(1, 0, 0), faceColor);
	vertexData[31] = VertexType::VertexColor(Vector3(x, -y, z), Vector3(1, 0, 0), faceColor);
	vertexData[32] = VertexType::VertexColor(Vector3(x, -y, -z), Vector3(1, 0, 0), faceColor);
	vertexData[33] = VertexType::VertexColor(Vector3(x, y, -z), Vector3(1, 0, 0), faceColor);
	vertexData[34] = VertexType::VertexColor(Vector3(x, y, z), Vector3(1, 0, 0), faceColor);
	vertexData[35] = VertexType::VertexColor(Vector3(x, -y, -z), Vector3(1, 0, 0), faceColor);


	this->vertexBuffer->unmap();
}

	

void EditorBox::render()
{
	TgcRenderer* renderer = GuiController::Instance->renderer;

	this->transform = Matrix4::Translation(this->position.X, this->position.Y, this->position.Z);
	GuiController::Instance->shaders->setShaderMatrix(this->effect, this->transform);

	renderer->setVertexBuffer(this->vertexBuffer);
	renderer->setIndexBuffer(this->indexBuffer);

	effect->begin();
	renderer->drawIndexed(PrimitiveTopology::TriangleList, VERTEX_COUNT);
	effect->end();



	border->render();
}


void EditorBox::dispose()
{
	vertexBuffer->dispose();
	indexBuffer->dispose();
}

AABB EditorBox::getFaceAABB(EditorBox::BoxFace face)
{
	AABB faceAABB;
	switch(face)
	{
	case EditorBox::Top:
		faceAABB.min = Vector3(aabb.min.X, aabb.max.Y, aabb.min.Z);
		faceAABB.max = Vector3(aabb.max.X, aabb.max.Y, aabb.max.Z);
		break;
	case EditorBox::Bottom:
		faceAABB.min = Vector3(aabb.min.X, aabb.min.Y, aabb.min.Z);
		faceAABB.max = Vector3(aabb.max.X, aabb.min.Y, aabb.max.Z);
		break;
	case EditorBox::Front:
		faceAABB.min = Vector3(aabb.min.X, aabb.min.Y, aabb.max.Z);
		faceAABB.max = Vector3(aabb.max.X, aabb.max.Y, aabb.max.Z);
		break;
	case EditorBox::Back:
		faceAABB.min = Vector3(aabb.min.X, aabb.min.Y, aabb.min.Z);
		faceAABB.max = Vector3(aabb.max.X, aabb.max.Y, aabb.min.Z);
		break;
	case EditorBox::Left:
		faceAABB.min = Vector3(aabb.min.X, aabb.min.Y, aabb.min.Z);
		faceAABB.max = Vector3(aabb.min.X, aabb.max.Y, aabb.max.Z);
		break;
	case EditorBox::Right:
		faceAABB.min = Vector3(aabb.max.X, aabb.min.Y, aabb.min.Z);
		faceAABB.max = Vector3(aabb.max.X, aabb.max.Y, aabb.max.Z);
		break;
	}
	return faceAABB;
}

EditorBox::BoxFace EditorBox::pickFace()
{
	PickingRay pickingRay;
	pickingRay.update();
	Vector3 q;
	float minDist = FastMath::MAX_FLOAT;
	EditorBox::BoxFace minFace = EditorBox::None;
	AABB faceAABB;

	for(int i = 0; i < 6; i++)
	{
		EditorBox::BoxFace face = (EditorBox::BoxFace)i;
		faceAABB = getFaceAABB(face);
		if(AABB::intersectRayAABB(pickingRay.ray, faceAABB, q))
		{
			float dist = Vector3(q - pickingRay.ray.origin).length();
			if(dist < minDist)
			{
				minDist = dist;
				minFace = face;
			}
		}
	}

	return minFace;
}