#include "Framework.h"

Tank::Tank() : speed(50)
{
	sprite = new Sprite(L"TankShader");	

	Texture* texture = Texture::Add(L"Textures/tank.png");
	Vector2 size = texture->GetSize();
	Vector2 frame(8, 4);
	Vector2 frameSize = size / frame;
	vector<Action::Clip> clips;

	for(UINT i = 0 ; i < 8 ; i++)
		clips.emplace_back(i * frameSize.x, frameSize.y * 2, frameSize.x, frameSize.y, texture);

	action = new Action(clips);
	action->Play();
}

Tank::~Tank()
{
	delete sprite;
	delete action;
}

void Tank::Update()
{
	Move();

	Action::Clip curClip = action->GetCurClip();

	action->Update();
	sprite->SetAction(curClip);
	scale = curClip.size;

	UpdateWorld();
}

void Tank::Render()
{
	SetWorldBuffer();
	sprite->Render();
}

void Tank::Move()
{
	if (order.size() == 0)
		return;

	Vector2 direction = order.back() - pos;

	rot.z = direction.Angle();

	pos += RightDir() * speed * DELTA;

	float distance = Vector2::Distance(pos, order.back());
	if (distance < 3.0f)
		order.pop_back();
}
