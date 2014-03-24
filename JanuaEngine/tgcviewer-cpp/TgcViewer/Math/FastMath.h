/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <math.h>
#include <stdlib.h>
#include <time.h>


//Project Includes:
#include "TgcViewer/globals.h"


namespace TgcViewer
{



/**
* Math utils
*/
class FastMath
{

public:

	/**
	* PI
	*/
	static const float PI;

	/**
	* PI / 2
	*/
	static const float HALF_PI;

	/**
	* 2PI
	*/
	static const float TWO_PI;

	/**
	* PI / 4
	*/
	static const float QUARTER_PI;

	/**
	* 1 / PI
	*/
	static const float INV_PI;

	/**
	* 1 / 2PI
	*/
	static const float INV_TWO_PI;

	/**
	* Degree-radian conversion
	*/
	static const float TO_DEG;
	static const float TO_RAD;
	

	/**
	* Number limits
	*/
	static const float MAX_FLOAT;
	static const float MIN_FLOAT;



	/**
	* Internal initialization
	*/
	static void init();

	/**
	* Trigonometric functions
	*/
	static float sin(float n);
	static float cos(float n);
	static float tan(float n);
	static float asin(float n);
	static float acos(float n);
	static float atan(float n);
	static float atan2(float y, float x);
	static float sinh(float n);
	static float cosh(float n);
	static float tanh(float n);

	static float sqrt(float n);
	static float invSqrt(float n);
	static float abs(float n);
	static float ceil(float n);
	static float floor(float n);

	static float log(float n);
	static float log10(float n);

	static float toDeg(float n);
	static float toRad(float n);

	static float pow(float x, float y);
	static float pow2(float x);
	static float exp(float n);

	static void swap(float &n1, float &n2);

	
	static float minf(float n1, float n2);
	static float maxf(float n1, float n2);
	

	static bool FastMath::epsilonEquals(float n1, float n2, float epsilon);

	static int random();
	static int random(int min, int max);

private:
	
	FastMath();


public:

private:



};



//////////////////////////////// Inline functions //////////////////////////////////

inline float FastMath::sin(float n)
{
	return sinf(n);
}

inline float FastMath::cos(float n)
{
	return cosf(n);
}

inline float FastMath::tan(float n)
{
	return tanf(n);
}

inline float FastMath::asin(float n)
{
	return asinf(n);
}

inline float FastMath::acos(float n)
{
	return acosf(n);
}

inline float FastMath::atan(float n)
{
	return atanf(n);
}

inline float FastMath::atan2(float y, float x)
{
	return atan2f(y, x);
}

inline float FastMath::sinh(float n)
{
	return sinhf(n);
}

inline float FastMath::cosh(float n)
{
	return coshf(n);
}

inline float FastMath::tanh(float n)
{
	return tanhf(n);
}



inline float FastMath::sqrt(float n)
{
	return sqrtf(n);
}

inline float FastMath::invSqrt(float n)
{
	return 1.0f / FastMath::sqrt(n);
}

inline float FastMath::abs(float n)
{
	return fabsf(n);
}

inline float FastMath::ceil(float n)
{
	return ceilf(n);
}

inline float FastMath::floor(float n)
{
	return floorf(n);
}

inline float FastMath::log(float n)
{
	return logf(n);
}

inline float FastMath::log10(float n)
{
	return log10f(n);
}

inline float FastMath::toDeg(float n)
{
	return n * FastMath::TO_DEG;
}

inline float FastMath::toRad(float n)
{
	return n * FastMath::TO_RAD;
}

inline float FastMath::pow(float x, float y)
{
	return powf(x, y);
}

inline float FastMath::pow2(float x)
{
	return FastMath::pow(x, 2);
}


inline void FastMath::swap(float &n1, float &n2)
{
	float aux = n1;
	n2 = n2;
	n1 = aux;
}

inline float FastMath::minf(float n1, float n2)
{
	return n1 < n2 ? n1 : n2;
}

inline float FastMath::maxf(float n1, float n2)
{
	return n1 > n2 ? n1 : n2;
}

inline float FastMath::exp(float n)
{
	return expf(n);
}

inline bool FastMath::epsilonEquals(float n1, float n2, float epsilon)
{
	return FastMath::abs(n1 - n2) < epsilon;
}

inline int FastMath::random()
{
	return rand();
}

inline int FastMath::random(int min, int max)
{
	return FastMath::random() % (max - min + 1) + min;
}


}
