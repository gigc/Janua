/*
* Text 2D shader
*/

/**************************************************************************************/
/* Common vars */
/**************************************************************************************/

//DiffuseMap
Texture2D texDiffuseMap : register(t0);
SamplerState diffuseMap : register(s0);

cbuffer TextBuffer : register(b0)
{
	float4 textColor;
};



/**************************************************************************************/
/* TEXT_2D */
/**************************************************************************************/

struct VS_INPUT_TEXT_2D
{
	float4 Position : POSITION;
	float2 Texcoord : TEXCOORD0;
};

struct VS_OUTPUT_TEXT_2D
{
	float2 Texcoord : TEXCOORD0;
	float4 Position : SV_POSITION;
};


VS_OUTPUT_TEXT_2D vs_text2d(VS_INPUT_TEXT_2D input)
{
	VS_OUTPUT_TEXT_2D output;

	output.Position = float4(input.Position.xy, 0, 1);
	output.Texcoord = input.Texcoord;
	  
	return output;
}

struct PS_INPUT_TEXT_2D
{
	float2 Texcoord : TEXCOORD0;
};

float4 ps_text2d(PS_INPUT_TEXT_2D input) : SV_TARGET
{   
	float4 bitmapColor = texDiffuseMap.Sample(diffuseMap, input.Texcoord);
	
	if(bitmapColor.r == 1.0f)
	{
		bitmapColor = textColor;
	}
	else
	{
		bitmapColor.a = 0.0f;
	}
	return bitmapColor;
}






