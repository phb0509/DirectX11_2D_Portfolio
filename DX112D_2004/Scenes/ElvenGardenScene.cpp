#include "Framework.h"
#include "ElvenGardenScene.h"

ElvenGardenScene::ElvenGardenScene()
{
	gunner = GM->GetGunner();
	bg = new Quad(L"Textures/Earth.png", L"TextureShader");
	sign = new Quad(L"Textures/ElvenGarden/sign.png", L"TextureShader");

	bg->pos = { CENTER_X, CENTER_Y + 147 };
	sign->pos = { 320,45 };

	linus = new Linus();
	linus->pos = { -100,-4 };

	brazier = new Brazier();
	brazier->pos = { -150,0 };



	/*bgLeftBottom = tile->GetSize() * tile->scale * -0.5f;
	bgRightTop = tile->GetSize() * tile->scale * 0.5f;*/
}

ElvenGardenScene::~ElvenGardenScene()
{
	delete bg;
	delete brazier;
	delete linus;
}

void ElvenGardenScene::Update()
{
	if (KEY_DOWN(VK_F1))
		SCENE->ChangeScene("Mirkwood");


	bg->Update();
	brazier->Update();
	sign->Update();
	linus->Update();



	gunner->Update();
}

void ElvenGardenScene::Render()
{
	bg->Render();
	brazier->Render();
	sign->Render();
	linus->Render();


	gunner->Render();
}


void ElvenGardenScene::PostRender()
{
}

void ElvenGardenScene::Start()
{
	//CAMERA->SetLeftBottom(bgLeftBottom);
	//CAMERA->SetRightTop(bgRightTop);
	gunner->Reactivation();
	gunner->pos = { 100,20 };
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
