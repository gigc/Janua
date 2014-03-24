/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <string>

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Renderer/TgcRendererGlobals.h"
#include "TgcViewer/Renderer/TgcVertexBuffer.h"
#include "TgcViewer/Renderer/TgcIndexBuffer.h"
#include "TgcViewer/Renderer/TgcEffect.h"
#include "TgcViewer/Renderer/TgcInputLayout.h"
#include "TgcViewer/TgcSceneLoader/TgcTexture.h"
#include "TgcViewer/Math/Vector2.h"
#include "TgcViewer/Math/Color.h"


namespace TgcViewer
{



/**
* A 2D static image
*/
class TgcSprite
{

public:

	/**
	* Helper to create a new Sprite
	* @param texturePath
	* @param position
	*/
	static TgcSprite* create(string texturePath, Vector2 position);

	TgcSprite();
	TgcSprite(const TgcSprite&);
	~TgcSprite();


	/**
	* Init the Sprite
	*/
	void init();

	/**
	* Update the drawing objetos of the sprite.
	* It must be called after some atributes of the sprite has been changed to take effect.
	*/
	void updateValues();

	/**
	* Render the sprite, if it is enabled
	*/
	void render();

	/**
	* Frees resources
	*/
	void dispose();

	/**
	* Computes the srcRect for a given index of a tiled texture
	* All texture tiles must be of equals size
	*/
	void setSrcRectFromTileIndex(int tileIndex, Vector2 tileSize);

	/**
	* Check if the point specified is inside the sprite boundaries
	*/
	bool inside(const Vector2 p);

private:
	

public:


	/**
	* Texture used by the sprite
	*/
	TgcTexture* texture;

	/**
	* Color applied to the sprite
	*/
	Color color;

	/**
	* Position in pixels of the sprite. (0, 0) is in upper left corner
	*/
	Vector2 position;

	/**
	* Size in pixels of the sprite
	*/
	Vector2 size;

	/**
	* Sprite avaliable to be rendered
	*/
	bool enabled;

	/**
	* Specifies a rectangular portion of the image to draw.
	* If not specified, all the image is rendered.
	*/
	ScreenSpace::ScreenRect srcRect;




	/**
	* VertexBuffer of the Sprite
	*/
	TgcVertexBuffer* vertexBuffer;

	/**
	* IndexBuffer of the Sprite
	*/
	TgcIndexBuffer* indexBuffer;

	/**
	* Shader effect of the Sprite
	*/
	TgcEffect* effect;


private:


	
};




}