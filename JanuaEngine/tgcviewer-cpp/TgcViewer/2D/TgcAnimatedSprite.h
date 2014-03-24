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
#include "TgcViewer/Math/Vector2.h"
#include "TgcViewer/2D/TgcSprite.h"
#include "TgcViewer/TgcSceneLoader/TgcTexture.h"



namespace TgcViewer
{



/**
* Tool to draw 2D animated sprites packed in a texture atlas.
* All the tiles must be of the same size
*/
class TgcAnimatedSprite
{

public:

	TgcAnimatedSprite();
	TgcAnimatedSprite(const TgcAnimatedSprite&);
	~TgcAnimatedSprite();

	/**
	* Init the Sprite
	*/
	void init(string texturePath, Vector2 frameSize, int totalFrames, float frameRate, Vector2 position);

	/**
	* Update the drawing objetos of the sprite.
	* It must be called after some atributes of the sprite has been changed to take effect.
	*/
	void updateValues();

	/**
	* Updates the animation and render the sprite, if it is enabled
	*/
	void render();

	/**
	* Frees resources
	*/
	void dispose();

private:

public:

	/**
	* Avaliable to be rendered
	*/
	bool enabled;

	/**
	* Start or stop the animation
	*/
	bool playing;

	/**
	* Animation speed in frames per second
	*/
	float frameRate;

	/**
	* Sprite to animate with the texture atlas
	*/
	TgcSprite* sprite;

	/**
	* The current frame being animated
	*/
	int currentFrame;

	/**
	* Tile's dimensions in pixels from the texture atlas
	*/
	Vector2 frameSize;
	
	/**
	* The number of tiles in the texture atlas
	*/
	int totalFrames;



	float currentTime;
	int framesPerRow;
	int framesPerColumn;
	float animationTimeLenght;

private:


	
};




}