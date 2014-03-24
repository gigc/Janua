/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#pragma once


//General Includes:
#include <string>
using namespace std;


namespace TgcViewer
{


/**
* Abstract interface for a example to be executed by the engine
*/
class TgcExample
{

public:

	TgcExample();
	TgcExample(const TgcExample&);
	~TgcExample();


	/**
	* Category of the example
	*/
	virtual string getCategory() = 0;

	/**
	* Name of the example
	*/
	virtual string getName() = 0;

	/**
	* Description of the sample
	*/
	virtual string getDescription() = 0;
	
	/**
	* Creates here all the resources requires by the example
	*/
	virtual void init() = 0;

	/**
	* Render loop call
	* @param elapsedTime seconds from the last frame
	*/
	virtual void render(float elapsedTime) = 0;

	/**
	* Free all the resources of the example
	*/
	virtual void close() = 0;

};




}