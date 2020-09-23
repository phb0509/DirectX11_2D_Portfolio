#include "Framework.h"



HPbar_Monster::HPbar_Monster(float _maxHP) : decreaseSpeed(1.0f), lerpStart(1.0f), lerpEnd(1.0f),
				trigger_UpdateHP(false), isHPbarDead(false), isMonsterDead(false), reductionSum(0.0f)
{
	back_HPbar = new Quad(L"Textures/Interface/Monster/HPBAR_BACK.png", L"TextureShader");
	front_HPbar = new Quad(L"Textures/Interface/Monster/HPBAR_RED.png", L"TextureShader");
	dead_HPbar = new Quad(L"Textures/Interface/Monster/HPBAR_DEAD.png", L"TextureShader");

	maxHP = _maxHP;

	back_HPbar->pos = Vector2{ 0,0 };
	front_HPbar->pos = back_HPbar->pos + Vector2(15, -6);

	viewBuffer = new MatrixBuffer();
}

HPbar_Monster::~HPbar_Monster()
{
	delete back_HPbar;
	delete front_HPbar;
}

void HPbar_Monster::Update()
{
	if (trigger_UpdateHP)
	{
		if (front_HPbar->scale.x >= lerpEnd &&
			front_HPbar->scale.x < lerpEnd + 0.001f)
		{
			trigger_UpdateHP = false;
		}

		else  // lerpEnd 까지 줄어들어야함.
		{
			front_HPbar->scale.x -= 0.3f * DELTA;
			reductionSum += 0.15f * DELTA;

			if (front_HPbar->scale.x < 0.0f)
			{
				front_HPbar->scale.x = 0.0f;
			}
		}
	}

	else if (isHPbarDead)
	{
		front_HPbar->scale.x = 0.0f;
	}
	 
	back_HPbar->pos.x = 450.0f;
	back_HPbar->pos.y = 500.0f;
	
	float tmp = front_HPbar->GetSize().x * reductionSum;

	front_HPbar->pos = back_HPbar->pos + Vector2(15, -6);
	front_HPbar->pos.x -= tmp;
	
	dead_HPbar->pos = back_HPbar->pos + Vector2(-299, 2);
	
	back_HPbar->Update();
	front_HPbar->Update();
	dead_HPbar->Update();
}

void HPbar_Monster::Render()
{
	if (isHPbarDead) return;
	viewBuffer->SetVSBuffer(1);
	back_HPbar->Render();
	front_HPbar->Render();

	if(isMonsterDead) dead_HPbar->Render();
}

void HPbar_Monster::UpdateHPbar(float beforeHP, float afterHP)
{
	trigger_UpdateHP = true;
	lerpStart = beforeHP / maxHP;  
	lerpEnd = afterHP / maxHP;    
}

void HPbar_Monster::SetHPbarDead()
{
	isHPbarDead = true;
}

void HPbar_Monster::SetMonsterDead()
{
	isMonsterDead = true;
}

void HPbar_Monster::Reactivation()
{
	isHPbarDead = false;
	isMonsterDead = false;
	front_HPbar->scale.x = 1.0f;
	lerpEnd = 1.0f;
	reductionSum = 0.0f;
}
