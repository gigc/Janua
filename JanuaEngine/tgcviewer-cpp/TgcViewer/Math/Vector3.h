/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <iostream>

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Math/FastMath.h"
#include "TgcViewer/Math/Matrix4.h"
#include "TgcViewer/Math/Vector4.h"
#include "TgcViewer/Math/Vector2.h"


namespace TgcViewer
{



/**
* A Vector 3: (x, y, z)
*/
struct Vector3  
{

    union
    {
        struct
        {
                float X,Y,Z;
        };
        float v[3];
    };

    ~Vector3();
    Vector3();
    Vector3( const float * );
    Vector3( float x, float y, float z );
	Vector3(const Vector3&);
        

    //static functions
    static float Dot(const Vector3 &v1, const Vector3 &v2);
    static Vector3 Cross(const Vector3 &v1, const Vector3 &v2);
	static float LengthSq(const Vector3 &v);
	static float Length(const Vector3 &v);
	static float MinAxis(const Vector3 &v);
	static float MaxAxis(const Vector3 &v);
    static Vector3 Normalize(const Vector3 &v);
    static Vector4 Transform(const Vector3 &v, const Matrix4 &mat);
    static Vector4 TransformCoordinate(const Vector3 &v, const Matrix4 &mat);
    static Vector4 TransformNormal(const Vector3 &v, const Matrix4 &mat);
        
        
    float dot(const Vector3 &v) const;
    Vector3 cross(const Vector3 &v) const;
    float lengthSq() const;
    float length() const;
    float normalize();
	float minAxis() const;
	float maxAxis() const;


    // casting
    operator float* ();
    operator const float* () const;
        
    // assignment operators
    Vector3& operator += ( const Vector3& );
    Vector3& operator -= ( const Vector3& );
    Vector3& operator *= ( float );
    Vector3& operator /= ( float );
        
    // unary operators
    Vector3 operator + () const;
    Vector3 operator - () const;

	//subscript operator
	float& operator [] (const int nIndex);
        
    // binary operators
    Vector3 operator + ( const Vector3& ) const;
    Vector3 operator - ( const Vector3& ) const;
    Vector3 operator * ( float ) const;
    Vector3 operator / ( float ) const;
        
    friend Vector3 operator * ( float, const Vector3& );
        
    bool operator == ( const Vector3& ) const;
    bool operator != ( const Vector3& ) const;

