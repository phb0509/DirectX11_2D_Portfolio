#include "Framework.h"
#include "SolarSystemScene.h"

SolarSystemScene::SolarSystemScene()
{
	sun = new Quad(L"Textures/sun.png");
	sun->scale = { 0.3f, 0.3f };

	earth = new Quad(L"Textures/earth.png");
	earth->pos.x = 1000;
	earth->SetParent(sun->GetMatrix());
	earth->scale = { 0.5f, 0.5f };

	moon = new Quad(L"Textures/moon.png");
	moon->pos.x = 1000;
	moon->SetParent(earth->GetMatrix());	
}

SolarSystemScene::~SolarSystemScene()
{
	delete sun;
	delete earth;
	delete moon;
}

void SolarSystemScene::Update()
{
	sun->pos = mousePos;

	sun->angle += DELTA;

	sun->Update();

	earth->angle -= DELTA * 3.0f;

	earth->Update();

	moon->angle += DELTA * 5.0f;

	moon->Update();
}

void SolarSystemScene::Render()
{	
	ADDITIVE_BLEND_STATE->SetState();
	sun->Render();

	ALPHA_BLEND_STATE->SetState();
	earth->Render();
	moon->Render();
}

void SolarSystemScene::PostRender()
{
}
