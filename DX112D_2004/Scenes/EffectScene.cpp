#include "Framework.h"
#include "EffectScene.h"

EffectScene::EffectScene()
{
	EffectManager::Get()->Add("fire", 20, L"Textures/Effects/fire_8x2.png", 8, 2, 0.05f, true);
	EffectManager::Get()->Add("whity", 20, L"Textures/Effects/whity_4x4.png", 4, 4, 0.1f, true);
}

EffectScene::~EffectScene()
{	
}

void EffectScene::Update()
{

	if (KEY_DOWN(VK_LBUTTON))
	{
		EffectManager::Get()->Play("fire", mousePos, Float4(1, 0, 0, 1));
	}

	if (KEY_DOWN(VK_RBUTTON))
	{
		EffectManager::Get()->Play("whity", mousePos, Float4(0, 0, 1, 1));
	}
}

void EffectScene::Render()
{	
}

void EffectScene::PostRender()
{
}
