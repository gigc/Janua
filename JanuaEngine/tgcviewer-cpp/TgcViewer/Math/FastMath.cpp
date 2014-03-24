/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Math/FastMath.h"
using namespace TgcViewer;


const float FastMath::PI = 3.14159265358979323846f;
const float FastMath::HALF_PI = FastMath::PI / 2;
const float FastMath::TWO_PI = FastMath::PI * 2;
const float FastMath::QUARTER_PI = FastMath::PI / 4;
const float FastMath::INV_PI = 1 / FastMath::PI;
const float FastMath::INV_TWO_PI = 1 / FastMath::TWO_PI;
const float FastMath::TO_DEG = 180.0f / FastMath::PI;
const float FastMath::TO_RAD = FastMath::PI / 180.0f;

const float FastMath::MAX_FLOAT = 1E+37f;
const float FastMath::MIN_FLOAT = 1E-37f;


FastMath::FastMath()
{
}

void FastMath::init()
{
	//initialize random seed
	srand ((unsigned int)time(NULL));
}





