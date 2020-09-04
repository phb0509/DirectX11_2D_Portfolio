#include "Framework.h"

Plane::Plane()
	: speed(100)
{
	quad = new Quad(L"Textures/airplane.png");
	collider = new RectCollider(Vector2(100, 100), quad);		
	collider->SetOffset(Vector2(100, 200));
}

Plane::~Plane()
{
	delete quad;
	delete collider;
}

void Plane::Update()
{
	if (KEY_PRESS('W'))
		quad->pos += quad->UpDir() * speed * DELTA;
	if (KEY_PRESS('S'))
		quad->pos -= quad->UpDir() * speed * DELTA;
	if (KEY_PRESS('A'))
		quad->angle += DELTA;
	if (KEY_PRESS('D'))
		quad->angle -= DELTA;	

	quad->Update();
	collider->Update();
}

void Plane::Render()
{
	quad->Render();
	collider->Render();
}
