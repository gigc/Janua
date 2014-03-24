/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/TgcSceneLoader/TgcTexture.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcTexture::TgcTexture()
{
	this->inPool = false;
	this->width = 0;
	this->height = 0;
	this->mipLevels = 0;
	this->references = 0;
}



TgcTexture::TgcTexture(const TgcTexture& other)
{
}


TgcTexture::~TgcTexture()
{
}


float TgcTexture::getAspectRatio()
{
	return (float)width / height;
}


void TgcTexture::dispose()
{
	//inside pool
    if (this->inPool)
    {
        bool disposed = GuiController::Instance->texturesPool->remove(this);
    }

    //outside pool
    else
    {
		this->internalDispose();
    }
}


TgcTexture* TgcTexture::createTexture(string filePath)
{
	return GuiController::Instance->texturesPool->add(filePath);
}


TgcTexture* TgcTexture::createTextureNoPool(string filePath)
{
	//Creates instance
	TgcTexture* texture = GuiController::Instance->renderer->createTgcTextureInstance();
	texture->filePath = filePath;
	texture->fileName = TgcParserUtils::getFileNameFromPath(filePath);
	texture->inPool = false;

	//Create texture
	texture->internalCreateFromFile();
	return texture;
}










///////////////////////////////////// Texture Pool /////////////////////////////////////////////


TgcTexture* TgcTexturePool::add(string filePath)
{
	TgcTexture* texture;

	//If it does not exists, creates a new texture
	unordered_map<string, TgcTexture*>::iterator  it = this->texturesPool.find(filePath);
	if (it == this->texturesPool.end() )
	{
		//Create new texture
		texture = GuiController::Instance->renderer->createTgcTextureInstance();
		texture->filePath = filePath;
		texture->fileName = TgcParserUtils::getFileNameFromPath(filePath);
		texture->inPool = true;
		texture->references = 1;
		texture->internalCreateFromFile();
		
		//Add it to the pool
		this->texturesPool[filePath] = texture;
	}
	else
	{
		//Increment reference count
		texture = this->texturesPool[filePath];
		texture->references++;
	}
	return texture;
}


bool TgcTexturePool::remove(TgcTexture* texture)
{
	//If it does not exists, ignore it
	unordered_map<string, TgcTexture*>::iterator  it = this->texturesPool.find(texture->filePath);
	if (it != this->texturesPool.end() )
	{
		//Decrement references
		texture->references--;

		//If nobody else is using it, then we delete the texture
		if(texture->references <= 0)
		{
			texture->internalDispose();
			this->texturesPool.erase(texture->filePath);
			delete texture;

			return true;
		}
	}

	return false;
}


void TgcTexturePool::clearAll()
{
	for (unordered_map<string, TgcTexture*>::iterator it = this->texturesPool.begin(); it != this->texturesPool.end(); ++it) 
	{
		TgcTexture* texture = it->second;
		texture->internalDispose();
		delete texture;
	}
	this->texturesPool.clear();
}