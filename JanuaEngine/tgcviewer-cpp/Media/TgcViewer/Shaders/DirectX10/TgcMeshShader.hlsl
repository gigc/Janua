/*
* Generic effect for TgcMesh.
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

//Lightmap
Texture2D texLightMap : register(t1);
SamplerState lightMap : register(s1);



/**************************************************************************************/
/* VERTEX_COLOR */
/**************************************************************************************/

struct VS_INPUT_VERTEX_COLOR 
{
	float4 Position : POSITION;
	float3 Normal : NORMAL;
	float4 Color : COLOR;
};

struct VS_OUTPUT_VERTEX_COLOR
{
	float4 Color : COLOR;
	float4 Position : SV_POSITION;
};


VS_OUTPUT_VERTEX_COLOR vs_VertexColor(VS_INPUT_VERTEX_COLOR input)
{
	VS_OUTPUT_VERTEX_COLOR output;

	output.Position = mul(input.Position, matWorldViewProj);
	output.Color = input.Color;
	  
	return output;
}

struct PS_INPUT_VERTEX_COLOR 
{
	float4 Color : COLOR; 
};

float4 ps_VertexColor(PS_INPUT_VERTEX_COLOR input) : SV_TARGET
{      
	return input.Color;
}


/**************************************************************************************/
/* DIFFUSE_MAP */
/**************************************************************************************/

struct VS_INPUT_DIFFUSE_MAP
{
	float4 Position : POSITION;
	float3 Normal : NORMAL;
	float4 Color : COLOR;
	float2 Texcoord : TEXCOORD0;
};

struct VS_OUTPUT_DIFFUSE_MAP
{
	float4 Color : COLOR;
	float2 Texcoord : TEXCOORD0;
	float4 Position : SV_POSITION;
};


VS_OUTPUT_DIFFUSE_MAP vs_DiffuseMap(VS_INPUT_DIFFUSE_MAP input)
{
	VS_OUTPUT_DIFFUSE_MAP output;

	output.Position = mul(input.Position, matWorldViewProj);
	output.Color = input.Color;
	output.Texcoord = input.Texcoord;
	  
	return output;
}

struct PS_DIFFUSE_MAP
{
	float4 Color : COLOR;
	float2 Texcoord : TEXCOORD0;
};

float4 ps_DiffuseMap(PS_DIFFUSE_MAP input) : SV_TARGET
{      
	return texDiffuseMap.Sample(diffuseMap, input.Texcoord) * input.Color;
}



/**************************************************************************************/
/* DIFFUSE_MAP_AND_LIGHTMAP */
/**************************************************************************************/

struct VS_INPUT_DIFFUSE_MAP_AND_LIGHTMAP
{
	float4 Position : POSITION;
	float3 Normal : NORMAL;
	float4 Color : COLOR;
	float2 Texcoord : TEXCOORD0;
	float2 TexcoordLightmap : TEXCOORD1;
};

struct VS_OUTPUT_DIFFUSE_MAP_AND_LIGHTMAP
{
	float4 Color : COLOR;
	float2 Texcoord : TEXCOORD;
	float2 TexcoordLightmap : TEXCOORD1;
	float4 Position : SV_POSITION;
};

VS_OUTPUT_DIFFUSE_MAP_AND_LIGHTMAP vs_diffuseMapAndLightmap(VS_INPUT_DIFFUSE_MAP_AND_LIGHTMAP input)
{
	VS_OUTPUT_DIFFUSE_MAP_AND_LIGHTMAP output;

	output.Position = mul(input.Position, matWorldViewProj);
	output.Color = input.Color;
	output.Texcoord = input.Texcoord;
	output.TexcoordLightmap = input.TexcoordLightmap;

	return output;
}


struct PS_INPUT_DIFFUSE_MAP_AND_LIGHTMAP
{
	float4 Color : COLOR;
	float2 Texcoord : TEXCOORD0;
	float2 TexcoordLightmap : TEXCOORD1;
};


float4 ps_diffuseMapAndLightmap(PS_INPUT_DIFFUSE_MAP_AND_LIGHTMAP input) : SV_TARGET
{      
	float4 albedo = texDiffuseMap.Sample(diffuseMap, input.Texcoord);
	float4 lightmapColor = texLightMap.Sample(lightMap, input.TexcoordLightmap);
	return albedo * lightmapColor * input.Color;
}


