#pragma once

class HPbar_Monster
{
public:
	HPbar_Monster(float _maxHP);
	~HPbar_Monster();

	void Update();
	void Render();
	void UpdateHPbar(float beforeHP, float afterHP);
	void SetHPbarDead();
	void SetMonsterDead();
	void Reactivation();

private:
	Quad* back_HPbar;
	Quad* front_HPbar;
	Quad* dead_HPbar;

	float maxHP;
	float decreaseSpeed;

	float curScale;
	float lerpStart;
	float lerpEnd;
	float reductionSum;
	
	bool trigger_UpdateHP;
	bool isHPbarDead;
	bool isMonsterDead;

	MatrixBuffer* viewBuffer;
};

