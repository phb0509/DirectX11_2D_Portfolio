#include "Framework.h"



HPbar_Monster::HPbar_Monster(float _maxHP)
{
	back_HPbar = new Quad(L"Textures/Interface/Monster/HPBAR_BACK.png", L"TextureShader");
	front_HPbar = new Quad(L"Textures/Interface/Monster/HPBAR_RED.png", L"TextureShader");
	temp = { 600,250 };

	maxHP = _maxHP;
	currentHP = maxHP;



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
	back_HPbar->pos = GM->GetGunner()->pos;
	front_HPbar->pos = back_HPbar->pos + Vector2(15.0f, -6.0f);


	char buff[100];
	sprintf_s(buff, "scale.x : %f,   y : %f\n", front_HPbar->scale.x, front_HPbar->scale.y);
	OutputDebugStringA(buff);


	if (KEY_PRESS('S'))
	{
		front_HPbar->scale.x -= 1 * DELTA;
	}



	back_HPbar->Update();
	front_HPbar->Update();
}

void HPbar_Monster::Render()
{
	back_HPbar->Render();
	front_HPbar->Render();

}
