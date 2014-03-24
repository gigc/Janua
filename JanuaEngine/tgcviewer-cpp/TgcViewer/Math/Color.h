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


namespace TgcViewer
{



/**
* Description of the class
*/
/**
* A 32 bits Color: (r, g, b, a)
*/
struct Color  
{
    union
    {
        struct
        {
                float R,G,B,A;
        };
        float v[4];
    };

	Color();
    ~Color();
    Color( float r, float g, float b, float a );
        
    // casting
    operator float* ();
    operator const float* () const;
        
    // assignment operators
    Color& operator += ( const Color& v2);
    Color& operator -= ( const Color& v2);
    Color& operator *= ( float val);
    Color& operator /= ( float val);
        
    // unary operators
    Color operator + () const;
    Color operator - () const;
        
    // binary operators
    Color operator + ( const Color& v2) const;
    Color operator - ( const Color& v2) const;
    Color operator * ( float val) const;
    Color operator / ( float val) const;
        
    friend Color operator * ( float, const Color& );
        
    bool operator == ( const Color& v2) const;
    bool operator != ( const Color& v2) const;


	static Color fromRGB(int r, int g, int b);
	static Color fromRGBA(int r, int g, int b, int a);


	//Color constants
	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Gray;
	static const Color Yellow;
	static const Color Brown;
	static const Color Pink;
	static const Color Violet;
	static const Color Magenta;
	static const Color Purple;
	static const Color LightBlue;
	static const Color Cyan;
	static const Color Orange;
	static const Color DarkGreen;
	static const Color Gold;
	static const Color DarkOrange;
	static const Color OrangeRed;
	static const Color Salmon;
	static const Color Navy;
	static const Color Silver;

};




}