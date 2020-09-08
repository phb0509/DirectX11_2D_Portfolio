#include "Framework.h"
#include "UVTestScene.h"

UVTestScene::UVTestScene()
{
	gunner = GM->GetGunner();
	gunner_bullets = GM->GetGunnerBullets();
	monster1 = new Monster1({ 700,400 });


	//bg = new Quad(L"Textures/sample.png", L"TextureShader");
	//bgTransform = new Transform();
	//bgTransform->scale = { 3, 3 };

	//Vector2 bgLeftBottom = bg->GetSize() * bgTransform->scale * -0.5f;
	//Vector2 bgRightTop = bg->GetSize() * bgTransform->scale * 0.5f;

	//CAMERA->SetLeftBottom(bgLeftBottom);
	//CAMERA->SetRightTop(bgRightTop);

	//EffectManager::Get()->Add("whity", 20, L"Textures/Effects/whity_4x4.png", 4, 4, 0.1f, true);

	//CAMERA->SetTarget(knight);
}

UVTestScene::~UVTestScene()
{
	//delete bg;
		//delete bgTransform;
}

void UVTestScene::Update()
{
	//if (KEY_DOWN(VK_LBUTTON))
	//{
	//	EffectManager::Get()->Play("whity", CAMERA->GetMouseWorldPos());
	//}

	gunner->Update();
	monster1->Update();

	for (int i = 0; i < gunner_bullets.size(); i++)
	{
		if (gunner_bullets[i]->isActive)
		{
			gunner_bullets[i]->Update(monster1);
		}
	}
	//bgTransform->UpdateWorld();
}

void UVTestScene::Render()
{
	ALPHA_BLEND_STATE->SetState();
	//	bgTransform->SetWorldBuffer();
		//bg->Render();

	gunner->Render();
	monster1->Render();
	for (int i = 0; i < gunner_bullets.size(); i++)
	{
		if (gunner_bullets[i]->isActive)
		{
			gunner_bullets[i]->Render();
		}
	}
}

void UVTestScene::PostRender()
{
}
