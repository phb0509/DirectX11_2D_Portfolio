#include "Framework.h"

Gunner::Gunner()
	: walkSpeed(250), runSpeed(600), jumpPower(0), gravity(980.0f), curAction(IDLE), attackOffset(100, 0),
	isRight(true), isAttack(false), isJump(false), isRightRun(false), isLeftRun(false), rightRunCheckTime(0.0f), leftRunCheckTime(0.0f),
	isFirstAttack(false), comboAttackCount(0), maxAttackTime(0), isComboShotEndTrigger(false)
{
	sprite = new Sprite();


	pos = { 0, 0 };

	string path = "Textures/Gunner/";

	LoadAction(path, "IDLE.xml", Action::PINGPONG, 0.15f);
	LoadAction(path, "WALK.xml", Action::LOOP);
	LoadAction(path, "RUN.xml", Action::LOOP);

	// 평타모션 head
	LoadAction(path, "FIRSTSHOT.xml", Action::END);
	LoadAction(path, "COMBOSHOT.xml", Action::END);
	LoadAction(path, "LASTSHOT.xml", Action::END, 0.07);
	LoadAction(path, "FINISHMOTION.xml", Action::END);
	// 평타모션 footer


	actions[FIRSTSHOT]->SetEndEvent(bind(&Gunner::FirstFire, this));
	actions[COMBOSHOT]->SetEndEvent(bind(&Gunner::ComboShotEnd, this));
	actions[LASTSHOT]->SetEndEvent(bind(&Gunner::SecondFire, this));
	actions[FINISHMOTION]->SetEndEvent(bind(&Gunner::SetIdle, this));

	/*FIRSTSHOT->EndEvent(Fire(1));
	LASTSHOT->EndEvent(Fire(2));*/


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

}

void Gunner::Update()
{

	//Test();

	Move();
	Attack();
	//Jump();

	Action::Clip curClip = actions[curAction]->GetCurClip();
	sprite->SetAction(curClip);

	actions[curAction]->Update();

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
	if (isComboShotEndTrigger == 1)
	{
		if (CheckAttackInterval())
		{
			SetAction(IDLE);
			isComboShotEndTrigger = false;
			count = 0;
			isAttack = false;
			isFirstAttack = false;
			comboAttackCount = 0;
		}
	}


	if (CheckAttackInterval())
	{
		isAttack = true;
	}

	else
	{
		isAttack = false;
		isFirstAttack = false;
		//SetAction(IDLE);
		comboAttackCount = 0;
	}

	if (curAction == LASTSHOT ||
		curAction == FINISHMOTION) return;


	if (KEY_DOWN('X'))
	{
		maxAttackTime = Timer::Get()->GetRunTime() + 0.4f;

		if (!isFirstAttack && comboAttackCount == 0)
		{
			isFirstAttack = true;
			SetAction(FIRSTSHOT); // EndEvent(FirstFire())
		}

		else if (isFirstAttack && comboAttackCount <= 4)
		{
			comboAttackCount++;
			SetAction(COMBOSHOT);
			Fire();
		}

		else if (comboAttackCount == 5)
		{
			comboAttackCount = 0;
			SetAction(LASTSHOT); // EndEvent(SecondFire());
		}
	}

}


bool Gunner::CheckAttackInterval()
{
	if (Timer::Get()->GetRunTime() <= maxAttackTime) return true;
	else return false;
}


void Gunner::Shot()
{
	//count++;
	//char buff[100];
	//sprintf_s(buff, "%d 번째 총알 발사!\n", count);
	//OutputDebugStringA(buff);


	

	for (int i = 0; i < GM->GetGunnerBullets().size(); i++)
	{
		if (GM->GetGunnerBullets()[i]->isActive == false)
		{
			GM->GetGunnerBullets()[i]->Fire(pos, isRight);
			break;
		}
	}

}


void Gunner::Fire()
{
	Shot();
}

void Gunner::FirstFire()
{
	SetAction(COMBOSHOT);
	Shot();
}

void Gunner::SecondFire()
{
	SetAction(FINISHMOTION);
	Shot();
	count = 0;
}

void Gunner::ComboShotEnd()
{
	maxAttackTime = Timer::Get()->GetRunTime() + 0.25f;
	isComboShotEndTrigger = true;
}

void Gunner::SetIdle()
{
	SetAction(IDLE);
}



void Gunner::SetAction(ActionType type)
{
	if (type == COMBOSHOT)
	{
		curAction = type;
		actions[curAction]->Play();
	}

	else
	{
		if (curAction != type)
		{
			curAction = type;
			actions[curAction]->Play();
		}
	}
}

void Gunner::Test()
{
	char buff[100];
	switch (curAction)
	{
	case 0:
		sprintf_s(buff, " IDLE \n");
		OutputDebugStringA(buff);
		break;

	case 1:
		sprintf_s(buff, " WALK \n");
		OutputDebugStringA(buff);
		break;

	case 2:
		sprintf_s(buff, " RUN \n");
		OutputDebugStringA(buff);
		break;

	case 3:
		sprintf_s(buff, " FIRSTSHOT \n");
		OutputDebugStringA(buff);
		break;

	case 4:
		sprintf_s(buff, " COMBOSHOT \n");
		OutputDebugStringA(buff);
		break;

	case 5:
		sprintf_s(buff, " LASTSHOT \n");
		OutputDebugStringA(buff);
		break;

	case 6:
		sprintf_s(buff, " FINISHMOTION \n");
		OutputDebugStringA(buff);
		break;
	}
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

void Gunner::Jump()
{

}