/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "Examples/ExampleEditor/ExampleEditor.h"
using namespace Examples;





string ExampleEditor::getCategory()
{
	return "Category";
}

string ExampleEditor::getName()
{
	return "ExampleEditor";
}

string ExampleEditor::getDescription()
{
	return "ExampleEditor";
}

void ExampleEditor::init()
{
	MIN_BOX_SIZE = Vector3(2, 2, 2);
	HEIGHT_MOVE_SPEED = 0.2f;
	STRUDE_SPEED = 0.1f;
	PAN_SPEED = 0.1f;
	ZOOM_SPEED = 1.0f;
	TRANSLATE_SPEED = 0.9f;
	
	cameraPos = Vector3(0, 70, -170);
	cameraLookAt = Vector3(0, 0, 0);

	GuiController::Instance->renderer->backgroundColor = Color::fromRGB(238, 221, 130);

	grid = new Grid();
	grid->create();

	creatingBox = new EditorBox();
	creatingBox->position = Vector3(0, 0, 0);
	creatingBox->size = Vector3(1, 1, 1);
	creatingBox->commonColor = Color::fromRGB(238, 238, 224);
	creatingBox->create();


	currentState = Nothing;
}

void ExampleEditor::render(float elapsedTime)
{
	updateCamera();



	//Update
	TgcInput* input = GuiController::Instance->input;
	switch(currentState)
	{
	case Nothing:
		if(input->buttonPress(TgcInput::BUTTON_LEFT))
		{
			EditorBox* pickedBox = pickObject();
			if(pickedBox != NULL)
			{
				selectedBox = pickedBox;
				selectedBox->selected = true;
				selectedBox->updateValues();
				currentState = ObjectSelected;
			}
		}
		else if(input->buttonDown(TgcInput::BUTTON_LEFT))
		{
			EditorBox* pickedBox = pickObject();
			if(pickedBox == NULL)
			{
				creatingBoxMin = groundPicking();
				creatingBoxMax = Vector3(creatingBoxMin.X, creatingBoxMin.Y + 5, creatingBoxMin.Z);
				creatingBox->setExtremes(creatingBoxMin, creatingBoxMax);
				creatingBox->selected = true;
				creatingBox->updateValues();

				currentState = CreatingBase;
			}
		}
		break;

	case CreatingBase:
		if(input->buttonDown(TgcInput::BUTTON_LEFT))
		{
			Vector3 q = groundPicking();
			creatingBoxMax = Vector3(q.X, q.Y + 0.5f, q.Z);
			creatingBox->setExtremes(creatingBoxMin, creatingBoxMax);
			creatingBox->updateValues();
		}
		else if(input->buttonUp(TgcInput::BUTTON_LEFT))
		{
			Vector3 diff = creatingBox->aabb.max - creatingBox->aabb.min;
			if(FastMath::abs(diff.X) > MIN_BOX_SIZE.X && FastMath::abs(diff.Z) > MIN_BOX_SIZE.Z)
			{
				currentState = CreatingHeight;
			}
			else
			{
				currentState = Nothing;
			}
			
		}
		break;

	case CreatingHeight:
		if(input->buttonPress(TgcInput::BUTTON_LEFT))
		{
			Vector3 diff = creatingBox->aabb.max - creatingBox->aabb.min;
			if(FastMath::abs(diff.Y) > MIN_BOX_SIZE.Y)
			{
				EditorBox* copyBox = new EditorBox();
				Vector3 copyMin = vecMin(creatingBox->aabb.min, creatingBox->aabb.max);
				Vector3 copyMax = vecMax(creatingBox->aabb.min, creatingBox->aabb.max);
				copyBox->setExtremes(copyMin, copyMax);
				copyBox->commonColor = creatingBox->commonColor;
				copyBox->selectedColor = Color::Red;
				copyBox->create();

				if(collisionWithBoxes(copyBox))
				{
					delete copyBox;
				}
				else
				{
					boxes.push_back(copyBox);
				}
			}
			currentState = Nothing;
		}
		else
		{
			float diffY = (float)input->deltaMouseY * HEIGHT_MOVE_SPEED;
			creatingBoxMax.Y += diffY;
			if(creatingBoxMax.Y < MIN_BOX_SIZE.Y)
			{
				creatingBoxMax.Y = MIN_BOX_SIZE.Y;
			}
			creatingBox->setExtremes(creatingBoxMin, creatingBoxMax);
			creatingBox->updateValues();
		}
		break;

	case ObjectSelected:
		if(input->buttonPress(TgcInput::BUTTON_LEFT))
		{
			EditorBox* pickedBox = pickObject();
			if(pickedBox != NULL)
			{
				if(pickedBox != selectedBox)
				{
					selectedBox->selected = false;
					selectedBox->selectedFace = EditorBox::None;
					selectedBox->updateValues();

					selectedBox = pickedBox;
					selectedBox->selected = true;
					selectedBox->updateValues();
				}
				else
				{
					EditorBox::BoxFace face = selectedBox->pickFace();
					selectedBox->selectedFace = face;
					selectedBox->updateValues();
					currentState = FaceSelected;
				}
			}
			else
			{
				selectedBox->selected = false;
				selectedBox->selectedFace = EditorBox::None;
				selectedBox->updateValues();
				selectedBox = NULL;
				currentState = Nothing;
			}
		}
		else if(input->buttonDown(TgcInput::BUTTON_LEFT))
		{
			EditorBox* pickedBox = pickObject();
			if(pickedBox != NULL && pickedBox == selectedBox)
			{
				initTranslatingPos = groundPicking();
				currentState = Translating;
			}
		}
		else if(input->keyPress(TgcInput::K_DELETE) || input->keyPress(TgcInput::K_BACK))
		{
			selectedBox->selected = false;
			selectedBox->selectedFace = EditorBox::None;
			selectedBox->updateValues();
			for(unsigned int i = 0; i < boxes.size(); i++)
			{
				if(boxes[i] == selectedBox)
				{
					boxes.erase(boxes.begin() + i);
					break;
				}
			}
			selectedBox->dispose();

			selectedBox = NULL;
			currentState = Nothing;
		}
		break;

	case Translating:
		if(input->buttonDown(TgcInput::BUTTON_LEFT))
		{
			Vector3 q = groundPicking();
			Vector3 diff = q - initTranslatingPos;
			selectedBox->position += Vector3(diff.X * TRANSLATE_SPEED, 0, diff.Z * TRANSLATE_SPEED);
			selectedBox->updateValues();
			initTranslatingPos = q;
		}
		else if(input->buttonUp(TgcInput::BUTTON_LEFT))
		{
			currentState = ObjectSelected;
		}
		break;

	case FaceSelected:
		if(input->buttonDown(TgcInput::BUTTON_LEFT))
		{
			EditorBox::BoxFace face = selectedBox->pickFace();
			if(face == EditorBox::None)
			{
				selectedBox->selected = false;
				selectedBox->selectedFace = EditorBox::None;
				selectedBox->updateValues();
				selectedBox = NULL;
				currentState = Nothing;
			}
			else if(face == selectedBox->selectedFace)
			{
				currentState = Struding;
			}
			else
			{
				selectedBox->selectedFace = EditorBox::None;
				selectedBox->updateValues();
				currentState = ObjectSelected;
			}
		}
		break;

	case Struding:
		if(input->buttonDown(TgcInput::BUTTON_LEFT))
		{
			strudeBox(selectedBox, selectedBox->selectedFace);
		} 
		else if(input->buttonUp(TgcInput::BUTTON_LEFT))
		{
			currentState = FaceSelected;
		}
		break;
	}








	//Render
	grid->render();
	if(currentState == CreatingBase || currentState == CreatingHeight)
	{
		creatingBox->render();
	}
	for(unsigned int i = 0; i < boxes.size(); i++)
	{
		boxes[i]->render();
	}

	
}