	static Vector2 ToVector2XY(const Vector3& v);
	Vector2 toVector2XY() const;
	static Vector2 ToVector2XZ(const Vector3& v);
	Vector2 toVector2XZ() const;
	static Vector2 ToVector2YZ(const Vector3& v);
	Vector2 toVector2YZ() const;

};



//////////////////////////////// Inline functions //////////////////////////////////

inline Vector3::Vector3()
{
	memset(v, 0, sizeof(v));
}

inline Vector3::Vector3( const float * v2)
{
    memcpy(v,v2,sizeof(v));
}

inline Vector3::Vector3( float x, float y, float z )
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

inline Vector3::~Vector3()
{
}

inline Vector3::Vector3(const Vector3& other)
{
	X = other.X;
	Y = other.Y;
	Z = other.Z;
}

inline Vector3::operator float*()
{
	return (float*)v;
}

inline Vector3::operator const float*() const
{
    return (const float*)v;
}

inline Vector3& Vector3::operator+=( const Vector3& v2)
{
    v[0] += v2.X;
    v[1] += v2.Y;
    v[2] += v2.Z;

    return (*this);
}

inline Vector3& Vector3::operator-=( const Vector3& v2)
{
    v[0] -= v2.X;
    v[1] -= v2.Y;
    v[2] -= v2.Z;
        
    return (*this);
}

inline float& Vector3::operator [] (const int nIndex)
{
	return v[nIndex];
}

inline Vector3& Vector3::operator*=( float val)
{
    v[0] *= val;
    v[1] *= val;
    v[2] *= val;
        
    return (*this);
}

inline Vector3& Vector3::operator/=( float val)
{
    v[0] /= val;
    v[1] /= val;
    v[2] /= val;
        
    return (*this);
}

inline Vector3 Vector3::operator-( const Vector3& v2) const
{
    return Vector3(v[0] - v2.X, v[1] - v2.Y, v[2] - v2.Z);
}

inline Vector3 Vector3::operator+( const Vector3& v2) const
{
    return Vector3(v[0] + v2.X, v[1] + v2.Y, v[2] + v2.Z);
}

inline Vector3 Vector3::operator*( float val) const
{
    return Vector3(X*val, Y*val, Z*val);
}

inline Vector3 Vector3::operator/( float val) const
{
    return Vector3(X/val, Y/val, Z/val);
}

inline bool Vector3::operator==( const Vector3& v2) const
{
    return X==v2.X && Y==v2.Y && Z==v2.Z;
}

inline bool Vector3::operator!=( const Vector3& v2) const
{
    return !((*this) == v2);
}

inline float Vector3::dot( const Vector3 &v ) const
{
    return Vector3::Dot((*this), v);
}

inline Vector3 Vector3::cross( const Vector3 &v ) const
{
    return Vector3::Cross((*this), v);
}

inline float Vector3::lengthSq() const
{
    return X*X + Y*Y + Z*Z;
}

inline float Vector3::length() const
{
    return FastMath::sqrt(lengthSq());
}

inline float Vector3::normalize()
{
    float len = length();
    (*this) /= len;
    return len;
}

inline float Vector3::minAxis() const
{
	return FastMath::minf(FastMath::minf(X, Y), Z);
}

inline float Vector3::maxAxis() const
{
	return FastMath::maxf(FastMath::maxf(X, Y), Z);
}

//Static functions
inline float Vector3::Dot(const Vector3 &v1, const Vector3 &v2)
{
    return v1.X*v2.X + v1.Y*v2.Y + v1.Z*v2.Z;
}

inline Vector3 Vector3::Cross(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3(
        v1.Y*v2.Z - v1.Z*v2.Y,
        v1.Z*v2.X - v1.X*v2.Z,
        v1.X*v2.Y - v1.Y*v2.X
        );
}

inline float Vector3::LengthSq(const Vector3 &v)
{
	return v.lengthSq();
}

inline float Vector3::Length(const Vector3 &v)
{
	return v.length();
}

inline float Vector3::MinAxis(const Vector3 &v)
{
	return v.minAxis();
}

inline float Vector3::MaxAxis(const Vector3 &v)
{
	return v.maxAxis();
}

inline Vector3 Vector3::Normalize(const Vector3 &v)
{
    return v/v.length();
}

inline Vector4 Vector3::Transform( const Vector3 &v, const Matrix4 &mat )
{
    return Vector4::Transform(Vector4(v.X,v.Y,v.Z, 1), mat);
}

inline Vector4 Vector3::TransformCoordinate( const Vector3 &v, const Matrix4 &mat)
{
    Vector4 v2 = Vector4::Transform(Vector4(v.X,v.Y,v.Z, 1), mat);
	v2.X /= v2.W;
	v2.Y /= v2.W;
	v2.Z /= v2.W;
	return v2;
}

inline Vector4 Vector3::TransformNormal( const Vector3 &v, const Matrix4 &mat )
{
	//TODO: check this
    return Vector4::Transform(Vector4(v.X,v.Y,v.Z, 0), mat);
}

inline Vector2 Vector3::ToVector2XY(const Vector3& v)
{
	return v.toVector2XY();
}
	
inline Vector2 Vector3::toVector2XY() const
{
	return Vector2(X, Y);
}

inline Vector2 Vector3::ToVector2XZ(const Vector3& v)
{
	return v.toVector2XZ();
}
	
inline Vector2 Vector3::toVector2XZ() const
{
	return Vector2(X, Z);
}

inline Vector2 Vector3::ToVector2YZ(const Vector3& v)
{
	return v.toVector2YZ();
}
	
inline Vector2 Vector3::toVector2YZ() const
{
	return Vector2(Y, Z);
}




}