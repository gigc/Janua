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
namespace TgcViewer{struct Vector3;} //Forward declaration of "TgcViewer/Math/Vector3.h"


namespace TgcViewer
{



/**
* A 4x4 Matrix
*/
struct Matrix4  
{

	union {
        struct {
            float        M11, M12, M13, M14;
            float        M21, M22, M23, M24;
            float        M31, M32, M33, M34;
            float        M41, M42, M43, M44;
        };
        float m[4][4];
    };

	static const float MATRIX_INVERSE_EPSILON;


    Matrix4();
    Matrix4( float _m00, float _m01, float _m02, float _m03,
            float _m10, float _m11, float _m12, float _m13,
            float _m20, float _m21, float _m22, float _m23,
            float _m30, float _m31, float _m32, float _m33
		);
    ~Matrix4();

    inline void identity();
    inline void translation(float x, float y, float z);
	inline void translation(const Vector3 &v);
    inline void rotationX(float angle);
    inline void rotationY(float angle);
    inline void rotationZ(float angle);
    inline void rotationYawPitchRoll(float yaw, float pitch, float roll);
    inline void rotationAxis(const Vector3 &vector, float angle);
    inline void scale(float sx, float sy, float sz);
	inline void scale(const Vector3 &v);

    inline void lookAtLH(const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector);
    inline void perspectiveFovLH(float fieldOfViewY,float aspectRatio, float znearPlane, float zfarPlane);
    inline void transpose();
	inline bool inverse();

    // access grants
    inline float& operator () ( int Row, int Col );
    inline float  operator () ( int Row, int Col ) const;
        
    // casting operators
    inline operator float* ();
    inline operator const float* () const;
        
    // assignment operators
    inline Matrix4& operator *= ( const Matrix4& );
    inline Matrix4& operator += ( const Matrix4& );
    inline Matrix4& operator -= ( const Matrix4& );
    inline Matrix4& operator *= ( float );
    inline Matrix4& operator /= ( float );
        
    // unary operators
    inline Matrix4 operator + () const;
    inline Matrix4 operator - () const;
        
    // binary operators
    Matrix4 operator * ( const Matrix4& ) const;
    inline Matrix4 operator + ( const Matrix4& ) const;
    inline Matrix4 operator - ( const Matrix4& ) const;
    inline Matrix4 operator * ( float ) const;
    inline Matrix4 operator / ( float ) const;
        
    inline friend Matrix4 operator * ( float, const Matrix4& );
        
    inline bool operator == ( const Matrix4& ) const;
    inline bool operator != ( const Matrix4& ) const;

    static Matrix4 Identity();
    static Matrix4 Translation(float x, float y, float z);
	static Matrix4 Translation(const Vector3 &v);
    static Matrix4 RotationX(float angle);
    static Matrix4 RotationY(float angle);
    static Matrix4 RotationZ(float angle);
    static Matrix4 RotationYawPitchRoll(float yaw, float pitch, float roll);
    static Matrix4 RotationAxis(const Vector3 &vector, float angle);
    static Matrix4 Scale(float sx, float sy, float sz);
	static Matrix4 Scale(const Vector3 &v);
        
    static Matrix4 LookAtLH(const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector);
    static Matrix4 PerspectiveFovLH(float fieldOfViewY,float aspectRatio, float znearPlane, float zfarPlane);
    static Matrix4 Transpose(const Matrix4 &mat);
	static Matrix4 Inverse(const Matrix4 &mat);


