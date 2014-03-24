/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "Examples/ExampleOCEngine1/ExampleCreateRawSceneXML.h"
using namespace Examples;





string ExampleCreateRawSceneXML::getCategory()
{
	return "Occlusion";
}

string ExampleCreateRawSceneXML::getName()
{
	return "ExampleCreateRawSceneXML";
}

string ExampleCreateRawSceneXML::getDescription()
{
	return "ExampleCreateRawSceneXML";
}


void ExampleCreateRawSceneXML::init()
{
	//Load 3D scene data (only parser)
	string filePath = GuiController::Instance->examplesMediaPath + "TgcModels\\NormalMapRoom2\\NormalMapRoom2-TgcScene.xml";
	string outputPath = GuiController::Instance->examplesMediaPath + "TgcModels\\NormalMapRoom2\\raw-scene.xml";

	string mediaPath = filePath.substr(0, filePath.find_last_of('\\') + 1);
	TgcSceneParser parser;
	TgcSceneData* sceneData = parser.parseSceneFromFile(filePath);


	//Create XML file
	xml_document doc;
	xml_node root = doc.append_child("janua_scene");
	xml_node meshesNode = root.append_child("meshes");
	meshesNode.append_attribute("count").set_value(sceneData->meshCount);

	//Add meshes to XML
	for(int i = 0; i < sceneData->meshCount; i++)
	{
		TgcMeshData* meshData = sceneData->meshesData[i];
		int vertexRawDataCount = meshData->coordinatesIndicesCount * 3;
		int triCount = meshData->coordinatesIndicesCount / 3;
		float* rawVertexData = new float[vertexRawDataCount];

		//vertex array
		int idx = 0;
		for(int j = 0; j < meshData->coordinatesIndicesCount; j++)
		{
			int vIdx = meshData->coordinatesIndices[j];
			rawVertexData[idx++] = meshData->verticesCoordinates[vIdx * 3];
			rawVertexData[idx++] = meshData->verticesCoordinates[vIdx * 3 + 1];
			rawVertexData[idx++] = meshData->verticesCoordinates[vIdx * 3 + 2];
		}

		//vertex string array
		stringstream vertexStream;
		for(int j = 0; j < vertexRawDataCount; j++)
		{
			vertexStream << rawVertexData[j] << " ";
		}

		//Mesh node
		xml_node meshNode = meshesNode.append_child("m");
		meshNode.append_attribute("id").set_value(i);
		meshNode.append_attribute("triCount").set_value(triCount);
		meshNode.append_child(node_pcdata).set_value(vertexStream.str().c_str());

		//Type
		if(TgcParserUtils::toUpper(meshData->layerName) == "OCCLUDER")
		{
			meshNode.append_attribute("type").set_value("OCCLUDER");
		}
		else
		{
			meshNode.append_attribute("type").set_value("OCCLUDEE");
		}

		
		delete[] rawVertexData;
	}
	delete sceneData;



	//Guardar XML
	doc.save_file(outputPath.c_str());

}



void ExampleCreateRawSceneXML::render(float elapsedTime)
{
}

void ExampleCreateRawSceneXML::close()
{
}



