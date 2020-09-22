#include "Framework.h"



HPbar_Monster::HPbar_Monster(float _maxHP) : reduction(0.0f), decreaseSpeed(1.0f), lerpStart(1.0f), lerpEnd(1.0f),
trigger_UpdateHP(false), isDead(false), reductionSum(0.0f)
{
	back_HPbar = new Quad(L"Textures/Interface/Monster/HPBAR_BACK.png", L"TextureShader");
	front_HPbar = new Quad(L"Textures/Interface/Monster/HPBAR_RED.png", L"TextureShader");
	temp = { 0,250 };

	maxHP = _maxHP;
	currentHP = maxHP;
	curScale = front_HPbar->scale.x;
	//back_HPbar->pos = Vector2(-375.0f, 200.0f);

	back_HPbar->pos = Vector2{ 0,0 };

	front_HPbar->pos = back_HPbar->pos + Vector2(15, -6);

	//front_HPbar->pos = { }
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

			char buff[100];
			sprintf_s(buff, "scale.x : %f\n reductionSum : %f\n",front_HPbar->scale.x,reductionSum);
			OutputDebugStringA(buff);
		}
	}

	else if (isDead)
	{
		front_HPbar->scale.x = 0.0f;
	}

	//float tmp = reductionSum * front_HPbar->GetSize().x * 100.0f;

	//char buff[100];
	//sprintf_s(buff, "reductionSum : %f\n front_Hpbar->GetSize().x : %f\n, tmp : %f\n", reductionSum,front_HPbar->GetSize().x, tmp);
	//OutputDebugStringA(buff);




	/*cameraPosition = CAMERA->pos;
	back_HPbar->pos.x = -cameraPosition.x + 450.0f;
	back_HPbar->pos.y = -cameraPosition.y + 500.0f;

	front_HPbar->pos = back_HPbar->pos + Vector2(15, -6);*/



	back_HPbar->Update();
	front_HPbar->Update();
}

void HPbar_Monster::Render()
{
	back_HPbar->Render();
	front_HPbar->Render();
}

void HPbar_Monster::UpdateHPbar(float beforeHP, float afterHP)
{
	trigger_UpdateHP = true;
	lerpStart = beforeHP / maxHP;  //  10/10
	lerpEnd = afterHP / maxHP;    // 9/10
}

void HPbar_Monster::SetDead()
{
	isDead = true;
}
