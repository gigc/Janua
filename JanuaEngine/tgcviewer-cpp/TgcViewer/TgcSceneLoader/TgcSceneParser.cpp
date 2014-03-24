/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "TgcViewer/TgcSceneLoader/TgcSceneParser.h"
using namespace TgcViewer;


TgcSceneParser::TgcSceneParser()
{

}


TgcSceneParser::TgcSceneParser(const TgcSceneParser& other)
{
}


TgcSceneParser::~TgcSceneParser()
{
}


TgcSceneData* TgcSceneParser::parseSceneFromFile(string filePath)
{
	//Load XML file
	xml_document doc;
	xml_parse_result result = doc.load_file(filePath.c_str());
	if(!result)
	{
		GuiController::Instance->logger->logError("Error parsing tgcScene.xml: " + filePath);
	}
	xml_node root = doc.child("tgcScene");

	//name
	TgcSceneData* tgcSceneData = new TgcSceneData();
	tgcSceneData->name = root.child("name").child_value();


	//Check texture data
	xml_node texturesExportNode = root.child("texturesExport");
	bool texturesExportEnabled = texturesExportNode.attribute("enabled").as_bool();
    if (texturesExportEnabled)
    {
		tgcSceneData->texturesDir = texturesExportNode.attribute("dir").as_string();
    }

	//Check lightmap data
	xml_node lightmapsExportNode = root.child("lightmapExport");
    tgcSceneData->lightmapsEnabled = lightmapsExportNode.attribute("enabled").as_bool();
    if (tgcSceneData->lightmapsEnabled)
    {
		tgcSceneData->lightmapsDir = lightmapsExportNode.attribute("dir").as_string();
    }

	//sceneBoundingBox (optional)
    xml_node sceneBoundingBoxNode = root.child("sceneBoundingBox");
    if (sceneBoundingBoxNode != NULL)
    {
		tgcSceneData->boundingBox = true;
		TgcParserUtils::parseFloat3Array(sceneBoundingBoxNode.attribute("min").as_string(), tgcSceneData->pMin);
        TgcParserUtils::parseFloat3Array(sceneBoundingBoxNode.attribute("max").as_string(), tgcSceneData->pMax);
    }
	else
	{
		tgcSceneData->boundingBox = false;
	}

	//Parse textures
    xml_node materialsNode = root.child("materials");
	tgcSceneData->materialCount = materialsNode.attribute("count").as_int();
    tgcSceneData->materialsData = new TgcMaterialData*[tgcSceneData->materialCount];
    int i = 0;
	for (xml_node matNode = materialsNode.first_child(); matNode; matNode = matNode.next_sibling())
    {
        //get material type
        TgcMaterialData* material = new TgcMaterialData();
		material->type = matNode.attribute("type").as_string();

        //Standard Material
        if (material->type.compare(TgcMaterialData::StandardMaterial) == 0)
        {
            parseStandardMaterial(material, matNode);
        }

        //Multi Material
        else if (material->type.compare(TgcMaterialData::MultiMaterial) == 0)
        {
            material->name = matNode.attribute("name").as_string();
			vector<TgcMaterialData*> vecSubMaterials;
			for (xml_node subMatNode = matNode.child("subM"); subMatNode; subMatNode = subMatNode.next_sibling("subM"))
			{
				TgcMaterialData* subMaterial = new TgcMaterialData();
				parseStandardMaterial(subMaterial, subMatNode);
				vecSubMaterials.push_back(subMaterial);
			}
			material->subMaterialsCount = vecSubMaterials.size();
			material->subMaterials = new TgcMaterialData*[material->subMaterialsCount];
			for(int j = 0; j < material->subMaterialsCount; j++)
			{
				material->subMaterials[j] = vecSubMaterials[j];
			}
        }

        tgcSceneData->materialsData[i++] = material;
    }



	//Parse meshes
	xml_node meshesNode = root.child("meshes");
	tgcSceneData->meshCount = meshesNode.attribute("count").as_int();
    tgcSceneData->meshesData = new TgcMeshData*[tgcSceneData->meshCount];
    i = 0;
	for (xml_node meshNode = meshesNode.first_child(); meshNode; meshNode = meshNode.next_sibling())
    {
        TgcMeshData* meshData = new TgcMeshData();

        //general values
		meshData->name = meshNode.attribute("name").as_string();
		meshData->materialId = meshNode.attribute("matId").as_int();
        TgcParserUtils::parseFloat3Array(meshNode.attribute("color").as_string(), meshData->color);
		TgcParserUtils::divFloatArrayValues(meshData->color, 3, 255.0f);
        meshData->lightmap = meshNode.attribute("lightmap").as_string();

        //layer
		xml_attribute layerAttr = meshNode.attribute("layer");
        if (layerAttr != NULL)
        {
			meshData->layerName = layerAttr.as_string();
        }

        //visibility
        float visibility = meshNode.attribute("visibility").as_float();
        meshData->alphaBlending = visibility != 1.0f ? true : false;

        //boundingBox
        xml_node boundingBoxNode = meshNode.child("boundingBox");
        if(boundingBoxNode != NULL)
        {
			meshData->boundingBox = true;
            TgcParserUtils::parseFloat3Array(boundingBoxNode.attribute("min").as_string(), meshData->pMin);
            TgcParserUtils::parseFloat3Array(boundingBoxNode.attribute("max").as_string(), meshData->pMax);
        }
		else
		{
			meshData->boundingBox = false;
		}

        //coordinatesIdx
        xml_node coordinatesIdxNode = meshNode.child("coordinatesIdx");
		meshData->coordinatesIndicesCount = coordinatesIdxNode.attribute("count").as_int();
		meshData->coordinatesIndices = new int[meshData->coordinatesIndicesCount];
		TgcParserUtils::parseIntStream(coordinatesIdxNode.child_value(), meshData->coordinatesIndices, meshData->coordinatesIndicesCount);

        //textCoordsIdx
        xml_node textCoordsIdxNode = meshNode.child("textCoordsIdx");
		meshData->texCoordinatesIndicesCount = textCoordsIdxNode.attribute("count").as_int();
		meshData->texCoordinatesIndices = new int[meshData->texCoordinatesIndicesCount];
        TgcParserUtils::parseIntStream(textCoordsIdxNode.child_value(), meshData->texCoordinatesIndices, meshData->texCoordinatesIndicesCount);

        //colorsIdx
        xml_node colorsIdxNode = meshNode.child("colorsIdx");
		meshData->colorIndicesCount = colorsIdxNode.attribute("count").as_int();
		meshData->colorIndices = new int[meshData->colorIndicesCount];
        TgcParserUtils::parseIntStream(colorsIdxNode.child_value(), meshData->colorIndices, meshData->colorIndicesCount);

        //matIds
        if (meshData->materialId != -1)
        {
            xml_node matIdsNode = meshNode.child("matIds");
			meshData->materialsIdsCount = matIdsNode.attribute("count").as_int();
			meshData->materialsIds = new int[meshData->materialsIdsCount];
            TgcParserUtils::parseIntStream(matIdsNode.child_value(), meshData->materialsIds, meshData->materialsIdsCount);
        }
		else
		{
			meshData->materialsIdsCount = 0;
		}

        //textCoordsLightMapIdx
		meshData->lightmapEnabled = tgcSceneData->lightmapsEnabled && TgcParserUtils::trim(meshData->lightmap).length() > 0;
        if (meshData->lightmapEnabled)
        {
            xml_node textCoordsLightMapIdxNode = meshNode.child("textCoordsLightMapIdx");
			meshData->texCoordinatesIndicesLightMapCount = textCoordsLightMapIdxNode.attribute("count").as_int();
			meshData->texCoordinatesIndicesLightMap = new int[meshData->texCoordinatesIndicesLightMapCount];
            TgcParserUtils::parseIntStream(textCoordsLightMapIdxNode.child_value(), meshData->texCoordinatesIndicesLightMap, meshData->texCoordinatesIndicesLightMapCount);
        }
		else
		{
			meshData->texCoordinatesIndicesLightMapCount = 0;
		}


        //vertices
        xml_node verticesNode = meshNode.child("vertices");
		meshData->verticesCoordinatesCount = verticesNode.attribute("count").as_int();
		meshData->verticesCoordinates = new float[meshData->verticesCoordinatesCount];
        TgcParserUtils::parseFloatStream(verticesNode.child_value(), meshData->verticesCoordinates, meshData->verticesCoordinatesCount);

        //parsear normals
        xml_node normalsNode = meshNode.child("normals");
        meshData->verticesNormalsCount = normalsNode.attribute("count").as_int();
		meshData->verticesNormals = new float[meshData->verticesNormalsCount];
        TgcParserUtils::parseFloatStream(normalsNode.child_value(), meshData->verticesNormals, meshData->verticesNormalsCount);

        //tangents (optional)
        xml_node tangentsNode = meshNode.child("tangents");
        if (tangentsNode != NULL)
        {
            meshData->verticesTangentsCount = tangentsNode.attribute("count").as_int();
			meshData->verticesTangents = new float[meshData->verticesTangentsCount];
            TgcParserUtils::parseFloatStream(tangentsNode.child_value(), meshData->verticesTangents, meshData->verticesTangentsCount);
        }
		else
		{
			meshData->verticesTangentsCount = 0;
		}

        //binormals (optional)
        xml_node binormalsNode = meshNode.child("binormals");
        if (binormalsNode != NULL)
        {
            meshData->verticesBinormalsCount = binormalsNode.attribute("count").as_int();
			meshData->verticesBinormals = new float[meshData->verticesBinormalsCount];
            TgcParserUtils::parseFloatStream(binormalsNode.child_value(), meshData->verticesBinormals, meshData->verticesBinormalsCount);
        }
		else
		{
			meshData->verticesBinormalsCount = 0;
		}

        //texCoords
        xml_node texCoordsNode = meshNode.child("texCoords");
        meshData->textureCoordinatesCount = texCoordsNode.attribute("count").as_int();
		meshData->textureCoordinates = new float[meshData->textureCoordinatesCount];
        TgcParserUtils::parseFloatStream(texCoordsNode.child_value(), meshData->textureCoordinates, meshData->textureCoordinatesCount);

        //colors
        xml_node colorsNode = meshNode.child("colors");
        meshData->verticesColorsCount = colorsNode.attribute("count").as_int();
		meshData->verticesColors = new float[meshData->verticesColorsCount];
		TgcParserUtils::parseFloatStream(colorsNode.child_value(), meshData->verticesColors, meshData->verticesColorsCount);
		TgcParserUtils::divFloatArrayValues(meshData->verticesColors, meshData->verticesColorsCount, 255.0f);

        //texCoordsLightMap
        if (meshData->lightmapEnabled)
        {
            xml_node texCoordsLightMapNode = meshNode.child("texCoordsLightMap");
            meshData->textureCoordinatesLightMapCount = texCoordsLightMapNode.attribute("count").as_int();
			meshData->textureCoordinatesLightMap = new float[meshData->textureCoordinatesLightMapCount];
            TgcParserUtils::parseFloatStream(texCoordsLightMapNode.child_value(), meshData->textureCoordinatesLightMap, meshData->textureCoordinatesLightMapCount);
        }
		else
		{
			meshData->textureCoordinatesLightMapCount = 0;
		}


        //userProperties (optional)
		xml_node userPropsNode = meshNode.child("userProps");
        if (userPropsNode != NULL)
        {
			for (xml_node propNode = userPropsNode.first_child(); propNode; propNode = propNode.next_sibling())
			{
				meshData->userProperties[propNode.name()] = propNode.child_value();
			}
        }


		tgcSceneData->meshesData[i++] = meshData;
    }

	return tgcSceneData;
}


