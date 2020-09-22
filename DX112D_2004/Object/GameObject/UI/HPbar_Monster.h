#pragma once

class HPbar_Monster
{
public:
	HPbar_Monster(float _maxHP);
	~HPbar_Monster();

	void Update();
	void Render();
	void UpdateHPbar(float beforeHP, float afterHP);
	void SetDead();

private:
	Quad* back_HPbar;
	Quad* front_HPbar;

	Vector2 cameraPosition;
	Vector2 temp;

	float maxHP;
	float currentHP;
	float reduction;
	float decreaseSpeed;

	float curScale;
	float lerpStart;
	float lerpEnd;
	float reductionSum;
	

	bool trigger_UpdateHP;
	bool isDead;
};

