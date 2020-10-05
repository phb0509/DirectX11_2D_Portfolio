#include "Framework.h"

Character_Interface::Character_Interface()
{
	character_Interface = new Quad(L"Textures/Interface/Gunner/Character_Interface.png", L"TextureShader");
	hpBar = new Quad(L"Textures/Interface/Gunner/HPbar.png", L"CharacterHPbarShader");
	mpBar = new Quad(L"Textures/Interface/Gunner/MPbar.png", L"TextureShader");


	viewBuffer = new MatrixBuffer();
	floatBuffer = new FloatBuffer();
}

Character_Interface::~Character_Interface()
{
	delete character_Interface;
	delete hpBar;
	delete mpBar;
	delete viewBuffer;
	delete floatBuffer;
}

void Character_Interface::Update()
{
	testValue = 1.0f - (GM->GetGunner()->GetCurrentHP() / GM->GetGunner()->GetMaxHP());
	floatBuffer->data.value[0] = testValue;

	character_Interface->pos = { CENTER_X,40 };
	character_Interface->Update();

	hpBar->pos = { character_Interface->pos.x - 349.0f,character_Interface->pos.y + 5.0f };
	mpBar->pos = { character_Interface->pos.x + 346.0f,character_Interface->pos.y + 5.0f };

	hpBar->Update();
	mpBar->Update();
}

void Character_Interface::Render()
{
	viewBuffer->SetVSBuffer(1);
	floatBuffer->SetPSBuffer(1);
	character_Interface->Render();
	hpBar->Render();
	mpBar->Render();
}

