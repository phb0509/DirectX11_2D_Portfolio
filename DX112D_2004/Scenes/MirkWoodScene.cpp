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



MirkWoodScene::MirkWoodScene() : gunner(nullptr), monsterDeathCount(0)
{
	gunner = GM->GetGunner();
	monsters = GM->GetMirkwoodMonsters();

	bg = new Quad(L"Textures/MirkWood/MirkWoodBackground.png", L"TextureShader");
	bg->pos = { 0, 180 };

	tile = new Quad(L"Textures/MirkWood/MirkWoodTile.png", L"TextureShader");
	tile->pos = { 0, 0 };

	upGate = new UpGate();
	upGate->SetPosition({ 50,300 });

	bgLeftBottom = tile->GetSize() * tile->scale * -0.5f;
	bgRightTop = tile->GetSize() * tile->scale * 0.5f;

	//CAMERA->SetLeftBottom(bgLeftBottom);
	//CAMERA->SetRightTop(bgRightTop);
	CAMERA->SetTarget(gunner);

	//EffectManager::Get()->Add("whity", 20, L"Textures/Effects/whity_4x4.png", 4, 4, 0.1f, true);
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
		SCENE->ChangeScene("SeriaHouse");
	}

	//if (KEY_DOWN(VK_LBUTTON))
	//{
	//	EffectManager::Get()->Play("whity", CAMERA->GetMouseWorldPos());
	//}

	bg->Update();
	tile->Update();
	gunner->Update();
	upGate->Update();
	
	CheckMonsterDeath();
	char buff[100];
	sprintf_s(buff, "%d\n",monsterDeathCount);
	OutputDebugStringA(buff);

	sort(monsters.begin(), monsters.end(), compare);

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
	upGate->Render();
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
	gunner->pos = { 48,100 };
	CAMERA->SetLeftBottom(bgLeftBottom);
	CAMERA->SetRightTop(bgRightTop);
	UM->set_IsRender_MonsterHPbar(true);

	gunner->Reactivation();
	upGate->SetGateEffectTrigger(false);

	for (int i = 0; i < monsters.size(); i++)
	{
		monsters[i]->Reactivation();
	}

}

void MirkWoodScene::End()
{
	UM->set_IsRender_MonsterHPbar(false);
}

void MirkWoodScene::CheckMonsterDeath()
{
	monsterDeathCount = 0;
	for (int i = 0; i < monsters.size(); i++)
	{
		if (monsters[i]->GetIsDie())
		{
			monsterDeathCount++;
		}
	}

	if (monsterDeathCount == monsters.size())
	{
		upGate->SetGateEffectTrigger(true);
	}
}
