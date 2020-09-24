#include "Framework.h"
#include "SeriaHouseScene.h"


SeriaHouseScene::SeriaHouseScene()
{
	gunner = GM->GetGunner();

	backGround = new Quad(L"Textures/SeriaHouse/SeriaHouse1.png", L"TextureShader");
	backGround->pos = { 0,0 };
	gateCollider = new RectCollider({ 400,100 });
	gateCollider->pos = { 10,-350 };


	bgLeftBottom = backGround->GetSize() * backGround->scale * -0.5f;
	bgRightTop = backGround->GetSize() * backGround->scale * 0.5f;

	CAMERA->SetTarget(gunner);
}

SeriaHouseScene::~SeriaHouseScene()
{
	delete backGround;
}

void SeriaHouseScene::Update()
{
	if (KEY_DOWN(VK_F1))
		SCENE->ChangeScene("ElvenGarden");

	if (gunner->pos.y < -260.0f) gunner->pos.y = -260.0f;

	if (gateCollider->IsCollision(gunner->GetGunnerCollider()))
	{
		SCENE->ChangeScene("ElvenGarden");
	}


	backGround->Update();
	gateCollider->Update();

	gunner->Update();
}



void SeriaHouseScene::Render()
{
	backGround->Render();
	gateCollider->Render();

	gunner->Render();
}





void SeriaHouseScene::PreRender()
{
}
void SeriaHouseScene::PostRender()
{
}

void SeriaHouseScene::Start()
{
	gunner->Reactivation();
	gunner->pos = { 0,-150 };
	CAMERA->SetLeftBottom(bgLeftBottom);
	CAMERA->SetRightTop(bgRightTop);
}

void SeriaHouseScene::End()
{
}
