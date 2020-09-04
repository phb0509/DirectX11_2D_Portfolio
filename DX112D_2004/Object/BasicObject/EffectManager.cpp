#include "Framework.h"

EffectManager* EffectManager::instance = nullptr;

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
	for (auto effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			delete effect;
	}
}

void EffectManager::Update()
{
	for (auto effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			effect->Update();
	}
}

void EffectManager::Render()
{
	for (auto effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			effect->Render();
	}
}

void EffectManager::Add(string key, UINT poolCount, wstring textureFile, UINT maxFrameX, UINT maxFrameY, float speed, bool isAdditive)
{
	if (totalEffect.count(key) > 0)
		return;

	vector<Effect*> effects;

	for (UINT i = 0; i < poolCount; i++)
	{
		Effect* effect = new Effect(textureFile, maxFrameX, maxFrameY, speed);
		effect->SetAdditive(isAdditive);
		effects.emplace_back(effect);
	}

	totalEffect[key] = effects;
}

void EffectManager::Play(string key, Vector2 pos, Float4 color)
{
	if (totalEffect.count(key) == 0) return;

	for (Effect* effect : totalEffect[key])
	{
		if (!effect->isActive)
		{
			effect->SetColor(color);
			effect->Play(pos);
			return;
		}
	}
}
