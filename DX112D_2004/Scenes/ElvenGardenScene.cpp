#include "Framework.h"
#include "ElvenGardenScene.h"

ElvenGardenScene::ElvenGardenScene()
{
	gunner = GM->GetGunner();
	bg = new Quad(L"Textures/Earth.png", L"TextureShader");
	bg->pos = { CENTER_X, CENTER_Y + 147 };
}

ElvenGardenScene::~ElvenGardenScene()
{
}

void ElvenGardenScene::Update()
{
	if (KEY_DOWN(VK_F1))
		SCENE->ChangeScene("Mirkwood");


	bg->Update();
	gunner->Update();
}

void ElvenGardenScene::Render()
{
	bg->Render();
	gunner->Render();
}








void ElvenGardenScene::PostRender()
{
}

void ElvenGardenScene::SetGunner()
{
}

void ElvenGardenScene::SetMonsters()
{
}