void TgcSceneParser::parseStandardMaterial(TgcMaterialData* material, const xml_node &matNode)
{
	material->name = matNode.attribute("name").as_string();
    material->type = matNode.attribute("type").as_string();
	material->subMaterialsCount = 0;

    //Material values
	string ambientStr = matNode.child("ambient").child_value();
    TgcParserUtils::parseFloat4Array(ambientStr, material->ambientColor);
    TgcParserUtils::divFloatArrayValues(material->ambientColor, 4, 255.0f);

    string diffuseStr = matNode.child("diffuse").child_value();
    TgcParserUtils::parseFloat4Array(diffuseStr, material->diffuseColor);
    TgcParserUtils::divFloatArrayValues(material->diffuseColor, 4, 255.0f);

    string specularStr = matNode.child("specular").child_value();
    TgcParserUtils::parseFloat4Array(specularStr, material->specularColor);
    TgcParserUtils::divFloatArrayValues(material->specularColor, 4, 255.0f);

    string opacityStr = matNode.child("opacity").child_value();
    material->opacity = TgcParserUtils::parseFloat(opacityStr) / 100.0f;

    xml_node alphaBlendEnableNode = matNode.child("alphaBlendEnable");
    if (alphaBlendEnableNode != NULL)
    {
        material->alphaBlendEnable = TgcParserUtils::parseBool(alphaBlendEnableNode.child_value());
    }
            
	//Bitmap values
    xml_node bitmapNode = matNode.child("bitmap");
    if (bitmapNode != NULL)
    {
		material->fileName = bitmapNode.child_value();

        //TODO: formatear correctamente TILING y OFFSET
		string uvTilingStr = bitmapNode.attribute("uvTiling").as_string();
        TgcParserUtils::parseFloat2Array(uvTilingStr, material->uvTiling);

        string uvOffsetStr = bitmapNode.attribute("uvOffset").as_string();
        TgcParserUtils::parseFloat2Array(uvOffsetStr, material->uvOffset);
    }
    else
    {
        material->fileName = "";
        //material.uvTiling = null;
        //material.uvOffset = null;
    }
}

