/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include "Examples/TgcViewerIncludes.h"
#include <D3DX10math.h>

namespace Examples {class BorderBox;}


namespace Examples
{

struct Ray
{
	Vector3 origin;
	Vector3 dir;
};

/**
* Axis aligned bounding box
*/
struct AABB
{
	Vector3 min;
	Vector3 max;

	AABB()
	{
		min = Vector3(0, 0, 0);
		max = Vector3(0, 0, 0);
	}

	AABB(Vector3 min, Vector3 max)
	{
		this->min = min;
		this->max = max;
	}

	/**
	* Test AABB-AABB
	*/
	static bool testAABBAABB(AABB a, AABB b)
    {
        // Exit with no intersection if separated along an axis
        if (a.max.X < b.min.X || a.min.X > b.max.X) return false;
        if (a.max.Y < b.min.Y || a.min.Y > b.max.Y) return false;
        if (a.max.Z < b.min.Z || a.min.Z > b.max.Z) return false;
        // Overlapping on all axes means AABBs are intersecting
        return true;
    }

	/**
	* Ray-AABB Colision
	*/
    static bool intersectRayAABB(Ray ray, AABB aabb, Vector3 &q)
    {
        bool inside = true;

        float max_t[] = {-1.0f, -1.0f, -1.0f};
        float coord[3];

        for (unsigned int i = 0; i < 3; ++i)
        {
			if (ray.origin.v[i] < aabb.min.v[i])
            {
                inside = false;
                coord[i] = aabb.min.v[i];

				if (ray.dir.v[i] != 0.0f)
                {
                    max_t[i] = (aabb.min.v[i] - ray.origin.v[i]) / ray.dir.v[i];
                }
            }
            else if (ray.origin.v[i] > aabb.max.v[i])
            {
                inside = false;
                coord[i] = aabb.max.v[i];

                if (ray.dir.v[i] != 0.0f)
                {
                    max_t[i] = (aabb.max.v[i] - ray.origin.v[i]) / ray.dir.v[i];
                }
            }
        }

        // If the Ray's start position is inside the Box, we can return true straight away.
        if (inside)
        {
			q = ray.origin;
            return true;
        }

        unsigned int plane = 0;
        if (max_t[1] > max_t[plane])
        {
            plane = 1;
        }
        if (max_t[2] > max_t[plane])
        {
            plane = 2;
        }
            
        if (max_t[plane] < 0.0f)
        {
            return false;
        }

        for (unsigned int i = 0; i < 3; ++i)
        {
            if (plane != i)
            {
                coord[i] = ray.origin.v[i] + max_t[plane] * ray.dir.v[i];

                if (coord[i] < aabb.min.v[i] - 0.001f || coord[i] > aabb.max.v[i] + 0.001f)
                {
                    return false;
                }
            }
        }

        q = Vector3(coord);
        return true;
    }

};


struct PickingRay
{
	Ray ray;

	void update()
	{
        //Crear Ray en base a coordenadas del mouse
		float sx = (float)GuiController::Instance->input->mouseX;
        float sy = (float)GuiController::Instance->input->mouseY;
		int w = GuiController::Instance->windowHandler->screenWidth;
        int h = GuiController::Instance->windowHandler->screenHeight;
		Matrix4 matProj = GuiController::Instance->renderer->projectionMatrix;

        Vector3 v;
        v.X = (((2.0f * sx) / w) - 1) / matProj.M11;
        v.Y = -(((2.0f * sy) / h) - 1) / matProj.M22;
        v.Z = 1.0f;

        //Transform the screen space pick ray into 3D space
        //Matrix4 m = Matrix4::SInvert(GuiController::Instance->renderer->viewMatrix);

		
		
		
		Matrix4 view = GuiController::Instance->renderer->viewMatrix;
		D3DXMATRIX dxView = D3DXMATRIX(
			view.M11, view.M12, view.M13, view.M14, 
			view.M21, view.M22, view.M23, view.M24, 
			view.M31, view.M32, view.M33, view.M34, 
			view.M41, view.M42, view.M43, view.M44
			);
		D3DXMATRIX mOut;
		D3DXMatrixInverse(&mOut, NULL, &dxView);
		Matrix4 m = Matrix4(
			mOut._11, mOut._12, mOut._13, mOut._14, 
			mOut._21, mOut._22, mOut._23, mOut._24, 
			mOut._31, mOut._32, mOut._33, mOut._34, 
			mOut._41, mOut._42, mOut._43, mOut._44 
			);
		
		//Matrix4 m = Matrix4::SInverse(GuiController::Instance->renderer->viewMatrix);
        
		Vector3 rayDir = Vector3(
            v.X * m.M11 + v.Y * m.M21 + v.Z * m.M31,
            v.X * m.M12 + v.Y * m.M22 + v.Z * m.M32,
            v.X * m.M13 + v.Y * m.M23 + v.Z * m.M33
            );
        Vector3 rayOrig = Vector3(m.M41, m.M42, m.M43);


        //Picking Ray creado
        ray.origin = rayOrig;
        ray.dir = rayDir;
	}
};



/**
* EditorBox
*/
class EditorBox
{



public:

	enum BoxFace {
		Front = 0,
		Back = 1,
		Top = 2,
		Bottom = 3,
		Left = 4,
		Right = 5,
		None = -1
	};


	EditorBox();
	EditorBox(const EditorBox&);
	~EditorBox();

	void create();
	void updateValues();
	void render();
	void dispose();
	void setExtremes(Vector3 min, Vector3 max);
	EditorBox::BoxFace pickFace();
	AABB getFaceAABB(EditorBox::BoxFace face);

private:
	



public:

	static const int VERTEX_COUNT = 36;

	TgcVertexBuffer* vertexBuffer;
	TgcIndexBuffer* indexBuffer;
	TgcEffect* effect;

	Vector3 size;
	Vector3 position;
	Color commonColor;
	Color selectedColor;
	Matrix4 transform;
	AABB aabb;
	BorderBox* border;


	BoxFace selectedFace;
	bool selected;



private:


};




}