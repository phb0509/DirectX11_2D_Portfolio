#include "Framework.h"

UpGate::UpGate() : isEffectTrigger_BossGate(false) , dir(1.0f), alphaValue (0.0f)
{
	gate = new Quad(L"Textures/MirkWood/UpGate.png", L"TextureShader");
	effect_BossGate = new Quad(L"Textures/MirkWood/UpGate_BossEffect.png", L"PathGateShader");

	floatBuffer = new FloatBuffer();
	gate->pos = { 100,100 };
}

UpGate::~UpGate()
{
	delete gate;
	delete effect_BossGate;
	delete floatBuffer;
}

void UpGate::Update()
{
	if (!isEffectTrigger_BossGate)
	{
		alphaValue = 0.0f;
	}

	else
	{
		if (alphaValue >= 0.8f) dir = -1.0f;
		else if (alphaValue <= 0.0f) dir = 1.0f;

		alphaValue += dir * DELTA;
	}

	floatBuffer->data.value[0] = alphaValue;
	
	gate->Update();
	effect_BossGate->Update();
}

void UpGate::Render()
{
	floatBuffer->SetPSBuffer(1);
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
	isEffectTrigger_BossGate = trigger;
}
