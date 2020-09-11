#include "Framework.h"

Gnoll_Mirkwood::Gnoll_Mirkwood()
{
	sprite = new Sprite();

	pos = { 300, 300 };

	string path = "Textures/Monster1/";

	LoadAction(path, "IDLE.xml", Action::END);
	LoadAction(path, "WALK.xml", Action::PINGPONG);

}

Gnoll_Mirkwood::Gnoll_Mirkwood(Vector2 _pos)
{
	sprite = new Sprite();
	collider = new RectCollider({118, 116 }, this);
	pos = _pos;

	string path = "Textures/Monster1/";

	LoadAction(path, "IDLE.xml", Action::END);
	LoadAction(path, "WALK.xml", Action::PINGPONG);

}

Gnoll_Mirkwood::~Gnoll_Mirkwood()
{
	delete sprite;

	for (Action* action : actions)
		delete action;
}

void Gnoll_Mirkwood::Update()
{

	if (!isActive) return;


	
	DetectPlayer();
	Move();
	Attack();

	Action::Clip curClip = actions[curAction]->GetCurClip();
	sprite->SetAction(curClip);

	actions[curAction]->Update();

	scale.x = isRight ? curClip.size.x : -curClip.size.x;
	scale.y = curClip.size.y;


	collider->Update();
	UpdateWorld();


	//effect->Update();
}

void Gnoll_Mirkwood::Render()
{
	if (!isActive) return;

	SetWorldBuffer();
	sprite->Render();

	collider->Render();
}

void Gnoll_Mirkwood::Move()
{
	if (isDetectedPlayer)
	{
		SetAction(WALK);
		Vector2 dir = (GM->GetGunner()->pos - pos).Normal();
		pos += dir * speed * DELTA;
	}
	else SetAction(IDLE);

}

void Gnoll_Mirkwood::Attack()
{
}

void Gnoll_Mirkwood::OnDamage(float damage)
{
	if (isDie) return;

	hp -= damage;

	if (hp <= 0)
	{
		hp = 0;
		Die();
	}
}

void Gnoll_Mirkwood::DetectPlayer()
{

	playerPos = GM->GetGunner()->pos;

	if (
		playerPos.x > pos.x - detectRange.x &&
		playerPos.x < pos.x + detectRange.x &&
		playerPos.y < pos.y + detectRange.y &&
		playerPos.y > pos.y - detectRange.y
		)
		isDetectedPlayer = true;
	else
	{
		isDetectedPlayer = false;
	}

	if (playerPos.x > pos.x) isRight = true;
	else isRight = false;
}

void Gnoll_Mirkwood::Die()
{
	char buff[100];
	sprintf_s(buff, "¿Ö È£Ãâ\n");
	OutputDebugStringA(buff);

	if (!isDie)
	{
		isDie = true;
		isActive = false;
		collider->isActive = false;
		pos = { 2000,2000 };
		collider->pos = { 2000,2000 };
	}
}

void Gnoll_Mirkwood::LoadAction(string path, string file, Action::Type type, float speed)
{
	XmlDocument* document = new XmlDocument();
	document->LoadFile((path + file).c_str());

	XmlElement* atlas = document->FirstChildElement();
	string fileName = atlas->Attribute("imagePath");
	fileName = path + fileName;
	wstring imagePath;
	imagePath.assign(fileName.begin(), fileName.end());

	Texture* texture = Texture::Add(imagePath);

	vector<Action::Clip> clips;
	XmlElement* sprite = atlas->FirstChildElement();

	while (sprite != nullptr)
	{
		float x, y, w, h;

		x = sprite->FloatAttribute("x");
		y = sprite->FloatAttribute("y");
		w = sprite->FloatAttribute("w");
		h = sprite->FloatAttribute("h");

		clips.emplace_back(x, y, w, h, texture);

		sprite = sprite->NextSiblingElement();
	}

	actions.emplace_back(new Action(clips, type, speed));

	delete document;
}

void Gnoll_Mirkwood::SetAction(ActionType type)
{
	if (curAction != type)
	{
		curAction = type;
		actions[curAction]->Play();
	}
}

void Gnoll_Mirkwood::SetIdle()
{
}

void Gnoll_Mirkwood::Test()
{
}
