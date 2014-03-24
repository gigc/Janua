/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Math/Matrix4.h"
#include "TgcViewer/Math/Vector3.h" //Forward declaration
using namespace TgcViewer;


const float Matrix4::MATRIX_INVERSE_EPSILON = 1e-14f;




void Matrix4::translation(const Vector3 &v)
{
	return translation(v.X, v.Y, v.Z);
}

void Matrix4::rotationAxis(const Vector3 &vector, float angle )
{
    float sin_a = FastMath::sin( angle ); 
    float cos_a = FastMath::cos( angle ); 
    float t = 1 - cos_a;
        
    float x_y = vector.X * vector.Y; 
    float x_z = vector.X * vector.Z; 
    float y_z = vector.Y * vector.Z; 
        
    m[0][0] = 1 + t * ( vector.X * vector.X - 1 ); 
    m[0][1] = -vector.Z * sin_a + t * x_y;     
    m[0][2] =  vector.Y * sin_a + t * x_z; 
    m[0][3] = 0; 
    
    m[1][0] = vector.Z * sin_a + t * x_y; 
    m[1][1] = 1 + t * ( vector.Y * vector.Y - 1 ); 
    m[1][2] = -vector.X * sin_a + t * y_z; 
    m[1][3] = 0; 
        
    m[2][0] = -vector.Y * sin_a + t * x_z; 
    m[2][1] =  vector.X * sin_a + t * y_z; 
    m[2][2] = 1 + t * ( vector.Z * vector.Z -1 ); 
    m[2][3] = 0; 
    
    m[3][0] = 0;          
    m[3][1] = 0; 
    m[3][2] = 0; 
    m[3][3] = 1; 
}

void Matrix4::scale(const Vector3 &v)
{
	return scale(v.X, v.Y, v.Z);
}

void Matrix4::lookAtLH( const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector )
{
    Vector3 zaxis = Vector3::Normalize(cameraTarget - cameraPosition);
    Vector3 xaxis = Vector3::Normalize(cameraUpVector.cross(zaxis));
    Vector3 yaxis = Vector3::Normalize(zaxis.cross(xaxis));

    m[0][0] = xaxis.X; m[0][1] = yaxis.X; m[0][2] = zaxis.X; m[0][3] = 0;
    m[1][0] = xaxis.Y; m[1][1] = yaxis.Y; m[1][2] = zaxis.Y, m[1][3] = 0;
    m[2][0] = xaxis.Z; m[2][1] = yaxis.Z; m[2][2] = zaxis.Z, m[2][3] = 0;
    m[3][0] = -xaxis.dot(cameraPosition); m[3][1] = -yaxis.dot(cameraPosition); m[3][2] = -zaxis.dot(cameraPosition); m[3][3] = 1;
}

Matrix4 Matrix4::Translation(const Vector3 &v)
{
	return Matrix4::Translation(v.X, v.Y, v.Z);
}

Matrix4 Matrix4::RotationAxis(const Vector3 &vector, float angle )
{
    Matrix4 mat;
    mat.rotationAxis(vector,angle);
    return mat;     
}

Matrix4 Matrix4::Scale(const Vector3 &v)
{
	return Matrix4::Scale(v.X, v.Y, v.Z);
}

Matrix4 Matrix4::LookAtLH( const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector )
{
    Matrix4 mat;
    mat.lookAtLH(cameraPosition, cameraTarget,cameraUpVector);
    return mat;
}

