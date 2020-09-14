#include "Framework.h"

Bullet::Bullet() : 
	curAction(IDLE), isRight(true), speed(700), damage(20), disabledDistance(0)
{
	pos = { 0, 0 };
	sprite = new Sprite();
	collider = new RectCollider({ 20, 10 }, this);

	isActive = false;
	collider->isActive = false;

	string path = "Textures/Gunner/";
	LoadAction(path, "BULLET.xml", Action::PINGPONG, 0.1f);

}

Bullet::~Bullet()
{
	delete sprite;
	delete collider;
	for (Action* action : actions)
		delete action;

}

void Bullet::Update(vector<Monster*> monsters)
{
	if (!isActive) return;

	CheckDisabledTime();

	Action::Clip curClip = actions[curAction]->GetCurClip();
	sprite->SetAction(curClip);

	actions[curAction]->Update();

	scale.x = isRight ? curClip.size.x : -curClip.size.x;
	scale.y = curClip.size.y;


	if (isRight)
	{
		pos.x += speed * DELTA;
		collider->SetOffset({ 35,0 });
	}

	else
	{
		pos.x -= speed * DELTA;
		collider->SetOffset({ -35,0 });
	}

	for (int i = 0; i < monsters.size(); i++)
	{
		if (monsters[i]->GetColliderIsActive())
		{
			if (collider->IsCollision(monsters[i]->GetCollider()))
			{
				monsters[i]->OnDamage(damage);
				isActive = false;
				collider->isActive = false;
			}
		}
	}
	
	collider->Update();
	UpdateWorld();
}

void Bullet::Render()
{
	if (!isActive) return;

	SetWorldBuffer();
	sprite->Render();

	collider->Render();
}

void Bullet::Fire(Vector2 gunner_position, bool gunner_isRight)
{
	isRight = gunner_isRight;
	pos.y = gunner_position.y + 60;

	if (isRight)
	{
		pos.x = gunner_position.x + 40;
		disabledDistance = pos.x + 500;
	}
	else
	{
		pos.x = gunner_position.x - 40;
		disabledDistance = pos.x - 500;
	}

	isActive = true;
	collider->isActive = true;

}

void Bullet::CheckDisabledTime()
{
	if (isRight)
	{
		if (pos.x >= disabledDistance)
		{
			isActive = false;
			collider->isActive = false;
		}
	}

	else
	{
		if (pos.x <= disabledDistance)
		{
			isActive = false;
			collider->isActive = false;
		}
	}
}




void Bullet::LoadAction(string path, string file, Action::Type type, float speed)
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

void Bullet::SetAction(ActionType type)
{
	if (curAction != type)
	{
		curAction = type;
		actions[curAction]->Play();
	}
}
