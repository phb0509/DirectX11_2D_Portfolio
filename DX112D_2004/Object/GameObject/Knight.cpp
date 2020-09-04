#include "Framework.h"

Knight::Knight()
	: speed(500), jumpPower(0), gravity(980.0f), curAction(IDLE), attackOffset(100, 0),
	isRight(true), isAttack(false), isJump(false)
{
	sprite = new Sprite(L"KnightShader");

	pos = { 0, 0 };

	string path = "Textures/Knight/";

	LoadAction(path, "KnightIdle.xml", Action::LOOP);
	LoadAction(path, "KnightWalk.xml", Action::LOOP);
	LoadAction(path, "KnightAttack.xml", Action::END);
	LoadAction(path, "KnightJump.xml", Action::END);

	actions[ATTACK]->SetEndEvent(bind(&Knight::AttackEnd, this));

	attackCollider = new RectCollider({ 150, 100 }, this);		
	attackCollider->isActive = false;

	effect = new Effect(L"Textures/Effects/fire_8x2.png", 8, 2);
	effect->SetAdditive(true);

	intBuffer = new IntBuffer();
	intBuffer->data.index[2] = 1;
	colorBuffer = new ColorBuffer();
	colorBuffer->data.color = Float4(1, 0, 0, 1);
}

Knight::~Knight()
{
	delete sprite;

	for (Action* action : actions)
		delete action;

	delete attackCollider;
}

void Knight::Update()
{
	Move();
	Attack();
	//Jump();

	Action::Clip curClip = actions[curAction]->GetCurClip();
	sprite->SetAction(curClip);

	actions[curAction]->Update();
	sprite->Update();

	scale.x = isRight ? curClip.size.x : -curClip.size.x;
	scale.y = curClip.size.y;

	UpdateWorld();

	attackCollider->Update();

	effect->Update();
}

void Knight::Render()
{
	intBuffer->SetPSBuffer(1);
	colorBuffer->SetPSBuffer(2);

	SetWorldBuffer();
	sprite->Render();
	attackCollider->Render();

	effect->Render();
}

void Knight::Move()
{
	if (isAttack) return;

	if (KEY_PRESS(VK_RIGHT))
	{
		if(!isJump)
			SetAction(WALK);
		pos.x += speed * DELTA;

		if (!isRight)
		{
			//rot.y = 0;
			isRight = true;
		}
	}

	if (KEY_PRESS(VK_LEFT))
	{
		if (!isJump)
			SetAction(WALK);
		pos.x -= speed * DELTA;

		if (isRight)
		{
			//rot.y = PI;
			isRight = false;
		}
	}

	if (KEY_PRESS(VK_UP))
		pos.y += speed * DELTA;
	if (KEY_PRESS(VK_DOWN))
		pos.y -= speed * DELTA;


	if (KEY_UP(VK_RIGHT) || KEY_UP(VK_LEFT))
		SetAction(IDLE);
}

void Knight::Attack()
{
	if (isAttack) return;

	if (KEY_DOWN(VK_SPACE))
	{
		SetAction(ATTACK);
		attackCollider->isActive = true;
		isAttack = true;

		Vector2 attackPos;
		if (isRight)
		{
			attackPos = attackOffset;
		}
		else
		{
			attackPos = { -attackOffset.x, attackOffset.y };
		}

		attackCollider->SetOffset(attackPos);

		effect->Play(pos + attackPos);
		CAMERA->ShakeStart(50, 1.0f, 100.0f);
	}
}

void Knight::Jump()
{
	if (isAttack) return;	

	if (KEY_DOWN(VK_UP) && !isJump)
	{
		jumpPower = 300.0f;
		SetAction(JUMP);
		isJump = true;
	}
	if (isJump)
	{
		jumpPower -= gravity * DELTA;
		pos.y += jumpPower * DELTA;

		if (pos.y < 300)
		{
			pos.y = 300;
			jumpPower = 0;
			SetAction(IDLE);
			isJump = false;
		}
	}
}

void Knight::LoadAction(string path, string file, Action::Type type, float speed)
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

void Knight::SetAction(ActionType type)
{
	if (curAction != type)
	{
		curAction = type;
		actions[curAction]->Play();
	}
}

void Knight::AttackEnd()
{
	SetAction(IDLE);
	attackCollider->isActive = false;
	isAttack = false;
}

