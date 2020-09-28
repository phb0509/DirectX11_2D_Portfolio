#pragma once

class UpGate
{
public:
	UpGate();
	~UpGate();

	void Update();
	void Render();

	void SetPosition(Vector2 pos);
	void SetGateEffectTrigger(bool trigger);

private:
	Quad* gate;
	Quad* effect_BossGate;

	bool isEffectTrigger_BossGate;
	float alphaValue;
	float dir;
	FloatBuffer* floatBuffer;
};

