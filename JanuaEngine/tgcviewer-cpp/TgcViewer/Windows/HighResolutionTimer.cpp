/*#############################################################
TgcViewer-cpp

Author: Matias Leone

#############################################################*/


#include "TgcViewer/Windows/HighResolutionTimer.h"
using namespace TgcViewer;


HighResolutionTimer::HighResolutionTimer()
{
	this->frameSecond = 0;
	this->fps = 0;
	this->frameTime = 0;
	this->frameCount = 0;
}


HighResolutionTimer::HighResolutionTimer(const HighResolutionTimer& other)
{
}


HighResolutionTimer::~HighResolutionTimer()
{
}

void HighResolutionTimer::reset()
{
	this->startTime = this->ticks();
}

void HighResolutionTimer::set()
{
	// Calc frame time.
	const long endTime = this->ticks();
	this->frameTime = (float)(endTime - this->startTime) / (float)this->frequency();
	this->startTime = endTime;

	// Calc fps.
	this->frameCount++;
	this->frameSecond += this->frameTime;
	if (this->frameSecond >= 1.0f)
	{
		this->frameSecond = 0;
		this->fps = this->frameCount;
		this->frameCount = 0;
	}
}

long HighResolutionTimer::frequency()
{
	LARGE_INTEGER freq;
	freq.QuadPart = 0;
    QueryPerformanceFrequency(&freq);
	return (long)freq.QuadPart;
}

long HighResolutionTimer::ticks()
{
	LARGE_INTEGER ticks;
	ticks.QuadPart = 0;
    QueryPerformanceCounter(&ticks);
	return (long)ticks.QuadPart;
}
