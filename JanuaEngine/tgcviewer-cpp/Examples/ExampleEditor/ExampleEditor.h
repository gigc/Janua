/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//Project Includes:
#include "Examples/TgcViewerIncludes.h"
#include "Examples/ExampleEditor/EditorBox.h"
#include "Examples/ExampleEditor/Grid.h"


namespace Examples
{


/**
* ExampleEditor 1
*/
class ExampleEditor : public TgcExample
{

public:

	enum EditorState
	{
		Nothing,
		CreatingBase,
		CreatingHeight,
		ObjectSelected,
		Translating,
		FaceSelected,
		Struding
	};

	//Virtual members
	string getCategory();
	string getName();
	string getDescription();
	void init();
	void render(float elapsedTime);
	void close();

private:

	Vector3 MIN_BOX_SIZE;
	float HEIGHT_MOVE_SPEED;
	float STRUDE_SPEED;
	float PAN_SPEED;
	float ZOOM_SPEED;
	float TRANSLATE_SPEED;


	EditorBox* pickObject();
	Vector3 groundPicking();
	void strudeBox(EditorBox* box, EditorBox::BoxFace face);
	void updateCamera();
	bool collisionWithBoxes(EditorBox* box);
	Vector3 vecMin(Vector3 a, Vector3 b);
	Vector3 vecMax(Vector3 a, Vector3 b);

public:

	EditorState currentState;
	vector<EditorBox*> boxes;
	Grid* grid;
	EditorBox* selectedFaceBox;
	EditorBox* selectedBox;

	EditorBox* creatingBox;
	Vector3 creatingBoxMin;
	Vector3 creatingBoxMax;

	Vector3 initTranslatingPos;

	Vector3 cameraPos;
	Vector3 cameraLookAt;

private:


	
};




}