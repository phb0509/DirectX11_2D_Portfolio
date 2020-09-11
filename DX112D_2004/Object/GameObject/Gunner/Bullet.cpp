#include "Framework.h"

Bullet::Bullet() : 
	curAction(IDLE), isRight(true), speed(700)
{
	sprite = new Sprite();

	pos = { 0, 0 };
	isActive = false;
	string path = "Textures/Gunner/";

	LoadAction(path, "BULLET.xml", Action::PINGPONG, 0.1f);
	
	//actions[FINISHMOTION]->SetEndEvent(bind(&Gunner::SetIdle, this));

	bulletCollider = new RectCollider({ 20, 10 }, this);
	//bulletCollider->SetOffset({ 35,0 });

	//bulletCollider->isActive = true;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	//if (!isActive) return;

	//Action::Clip curClip = actions[curAction]->GetCurClip();
	//sprite->SetAction(curClip);

	//actions[curAction]->Update();

	//scale.x = isRight ? curClip.size.x : -curClip.size.x;
	//scale.y = curClip.size.y;

	//if (isRight)
	//{
	//	pos.x += speed * DELTA;
	//	bulletCollider->SetOffset({ 35,0 });
	//}
	//else
	//{
	//	pos.x -= speed * DELTA;
	//	bulletCollider->SetOffset({ -35,0 });
	//}

	//bulletCollider->Update();
	//UpdateWorld();
}

void Bullet::Update(vector<Monster*> monsters)
{
	if (!isActive) return;

	Action::Clip curClip = actions[curAction]->GetCurClip();
	sprite->SetAction(curClip);

	actions[curAction]->Update();

	scale.x = isRight ? curClip.size.x : -curClip.size.x;
	scale.y = curClip.size.y;

	if (isRight)
	{
		pos.x += speed * DELTA;
		bulletCollider->SetOffset({ 35,0 });
	}
	else
	{
		pos.x -= speed * DELTA;
		bulletCollider->SetOffset({ -35,0 });
	}

	for (int i = 0; i < monsters.size(); i++)
	{
		if (bulletCollider->IsCollision(monsters[i]->GetCollider()))
		{
			monsters[i]->OnDamage(20);
			isActive = false;
			pos = { -100,-100 };
			bulletCollider->pos = { -100,-100 };
		}
	}
	









	bulletCollider->Update();
	UpdateWorld();
}

void Bullet::Render()
{
	if (!isActive) return;

	SetWorldBuffer();
	sprite->Render();

	bulletCollider->Render();
}

void Bullet::Fire(Vector2 gunner_position, bool gunner_isRight)
{
	isRight = gunner_isRight;
	pos.y = gunner_position.y + 60;

	if (isRight)
	{
		pos.x = gunner_position.x + 40;
	}
	else
	{
		pos.x = gunner_position.x - 40;
	}

	isActive = true;

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
