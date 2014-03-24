/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/2D/TgcAnimatedSprite.h"
using namespace TgcViewer;


TgcAnimatedSprite::TgcAnimatedSprite()
{
}


TgcAnimatedSprite::TgcAnimatedSprite(const TgcAnimatedSprite& other)
{
}


TgcAnimatedSprite::~TgcAnimatedSprite()
{
}

void TgcAnimatedSprite::init(string texturePath, Vector2 frameSize, int totalFrames, float frameRate, Vector2 position)
{
	this->enabled = true;
	this->currentFrame = 0;
	this->currentTime = 0;
	this->playing = true;

	this->frameSize = frameSize;
	this->totalFrames = totalFrames;
	this->frameRate = frameRate;

	this->sprite = new TgcSprite();
	this->sprite->texture = TgcTexture::createTexture(texturePath);
	this->sprite->size = this->sprite->texture->size();
	this->sprite->position = position;
	this->sprite->init();

	//Calcular valores de frames de la textura
	framesPerColumn = (int)(this->sprite->texture->width / frameSize.X);
	framesPerRow = (int)(this->sprite->texture->height / frameSize.Y);
    int realTotalFrames = framesPerRow * framesPerColumn;
    if (realTotalFrames > totalFrames)
    {
		GuiController::Instance->logger->logError("The totalFrames and the texture size does not match. AnimatedSprite: " + texturePath);
		return;
    }

    this->animationTimeLenght = (float)totalFrames / frameRate;
}

void TgcAnimatedSprite::updateValues()
{
	this->animationTimeLenght = (float)totalFrames / frameRate;
	this->sprite->updateValues();
}

void TgcAnimatedSprite::render()
{
	if (!enabled)
        return;

	//Increase the time
    if (playing)
    {
		currentTime += GuiController::Instance->elapsedTime;
        if (currentTime > animationTimeLenght)
        {
            //Restart
            currentTime = 0;
        }
    }

    //Compute current frame
    currentFrame = (int)(currentTime * frameRate);

    //Compute srcRect for this frame
	this->sprite->srcRect.y = frameSize.X * (currentFrame % framesPerRow);
	this->sprite->srcRect.width = frameSize.X;
	this->sprite->srcRect.x = frameSize.Y * (currentFrame % framesPerColumn);
	this->sprite->srcRect.height = frameSize.Y;
	this->sprite->updateValues();
	//this->sprite->setSrcRectFromTileIndex(currentFrame, frameSize);

	//Render the sprite
	this->sprite->render();
}

void TgcAnimatedSprite::dispose()
{
	this->sprite->dispose();
}

