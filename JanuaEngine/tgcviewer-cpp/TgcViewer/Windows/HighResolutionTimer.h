/*#############################################################
TgcViewer-cpp

Author: Matias Leone

#############################################################*/


#pragma once


//General Includes:
#include <windows.h>


namespace TgcViewer
{



/*////////////////////////////////////////////////////////////////////////////////
Class name: HighResolutionTimer
////////////////////////////////////////////////////////////////////////////////*/
class HighResolutionTimer
{

public:

	HighResolutionTimer();
	HighResolutionTimer(const HighResolutionTimer&);
	~HighResolutionTimer();
	
	void reset();
	void set();
	

private:
	
	long ticks();
	long frequency();
	
public:
	
	float frameTime;
	int fps;
	

private:

	long startTime;
	int frameCount;
	float frameSecond;
	
};




}