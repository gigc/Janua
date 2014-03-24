/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Math/Color.h"
using namespace TgcViewer;


//Color constants
const Color Color::Black = Color(0, 0, 0, 1);
const Color Color::White = Color(1, 1, 1, 1);
const Color Color::Red = Color(1, 0, 0, 1);
const Color Color::Green = Color(0, 1, 0, 1);
const Color Color::Blue = Color(0, 0, 1, 1);
const Color Color::Gray = Color(190.0f/255.0f, 190.0f/255.0f, 190.0f/255.0f, 1);
const Color Color::Yellow = Color(1, 1, 0, 1);
const Color Color::Brown = Color(165/255.0f, 42/255.0f, 42/255.0f, 1);
const Color Color::Pink = Color(255/255.0f, 192/255.0f, 203/255.0f, 1);
const Color Color::Violet = Color(238/255.0f, 130/255.0f, 238/255.0f, 1);
const Color Color::Magenta = Color(1, 0, 1, 1);
const Color Color::Purple = Color(128/255.0f, 0, 128/255.0f, 1);
const Color Color::LightBlue = Color(173/255.0f, 216/255.0f, 230/255.0f, 1);
const Color Color::Cyan = Color(0, 1, 1, 1);
const Color Color::Orange = Color(1, 128/255.0f, 0, 1);
const Color Color::DarkGreen = Color(0, 100/255.0f, 0, 1);
const Color Color::Gold = Color(1, 215/255.0f, 0, 1);
const Color Color::DarkOrange = Color(1, 140/255.0f, 0, 1);
const Color Color::OrangeRed = Color(1, 69/255.0f, 0, 1);
const Color Color::Salmon = Color(250/255.0f, 128/255.0f, 114/255.0f, 1);
const Color Color::Navy = Color(0, 0, 128/255.0f, 1);
const Color Color::Silver = Color(192/255.0f, 192/255.0f, 192/255.0f, 1);


Color::Color()
{
    memset(v, 0, sizeof(v));
}

Color::Color( float r, float g, float b, float a )
{
    R = r;
    G = g;
    B = b;
    A = a;
}

Color::~Color()
{

}

Color::operator float*()
{
    return (float *)v;
}

Color::operator const float*() const
{
    return (const float *)v;
}

Color& Color::operator+=( const Color& v2)
{
    R += v2.R;
    G += v2.G;
    B += v2.B;
    A += v2.A;
    return (*this);
}

Color& Color::operator-=( const Color& v2)
{
    R -= v2.R;
    G -= v2.G;
    B -= v2.B;
    A -= v2.A;
    return (*this);
}

Color& Color::operator*=( float val )
{
    R *= val;
    G *= val;
    B *= val;
    A *= val;
    return (*this);
}

Color& Color::operator/=( float val )
{
    R *= val;
    G *= val;
    B *= val;
    A *= val;
    return (*this);
}

Color Color::operator+() const
{
    return Color(R,G,B,A);
}

Color Color::operator+( const Color& v2) const
{
    return Color(R+v2.R,G+v2.G,B+v2.B,A+v2.A);
}

Color Color::operator-() const
{
    return Color(-R,-G,-B,-A);
}

Color Color::operator-( const Color& v2) const
{
    return Color(R+v2.R,G+v2.G,B+v2.B,A+v2.A);
}

Color Color::operator*( float val) const
{
    return Color(R*val,G*val,B*val,A*val);
}

Color Color::operator/( float val) const
{
    return Color(R/val,G/val,B/val,A/val);
}

bool Color::operator==( const Color& v2) const
{
    return R==v2.R && G==v2.G && B==v2.B && A==v2.A;
}

bool Color::operator!=( const Color& v2) const
{
    return !((*this)== v2);
}

Color Color::fromRGB(int r, int g, int b)
{
	return Color::fromRGBA(r, g, b, 255);
}
Color Color::fromRGBA(int r, int g, int b, int a)
{
	return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

