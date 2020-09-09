#include "Framework.h"

Monster1::Monster1() 
{
	sprite = new Sprite();

	pos = { 300, 300 };

	string path = "Textures/Monster1/";

	LoadAction(path, "IDLE.xml", Action::END);
	LoadAction(path, "WALK.xml", Action::PINGPONG);


	//actions[FIRSTSHOT]->SetEndEvent(bind(&Gunner::FirstFire, this));
}

Monster1::Monster1(Vector2 _pos) : isRight(false) , isAttack(false), hp(100), isDie(false)
{
	sprite = new Sprite();
	collider = new RectCollider({118, 116 }, this);
	pos = _pos;

	string path = "Textures/Monster1/";

	LoadAction(path, "IDLE.xml", Action::END);
	LoadAction(path, "WALK.xml", Action::PINGPONG);


	//actions[FIRSTSHOT]->SetEndEvent(bind(&Gunner::FirstFire, this));
}

Monster1::~Monster1()
{
	delete sprite;

	for (Action* action : actions)
		delete action;
}

void Monster1::Update()
{
	if (!isActive) return;
	//Test();

	Move();
	Attack();
	//Jump();

	Action::Clip curClip = actions[curAction]->GetCurClip();
	sprite->SetAction(curClip);

	actions[curAction]->Update();

	scale.x = isRight ? curClip.size.x : -curClip.size.x;
	scale.y = curClip.size.y;


	collider->Update();
	UpdateWorld();

	//attackCollider->Update();

	//effect->Update();
}

void Monster1::Render()
{
	if (!isActive) return;

	SetWorldBuffer();
	sprite->Render();

	collider->Render();
}

void Monster1::Move()
{
	Vector2 dir = (GM->GetGunner()->pos - pos).Normal();
	pos += dir * 100 * DELTA;
}

void Monster1::Attack()
{
}

void Monster1::OnDamage(float damage)
{
	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;
		Die();
	}
}

void Monster1::Die()
{
	if (!isDie)
	{
		isDie = true;
		isActive = false;
		collider->isActive = false;
		pos = { 2000,2000 };
		collider->pos = { 2000,2000 };
	}
}

void Monster1::LoadAction(string path, string file, Action::Type type, float speed)
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

void Monster1::SetAction(ActionType type)
{
	if (curAction != type)
	{
		curAction = type;
		actions[curAction]->Play();
	}
}

void Monster1::SetIdle()
{
}

void Monster1::Test()
{
}
