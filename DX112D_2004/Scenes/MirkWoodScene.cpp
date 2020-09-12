#include "Framework.h"
#include "MirkWoodScene.h"

MirkWoodScene::MirkWoodScene()
{
	SetGunner();
	SetMonsters();

	bg = new Quad(L"Textures/MirkWood/MirkWoodBackground.png", L"TextureShader");
	bg->pos = { CENTER_X, CENTER_Y + 147 };

	tile = new Quad(L"Textures/MirkWood/MirkWoodTile.png", L"TextureShader");
	tile->pos = { 700, 40 };
	//CAMERA->SetTarget(gunner);
	bgTransform = new Transform();
	bgTransform->scale = { 3, 3 };

	Vector2 bgLeftBottom = tile->GetSize() * bgTransform->scale * -0.5f;
	Vector2 bgRightTop = tile->GetSize() * bgTransform->scale * 0.5f;

	CAMERA->SetLeftBottom(bgLeftBottom);
	CAMERA->SetRightTop(bgRightTop);

	//EffectManager::Get()->Add("whity", 20, L"Textures/Effects/whity_4x4.png", 4, 4, 0.1f, true);

	CAMERA->SetTarget(gunner);
}

MirkWoodScene::~MirkWoodScene()
{
	delete bg;
	//delete bgTransform;
}

void MirkWoodScene::Update()
{
	//if (KEY_DOWN(VK_LBUTTON))
	//{
	//	EffectManager::Get()->Play("whity", CAMERA->GetMouseWorldPos());
	//}

	bg->Update();
	tile->Update();
	gunner->Update();


	for (int i = 0; i < gunner_bullets.size(); i++)
	{
		if (gunner_bullets[i]->isActive)
		{
			gunner_bullets[i]->Update(monsters);
		}
	}

	for (int i = 0; i < monsters.size(); i++)
	{
		if (monsters[i]->isActive)
		{
			monsters[i]->Update();
		}
	}

	bgTransform->UpdateWorld();
}

void MirkWoodScene::Render()
{
	ALPHA_BLEND_STATE->SetState();
	bgTransform->SetWorldBuffer();

	bg->Render();
	tile->Render();
	gunner->Render();


	for (int i = 0; i < gunner_bullets.size(); i++)
	{
		if (gunner_bullets[i]->isActive)
		{
			gunner_bullets[i]->Render();
		}
	}

	for (int i = 0; i < monsters.size(); i++)
	{
		if (monsters[i]->isActive)
		{
			monsters[i]->Render();
		}
	}
}

void MirkWoodScene::PostRender()
{
}

void MirkWoodScene::SetGunner()
{
	gunner = GM->GetGunner();
	gunner_bullets = GM->GetGunnerBullets();
}

void MirkWoodScene::SetMonsters()
{
	//for (int y = 0; y < 2; y++)
	//{
	//	for (int x = 0; x < 2; x++)
	//	{
	//		gnoll = new Gnoll_Mirkwood({ 700.0f + x * 150.0f,100.0f + y * 150.0f });
	//		monsters.emplace_back(gnoll);
	//	}
	//}

	for (int y = 0; y < 1; y++)
	{

		gnoll = new Gnoll_Mirkwood({ 700.0f ,100.0f });
		monsters.emplace_back(gnoll);

	}
}
