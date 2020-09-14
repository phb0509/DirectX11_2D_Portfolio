#include "Framework.h"
#include "MirkWoodScene.h"

MirkWoodScene::MirkWoodScene() : gunner(nullptr)
{
	gunner = GM->GetGunner();
	monsters = GM->GetMirkwoodMonsters();


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
	delete tile;
	delete bgTransform;
}

void MirkWoodScene::Update()
{
	if (KEY_DOWN(VK_F1))
	{
		SCENE->ChangeScene("ElvenGarden");
	}

	gnoll = GM->GetMirkwoodMonsters()[0];

	char buff[100];
	sprintf_s(buff, "isActive : %d\n  pos.x : %f\n pos.y : %f\n", gnoll->isActive,gnoll->pos.x, gnoll->pos.y);
	OutputDebugStringA(buff);


	//if (KEY_DOWN(VK_LBUTTON))
	//{
	//	EffectManager::Get()->Play("whity", CAMERA->GetMouseWorldPos());
	//}

	bg->Update();
	tile->Update();
	gunner->Update();


	for (int i = 0; i < monsters.size(); i++)
	{
		monsters[i]->Update();	
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
	
	for (int i = 0; i < monsters.size(); i++)
	{
		monsters[i]->Reactivation();
	}

}

void MirkWoodScene::End()
{

}
