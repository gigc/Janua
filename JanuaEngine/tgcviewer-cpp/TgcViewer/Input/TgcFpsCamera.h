/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
//#include <string>

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Input/TgcInput.h"
#include "TgcViewer/Math/FastMath.h"
#include "TgcViewer/Math/Vector3.h"
#include "TgcViewer/Math/Matrix4.h"


namespace TgcViewer
{



/**
* Description of the class
*/
class TgcFpsCamera
{

public:

	static const float DEFAULT_ROTATION_SPEED;
	static const float DEFAULT_MOVEMENT_SPEED;
	static const float DEFAULT_JUMP_SPEED;


	TgcFpsCamera();
	TgcFpsCamera(const TgcFpsCamera&);
	~TgcFpsCamera();

	/**
	* Upadte camera position
	*/
	void updateCamera();

	/**
	* Upadte view matrix
	*/
	void updateViewMatrix();


private:

public:


	/**
	* Camera rotation speed, in radians
	*/
    float rotationSpeed;

	/**
	* Camera movement speed in XZ axis
	*/
    float movementSpeed;

	/**
	* Camera movement speed in Y axis
	*/
    float jumpSpeed;

	/**
	* Current camera position
	*/
    Vector3 position;

	/**
	* Current camera look at
	*/
    Vector3 lookAt;
        
	/**
	* Current y axis rotation
	*/
    float currentRotY;
        
	 /**
	 * Current XZ axis rotation
	 */
    float currentRotXZ;


private:

	
};




}