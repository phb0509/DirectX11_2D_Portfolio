#pragma once

class HPbar_Monster
{
public:
	HPbar_Monster(float _maxHP);
	~HPbar_Monster();

	void Update();
	void Render();

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
	float t_damage = 1000;
};

