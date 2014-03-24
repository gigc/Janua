/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/DirectX10/TgcDX10InputLayout.h"
using namespace TgcViewer;


void TgcDX10InputLayout::internalCreate()
{
	ID3D10Device* device = ((TgcDX10Renderer*)GuiController::Instance->renderer)->device;

	this->layoutDesc = new D3D10_INPUT_ELEMENT_DESC[this->elements.size()];
	for(unsigned int i = 0; i < this->elements.size(); i++)
	{
		InputElement::Element element = this->elements[i];

		D3D10_INPUT_ELEMENT_DESC desc;
		desc.SemanticName = this->getSemantic(element.semantic);
		desc.Format = this->getFormat(element.type);
		desc.InputSlot = 0;
		desc.AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
		desc.InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
		desc.SemanticIndex = element.index;

		this->layoutDesc[i] = desc;
	}

	//The ID3D10InputLayout is created later by TgcDX10Effect
	this->layout = NULL;
}

void TgcDX10InputLayout::dispose()
{
	if(this->layoutDesc)
	{
		delete[] this->layoutDesc;
		this->layoutDesc = NULL;
	}
	if(this->layout)
	{
		this->layout->Release();
		this->layout = NULL;
	}
}

LPCSTR TgcDX10InputLayout::getSemantic(InputElement::Semantic semantic)
{
	LPCSTR dxSemantic;
	switch(semantic)
	{
		case InputElement::Position:
			dxSemantic = "POSITION";
			break;
		case InputElement::Normal:
			dxSemantic = "NORMAL";
			break;
		case InputElement::Texcoord:
			dxSemantic = "TEXCOORD";
			break;
		case InputElement::Color:
			dxSemantic = "COLOR";
			break;
		case InputElement::Binormal:
			dxSemantic = "BINORMAL";
			break;
		case InputElement::Tangent:
			dxSemantic = "TANGENT";
			break;
		case InputElement::BlendIndices:
			dxSemantic = "BLENDWEIGHT";
			break;
		case InputElement::BlendWeight:
			dxSemantic = "BLENDWEIGHT";
			break;
		case InputElement::TransformedPosition:
			dxSemantic = "POSITIONT";
			break;
		case InputElement::PointSize:
			dxSemantic = "PSIZE";
			break;
		break;
	}

	return dxSemantic;
}

DXGI_FORMAT TgcDX10InputLayout::getFormat(InputElement::Type type)
{
	DXGI_FORMAT dxFormat;
	switch(type)
	{
		case InputElement::Float:
			dxFormat = DXGI_FORMAT_R32_FLOAT;
			break;
		case InputElement::Float2:
			dxFormat = DXGI_FORMAT_R32G32_FLOAT;
			break;
		case InputElement::Float3:
			dxFormat = DXGI_FORMAT_R32G32B32_FLOAT;
			break;
		case InputElement::Float4:
			dxFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
			break;
		case InputElement::UnsignedInt:
			dxFormat = DXGI_FORMAT_R32_UINT;
			break;
		case InputElement::SignedInt:
			dxFormat = DXGI_FORMAT_R32_SINT;
			break;
	}
	return dxFormat;
}