bool Matrix4::inverse()
{
	// 84+4+16 = 104 multiplications
	//			   1 division
	//double det, invDet;
	float det, invDet;
	
	// 2x2 sub-determinants required to calculate 4x4 determinant
	float det2_01_01 = m[0][0] * m[1][1] - m[1][0] * m[0][1];
	float det2_01_02 = m[0][0] * m[2][1] - m[2][0] * m[0][1];
	float det2_01_03 = m[0][0] * m[3][1] - m[3][0] * m[0][1];
	float det2_01_12 = m[1][0] * m[2][1] - m[2][0] * m[1][1];
	float det2_01_13 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
	float det2_01_23 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
	
	// 3x3 sub-determinants required to calculate 4x4 determinant
	float det3_201_012 = m[0][2] * det2_01_12 - m[1][2] * det2_01_02 + m[2][2] * det2_01_01;
	float det3_201_013 = m[0][2] * det2_01_13 - m[1][2] * det2_01_03 + m[3][2] * det2_01_01;
	float det3_201_023 = m[0][2] * det2_01_23 - m[2][2] * det2_01_03 + m[3][2] * det2_01_02;
	float det3_201_123 = m[1][2] * det2_01_23 - m[2][2] * det2_01_13 + m[3][2] * det2_01_12;
	
	det = ( - det3_201_123 * m[0][3] + det3_201_023 * m[1][3] - det3_201_013 * m[2][3] + det3_201_012 * m[3][3] );
	
	if ( fabs( det ) < MATRIX_INVERSE_EPSILON ) {
		return false;
	}
	
	invDet = 1.0f / det;
	
	// remaining 2x2 sub-determinants
	float det2_03_01 = m[0][0] * m[1][3] - m[1][0] * m[0][3];
	float det2_03_02 = m[0][0] * m[2][3] - m[2][0] * m[0][3];
	float det2_03_03 = m[0][0] * m[3][3] - m[3][0] * m[0][3];
	float det2_03_12 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
	float det2_03_13 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
	float det2_03_23 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
	
	float det2_13_01 = m[0][1] * m[1][3] - m[1][1] * m[0][3];
	float det2_13_02 = m[0][1] * m[2][3] - m[2][1] * m[0][3];
	float det2_13_03 = m[0][1] * m[3][3] - m[3][1] * m[0][3];
	float det2_13_12 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
	float det2_13_13 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
	float det2_13_23 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
	
	// remaining 3x3 sub-determinants
	float det3_203_012 = m[0][2] * det2_03_12 - m[1][2] * det2_03_02 + m[2][2] * det2_03_01;
	float det3_203_013 = m[0][2] * det2_03_13 - m[1][2] * det2_03_03 + m[3][2] * det2_03_01;
	float det3_203_023 = m[0][2] * det2_03_23 - m[2][2] * det2_03_03 + m[3][2] * det2_03_02;
	float det3_203_123 = m[1][2] * det2_03_23 - m[2][2] * det2_03_13 + m[3][2] * det2_03_12;
	
	float det3_213_012 = m[0][2] * det2_13_12 - m[1][2] * det2_13_02 + m[2][2] * det2_13_01;
	float det3_213_013 = m[0][2] * det2_13_13 - m[1][2] * det2_13_03 + m[3][2] * det2_13_01;
	float det3_213_023 = m[0][2] * det2_13_23 - m[2][2] * det2_13_03 + m[3][2] * det2_13_02;
	float det3_213_123 = m[1][2] * det2_13_23 - m[2][2] * det2_13_13 + m[3][2] * det2_13_12;
	
	float det3_301_012 = m[0][3] * det2_01_12 - m[1][3] * det2_01_02 + m[2][3] * det2_01_01;
	float det3_301_013 = m[0][3] * det2_01_13 - m[1][3] * det2_01_03 + m[3][3] * det2_01_01;
	float det3_301_023 = m[0][3] * det2_01_23 - m[2][3] * det2_01_03 + m[3][3] * det2_01_02;
	float det3_301_123 = m[1][3] * det2_01_23 - m[2][3] * det2_01_13 + m[3][3] * det2_01_12;
	
	m[0][0] =	- det3_213_123 * invDet;
	m[1][0] = + det3_213_023 * invDet;
	m[2][0] = - det3_213_013 * invDet;
	m[3][0] = + det3_213_012 * invDet;
	
	m[0][1] = + det3_203_123 * invDet;
	m[1][1] = - det3_203_023 * invDet;
	m[2][1] = + det3_203_013 * invDet;
	m[3][1] = - det3_203_012 * invDet;
	
	m[0][2] = + det3_301_123 * invDet;
	m[1][2] = - det3_301_023 * invDet;
	m[2][2] = + det3_301_013 * invDet;
	m[3][2] = - det3_301_012 * invDet;
	
	m[0][3] = - det3_201_123 * invDet;
	m[1][3] = + det3_201_023 * invDet;
	m[2][3] = - det3_201_013 * invDet;
	m[3][3] = + det3_201_012 * invDet;
	
	return true;
}




