#include "Framework.h"
#include "OffsetTestScene.h"

OffsetTestScene::OffsetTestScene()
{
	plane = new Plane();
	test = new RectCollider({ 100, 100 });
}

OffsetTestScene::~OffsetTestScene()
{
	delete plane;
	delete test;
}

void OffsetTestScene::Update()
{
	if (plane->GetCollider()->IsCollision(test))
	{
		test->SetColor({ 1, 0, 0, 1 });
	}
	else
	{
		test->SetColor({ 0, 1, 0, 1 });
	}

	if (plane->GetCollider()->IsCollision(mousePos))
	{
		plane->GetCollider()->SetColor({ 1, 0, 0, 1 });
	}
	else
	{
		plane->GetCollider()->SetColor({ 0, 1, 0, 1 });
	}

	plane->Update();
	test->Update();
}

void OffsetTestScene::Render()
{	
	plane->Render();
	test->Render();
}

void OffsetTestScene::PostRender()
{
}
