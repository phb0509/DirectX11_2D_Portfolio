#include "Framework.h"
#include "MirkWoodScene.h"


bool compare(Monster*& a, Monster*& b)
{
	if (a->pos.y >= b->pos.y)
	{
		return false;
	}
	else
	{
		return true;
	}
}



MirkWoodScene::MirkWoodScene() : gunner(nullptr)
{
	gunner = GM->GetGunner();
	monsters = GM->GetMirkwoodMonsters();

	bg = new Quad(L"Textures/MirkWood/MirkWoodBackground.png", L"TextureShader");
	bg->pos = { 0, 180 };

	tile = new Quad(L"Textures/MirkWood/MirkWoodTile.png", L"TextureShader");
	tile->pos = { 0, 0 };

	Vector2 bgLeftBottom = tile->GetSize() * tile->scale * -0.5f;
	Vector2 bgRightTop = tile->GetSize() * tile->scale * 0.5f;

	CAMERA->SetLeftBottom(bgLeftBottom);
	CAMERA->SetRightTop(bgRightTop);

	//EffectManager::Get()->Add("whity", 20, L"Textures/Effects/whity_4x4.png", 4, 4, 0.1f, true);

	CAMERA->SetTarget(gunner);
}

MirkWoodScene::~MirkWoodScene()
{
	delete bg;
	delete tile;
}

void MirkWoodScene::Update()
{
	if (KEY_DOWN(VK_F1))
	{
		SCENE->ChangeScene("ElvenGarden");
	}

	//if (KEY_DOWN(VK_LBUTTON))
	//{
	//	EffectManager::Get()->Play("whity", CAMERA->GetMouseWorldPos());
	//}

	bg->Update();
	tile->Update();
	gunner->Update();
	

	sort(monsters.begin(), monsters.end(), compare);

	for (int i = 0; i < monsters.size(); i++)
	{

		char buff[100];
		sprintf_s(buff, "%d 번째 몬스터 y값 : %f\n", i,monsters[i]->pos.y);
		OutputDebugStringA(buff);


	}



	for (int i = 0; i < monsters.size(); i++)
	{
		monsters[i]->Update();
	}
}

void MirkWoodScene::Render()
{
	ALPHA_BLEND_STATE->SetState();

	bg->Render();
	tile->Render();
	gunner->Render();


	for (int i = 0; i < monsters.size(); i++)
	{
		monsters[i]->Render();
	}
}

void MirkWoodScene::PostRender()
{
}

void MirkWoodScene::Start()
{
	UM->set_IsRender_MonsterHPbar(true);
	for (int i = 0; i < monsters.size(); i++)
	{
		monsters[i]->Reactivation();
	}

}

void MirkWoodScene::End()
{
	UM->set_IsRender_MonsterHPbar(false);
}
