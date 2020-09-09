// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_WIDTH 1500
#define WIN_HEIGHT 600

#define CENTER_X WIN_WIDTH * 0.5f
#define CENTER_Y WIN_HEIGHT * 0.5f

#define WIN_START_X 0
#define WIN_START_Y 0

#define PI 3.141592f

#define LERP(s, e, t) (s + (e - s) * t)

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)
#define KEY_UP(k) Keyboard::Get()->Up(k)

#define DELTA Timer::Get()->GetElapsedTime()

#define SAMPLER_STATE StateManager::Get()->GetSampler()
#define ALPHA_BLEND_STATE StateManager::Get()->GetAlphaBlend()
#define ADDITIVE_BLEND_STATE StateManager::Get()->GetAdditiveBlend()
#define BLEND_STATE StateManager::Get()->GetBlend()
#define CULL_MODE_STATE StateManager::Get()->GetCullMode()

#define SHADER ShaderManager::Get()

#define CAMERA Camera::Get()
#define GM GameManager::Get()

#define V(hr) assert(SUCCEEDED(hr))

#include <windows.h>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <assert.h>
#include <functional>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//DirectXTex
#include "../DirectXTex/DirectXTex.h"

//ImGui
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../ImGui/imgui_impl_win32.h"

//DirectWrite
#include <d2d1_2.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMMATRIX Matrix;
typedef XMFLOAT4X4 Float4x4;
typedef function<void()> CallBack;
typedef function<void(void*)> CallBackParam;

//Framework Header
#include "Framework/Device/Device.h"

#include "Framework/Render/Shader.h"
#include "Framework/Render/VertexShader.h"
#include "Framework/Render/PixelShader.h"
#include "Framework/Render/GeometryShader.h"
#include "Framework/Render/ComputeShader.h"

#include "Framework/Render/ShaderManager.h"
#include "Framework/Render/VertexBuffer.h"
#include "Framework/Render/IndexBuffer.h"
#include "Framework/Render/VertexLayouts.h"
#include "Framework/Render/ConstBuffer.h"
#include "Framework/Render/GlobalBuffer.h"
#include "Framework/Render/RawBuffer.h"
#include "Framework/Render/StructuredBuffer.h"

#include "Framework/Render/Texture.h"
#include "Framework/Render/Material.h"
#include "Framework/Render/RenderTarget.h"

#include "Framework/State/SamplerState.h"
#include "Framework/State/BlendState.h"
#include "Framework/State/RasterizerState.h"
#include "Framework/State/StateManager.h"

#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"
#include "Framework/Math/Math.h"

#include "Framework/Utility/Keyboard.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/Xml.h"
#include "Framework/Utility/BinaryWriter.h"
#include "Framework/Utility/BinaryReader.h"
#include "Framework/Utility/DirectWrite.h"

#include "Framework/Collision/Line.h"
#include "Framework/Collision/Collider.h"
#include "Framework/Collision/RectCollider.h"
#include "Framework/Collision/CircleCollider.h"
#include "Framework/Collision/PolygonCollider.h"


#include "Framework/Animation/Action.h"
#include "Framework/Camera/Camera.h"


//Object Header
#include "Object/BasicObject/QuadMesh.h"
#include "Object/BasicObject/Quad.h"
#include "Object/BasicObject/Sprite.h"
#include "Object/BasicObject/Effect.h"
#include "Object/BasicObject/EffectManager.h"
#include "Object/BasicObject/Button.h"

#include "Object/GameObject/Monsters/Monster1.h"

#include "Object/GameObject/Gunner/Bullet.h"
#include "Object/GameObject/Gunner/Gunner.h"
#include "Object/GameObject/GameManager.h"

//Program;
#include "Scenes/Scene.h"
#include "Program/Program.h"

extern Vector2 mousePos;
extern short mouseWheel;