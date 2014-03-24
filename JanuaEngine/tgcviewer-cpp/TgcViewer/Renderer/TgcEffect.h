/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <string>
#include <unordered_map>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Renderer/TgcVertexBuffer.h"
#include "TgcViewer/TgcSceneLoader/TgcTexture.h"
#include "TgcViewer/Math/Color.h"

//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;}

namespace TgcViewer
{

	/**
	* Enums and structs for effect definition
	*/
	namespace TgcEffectValues
	{
		/**
		* Description of the effect features
		*/
		struct Description
		{
			string vsFunctionName;
			string psFunctionName;
			//TODO: otros tipos de shaders
			//TODO: parametros de include y define de DX11

			Description()
			{
			}

			Description(string vsFunctionName, string psFunctionName)
			{
				this->vsFunctionName = vsFunctionName;
				this->psFunctionName = psFunctionName;
			}
		};

		/**
		* Type of pixel shader
		*/
		enum ShaderType
		{
			VS,
			PS,
			VS_AND_PS
			//TODO: agregar los otros shaders
		};

		/**
		* Texture filter types for a sampler
		*/
		enum Filter
		{
			MinMagMipPoint,
			MinMagMipLinear,
			Anisotropic
			//TODO: ver que otros filter agregar: http://msdn.microsoft.com/en-us/library/windows/desktop/ff476132(v=vs.85).aspx
		};

		/**
		* Texture coordinates address mode
		*/
		enum AddressMode
		{
			Wrap,
			Mirror,
			Clamp,
			Border,
			MirrorOnce
		};

		/**
		* A texture sampler for the effect
		*/
		struct Sampler
		{
			string samplerName;
			string textureName;
			unsigned int slot;
			ShaderType shaderType;
			Filter filter;
			AddressMode addressU;
			AddressMode addressV;
			AddressMode addressW;
			Color borderColor;
			//TODO: ver otros parametros de sampler: http://msdn.microsoft.com/en-us/library/windows/desktop/ff476207(v=vs.85).aspx

			Sampler()
			{
				this->shaderType = TgcEffectValues::PS;
				this->slot = 0;
				this->filter = TgcEffectValues::MinMagMipLinear;
				this->addressU = TgcEffectValues::Wrap;
				this->addressV = TgcEffectValues::Wrap;
				this->addressW = TgcEffectValues::Wrap;
				this->borderColor = Color::Black;
			}

			Sampler(string samplerName, string textureName, ShaderType shaderType = TgcEffectValues::PS, unsigned int slot = 0)
			{
				this->samplerName = samplerName;
				this->textureName = textureName;
				this->shaderType = shaderType;
				this->slot = slot;
				this->filter = TgcEffectValues::MinMagMipLinear;
				this->addressU = TgcEffectValues::Wrap;
				this->addressV = TgcEffectValues::Wrap;
				this->addressW = TgcEffectValues::Wrap;
				this->borderColor = Color::Black;
			}
		};

		/**
		* A constant buffer for the effect
		*/
		struct ConstantBuffer
		{
			string name;
			ShaderType shaderType;
			unsigned int size;
			unsigned int slot;

			ConstantBuffer()
			{
				this->shaderType = TgcEffectValues::VS;
				this->slot = 0;
			}

			ConstantBuffer(string name, ShaderType shaderType, unsigned int size, unsigned int slot = 0)
			{
				this->name = name;
				this->shaderType = shaderType;
				this->size = size;
				this->slot = slot;
			}
			
		};

	}

/**
* Represents a shader effect composed of one sigle pass and one technique
* 
* The creation steps are:
*	- create()
*	- addSampler()
*	- addConstantBuffer()
* 
* The render steps are:
*	- begin()
*	- setTexture()
*	- setConstantBuffer
*	- {draw}
*	- end()
* 
*/
class TgcEffect
{

public:

	TgcEffect();
	TgcEffect(const TgcEffect&);
	~TgcEffect();

	/**
	* Constructor helper
	*/
	static TgcEffect* createFromFile(string filePath, string vsFunctionName, string psFunctionName);



	/**
	* Creates the effect from a shader file
	* @param filePath path of the shader file
	*/
	void create(string filePath, TgcEffectValues::Description desc);

	/**
	* Adds a new texture sampler to the effect
	*/
	void addSampler(TgcEffectValues::Sampler sampler);
	
	/**
	* Adds a new constant buffer to the effect
	*/
	void addConstantBuffer(TgcEffectValues::ConstantBuffer constantBuffer);

	/**
	* Init the shader for the vertex buffer input layout
	*/
	virtual void init(const TgcVertexBuffer* vertexBuffer) = 0;

	/**
	* Init the effect before drawing
	*/
	virtual void begin() = 0;

	/**
	* Set a texture to be used by the effect
	* @param name texture name used in TgcEffectValues::Sampler
	* @param texture
	*/
	virtual void setTexture(string name, const TgcTexture* texture) = 0;

	/**
	* Set constant buffer values to be used by the effect
	* @param name constant buffer name used in TgcEffectValues::ConstantBuffer
	* @param bufferData pointer to the constant buffer struct with the values allready filled
	*/
	virtual void setConstantBuffer(string name, const void* bufferData) = 0;

	/**
	* Ends the effect after drawing
	*/
	virtual void end() = 0;


	/**
	* Frees resources
	*/
	virtual void dispose() = 0;





	/**
	* {Renderer-dependent}
	* Create effect
	*/
	virtual void internalCreate() = 0;

	/**
	* {Renderer-dependent}
	* Add sampler
	*/
	virtual void internalAddSampler(TgcEffectValues::Sampler sampler) = 0;

	/**
	* {Renderer-dependent}
	* Add constant buffer
	*/
	virtual void internalAddConstantBuffer(TgcEffectValues::ConstantBuffer constantBuffer) = 0;


private:

public:

	/**
	* File path of the effect
	*/
	string filePath;

	/**
	* Description of the effect
	*/
	TgcEffectValues::Description description;


	/**
	* Texture samples of the effect
	*/
	unordered_map<string, TgcEffectValues::Sampler> samplers;

	/**
	* Constant buffers of the effect
	*/
	unordered_map<string, TgcEffectValues::ConstantBuffer> constantBuffers;

private:

	
};




}