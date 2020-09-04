#include "Framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	rect = new RectCollider({ 200, 100 });
	//rect = new CircleCollider(100);
	rect->pos = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f };

	colliders.emplace_back(rect);

	rect2 = new RectCollider({ 100, 100 });
	rect2->pos = { WIN_WIDTH * 0.5f, 500 };

	colliders.emplace_back(rect2);

	circle = new CircleCollider(100);
	circle->pos = { 200, 200 };

	colliders.emplace_back(circle);
}

CollisionScene::~CollisionScene()
{
	for (Collider* collider : colliders)
		delete collider;
}

void CollisionScene::Update()
{	
	Move();
	Collision();

	for (Collider* collider : colliders)
		collider->Update();
}

void CollisionScene::Render()
{
	for (Collider* collider : colliders)
		collider->Render();
}

void CollisionScene::PostRender()
{
	ImGui::SliderFloat2("Pos", (float*)&rect->pos, 0, WIN_WIDTH);
}


void CollisionScene::Move()
{
	if (KEY_PRESS(VK_RIGHT))
		rect->pos.x += DELTA * 100;
	if (KEY_PRESS(VK_LEFT))
		rect->pos.x -= DELTA * 100;
	if (KEY_PRESS(VK_UP))
		rect->pos.y += DELTA * 100;
	if (KEY_PRESS(VK_DOWN))
		rect->pos.y -= DELTA * 100;

	if (KEY_PRESS('D'))
		rect->scale.x += DELTA;
	if (KEY_PRESS('A'))
		rect->scale.x -= DELTA;
	if (KEY_PRESS('W'))
		rect->scale.y += DELTA;
	if (KEY_PRESS('S'))
		rect->scale.y -= DELTA;

	if (KEY_PRESS(VK_ADD))
		rect->rot.z += DELTA;
	if (KEY_PRESS(VK_SUBTRACT))
		rect->rot.z -= DELTA;
}

void CollisionScene::Collision()
{
	for (int i = 0; i < colliders.size() - 1; i++)
	{
		for (int j = i + 1; j < colliders.size(); j++)
		{
			if (colliders[i]->IsCollision(colliders[j]))
			{
				colliders[i]->SetColor(Float4(1, 0, 0, 1));
				colliders[j]->SetColor(Float4(1, 0, 0, 1));
			}
		}
	}

	if (rect->IsCollision(circle))
		circle->SetColor(Float4(1, 0, 0, 1));
	else
		circle->SetColor(Float4(0, 1, 0, 1));
}