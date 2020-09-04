#include "Framework.h"
#include "TurorialScene.h"

TutorialScene::TutorialScene()
{
	texture = new Texture(L"Textures/sample.png");
}

TutorialScene::~TutorialScene()
{
	delete texture;
}

void TutorialScene::Update()
{
	texture->Update();
}

void TutorialScene::Render()
{
	texture->Render();
}
