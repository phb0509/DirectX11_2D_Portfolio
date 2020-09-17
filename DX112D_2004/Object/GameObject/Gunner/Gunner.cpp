#include "Framework.h"

Gunner::Gunner()
	: currentTime(0.0f), walkSpeed(250), runSpeed(600), jumpPower(0), gravity(980.0f), curAction(IDLE), attackOffset(100, 0),
	isRight(true), isAttack(false), isJump(false), isRightRun(false), isLeftRun(false), rightRunCheckTime(0.0f), leftRunCheckTime(0.0f), trigger_Move(true),
	isFirstAttack(false), comboAttackCount(0), maxAttackTime(0), isComboShotEndTrigger(false)
{
	pos = { 0, 200 };

	InitMotion();


	// Init Bullet
	for (int i = 0; i < 500; i++)
	{
		bullet = new Bullet();
		gunner_bullets.emplace_back(bullet);
	}
}

Gunner::~Gunner()
{
	delete sprite;

	for (Action* action : actions)
		delete action;

	for (int i = 0; i < gunner_bullets.size(); i++)
	{
		delete gunner_bullets[i];
	}

}

void Gunner::Update()
{
	if (!isActive) return;

	currentTime = Timer::Get()->GetRunTime();

	CheckIdle_AfterRun();
	Move();
	Run();
	Attack();
	//Jump();

	Action::Clip curClip = actions[curAction]->GetCurClip();
	sprite->SetAction(curClip);

	actions[curAction]->Update();

	scale.x = isRight ? curClip.size.x : -curClip.size.x;
	scale.y = curClip.size.y;

	for (int i = 0; i < gunner_bullets.size(); i++)
	{
		gunner_bullets[i]->Update(GM->GetMirkwoodMonsters());
	}

	UpdateWorld();

	//attackCollider->Update();
	//effect->Update();
}

void Gunner::Render()
{
	if (!isActive) return;
	/*intBuffer->SetPSBuffer(1);
	colorBuffer->SetPSBuffer(2);*/

	for (int i = 0; i < gunner_bullets.size(); i++)
	{
		gunner_bullets[i]->Render();
	}

	SetWorldBuffer();
	sprite->Render();

	//attackCollider->Render();
	//effect->Render();
}

void Gunner::Move()
{
	if (isJump) return;
	if (isAttack) return;
	if (!trigger_Move) return;


	if (KEY_PRESS(VK_RIGHT))
	{
		SetAction(WALK);

		pos.x += walkSpeed * DELTA;

		if (!isRight)
		{
			isRight = true;
		}
	}

	if (KEY_PRESS(VK_LEFT))
	{

		SetAction(WALK);


		pos.x -= walkSpeed * DELTA;

		if (isRight)
		{
			isRight = false;
		}
	}


	if (KEY_PRESS(VK_UP))
	{
		pos.y += walkSpeed * DELTA;

		SetAction(WALK);
	}


	if (KEY_PRESS(VK_DOWN))
	{
		pos.y -= walkSpeed * DELTA;

		SetAction(WALK);
	}


	if (KEY_UP(VK_UP) || KEY_UP(VK_DOWN))
	{
		SetAction(IDLE);
	}

	{ // 오른쪽 달리기 체크
		if (KEY_DOWN(VK_RIGHT) && (currentTime <= rightRunCheckTime))
		{
			isRightRun = true;
			trigger_Move = false;
		}

		if (KEY_UP(VK_RIGHT))
		{
			rightRunCheckTime = currentTime + 0.1f;
			SetAction(IDLE);
		}
	}

	{ // 왼쪽 달리기 체크

		if (KEY_DOWN(VK_LEFT) && (currentTime <= leftRunCheckTime))
		{
			isLeftRun = true;
			trigger_Move = false;
		}

		if (KEY_UP(VK_LEFT))
		{
			leftRunCheckTime = currentTime + 0.1f;
			SetAction(IDLE);
		}
	}
}

void Gunner::Run()
{
	if (isJump) return;
	if (isAttack) return;
	if (trigger_Move) return;


	SetAction(RUN);

	if (KEY_PRESS(VK_RIGHT))
	{
		pos.x += runSpeed * DELTA;
	}

	if (KEY_PRESS(VK_LEFT))
	{
		pos.x -= runSpeed * DELTA;
	}

	if (KEY_PRESS(VK_UP))
	{
		pos.y += runSpeed * DELTA;
	}

	if (KEY_PRESS(VK_DOWN))
	{
		pos.y -= runSpeed * DELTA;
	}



	
	if (isRight)
	{
		if (KEY_DOWN(VK_LEFT))
		{
			trigger_Move = true;
		}
	}
	else
	{
		if (KEY_DOWN(VK_RIGHT))
		{
			trigger_Move = true;
		}
	}

	if (!(GetAsyncKeyState(VK_UP) & 0x8000) &&
		!(GetAsyncKeyState(VK_DOWN) & 0x8000) &&
		!(GetAsyncKeyState(VK_LEFT) & 0x8000) &&
		!(GetAsyncKeyState(VK_RIGHT) & 0x8000))
	{
		trigger_Move = true;
		SetAction(IDLE);
	}
}






void Gunner::CheckIdle_AfterRun()
{

}



void Gunner::Attack()
{
	if (isComboShotEndTrigger == true)
	{
		if (CheckAttackInterval())
		{
			SetAction(IDLE);
			isComboShotEndTrigger = false;
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
		comboAttackCount = 0;
	}

	if (curAction == LASTSHOT ||
		curAction == FINISHMOTION) return;


	if (KEY_DOWN('X'))
	{
		maxAttackTime = currentTime + 0.4f;

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
	if (currentTime <= maxAttackTime) return true;
	else return false;
}




void Gunner::Shot()
{
	for (int i = 0; i < gunner_bullets.size(); i++)
	{
		if (gunner_bullets[i]->isActive == false)
		{
			gunner_bullets[i]->Fire(pos, isRight);
			break;
		}
	}
}

void Gunner::Jump()
{


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
}

void Gunner::ComboShotEnd()
{
	maxAttackTime = currentTime + 0.25f;
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



void Gunner::InitMotion()
{
	sprite = new Sprite();
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