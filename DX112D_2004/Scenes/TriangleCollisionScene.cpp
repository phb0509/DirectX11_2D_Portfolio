#include "Framework.h"
#include "TriangleCollisionScene.h"

TriangleCollisionScene::TriangleCollisionScene()
{	
	vector<Vector2> edges;
	edges.emplace_back(-50.0f, 0.0f);
	edges.emplace_back(50.0f, 0.0f);
	edges.emplace_back(0.0f, 50.0f * sqrt(3.0f));
	//edges.emplace_back(-80.0f, 50.0f * sqrt(3.0f));
	collider = new PolygonCollider(edges);
	collider->pos = { CENTER_X, CENTER_Y };
	//collider2 = new PolygonCollider(edges);
	collider2 = new CircleCollider(50);
	collider2->pos = { 500, 500 };
}

TriangleCollisionScene::~TriangleCollisionScene()
{
	delete collider;
}

void TriangleCollisionScene::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		if (collider->IsCollision(collider2))
		{
			collider->SetColor({ 1, 0, 0, 1 });
		}
		else
		{
			collider->SetColor({ 0, 1, 0, 1 });
		}
	}

	collider2->pos = mousePos;

	collider->Update();
	collider2->Update();
}

void TriangleCollisionScene::Render()
{
	collider->Render();
	collider2->Render();
}

void TriangleCollisionScene::PostRender()
{
	ImGui::SliderFloat3("Rotation", (float*)&collider->rot, 0, PI * 2);
}
