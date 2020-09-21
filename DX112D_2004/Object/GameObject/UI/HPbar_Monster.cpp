#include "Framework.h"



HPbar_Monster::HPbar_Monster(float _maxHP): reduction(0.0f), decreaseSpeed(1.0f)
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



	//cameraPosition = CAMERA->pos;
	//back_HPbar->pos.x = -cameraPosition.x + 450.0f;
	//back_HPbar->pos.y = -cameraPosition.y + 500.0f;
	//
	//front_HPbar->pos = back_HPbar->pos + Vector2(15, -6);



	 
	if (KEY_PRESS('A')) // 몬스터의 OnDamage가 호출되었다고 가정.
	{
		float e = 1 - (t_damage / maxHP); // 0.9
		float t = LERP(curScale, e, 10.0f * DELTA);
		front_HPbar->scale.x = t; // 이것이 감소량
		front_HPbar->pos.x -= front_HPbar->GetSize().x * 0.5 * (1-t) * DELTA; // 여기서바꿔도 위에서 다시 강제로잡아버리니까.

		curScale = front_HPbar->scale.x;
		// 동시에 x좌표도 이동.
	}


	//if (KEY_PRESS('S'))
	//{
	//	front_HPbar->scale.x -= decreaseSpeed * DELTA;
	//	front_HPbar->pos.x -= front_HPbar->GetSize().x * 0.5 * decreaseSpeed  * DELTA;
	//}

	//if (front_HPbar->scale.x < 0.0f)
	//{
	//	front_HPbar->scale.x = 0.0f;
	//}


	back_HPbar->Update();
	front_HPbar->Update();
}

void HPbar_Monster::Render()
{
	back_HPbar->Render();
	front_HPbar->Render();
}
