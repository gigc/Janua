/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#pragma once


//General Includes:
#include <string>
#include <vector>
using namespace std;


//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/TgcSceneLoader/TgcSceneData.h"
#include "TgcViewer/TgcSceneLoader/TgcParserUtils.h"
#include "TgcViewer/Xml/pugixml.hpp"
using namespace pugi;

namespace TgcViewer
{


/**
* Parse an XML scene file of format tgcScene.xml.
* Retrieves an object representation of the scene.
*/
class TgcSceneParser
{

public:

	TgcSceneParser();
	TgcSceneParser(const TgcSceneParser&);
	~TgcSceneParser();


	/**
	* Loads a tgcScene.xml file into TgcSceneData object structure
	* @param filePath absolute file path
	* @return the structure of the scene
	*/
	TgcSceneData* TgcSceneParser::parseSceneFromFile(string filePath);
	

private:
	
	/**
	* Loads a Standard Material from an xml node
	*/
	void parseStandardMaterial(TgcMaterialData* material, const xml_node &matNode);


private:


	
};




}