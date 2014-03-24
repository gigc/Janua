/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Math/FastMath.h"


namespace TgcViewer
{



/**
* A vector2 (x, y) or (u, v)
*/
struct Vector2  
{
public:
    union
    {
        struct
        {
                float X,Y;
        };
        float v[2];
		struct
        {
                float U,V;
        };
		struct
        {
                float Width,Height;
        };
    };
public:
    Vector2();
    Vector2( const float * vector);
    Vector2( float x, float y);
    ~Vector2();

    // casting
    operator float* ();
    operator const float* () const;
        
    // assignment operators
    Vector2& operator += ( const Vector2& v2);
    Vector2& operator -= ( const Vector2& v2);
    Vector2& operator *= ( float val);
    Vector2& operator /= ( float val);
        
    // unary operators
    Vector2 operator + () const;
    Vector2 operator - () const;
        
    // binary operators
    Vector2 operator + ( const Vector2& v2) const;
    Vector2 operator - ( const Vector2& v2) const;
    Vector2 operator * ( float val) const;
    Vector2 operator / ( float val) const;
        
    friend Vector2 operator * ( float, const Vector2& );
        
    bool operator == ( const Vector2& v2) const;
    bool operator != ( const Vector2& v2) const;

	//subscript operator
	float& operator [] (const int nIndex);
    

    float dot(const Vector2 &v) const;
    float lengthSq() const;
    float length() const;
    float normalize();
	float minAxis() const;
	float maxAxis() const;

	//static functions
    static float Dot(const Vector2 &v1, const Vector2 &v2);
	static float LengthSq(const Vector2 &v);
	static float Length(const Vector2 &v);
    static Vector2 Normalize(const Vector2 &v);

};



//////////////////////////////// Inline functions //////////////////////////////////



inline Vector2::Vector2()
{
	X = 0;
	Y = 0;
}

inline Vector2::Vector2( const float * vector)
{
    v[0] = vector[0];
    v[1] = vector[1];
}

inline Vector2::Vector2( float x, float y )
{
    v[0] = x;
    v[1] = y;
}

inline Vector2::~Vector2()
{

}

inline Vector2::operator float*()
{
    return (float *)v;
}

inline Vector2::operator const float*() const
{
    return (const float *)v;
}

inline Vector2& Vector2::operator+=( const Vector2& v2)
{
    X += v2.X;
    Y += v2.Y;
    return (*this);
}

inline Vector2& Vector2::operator-=( const Vector2& v2)
{
    X -= v2.X;
    Y -= v2.Y;
    return (*this);
}

inline Vector2& Vector2::operator*=( float val )
{
    X *= val;
    Y *= val;
    return (*this);
}

inline Vector2& Vector2::operator/=( float val )
{
    X *= val;
    Y *= val;
    return (*this);
}

inline Vector2 Vector2::operator+() const
{
    return Vector2(X,Y);
}

inline Vector2 Vector2::operator+( const Vector2& v2) const
{
    return Vector2(X+v2.X,Y+v2.Y);
}

inline Vector2 Vector2::operator-() const
{
    return Vector2(-X,-Y);
}

inline Vector2 Vector2::operator-( const Vector2& v2) const
{
    return Vector2(X+v2.X,Y+v2.Y);
}

inline Vector2 Vector2::operator*( float val) const
{
    return Vector2(X*val,Y*val);
}

inline Vector2 Vector2::operator/( float val) const
{
    return Vector2(X/val,Y/val);
}

inline bool Vector2::operator==( const Vector2& v2) const
{
    return X==v2.X && Y==v2.Y;;
}

inline bool Vector2::operator!=( const Vector2& v2) const
{
    return !((*this)== v2);
}

inline float& Vector2::operator [] (const int nIndex)
{
	return v[nIndex];
}

inline float Vector2::dot(const Vector2 &v) const
{
	return Vector2::Dot((*this), v);
}

inline float Vector2::Dot(const Vector2 &v1, const Vector2 &v2)
{
	return v1.X * v2.X + v1.Y + v2.Y;
}

inline float Vector2::lengthSq() const
{
	return Vector2::LengthSq((*this));
}

inline float Vector2::LengthSq(const Vector2 &v)
{
	return v.X * v.X + v.Y * v.Y;
}

inline float Vector2::length() const
{
	return Vector2::Length((*this));
}

inline float Vector2::Length(const Vector2 &v)
{
	return FastMath::sqrt(Vector2::Length(v));
}

inline float Vector2::normalize()
{
	float len = length();
    (*this) /= len;
    return len;
}

inline Vector2 Vector2::Normalize(const Vector2 &v)
{
	return v/v.length();
}











}