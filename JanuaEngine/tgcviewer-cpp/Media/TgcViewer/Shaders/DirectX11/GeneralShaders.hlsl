/*
* General shaders
*/

/**************************************************************************************/
/* Common vars */
/**************************************************************************************/

//Transformation matrices
cbuffer MatrixBuffer : register(b0)
{
	matrix matWorld;
	matrix matWorldView;
	matrix matWorldViewProj;
	matrix matInverseTransposeWorld;
};


//DiffuseMap
Texture2D texDiffuseMap : register(t0);
SamplerState diffuseMap : register(s0);

cbuffer InputColorBuffer : register(b1)
{
	float4 inputColor;
};


/**************************************************************************************/
/* POSITION_COLOR */
/**************************************************************************************/

struct VS_INPUT_POSITION_COLOR
{
	float4 Position : POSITION;
	float4 Color : COLOR;
};

struct VS_OUTPUT_POSITION_COLOR
{
	float4 Color : COLOR;
	float4 Position : SV_POSITION;
};


VS_OUTPUT_POSITION_COLOR vs_positionColor(VS_INPUT_POSITION_COLOR input)
{
	VS_OUTPUT_POSITION_COLOR output;

	output.Position = mul(input.Position, matWorldViewProj);
	output.Color = input.Color;
	  
	return output;
}

struct PS_INPUT_POSITION_COLOR
{
	float4 Color : COLOR; 
};

float4 ps_positionColor(PS_INPUT_POSITION_COLOR input) : SV_TARGET
{      
	return input.Color;
}



/**************************************************************************************/
/* POSITION_COLOR_TEXCOORD */
/**************************************************************************************/

struct VS_INPUT_POSITION_COLOR_TEXCOORD
{
	float4 Position : POSITION;
	float4 Color : COLOR;
	float2 Texcoord : TEXCOORD0;
};

struct VS_OUTPUT_POSITION_COLOR_TEXCOORD
{
	float4 Color : COLOR;
	float2 Texcoord : TEXCOORD0;
	float4 Position : SV_POSITION;
};


VS_OUTPUT_POSITION_COLOR_TEXCOORD vs_positionColorTexcoord(VS_INPUT_POSITION_COLOR_TEXCOORD input)
{
	VS_OUTPUT_POSITION_COLOR_TEXCOORD output;

	output.Position = mul(input.Position, matWorldViewProj);
	output.Color = input.Color;
	output.Texcoord = input.Texcoord;
	  
	return output;
}

struct PS_INPUT_POSITION_COLOR_TEXCOORD
{
	float4 Color : COLOR; 
	float2 Texcoord : TEXCOORD0;
};

float4 ps_positionColorTexcoord(PS_INPUT_POSITION_COLOR_TEXCOORD input) : SV_TARGET
{      
	return texDiffuseMap.Sample(diffuseMap, input.Texcoord) * input.Color;
}


/**************************************************************************************/
/* POSITION_COLOR_TEXCOORD_NO_TEXTURE */
/**************************************************************************************/

struct VS_INPUT_POSITION_COLOR_TEXCOORD_NO_TEXTURE
{
	float4 Position : POSITION;
	float4 Color : COLOR;
	float2 Texcoord : TEXCOORD0;
};

struct VS_OUTPUT_POSITION_COLOR_TEXCOORD_NO_TEXTURE
{
	float4 Color : COLOR;
	float2 Texcoord : TEXCOORD0;
	float4 Position : SV_POSITION;
};


VS_OUTPUT_POSITION_COLOR_TEXCOORD_NO_TEXTURE vs_positionColorTexcoordNoTexture(VS_INPUT_POSITION_COLOR_TEXCOORD_NO_TEXTURE input)
{
	VS_OUTPUT_POSITION_COLOR_TEXCOORD_NO_TEXTURE output;

	output.Position = mul(input.Position, matWorldViewProj);
	output.Color = input.Color;
	output.Texcoord = input.Texcoord;
	  
	return output;
}

struct PS_INPUT_POSITION_COLOR_TEXCOORD_NO_TEXTURE
{
	float4 Color : COLOR; 
	float2 Texcoord : TEXCOORD0;
};

float4 ps_positionColorTexcoordNoTexture(PS_INPUT_POSITION_COLOR_TEXCOORD_NO_TEXTURE input) : SV_TARGET
{      
	return input.Color;
}


/**************************************************************************************/
/* TRANSFORMED_POSITION_TEXCOORD */
/**************************************************************************************/

struct VS_INPUT_TRANSFORMED_POSITION_TEXCOORD
{
	float4 Position : POSITION;
	float2 Texcoord : TEXCOORD0;
};

struct VS_OUTPUT_TRANSFORMED_POSITION_TEXCOORD
{
	float2 Texcoord : TEXCOORD0;
	float4 Position : SV_POSITION;
};


VS_OUTPUT_TRANSFORMED_POSITION_TEXCOORD vs_transformedPositionTexcoord(VS_INPUT_TRANSFORMED_POSITION_TEXCOORD input)
{
	VS_OUTPUT_TRANSFORMED_POSITION_TEXCOORD output;

	output.Position = float4(input.Position.xy, 0, 1);
	output.Texcoord = input.Texcoord;
	  
	return output;
}

struct PS_INPUT_TRANSFORMED_POSITION_TEXCOORD
{
	float2 Texcoord : TEXCOORD0;
};

float4 ps_transformedPositionTexcoord(PS_INPUT_TRANSFORMED_POSITION_TEXCOORD input) : SV_TARGET
{      
	return texDiffuseMap.Sample(diffuseMap, input.Texcoord) * inputColor;
}










