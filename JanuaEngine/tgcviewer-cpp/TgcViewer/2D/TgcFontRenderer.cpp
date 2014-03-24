/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/2D/TgcFontRenderer.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcFontRenderer::TgcFontRenderer()
{
	//input layout
	TgcInputLayout* inputLayout = GuiController::Instance->renderer->createTgcInputLayoutInstance();
	inputLayout->elements.push_back(InputElement::Element(InputElement::Position, InputElement::Float3, 0));
	inputLayout->elements.push_back(InputElement::Element(InputElement::Texcoord, InputElement::Float2, 0));
	inputLayout->create();

	//Vertex buffer
	VertexFormat::PositionTexcoord vertices[VERTEX_COUNT];
	vertexBuffer = GuiController::Instance->renderer->createTgcVertexBufferInstance();
	vertexBuffer->create(VERTEX_COUNT, inputLayout, vertices, BufferUsage::Dynamic);

	//Shader
	this->effect = GuiController::Instance->shaders->text2dShader;
	this->effect->init(this->vertexBuffer);

	//Load common fonts
	loadFont(TgcFont::MICROSOFT_SANS_SERIF_12);
	loadFont(TgcFont::MICROSOFT_SANS_SERIF_16);
	loadFont(TgcFont::MICROSOFT_SANS_SERIF_20);
	loadFont(TgcFont::MICROSOFT_SANS_SERIF_26);
}


TgcFontRenderer::TgcFontRenderer(const TgcFontRenderer& other)
{
}


TgcFontRenderer::~TgcFontRenderer()
{
}

void TgcFontRenderer::loadFont(string id)
{
	this->loadFont(id, GuiController::Instance->engineMediaPath + "Fonts\\");
}

void TgcFontRenderer::loadFont(string id, string fontFolderPath)
{
	unordered_map<string, TgcFont*>::iterator  it = this->fonts.find(id);

	//Load new font
	if (it == this->fonts.end())
	{
		TgcFont* font = new TgcFont();
		font->loadFromFile(id, fontFolderPath + id + ".bmp", fontFolderPath + id + ".csv");
		this->fonts[id] = font;
	}
}

void TgcFontRenderer::render(TgcText2d* text2d)
{
	int vertexToDraw = text2d->text.length() * 6;
	if(vertexToDraw > VERTEX_COUNT)
	{
		GuiController::Instance->logger->logError("The text is too large to render in one peace. Text: " + text2d->text);
		return;
	}

	//Map vertexBuffer for update
	VertexFormat::PositionTexcoord* vertexData = (VertexFormat::PositionTexcoord*)this->vertexBuffer->map(BufferMap::WriteDiscard);
	
	//Compute the vertex coordinates and UV for each word
	vector<string> words = splitText(text2d->text);
	Vector2 currentPos = text2d->position;
	int lineStartVertex = 0;
	int currentVertex = 0;
	int initWordVertex;
	TgcFont* font = this->fonts[text2d->fontId];
	float initWordX = 0;
	int linesCount = 1;
	const int w = GuiController::Instance->windowHandler->screenWidth;
	const int h = GuiController::Instance->windowHandler->screenHeight;
	for(unsigned int i = 0; i < words.size(); i++)
	{
		//Compute coordinates for one word
		initWordVertex = currentVertex;
		initWordX = currentPos.X;
		updateVertexDataForWord(words[i], vertexData, currentPos, font, currentVertex);

		//Word wrap
		if(currentPos.X >= text2d->position.X + text2d->size.X)
		{
			//Apply text align
			float diff = 0;
			if(text2d->align == TextAlign::Center)
			{
				diff = FastMath::floor((text2d->size.X - (currentPos.X - text2d->position.X)) / 2);
			}
			else if(text2d->align == TextAlign::Right)
			{
				diff = text2d->position.X + text2d->size.X - currentPos.X;
			}
			if(diff != 0)
			{
				for(int j = lineStartVertex; j < initWordVertex; j++)
				{
					//The adjustment must be in screen-space
					Vector2 alignAdjust = vertexData[j].position.toVector2XY();
					toWorldSpace(alignAdjust);
					alignAdjust.X += diff;
					toScreenSpace(alignAdjust);

					vertexData[j].position.X = alignAdjust.X;
				}
			}
			
			
			//Move the last word to the next line
			const float offsetX = initWordX - text2d->position.X;
			for(int j = initWordVertex; j < currentVertex; j++)
			{
				//The adjustment must be in screen-space
				Vector2 wrapAdjust = vertexData[j].position.toVector2XY();
				toWorldSpace(wrapAdjust);
				wrapAdjust.X -= offsetX;
				wrapAdjust.Y += (float)font->height;
				toScreenSpace(wrapAdjust);

				vertexData[j].position = Vector3(wrapAdjust.X, wrapAdjust.Y, 1);
			}
			
			//Jump to next line
			currentPos.X = text2d->position.X + (currentPos.X - initWordX);
			currentPos.Y += font->height;
			lineStartVertex = initWordVertex;
			linesCount++;

			//Check height limit
			if(currentPos.Y >= text2d->position.Y + text2d->size.Y)
			{
				//Don't draw the last word and abort writting
				vertexToDraw = initWordVertex;
				break;
			}
		}
	}

	//Apply text align for last line
	float diff = 0;
	if(text2d->align == TextAlign::Center)
	{
		diff = FastMath::floor((text2d->size.X - (currentPos.X - text2d->position.X)) / 2);
	}
	else if(text2d->align == TextAlign::Right)
	{
		diff = text2d->position.X + text2d->size.X - currentPos.X;
	}
	if(diff != 0)
	{
		for(int j = lineStartVertex; j < currentVertex; j++)
		{
			//The adjustment must be in screen-space
			Vector2 alignAdjust = vertexData[j].position.toVector2XY();
			toWorldSpace(alignAdjust);
			alignAdjust.X += diff;
			toScreenSpace(alignAdjust);

			vertexData[j].position.X = alignAdjust.X;
		}
	}




	this->vertexBuffer->unmap();


	//Render
	TgcRenderer* renderer = GuiController::Instance->renderer;
	
	renderer->enableAlphaBlending(true);
	renderer->enableDepthTest(false);

	renderer->setVertexBuffer(this->vertexBuffer);
	effect->setTexture("texDiffuseMap", font->texture);
	TgcShadersCommon::TextBuffer textBuffer;
	textBuffer.textColor = text2d->color;
	effect->setConstantBuffer("TextBuffer", &textBuffer);

	effect->begin();
	renderer->draw(PrimitiveTopology::TriangleList, vertexToDraw);
	effect->end();

	renderer->enableAlphaBlending(false);
	renderer->enableDepthTest(true);
}