EditorBox* ExampleEditor::pickObject()
{
	float minDist = FastMath::MAX_FLOAT;
	EditorBox* minBox = NULL;
	PickingRay pickingRay;
	pickingRay.update();
	Vector3 q;

	for(unsigned int i = 0; i < boxes.size(); i++)
	{
		if(AABB::intersectRayAABB(pickingRay.ray, boxes[i]->aabb, q))
		{
			float dist = Vector3(q - pickingRay.ray.origin).length();
			if(dist < minDist)
			{
				minDist = dist;
				minBox = boxes[i];
			}
		}
	}

	return minBox;
}

Vector3 ExampleEditor::vecMin(Vector3 a, Vector3 b)
{
	return Vector3(FastMath::minf(a.X, b.X), FastMath::minf(a.Y, b.Y), FastMath::minf(a.Z, b.Z));
}


Vector3 ExampleEditor::vecMax(Vector3 a, Vector3 b)
{
	return Vector3(FastMath::maxf(a.X, b.X), FastMath::maxf(a.Y, b.Y), FastMath::maxf(a.Z, b.Z));
}


Vector3 ExampleEditor::groundPicking()
{
	PickingRay pickingRay;
	pickingRay.update();
	Vector3 q;
	AABB::intersectRayAABB(pickingRay.ray, grid->aabb, q);
	return q;
}

