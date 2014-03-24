/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <string>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Math/Vector2.h"
#include "TgcViewer/Math/Vector3.h"
#include "TgcViewer/Math/Color.h"


/**
* Enums and constants for render settings
*/
namespace TgcViewer
{

	namespace MeshValues
	{
		/**
		* Different types of mesh
		*/
		enum RenderType
		{
			/**
			* Only vertex color
			*/
			VertexColor,
			/**
			* With a diffuse map
			*/
			DiffuseMap,
			/**
			* With diffuse map and lightmap
			*/
			DiffuseMapAndLightmap,
		};

	}

	namespace BufferUsage
	{
		/**
		* Usage flags for buffers
		*/
		enum Usage
		{
			Default,
			Immutable,
			Dynamic,
			Staging
		};
	}

	namespace BufferMap
	{
		/**
		* Map flags for buffers
		*/
		enum Map
		{
			Read,
			Write,
			ReadWrite,
			WriteDiscard,
			WriteNoOverwrite
		};
	}
	

	namespace PrimitiveTopology
	{
		/**
		* Primitive topology values 
		*/
		enum Topology
		{
			TriangleList,
			TriangleStrip,
			LineList,
			LineStrip,
			PointList
		};
	}


	/**
	* Componentes of the vertex format
	*/
	namespace InputElement
	{
		/**
		* Vertex element semantic
		*/
		enum Semantic
		{
			Position,
			Normal,
			Texcoord,
			Color,
			Binormal,
			Tangent,
			BlendIndices,
			BlendWeight,
			TransformedPosition,
			PointSize
		};

		/**
		* Vertex element type
		*/
		enum Type
		{
			Float,
			Float2,
			Float3,
			Float4,
			UnsignedInt,
			SignedInt
		};

		/**
		* Individual element of the vertex format
		*/
		struct Element
		{
			Semantic semantic;
			Type type;
			int index;
			string name;

			Element(Semantic semantic, Type type, int index = 0, string name = "")
			{
				this->semantic = semantic;
				this->type = type;
				this->index = index;
				if(name != "")
				{
					this->name = name;
				}
				else
				{
					//Generic name based on semantic
					this->name = getSemanticName(this->semantic);

					//Add index if there is more than one
					if(this->index > 0)
					{
						this->name += this->index;
					}
				}
			}

			/**
			* Size of the element in bytes
			*/
			unsigned int size()
			{
				switch(type)
				{
					case Float:
						return sizeof(float);
						break;
					case Float2:
						return sizeof(float) * 2;
						break;
					case Float3:
						return sizeof(float) * 3;
						break;
					case Float4:
						return sizeof(float) * 4;
						break;
					case UnsignedInt:
						return sizeof(unsigned int);
						break;
					case SignedInt:
						return sizeof(signed int);
						break;
				}
				return sizeof(float);
			}

			/**
			* Semantic generic name
			*/
			string getSemanticName(InputElement::Semantic s)
			{
				switch(s)
				{
				case InputElement::Position:
					return "Position";
				case InputElement::Normal:
					return "Normal";
				case InputElement::Texcoord:
					return "Texcoord";
				case InputElement::Color:
					return "Color";
				case InputElement::Binormal:
					return "Binormal";
				case InputElement::Tangent:
					return "Tangent";
				case InputElement::BlendIndices:
					return "BlendIndices";
				case InputElement::BlendWeight:
					return "BlendWeight";
				case InputElement::TransformedPosition:
					return "TransformedPosition";
				case InputElement::PointSize:
					return "PointSize";
				}
				return "";
			}

		};
	}


	namespace TextureFormat
	{
		/**
		* Texture formats
		*/
		enum Format
		{
			R8_UINT,
			R8_SINT,
			R8_UNORM,

			R16_UINT,
			R16_SINT,
			R16_UNORM,
			R16_FLOAT,

			R8G8_UINT,
			R8G8_SINT,
			R8G8_UNORM,

			R32_UINT,
			R32_SINT,
			R32_FLOAT,

			R16G16_UINT,
			R16G16_SINT,
			R16G16_UNORM,
			R16G16_FLOAT,

			R8G8B8A8_UINT,
			R8G8B8A8_SINT,
			R8G8B8A8_UNORM,

			R32G32_UINT,
			R32G32_SINT,
			R32G32_FLOAT,

			R32G32B32_UINT,
			R32G32B32_SINT,
			R32G32B32_FLOAT,

			R16G16B16A16_UINT,
			R16G16B16A16_SINT,
			R16G16B16A16_UNORM,
			R16G16B16A16_FLOAT,

			R32G32B32A32_UINT,
			R32G32B32A32_SINT,
			R32G32B32A32_FLOAT
		};
	}

	
	/**
	* Common vertex formats
	*/
	namespace VertexFormat
	{
		/**
		* Position + Color vertex
		*/
		struct PositionColor
		{
			Vector3 position;
			Color color;

			PositionColor()
			{
			}

			PositionColor(Vector3 position, Color color)
			{
				this->position = position;
				this->color = color;
			}
		};

		/**
		* Position + Texcoord vertex
		*/
		struct PositionTexcoord
		{
			Vector3 position;
			Vector2 texcoord;

			PositionTexcoord()
			{
			}

			PositionTexcoord(Vector3 position, Vector2 texcoord)
			{
				this->position = position;
				this->texcoord = texcoord;
			}
		};

		/**
		* Position + Color + Texcoord vertex
		*/
		struct PositionColorTexcoord
		{
			Vector3 position;
			Color color;
			Vector2 texcoord;

			PositionColorTexcoord()
			{
			}

			PositionColorTexcoord(Vector3 position, Color color, Vector2 texcoord)
			{
				this->position = position;
				this->color = color;
				this->texcoord = texcoord;
			}
		};

	}


	/**
	* Common structs for engine shaders
	*/
	namespace TgcShadersCommon
	{
		/**
		* Constant buffer for common matrix values
		*/
		struct MatrixBuffer
		{
			Matrix4 matWorld;
			Matrix4 matWorldView;
			Matrix4 matWorldViewProj;
			Matrix4 matInverseTransposeWorld;
		};

		/**
		* Constant buffer for 2D text rendering
		*/
		struct TextBuffer
		{
			Color textColor;
		};

		/**
		* Constant buffer for input color
		*/
		struct InputColorBuffer
		{
			Color inputColor;
		};
	}

	/**
	* Fill mode
	*/
	namespace FillMode
	{
		enum Mode
		{
			Solid,
			WireFrame
		};
	}

	/**
	* Elementos to work in screen-space
	*/
	namespace ScreenSpace
	{
		/**
		* A screen rectangle area
		*/
		struct ScreenRect
		{
			float x;
			float y;
			float width;
			float height;

			ScreenRect()
			{
				x = y = width = height = 0.0f;
			}

			ScreenRect(float x, float y, float width, float height)
			{
				this->x = x;
				this->y = y;
				this->width = width;
				this->height = height;
			}

			ScreenRect(Vector2 pos, Vector2 size)
			{
				x = pos.X;
				y = pos.Y;
				width = size.X;
				height = size.Y;
			}

			bool empty()
			{
				return width == 0.0f || height == 0.0f;
			}
		};
	}




	/**
	* Text align
	*/
	namespace TextAlign
	{
		enum Align
		{
			Left,
			Right,
			Center
		};
	}






}