void TgcFontRenderer::updateVertexDataForWord(string word, VertexFormat::PositionTexcoord* vertexData, Vector2& currentPos, TgcFont* font, int & currentVertex)
{
	const int w = GuiController::Instance->windowHandler->screenWidth;
	const int h = GuiController::Instance->windowHandler->screenHeight;
	Vector2 uvMin;
	Vector2 uvMax;
	Vector2 min;
	Vector2 max;
	for(unsigned int i = 0; i < word.length(); i++)
	{
		const char c = word.at(i);
		const float width = (float)font->charWidth[c];
		font->getUvExtremes(c, uvMin, uvMax);

		//Extremes points
		min = currentPos;
		max = Vector2(currentPos.X + width, currentPos.Y + font->height);

		//Normalize to projected values: X [-1, 1], Y [1, -1]
		toScreenSpace(min);
		toScreenSpace(max);

		//Create quad
		vertexData[currentVertex++] = VertexFormat::PositionTexcoord(Vector3(min.X, min.Y, 1), uvMin);
		vertexData[currentVertex++] = VertexFormat::PositionTexcoord(Vector3(max.X, min.Y, 1), Vector2(uvMax.U, uvMin.V));
		vertexData[currentVertex++] = VertexFormat::PositionTexcoord(Vector3(max.X, max.Y, 1), uvMax);

		vertexData[currentVertex++] = VertexFormat::PositionTexcoord(Vector3(max.X, max.Y, 1), uvMax);
		vertexData[currentVertex++] = VertexFormat::PositionTexcoord(Vector3(min.X, max.Y, 1), Vector2(uvMin.U, uvMax.V));
		vertexData[currentVertex++] = VertexFormat::PositionTexcoord(Vector3(min.X, min.Y, 1), uvMin);

		currentPos += Vector2(width, 0);
	}
}

vector<string> TgcFontRenderer::splitText(const string &text)
{
	vector<string> tokens;
	const char sep = ' ';
	const string sep_s = " ";
	int start = 0, end = 0;
	while ((end = text.find(sep, start)) != string::npos) 
	{
		tokens.push_back(text.substr(start, end - start));
		tokens.push_back(sep_s);
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}

void TgcFontRenderer::dispose()
{
	this->vertexBuffer->dispose();
	delete this->vertexBuffer;

	for (unordered_map<string, TgcFont*>::iterator it = this->fonts.begin(); it != this->fonts.end(); ++it) 
	{
		TgcFont* font = it->second;
		font->dispose();
		delete font;
	}
	this->fonts.clear();
}

void TgcFontRenderer::toScreenSpace(Vector2 &v)
{
	v.X = -1 + v.X * 2 / GuiController::Instance->windowHandler->screenWidth;
	v.Y = 1 - v.Y * 2 / GuiController::Instance->windowHandler->screenHeight;
}

void TgcFontRenderer::toWorldSpace(Vector2 &v)
{
	v.X = (1 + v.X) * GuiController::Instance->windowHandler->screenWidth / 2;
	v.Y = (1 - v.Y) * GuiController::Instance->windowHandler->screenHeight / 2;
}