void ExampleEditor::close()
{
	grid->dispose();
	delete grid;

	for(unsigned int i = 0; i < boxes.size(); i++)
	{
		boxes[i]->dispose();
		delete boxes[i];
	}

	selectedBox = NULL;

	creatingBox->dispose();
	delete creatingBox;
}

void ExampleEditor::strudeBox(EditorBox* box, EditorBox::BoxFace face)
{
	Vector3 min = box->aabb.min;
	Vector3 max = box->aabb.max;
	float epsilon = 1.0f;
	float deltaX = GuiController::Instance->input->deltaMouseX * STRUDE_SPEED;
	float deltaY = GuiController::Instance->input->deltaMouseY * STRUDE_SPEED;

	switch(face)
	{
	case EditorBox::Top:
		max.Y += deltaY;
		max.Y = max.Y < min.Y + epsilon ? min.Y + epsilon : max.Y;
		break;
	case EditorBox::Bottom:
		min.Y -= deltaY;
		min.Y = max.Y > max.Y - epsilon ? max.Y - epsilon : min.Y;
		break;
	case EditorBox::Front:
		max.Z -= deltaY;
		max.Z = max.Z < min.Z + epsilon ? min.Z + epsilon : max.Z;
		break;
	case EditorBox::Back:
		min.Z += deltaY;
		min.Z = min.Z > max.Z - epsilon ? max.Z - epsilon : min.Z;
		break;
	case EditorBox::Left:
		min.X -= deltaX;
		min.X = min.X > max.X - epsilon ? max.X - epsilon : min.X;
		break;
	case EditorBox::Right:
		max.X -= deltaX;
		max.X = max.X < min.X + epsilon ? min.X + epsilon : max.X;
		break;
	}


	box->setExtremes(min, max);
	box->updateValues();
}


void ExampleEditor::updateCamera()
{
	TgcInput* input = GuiController::Instance->input;
	float deltaX = input->deltaMouseX * PAN_SPEED;
	float deltaY = input->deltaMouseY * PAN_SPEED;

	if(input->buttonDown(TgcInput::BUTTON_RIGHT) || input->buttonDown(TgcInput::BUTTON_MIDDLE))
	{
		cameraPos.X += deltaX;
		cameraPos.Z -= deltaY;
		cameraLookAt.X += deltaX;
		cameraLookAt.Z -= deltaY;
	}
	
	/* TODO: estudiar mejor el evento de mouse wheel de windows
	float scroll = input->mouseWheel * ZOOM_SPEED;
	cameraPos.Z = -170 + scroll;
	cameraPos.Y = 170 / 2 + scroll / 2;
	*/

	GuiController::Instance->renderer->viewMatrix = Matrix4::LookAtLH(cameraPos, cameraLookAt, Vector3(0, 1, 0));
}

bool ExampleEditor::collisionWithBoxes(EditorBox* box)
{
	for(unsigned int i = 0; i < boxes.size(); i++)
	{
		if(AABB::testAABBAABB(boxes[i]->aabb, box->aabb))
		{
			return true;
		}
	}
	return false;
}