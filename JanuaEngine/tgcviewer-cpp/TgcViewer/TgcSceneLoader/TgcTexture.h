/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Renderer/TgcRendererGlobals.h"
#include "TgcViewer/TgcSceneLoader/TgcParserUtils.h"
#include "TgcViewer/Math/Vector2.h"

//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;}



namespace TgcViewer
{

/**
* A texture resource
* It is an abstract class. Then each renderer implement its concrete class.
*/
class TgcTexture
{

public:

	TgcTexture();
	TgcTexture(const TgcTexture&);
	~TgcTexture();

	/**
	* Compute texture aspect ratio
	*/
	float getAspectRatio();

	/**
	* Destroy the textures (if nobody else is using it from the pool)
	*/
	void dispose();

	/**
	* Creates a new texture from the path specified.
	* A texture pool is used to avoid loading the same filePath twice.
	* @param filePath absolute path of the textue
	*/
	static TgcTexture* createTexture(string filePath);

	/**
	* Creates a new texture from the path specified.
	* The texture pool is not used
	* @param filePath absolute path of the textue
	*/
	static TgcTexture* createTextureNoPool(string filePath);


	/**
	* {Renderer-dependent}
	* Creates a new texture from an image file
	*/
	virtual void internalCreateFromFile() = 0;

	/**
	* {Renderer-dependent}
	* Destroys the texture
	*/
	virtual void internalDispose() = 0;

	/**
	* Texture size
	*/
	Vector2 size();

private:
	

public:

	/**
	* Texture name
	*/
	string fileName;

	/**
	* Absolute file path
	*/
	string filePath;

	/**
	* Shows if the texture was created inside the texture pool of the engine
	*/
	bool inPool;

	/**
	* Width of the texture
	*/
	int width;

	/**
	* Height of the texture
	*/
	int height;

	/**
	* Objects using this texture from the pool
	*/
	int references;

	/**
	* Number of mipmaps
	*/
	int mipLevels;

	/**
	* Texture format
	*/ 
	TextureFormat::Format format;

private:


	
};


inline Vector2 TgcTexture::size()
{
	return Vector2((float)this->width, (float)this->height);
}


//////////////////////////////////////////////////////////////////////////////////////////////////



/**
* Pool to avoid loading textures with the same path that have already been loaded
*/
class TgcTexturePool
{

public:

	/**
	* Adds a texture to the pool.
	* If the texture is not currently in the pool then it is created.
	* Otherwise it only increments the reference counter.
	*/
	TgcTexture* add(string filePath);

	/**
	* Removes a texture form the pool.
	* If nobody else is using it then it frees the resource.
	*/
	bool remove(TgcTexture* texture);

	/**
	* Disposes all textures from the pool
	*/
	void clearAll();

private:

public:

private:

	/**
	* Pool of textures
	*/
	unordered_map<string, TgcTexture*> texturesPool;

};





}