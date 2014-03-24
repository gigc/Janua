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
#include "TgcViewer/Math/Vector2.h"
#include "TgcViewer/Math/Vector3.h"
#include "TgcViewer/Renderer/TgcRendererGlobals.h"
#include "TgcViewer/TgcSceneLoader/TgcTexture.h"
#include "TgcViewer/Renderer/TgcVertexBuffer.h"
#include "TgcViewer/Renderer/TgcIndexBuffer.h"
#include "TgcViewer/Renderer/TgcEffect.h"
#include "TgcViewer/Renderer/TgcInputLayout.h"
#include "TgcViewer/2D/TgcText2d.h"
#include "TgcViewer/2D/TgcFont.h"

//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;}


namespace TgcViewer
{



/**
* Tool to render 2D Bitmap fonts
*/
class TgcFontRenderer
{

public:

	TgcFontRenderer();
	TgcFontRenderer(const TgcFontRenderer&);
	~TgcFontRenderer();

	/**
	* Load a new font (if it has not been loaded yet).
	* The font is searched in the default font folder
	* @param id font identifier that represents a <id>.bmp and <id>.csv file
	*/
	void loadFont(string id);

	/**
	* Load a new font (if it has not been loaded yet).
	* @param id font identifier that represents a <id>.bmp and <id>.csv file
	* @param fontFolderPath
	*/
	void loadFont(string id, string fontFolderPath);

	/**
	* Render text
	* @param text2d
	*/
	void render(TgcText2d* text2d);

	/**
	* Free resources
	*/
	void dispose();






	/**
	* Update the vertexBuffer with a word
	*/
	void updateVertexDataForWord(string word, VertexFormat::PositionTexcoord* vertexData, Vector2& currentPos, TgcFont* font, int & currentVertex);

	/**
	* Sprit the text in tokens
	*/
	vector<string> splitText(const string &text);

	/**
	* Normalize to projected values: X [-1, 1], Y [1, -1]
	*/
	void toScreenSpace(Vector2 &v);

	/**
	* From projected values: X [-1, 1], Y [1, -1] to World values
	*/
	void toWorldSpace(Vector2 &v);

private:
	
public:

	static const int MAX_TEXT_LENGTH = 1000;
	static const int VERTEX_COUNT = MAX_TEXT_LENGTH * 6;

	/**
	* Fonts loaded
	*/
	unordered_map<string, TgcFont*> fonts;

	/**
	* Big buffer to render all TgcText2d
	*/
	TgcVertexBuffer* vertexBuffer;

	/**
	* Shader to render TgcText2d
	*/
	TgcEffect* effect;

private:

};




}