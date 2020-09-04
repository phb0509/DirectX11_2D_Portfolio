#include "Framework.h"

Gunner::Gunner()
	: walkSpeed(250), runSpeed(600), jumpPower(0), gravity(980.0f), curAction(IDLE), attackOffset(100, 0),
	isRight(true), isAttack(false), isJump(false), isRightRun(false), isLeftRun(false), rightRunCheckTime(0.0f), leftRunCheckTime(0.0f)
{
	sprite = new Sprite(L"KnightShader");

	pos = { 0, 0 };

	string path = "Textures/Gunner/";

	LoadAction(path, "IDLE.xml", Action::PINGPONG, 0.15f);
	LoadAction(path, "WALK.xml", Action::LOOP);
	LoadAction(path, "RUN.xml", Action::LOOP);



	//actions[ATTACK]->SetEndEvent(bind(&Knight::AttackEnd, this));

	//attackCollider = new RectCollider({ 150, 100 }, this);
	//attackCollider->isActive = false;

	/*effect = new Effect(L"Textures/Effects/fire_8x2.png", 8, 2);
	effect->SetAdditive(true);

	intBuffer = new IntBuffer();
	intBuffer->data.index[2] = 1;
	colorBuffer = new ColorBuffer();
	colorBuffer->data.color = Float4(1, 0, 0, 1);*/
}

Gunner::~Gunner()
{
	delete sprite;

	for (Action* action : actions)
		delete action;

	delete attackCollider;
}

void Gunner::Update()
{
	Move();
	//Attack();
	//Jump();

	Action::Clip curClip = actions[curAction]->GetCurClip();
	sprite->SetAction(curClip);

	actions[curAction]->Update();
	sprite->Update();

	scale.x = isRight ? curClip.size.x : -curClip.size.x;
	scale.y = curClip.size.y;

	UpdateWorld();

	//attackCollider->Update();

	//effect->Update();
}

void Gunner::Render()
{
	/*intBuffer->SetPSBuffer(1);
	colorBuffer->SetPSBuffer(2);*/

	SetWorldBuffer();
	sprite->Render();
	//attackCollider->Render();

	//effect->Render();
}

void Gunner::Move()
{
	if (isAttack) return;


	{ // 오른쪽 달리기 체크
		if (KEY_DOWN(VK_RIGHT) && (Timer::Get()->GetRunTime() <= rightRunCheckTime))
		{
			isRightRun = true;
		}

		if (KEY_UP(VK_RIGHT))
		{
			rightRunCheckTime = Timer::Get()->GetRunTime() + 0.1f;
		}
	}

	{ // 왼쪽 달리기 체크
		if (KEY_DOWN(VK_LEFT) && (Timer::Get()->GetRunTime() <= leftRunCheckTime))
		{
			isLeftRun = true;
		}

		if (KEY_UP(VK_LEFT))
		{
			leftRunCheckTime = Timer::Get()->GetRunTime() + 0.1f;
		}
	}


	if (KEY_PRESS(VK_RIGHT))
	{
		if (!isJump)
		{
			if (!isRightRun) SetAction(WALK);
			else if (isRightRun) SetAction(RUN);
		}

		if (!isRightRun) pos.x += walkSpeed * DELTA;
		else if (isRightRun) pos.x += runSpeed * DELTA;

		if (!isRight)
		{
			isRight = true;
		}

	}



	if (KEY_PRESS(VK_LEFT))
	{
		if (!isJump)
		{
			if (!isLeftRun) SetAction(WALK);
			else if (isLeftRun) SetAction(RUN);
		}

		if (!isLeftRun) pos.x -= walkSpeed * DELTA;
		else if (isLeftRun) pos.x -= runSpeed * DELTA;

		if (isRight)
		{
			isRight = false;
		}
	}


	if (KEY_PRESS(VK_UP))
	{
		pos.y += walkSpeed * DELTA;
	}

	if (KEY_PRESS(VK_DOWN))
	{
		pos.y -= walkSpeed * DELTA;
	}

	if (KEY_UP(VK_RIGHT) || KEY_UP(VK_LEFT)) // 여기서 땠을 때 카운트. 0.1초안에 위,아래 입력이 들어가며
	{
		isRightRun = false;
		isLeftRun = false;
		SetAction(IDLE);
	}
}

void Gunner::Attack()
{
	/*if (isAttack) return;

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
	}*/
}

void Gunner::Jump()
{
	/*if (isAttack) return;

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
	}*/
}

void Gunner::LoadAction(string path, string file, Action::Type type, float speed)
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

void Gunner::SetAction(ActionType type)
{
	if (curAction != type)
	{
		curAction = type;
		actions[curAction]->Play();
	}
}

void Gunner::AttackEnd()
{
	SetAction(IDLE);
	attackCollider->isActive = false;
	isAttack = false;
}

