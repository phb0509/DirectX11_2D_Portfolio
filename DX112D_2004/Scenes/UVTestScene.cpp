#include "Framework.h"
#include "UVTestScene.h"

UVTestScene::UVTestScene()
{
	gunner = new Gunner();
	//bg = new Quad(L"Textures/sample.png", L"TextureShader");
	//bgTransform = new Transform();
	//bgTransform->scale = { 3, 3 };

	//Vector2 bgLeftBottom = bg->GetSize() * bgTransform->scale * -0.5f;
	//Vector2 bgRightTop = bg->GetSize() * bgTransform->scale * 0.5f;

	//CAMERA->SetLeftBottom(bgLeftBottom);
	//CAMERA->SetRightTop(bgRightTop);

	EffectManager::Get()->Add("whity", 20, L"Textures/Effects/whity_4x4.png", 4, 4, 0.1f, true);

	//CAMERA->SetTarget(knight);
}

UVTestScene::~UVTestScene()
{
	delete gunner;
	//delete bg;
		//delete bgTransform;
}

void UVTestScene::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		EffectManager::Get()->Play("whity", CAMERA->GetMouseWorldPos());
	}

	gunner->Update();
	//bgTransform->UpdateWorld();
}

void UVTestScene::Render()
{
	ALPHA_BLEND_STATE->SetState();
	//	bgTransform->SetWorldBuffer();
		//bg->Render();

	gunner->Render();
}

void UVTestScene::PostRender()
{
}
