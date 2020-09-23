#include "Framework.h"
#include "ElvenGardenScene.h"

ElvenGardenScene::ElvenGardenScene()
{
	gunner = GM->GetGunner();
	bg = new Quad(L"Textures/Earth.png", L"TextureShader");
	sign = new Quad(L"Textures/ElvenGarden/sign.png", L"TextureShader");

	bg->pos = { CENTER_X, CENTER_Y + 147 };
	sign->pos = { 100,100 };
	brazier = new Brazier();
}

ElvenGardenScene::~ElvenGardenScene()
{
	delete bg;
	delete brazier;
}

void ElvenGardenScene::Update()
{
	if (KEY_DOWN(VK_F1))
		SCENE->ChangeScene("Mirkwood");


	bg->Update();
	brazier->Update();
	sign->Update();



	gunner->Update();
}

void ElvenGardenScene::Render()
{
	bg->Render();
	brazier->Render();
	sign->Render();



	gunner->Render();
}


void ElvenGardenScene::PostRender()
{
}

void ElvenGardenScene::Start()
{
	gunner->Reactivation();
}

void ElvenGardenScene::End()
{
}

void ElvenGardenScene::SetGunner()
{
}

void ElvenGardenScene::SetMonsters()
{
}
