#include "Framework.h"

UpGate::UpGate() : isEffectTrigger_BossGate(false)
{
	gate = new Quad(L"Textures/MirkWood/UpGate.png", L"TextureShader");
	effect_BossGate = new Quad(L"Textures/MirkWood/UpGate_BossEffect.png", L"PathGateShader");

	gate->pos = { 100,100 };
}

UpGate::~UpGate()
{
	delete gate;
	delete effect_BossGate;
}

void UpGate::Update()
{
	gate->Update();
	effect_BossGate->Update();
}

void UpGate::Render()
{
	gate->Render();
	effect_BossGate->Render();
}

void UpGate::SetPosition(Vector2 _pos)
{
	gate->pos = _pos;
	effect_BossGate->pos = _pos + Vector2(0, -7);
}

void UpGate::SetGateEffectTrigger(bool trigger)
{
}
