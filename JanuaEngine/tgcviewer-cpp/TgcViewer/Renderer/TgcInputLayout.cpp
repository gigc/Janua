/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/TgcInputLayout.h"
using namespace TgcViewer;


TgcInputLayout::TgcInputLayout()
{
}


TgcInputLayout::TgcInputLayout(const TgcInputLayout& other)
{
}


TgcInputLayout::~TgcInputLayout()
{
}

void TgcInputLayout::create()
{
	//Compute size and offsets
	this->size = 0;
	unsigned int lastOffset = 0;
	unsigned int elementSize;
	for(unsigned int i = 0; i < this->elements.size(); i++)
	{
		elementSize = this->elements[i].size();
		this->size += elementSize;
		this->offsets.push_back(lastOffset);
		lastOffset += elementSize;
	}


	this->internalCreate();
}