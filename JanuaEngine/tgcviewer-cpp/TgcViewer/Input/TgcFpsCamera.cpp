/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Input/TgcFpsCamera.h"
using namespace TgcViewer;

const float TgcFpsCamera::DEFAULT_ROTATION_SPEED = 0.5f; 
const float TgcFpsCamera::DEFAULT_MOVEMENT_SPEED = 1;
const float TgcFpsCamera::DEFAULT_JUMP_SPEED = 1;


TgcFpsCamera::TgcFpsCamera()
{
	rotationSpeed = TgcFpsCamera::DEFAULT_ROTATION_SPEED;
	movementSpeed = TgcFpsCamera::DEFAULT_MOVEMENT_SPEED;
	jumpSpeed = TgcFpsCamera::DEFAULT_JUMP_SPEED;
	position = Vector3(0, 0, 0);
	lookAt = Vector3(0, 0, 0);
	currentRotY = 0;
	currentRotXZ = 0;
}


TgcFpsCamera::TgcFpsCamera(const TgcFpsCamera& other)
{
}


TgcFpsCamera::~TgcFpsCamera()
{
}




void TgcFpsCamera::updateCamera()
{
	float elapsedTime = GuiController::Instance->elapsedTime;
	TgcInput* tgcInput = GuiController::Instance->input;
        
    float forwardMovement = 0;
    float strafeMovement = 0;
    float jumpMovement = 0;
    float xzRotation = 0;
    float yRotation = 0;
    bool moving = false;
    bool rotating = false;
        
    //Check keyboard input
    if(tgcInput->keyDown(TgcInput::K_W)) 
	{
        forwardMovement = this->movementSpeed;
        moving = true;
    } 
	else if(tgcInput->keyDown(TgcInput::K_S)) 
	{
        forwardMovement = -this->movementSpeed;
        moving = true;
    }
    if(tgcInput->keyDown(TgcInput::K_A)) 
	{
        strafeMovement = -this->movementSpeed;
        moving = true;
    } 
	else if(tgcInput->keyDown(TgcInput::K_D)) 
	{
        strafeMovement = this->movementSpeed;
        moving = true;
    }
    if(tgcInput->keyDown(TgcInput::K_SPACE)) 
	{
        jumpMovement = this->jumpSpeed;
		moving = true;
	} else if(tgcInput->keyDown(TgcInput::K_CONTROL)) 
	{
        jumpMovement = -this->jumpSpeed;
        moving = true;
    }
        
    //Check mouse input
    if(tgcInput->buttonDown(TgcInput::BUTTON_LEFT)) 
	{
		yRotation = -tgcInput->deltaMouseX * this->rotationSpeed;
        xzRotation = tgcInput->deltaMouseY * this->rotationSpeed;
        rotating = true;
    }
        

    //Acumulate rotation
    this->currentRotY += yRotation * elapsedTime;
    this->currentRotXZ += xzRotation * elapsedTime;
        
    //Clamp XZ rotation between [-PI/2, PI/2]
    this->currentRotXZ = this->currentRotXZ > FastMath::HALF_PI ? FastMath::HALF_PI : this->currentRotXZ;
    this->currentRotXZ = this->currentRotXZ < -FastMath::HALF_PI ? -FastMath::HALF_PI : this->currentRotXZ;
        
    //Clamp Y rotation between [0, 2PI]
    this->currentRotY = this->currentRotY > FastMath::TWO_PI ? this->currentRotY - FastMath::TWO_PI : this->currentRotY;
    this->currentRotY = this->currentRotY < 0 ? FastMath::TWO_PI + this->currentRotY : this->currentRotY;

    //Compute dir angles from Y and XZ rotation
	float dirX = FastMath::sin(this->currentRotY);
    float dirZ = FastMath::cos(this->currentRotY);
    float dirY = FastMath::sin(this->currentRotXZ);
        
    //Movement dir
    Vector3 movementDir = Vector3(dirX, 0, dirZ);
	movementDir.normalize();
	Vector3 upVector = Vector3(0, 1, 0);
	Vector3 strafeDir = Vector3::Cross(upVector, movementDir);        
        
    //Forward-backward movement
	movementDir *= forwardMovement /* * elapsedTime */;

    //Strafe movement
	strafeDir *= strafeMovement /* * elapsedTime */;
        
    //Add movement
	this->position += movementDir + strafeDir;
	this->position.Y += jumpMovement;
        
    //Hacia donde mirar
    Vector3 lookAtDir = Vector3(dirX, dirY, dirZ);
	lookAtDir.normalize();
	this->lookAt = this->position + lookAtDir;
}


void TgcFpsCamera::updateViewMatrix()
{
	GuiController::Instance->renderer->viewMatrix = Matrix4::LookAtLH(this->position, this->lookAt, Vector3(0, 1, 0));
}