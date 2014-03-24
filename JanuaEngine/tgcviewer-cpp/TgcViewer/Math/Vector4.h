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


namespace TgcViewer
{



/**
* A Vector 4: (x, y, z, w)
*/
struct Vector4  
{
    union
    {
        struct
        {
                float X,Y,Z,W;
        };
        float v[4];
    };

	Vector4();
    ~Vector4();
    Vector4( float x, float y, float z, float w );
        
    // casting
    operator float* ();
    operator const float* () const;
        
    // assignment operators
    Vector4& operator += ( const Vector4& v2);
    Vector4& operator -= ( const Vector4& v2);
    Vector4& operator *= ( float val);
    Vector4& operator /= ( float val);
        
    // unary operators
    Vector4 operator + () const;
    Vector4 operator - () const;
        
    // binary operators
    Vector4 operator + ( const Vector4& v2) const;
    Vector4 operator - ( const Vector4& v2) const;
    Vector4 operator * ( float val) const;
    Vector4 operator / ( float val) const;
        
    friend Vector4 operator * ( float, const Vector4& );
        
    bool operator == ( const Vector4& v2) const;
    bool operator != ( const Vector4& v2) const;

    //statics
    static Vector4 Transform( const Vector4& v2, const Matrix4 &mat);

};




}