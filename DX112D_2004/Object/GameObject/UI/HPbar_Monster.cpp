#include "Framework.h"



HPbar_Monster::HPbar_Monster(float _maxHP): reduction(0.0f), decreaseSpeed(0.2f)
{
	back_HPbar = new Quad(L"Textures/Interface/Monster/HPBAR_BACK.png", L"TextureShader");
	front_HPbar = new Quad(L"Textures/Interface/Monster/HPBAR_RED.png", L"TextureShader");
	temp = { 0,250 };

	maxHP = _maxHP;
	currentHP = maxHP;

	back_HPbar->pos = Vector2(-375.0f, 200.0f);
	front_HPbar->pos = back_HPbar->pos + Vector2(15.0f, -6.0f);

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

	//back_HPbar->pos.x = -cameraPosition.x;
	//back_HPbar->pos.y = -cameraPosition.y;
	

	 


	if (KEY_PRESS('S'))
	{
		front_HPbar->scale.x -= decreaseSpeed * DELTA;
		front_HPbar->pos.x -= front_HPbar->GetSize().x * decreaseSpeed * 0.5 * DELTA;
	}

	if (front_HPbar->scale.x < 0.0f)
	{
		front_HPbar->scale.x = 0.0f;
	}


	back_HPbar->Update();
	front_HPbar->Update();
}

void HPbar_Monster::Render()
{
	back_HPbar->Render();
	front_HPbar->Render();
}