	static float Matrix4::Dot4hv(const Matrix4& m1, const Matrix4& m2, int r, int c);
};




//////////////////////////////// Inline functions //////////////////////////////////


inline Matrix4::Matrix4()
{

}

inline Matrix4::Matrix4( float _m00, float _m01, float _m02, float _m03, float _m10, float _m11, float _m12, float _m13, float _m20, float _m21, float _m22, float _m23, float _m30, float _m31, float _m32, float _m33 )
{
    m[0][0] = _m00; m[0][1] = _m01; m[0][2] = _m02; m[0][3] = _m03;
    m[1][0] = _m10; m[1][1] = _m11; m[1][2] = _m12; m[1][3] = _m13;
    m[2][0] = _m20; m[2][1] = _m21; m[2][2] = _m22; m[2][3] = _m23;
    m[3][0] = _m30; m[3][1] = _m31; m[3][2] = _m32; m[3][3] = _m33;
}

inline Matrix4::~Matrix4()
{

}

inline void Matrix4::identity()
{
    m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
    m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
    m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
    m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
}

inline void Matrix4::translation( float x, float y, float z )
{
    m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
    m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
    m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
    m[3][0] = x; m[3][1] = y; m[3][2] = z; m[3][3] = 1;     
}

inline void Matrix4::rotationX( float angle )
{
    float sinv = FastMath::sin(angle);
    float cosv = FastMath::cos(angle);

    m[0][0] = 1;    m[0][1] = 0;            m[0][2] = sinv;         m[0][3] = 0;
    m[1][0] = 0;    m[1][1] = cosv;         m[1][2] = 0;            m[1][3] = 0;
    m[2][0] = 0;    m[2][1] = -sinv;        m[2][2] = cosv;         m[2][3] = 0;
    m[3][0] = 0;    m[3][1] = 0;            m[3][2] = 0;            m[3][3] = 1;

}

inline void Matrix4::rotationY( float angle )
{
    float sinv = FastMath::sin(angle);
    float cosv = FastMath::cos(angle);
        
    m[0][0] = cosv; m[0][1] = 0;            m[0][2] = -sinv;        m[0][3] = 0;
    m[1][0] = 0;    m[1][1] = 1;            m[1][2] = 0;            m[1][3] = 0;
    m[2][0] = sinv; m[2][1] = 0;            m[2][2] = cosv;         m[2][3] = 0;
    m[3][0] = 0;    m[3][1] = 0;            m[3][2] = 0;            m[3][3] = 1;
}

inline void Matrix4::rotationZ( float angle )
{
    float sinv = FastMath::sin(angle);
    float cosv = FastMath::cos(angle);

    m[0][0] = cosv;         m[0][1] = sinv;         m[0][2] = 0;            m[0][3] = 0;
    m[1][0] = -sinv;        m[1][1] = cosv;         m[1][2] = 0;            m[1][3] = 0;
    m[2][0] = 0;            m[2][1] = 0;            m[2][2] = 1;            m[2][3] = 0;
    m[3][0] = 0;            m[3][1] = 0;            m[3][2] = 0;            m[3][3] = 1;
}

inline void Matrix4::rotationYawPitchRoll( float yaw, float pitch, float roll )
{
    float siny = FastMath::sin(yaw);
    float cosy = FastMath::cos(yaw);
    float sinp = FastMath::sin(pitch);
    float cosp = FastMath::cos(pitch);
    float sinr = FastMath::sin(roll);
    float cosr = FastMath::cos(roll);

    m[0][0] = cosy*cosr + siny*sinp*sinr; 
    m[0][1] = siny*cosp; 
    m[0][2] = -cosy*sinr + siny*sinp*cosr;
    m[0][3] = 0;

    m[1][0] = -siny*cosp + cosy*sinp*sinr; 
    m[1][1] = cosy*cosp;
    m[1][2] = siny*sinr + cosy*sinp*cosr; 
    m[1][3] = 0;

    m[2][0] = cosp*sinr; 
    m[2][1] = -sinp; 
    m[2][2] = cosp*cosr; 
    m[2][3] = 0;

    m[3][0] = 0; 
    m[3][1] = 0; 
    m[3][2] = 0; 
    m[3][3] = 1;  
}

inline void Matrix4::scale( float sx, float sy, float sz )
{
    m[0][0] = sx; m[0][1] = 0;  m[0][2] = 0;  m[0][3] = 0;
    m[1][0] = 0;  m[1][1] = sy; m[1][2] = 0;  m[1][3] = 0;
    m[2][0] = 0;  m[2][1] = 0;  m[2][2] = sz; m[2][3] = 0;
    m[3][0] = 0;  m[3][1] = 0;  m[3][2] = 0;  m[3][3] = 1;
}

inline float& Matrix4::operator()( int Row, int Col )
{
    return m[Row][Col];
}

inline float Matrix4::operator()( int Row, int Col ) const
{
    return m[Row][Col];
}

inline Matrix4::operator float*()
{
    return (float*)m;
}

inline Matrix4::operator const float*() const
{
    return (const float*)m;
}

inline Matrix4& Matrix4::operator*=( const Matrix4& mat)
{
    *(this) = (*(this))*mat;
    return *(this);
}

inline Matrix4& Matrix4::operator*=( float val)
{
    m[0][0] *= val;  m[0][1] *= val;  m[0][2] *= val;  m[0][3] *= val;
    m[1][0] *= val;  m[1][1] *= val;  m[1][2] *= val;  m[1][3] *= val;
    m[2][0] *= val;  m[2][1] *= val;  m[2][2] *= val;  m[2][3] *= val;
    m[3][0] *= val;  m[3][1] *= val;  m[3][2] *= val;  m[3][3] *= val;

    return *(this);
}

inline Matrix4& Matrix4::operator+=( const Matrix4& m2)
{
    m[0][0] += m2.M11; m[0][1] += m2.M12; m[0][2] += m2.M13; m[0][3] += m2.M14;
    m[1][0] += m2.M21; m[1][1] += m2.M22; m[1][2] += m2.M23; m[1][3] += m2.M24;
    m[2][0] += m2.M31; m[2][1] += m2.M32; m[2][2] += m2.M33; m[2][3] += m2.M34;
    m[3][0] += m2.M41; m[3][1] += m2.M42; m[3][2] += m2.M43; m[3][3] += m2.M44;
        
    return *(this);
}

inline Matrix4& Matrix4::operator-=( const Matrix4& m2)
{
    m[0][0] -= m2.M11; m[0][1] -= m2.M12; m[0][2] -= m2.M13; m[0][3] -= m2.M14;
    m[1][0] -= m2.M21; m[1][1] -= m2.M22; m[1][2] -= m2.M23; m[1][3] -= m2.M24;
    m[2][0] -= m2.M31; m[2][1] -= m2.M32; m[2][2] -= m2.M33; m[2][3] -= m2.M34;
    m[3][0] -= m2.M41; m[3][1] -= m2.M42; m[3][2] -= m2.M43; m[3][3] -= m2.M44;
        
    return *(this);
}

inline Matrix4& Matrix4::operator/=( float val)
{
    m[0][0] /= val;  m[0][1] /= val;  m[0][2] /= val;  m[0][3] /= val;
    m[1][0] /= val;  m[1][1] /= val;  m[1][2] /= val;  m[1][3] /= val;
    m[2][0] /= val;  m[2][1] /= val;  m[2][2] /= val;  m[2][3] /= val;
    m[3][0] /= val;  m[3][1] /= val;  m[3][2] /= val;  m[3][3] /= val;
        
    return *(this);
}

inline Matrix4 Matrix4::operator+() const
{
    return (*this);
}

inline Matrix4 Matrix4::operator+( const Matrix4& m2) const
{
    return Matrix4(
            m[0][0]+m2.m[0][0],m[0][1]+m2.m[0][1],m[0][2]+m2.m[0][2],m[0][3]+m2.m[0][3],
            m[1][0]+m2.m[1][0],m[1][1]+m2.m[1][1],m[1][2]+m2.m[1][2],m[1][3]+m2.m[1][3],
            m[2][0]+m2.m[2][0],m[2][1]+m2.m[2][1],m[2][2]+m2.m[2][2],m[2][3]+m2.m[2][3],
            m[3][0]+m2.m[3][0],m[3][1]+m2.m[3][1],m[3][2]+m2.m[3][2],m[3][3]+m2.m[3][3]);
}

inline Matrix4 Matrix4::operator-() const
{
    return (*this)*-1;
}

inline Matrix4 Matrix4::operator*( const Matrix4& m2) const
{
    return Matrix4(
            Matrix4::Dot4hv((*this), m2,0,0),Matrix4::Dot4hv((*this), m2,0,1),Matrix4::Dot4hv((*this), m2,0,2),Matrix4::Dot4hv((*this), m2,0,3),
            Matrix4::Dot4hv((*this), m2,1,0),Matrix4::Dot4hv((*this), m2,1,1),Matrix4::Dot4hv((*this), m2,1,2),Matrix4::Dot4hv((*this), m2,1,3),
            Matrix4::Dot4hv((*this), m2,2,0),Matrix4::Dot4hv((*this), m2,2,1),Matrix4::Dot4hv((*this), m2,2,2),Matrix4::Dot4hv((*this), m2,2,3),
            Matrix4::Dot4hv((*this), m2,3,0),Matrix4::Dot4hv((*this), m2,3,1),Matrix4::Dot4hv((*this), m2,3,2),Matrix4::Dot4hv((*this), m2,3,3));

}

inline Matrix4 Matrix4::operator*( float val) const
{
    return Matrix4(
            m[0][0]*val,m[0][1]*val,m[0][2]*val,m[0][3]*val,
            m[1][0]*val,m[1][1]*val,m[1][2]*val,m[1][3]*val,
            m[2][0]*val,m[2][1]*val,m[2][2]*val,m[2][3]*val,
            m[3][0]*val,m[3][1]*val,m[3][2]*val,m[3][3]*val);
}

inline Matrix4 Matrix4::operator-( const Matrix4& m2) const
{
    return Matrix4(
            m[0][0]-m2.m[0][0],m[0][1]-m2.m[0][1],m[0][2]-m2.m[0][2],m[0][3]-m2.m[0][3],
            m[1][0]-m2.m[1][0],m[1][1]-m2.m[1][1],m[1][2]-m2.m[1][2],m[1][3]-m2.m[1][3],
            m[2][0]-m2.m[2][0],m[2][1]-m2.m[2][1],m[2][2]-m2.m[2][2],m[2][3]-m2.m[2][3],
            m[3][0]-m2.m[3][0],m[3][1]-m2.m[3][1],m[3][2]-m2.m[3][2],m[3][3]-m2.m[3][3]);
}

inline Matrix4 Matrix4::operator/( float val) const
{
    return Matrix4(
            m[0][0]/val,m[0][1]/val,m[0][2]/val,m[0][3]/val,
            m[1][0]/val,m[1][1]/val,m[1][2]/val,m[1][3]/val,
            m[2][0]/val,m[2][1]/val,m[2][2]/val,m[2][3]/val,
            m[3][0]/val,m[3][1]/val,m[3][2]/val,m[3][3]/val);
}

inline bool Matrix4::operator==( const Matrix4& m2) const
{
    return
            m[0][0]==m2.m[0][0] && m[0][1]==m2.m[0][1] && m[0][2]==m2.m[0][2] && m[0][3]==m2.m[0][3] &&
            m[1][0]==m2.m[1][0] && m[1][1]==m2.m[1][1] && m[1][2]==m2.m[1][2] && m[1][3]==m2.m[1][3] &&
            m[2][0]==m2.m[2][0] && m[2][1]==m2.m[2][1] && m[2][2]==m2.m[2][2] && m[2][3]==m2.m[2][3] &&
            m[3][0]==m2.m[3][0] && m[3][1]==m2.m[3][1] && m[3][2]==m2.m[3][2] && m[3][3]==m2.m[3][3];
}

inline bool Matrix4::operator!=( const Matrix4& m2) const
{
    return !((*this)==m2);
}

inline void Matrix4::perspectiveFovLH( float fieldOfViewY,float aspectRatio, float znearPlane, float zfarPlane )
{
    //cotangente(x) = tan(PI/2 - x)
	float h = FastMath::tan(1.57079633f - fieldOfViewY/2);
    float w = h/aspectRatio;
        
    m[0][0] = w; m[0][1] = 0; m[0][2] = 0;                                                                  m[0][3] = 0;
    m[1][0] = 0; m[1][1] = h; m[1][2] = 0;                                                                  m[1][3] = 0;
    m[2][0] = 0; m[2][1] = 0; m[2][2] = zfarPlane/(zfarPlane-znearPlane);   m[2][3] = 1;
    m[3][0] = 0; m[3][1] = 0; m[3][2] = -znearPlane*zfarPlane/(zfarPlane-znearPlane);       m[3][3] = 0;
}

inline Matrix4 Matrix4::Translation( float x, float y, float z )
{
    Matrix4 mat;
    mat.translation(x,y,z);
    return mat;     
}

inline Matrix4 Matrix4::Identity()
{
    Matrix4 mat;
    mat.identity();
    return mat;     
}

inline Matrix4 Matrix4::RotationX( float angle )
{
    Matrix4 mat;
    mat.rotationX(angle);
    return mat;     
}

inline Matrix4 Matrix4::RotationY( float angle )
{
    Matrix4 mat;
    mat.rotationY(angle);
    return mat;     
}

inline Matrix4 Matrix4::RotationZ( float angle )
{
    Matrix4 mat;
    mat.rotationZ(angle);
    return mat;     
}

inline Matrix4 Matrix4::RotationYawPitchRoll( float yaw, float pitch, float roll )
{
    Matrix4 mat;
    mat.rotationYawPitchRoll(yaw,pitch,roll);
    return mat;     
}

inline Matrix4 Matrix4::Scale( float sx, float sy, float sz )
{
    Matrix4 mat;
    mat.scale(sx,sy,sz);
    return mat;     
}

inline Matrix4 Matrix4::PerspectiveFovLH( float fieldOfViewY,float aspectRatio, float znearPlane, float zfarPlane )
{
    Matrix4 mat;
    mat.perspectiveFovLH(fieldOfViewY,aspectRatio, znearPlane, zfarPlane);
    return mat;     
}

inline void Matrix4::transpose()
{
	FastMath::swap(m[0][1],m[1][0]);
    FastMath::swap(m[0][2],m[2][0]);
    FastMath::swap(m[0][3],m[3][0]);
    FastMath::swap(m[1][2],m[2][1]);
    FastMath::swap(m[1][3],m[3][1]);
    FastMath::swap(m[2][3],m[3][2]);
}

inline Matrix4 Matrix4::Transpose( const Matrix4 &mat )
{
    Matrix4 rta = mat;
    rta.transpose();
    return rta;
}

inline Matrix4 Matrix4::Inverse( const Matrix4 &mat )
{
    Matrix4 rta = mat;
    rta.inverse();
    return rta;
}

inline float Matrix4::Dot4hv(const Matrix4& m1, const Matrix4& m2, int r, int c)
{
	return m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
}






}