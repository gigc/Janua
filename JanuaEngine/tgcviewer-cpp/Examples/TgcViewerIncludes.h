/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once

//STL
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

//General
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Example/TgcExample.h"
using namespace TgcViewer;

//Input
#include "TgcViewer/Input/TgcInput.h"
#include "TgcViewer/Input/TgcFpsCamera.h"

//Math
#include "TgcViewer/Math/FastMath.h"
#include "TgcViewer/Math/Vector3.h"
#include "TgcViewer/Math/Vector4.h"
#include "TgcViewer/Math/Vector2.h"
#include "TgcViewer/Math/Color.h"

//Renderer
#include "TgcViewer/Renderer/TgcRenderer.h"
#include "TgcViewer/Renderer/TgcRendererGlobals.h"
#include "TgcViewer/Renderer/TgcEffect.h"
#include "TgcViewer/Renderer/TgcVertexBuffer.h"
#include "TgcViewer/Renderer/TgcIndexBuffer.h"
#include "TgcViewer/Renderer/TgcInputLayout.h"

//TgcSceneLoader
#include "TgcViewer/TgcSceneLoader/TgcSceneLoader.h"
#include "TgcViewer/TgcSceneLoader/TgcScene.h"
#include "TgcViewer/TgcSceneLoader/TgcMesh.h"
#include "TgcViewer/TgcSceneLoader/TgcTexture.h"

//TgcGeometry
#include "TgcViewer/TgcGeometry/TgcBoundingBox.h"
#include "TgcViewer/TgcGeometry/TgcBox.h"
#include "TgcViewer/TgcGeometry/TgcDebugBox.h"

//2D
#include "TgcViewer/2D/TgcSprite.h"
#include "TgcViewer/2D/TgcAnimatedSprite.h"
#include "TgcViewer/2D/TgcText2d.h"

//Ui
#include "TgcViewer/Ui/TgcUserVars.h"
#include "TgcViewer/Ui/Gui/TgcGui.h"
#include "TgcViewer/Ui/Gui/TgcGuiItem.h"
#include "TgcViewer/Ui/Gui/TgcGuiCheckBox.h"
#include "TgcViewer/Ui/Gui/TgcGuiButton.h"
#include "TgcViewer/Ui/Gui/TgcGuiSlider.h"
#include "TgcViewer/Ui/Modifiers/TgcModifiers.h"
#include "TgcViewer/Ui/Modifiers/TgcModifierItem.h"
#include "TgcViewer/Ui/Modifiers/TgcBoolModifier.h"
#include "TgcViewer/Ui/Modifiers/TgcFloatModifier.h"
