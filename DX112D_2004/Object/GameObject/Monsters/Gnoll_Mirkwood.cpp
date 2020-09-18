#include "Framework.h"



Gnoll_Mirkwood::Gnoll_Mirkwood(Vector2 _pos)
{
	sprite = new Sprite();
	collider = new RectCollider({118, 116 }, this);
	hpBar = new HPbar_Monster(hp);
	pos = _pos;

	string path = "Textures/Monster1/";

	LoadAction(path, "IDLE.xml", Action::END);
	LoadAction(path, "WALK.xml", Action::PINGPONG);
	LoadAction(path, "StandOnDamage.xml", Action::END,0.1f);
	LoadAction(path, "DIE.xml", Action::END, 0.1f);
}

Gnoll_Mirkwood::~Gnoll_Mirkwood()
{
	delete sprite;
	delete collider;
	delete hpBar;

	for (Action* action : actions)
		delete action;
}

void Gnoll_Mirkwood::Update()
{
	if (!isActive) return;

	CheckDead(); // 안죽었으면 X
	CheckOnDamage(); // 죽으면 X
	DetectPlayer(); // 죽으면 X
	Move(); // 죽거나,공격받는중이면 X  
	Attack(); // 미구현.

	Action::Clip curClip = actions[curAction]->GetCurClip();
	sprite->SetAction(curClip);

	actions[curAction]->Update();

	scale.x = isRight ? curClip.size.x : -curClip.size.x;
	scale.y = curClip.size.y;

	collider->Update();
	hpBar->Update();
	UpdateWorld();

	//effect->Update();
}

void Gnoll_Mirkwood::Render()
{
	if (!isActive) return;

	SetWorldBuffer();
	sprite->Render();

	collider->Render();
	hpBar->Render();
}


void Gnoll_Mirkwood::Move()
{
	if (isDie) return;

	if (isOnDamage) return;

	if (isDetectedPlayer)
	{
		SetAction(Walk);

		if (GM->GetGunner()->pos == pos)
		{
			pos.x -= 0.5f;
		}

		Vector2 dir = (GM->GetGunner()->pos - pos).Normal();
		pos += dir * speed * DELTA;
	}

	else SetAction(Idle);
}

void Gnoll_Mirkwood::Attack()
{
}

void Gnoll_Mirkwood::OnDamage(float damage)
{
	if (isDie) return;

	onDamageStateCheckTime = Timer::Get()->GetRunTime() + hitRecovery;

	hp -= damage;

	if (hp <= 0)
	{
		hp = 0;
		Die();
	}
}



void Gnoll_Mirkwood::CheckOnDamage()
{
	if (isDie) return;

	if (Timer::Get()->GetRunTime() < onDamageStateCheckTime) // 아직 피격중이면.
	{
		isOnDamage = true;
		SetAction(StandOnDamage);

		if (isRight) pos.x -= 50 * DELTA;
		else pos.x += 50 * DELTA;

	}

	else
	{
		isOnDamage = false;
	}
}

void Gnoll_Mirkwood::CheckDead()
{
	if(!isDie) return;

	if (Timer::Get()->GetRunTime() < deadTime)
	{
		SetAction(DIE);
	}

	else
	{
		isActive = false;
	}
}


void Gnoll_Mirkwood::DetectPlayer()
{
	if (isDie) return;

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

	if (playerPos.x >= pos.x) isRight = true;
	else isRight = false;
}

void Gnoll_Mirkwood::Die()
{
	if (!isDie)
	{
		isDie = true;
		deadTime = Timer::Get()->GetRunTime() + 2.0f;
		collider->isActive = false;
	}
}

void Gnoll_Mirkwood::Reactivation()
{
	hp = 100.0f;
	isActive = true;
	collider->isActive = true;
	isDie = false;
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
