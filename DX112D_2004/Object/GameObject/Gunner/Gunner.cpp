#include "Framework.h"

Gunner::Gunner()
	: currentTime(0.0f), walkSpeed(250), runSpeed(600), jumpPower(0), gravity(980.0f), curAction(IDLE), attackOffset(100, 0), isDie(false), hitRecovery(0.3f),deadTime(0.0f),
	isRight(true), isAttack(false), isJump(false), isRightRun(false), isLeftRun(false), rightRunCheckTime(0.0f), leftRunCheckTime(0.0f), trigger_Move(true), trigger_AfterOnDamage(false),
	isFirstAttack(false), comboAttackCount(0), maxAttackTime(0), isComboShotEndTrigger(false) , maxHP(10000), maxMP(2000),isOnDamage(false), onDamageStateCheckTime(0.0f), onDamageDir(false),
	hitCheckColliderHeight(13.0f),isUpShot(true)
{
	currentHP = maxHP;
	currentMP = maxMP;

	pos = { 0, 0 };
	collider = new RectCollider({ 80,120 }, this);
	hitCheckCollider = new RectCollider({ 80, hitCheckColliderHeight * 2});


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
	delete collider;

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
	hitCheckCollider->pos = { pos.x,pos.y - 60 };

	Move();
	Run();
	Attack();
	CheckOnDamage();
	CheckDead();
	
	//Jump();


	//char buff[100];
	//sprintf_s(buff, "mousePos.x : %f, mousePos.y : %f ,  radian : %f \n",mousePos.x,mousePos.y, atan2(mousePos.y - pos.y, mousePos.x - pos.x));
	//OutputDebugStringA(buff);

	Action::Clip curClip = actions[curAction]->GetCurClip();
	sprite->SetAction(curClip);

	actions[curAction]->Update();

	scale.x = isRight ? curClip.size.x : -curClip.size.x;
	scale.y = curClip.size.y;

	for (int i = 0; i < gunner_bullets.size(); i++)
	{
		gunner_bullets[i]->Update(GM->GetMirkwoodMonsters());
	}


	collider->Update();
	hitCheckCollider->Update();
	UpdateWorld();

	//char buff[100];
	//sprintf_s(buff, "isAttack : %d\n",isAttack);
	//OutputDebugStringA(buff);

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

	collider->Render();
	hitCheckCollider->Render();

	SetWorldBuffer();
	sprite->Render();
	//effect->Render();
}

void Gunner::Attack()
{
	if (curAction == LASTSHOT ||            // x키연타중이여도 계속 애니메이션 그대로 재생시키게 리턴시켜놨음.
		curAction == FINISHMOTION ||
		curAction == DOWNLASTSHOT ||
		curAction == DOWNFINISHMOTION
		) return;

	if (isComboShotEndTrigger == true) // 콤보샷 도중인상태에서
	{
		if (!CheckAttackInterval()) // 
		{
			SetAction(IDLE);
			isComboShotEndTrigger = false;
			isAttack = false;
			isFirstAttack = false;
			comboAttackCount = 0;
		}
	}

	if (CheckAttackInterval()) // 마지막 공격끝난지 별로 안됐으면 공격상태유지.
	{
		isAttack = true;
	}

	else // 마지막 공격 끝난지 일정시간 지났으면 공격상태 해제, 다시 첫공격부터시작.
	{
		isAttack = false;
		isFirstAttack = false;
		comboAttackCount = 0;
	}

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
			
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				SetAction(DOWNCOMBOSHOT); // EndEvent(ComboShotEnd());
				isUpShot = false;
				Fire();
			}

			else
			{
				SetAction(UPCOMBOSHOT); // EndEvent(ComboShotEnd());
				isUpShot = true;
				Fire();
			}
		}

		else if (comboAttackCount == 5)
		{
			comboAttackCount = 0;

			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				isUpShot = false;
				SetAction(DOWNLASTSHOT);
				char buff[100];
				sprintf_s(buff, "다운 라스트샷\n");
				OutputDebugStringA(buff);
			}

			else
			{
				isUpShot = true;
				SetAction(LASTSHOT); // EndEvent(SecondFire());
			}
		}
	}
}

bool Gunner::CheckAttackInterval()
{
	if (currentTime <= maxAttackTime) return true; // 아직 공격중이면
	else return false;
}


void Gunner::Shot()
{
	for (int i = 0; i < gunner_bullets.size(); i++)
	{
		if (gunner_bullets[i]->isActive == false)
		{
			gunner_bullets[i]->Fire(pos, isRight, isUpShot); // 플레이어 위치만 넘겨주니까 업,다운샷 여부에 따른 위치조정은 불렛에서 처리하기.
			break;
		}
	}
}

void Gunner::Fire()
{
	Shot();
}

void Gunner::FirstFire() // 
{
	if (isUpShot) SetAction(UPCOMBOSHOT);
	else SetAction(DOWNCOMBOSHOT);

	Shot();
}

void Gunner::SecondFire()
{
	if (isUpShot) SetAction(FINISHMOTION);
	else SetAction(DOWNFINISHMOTION);

	Shot();
}

void Gunner::ComboShotEnd() // 콤보샷 애니메이션 실행 후 실행되는 함수.
{
	maxAttackTime = currentTime + 0.25f;
	isComboShotEndTrigger = true;
}


void Gunner::InitMotion()
{
	sprite = new Sprite();
	string path = "Textures/Gunner/";

	//LoadAction(path, "IDLE.xml", Action::PINGPONG, 0.15f);
	LoadAction(path, "IDLE.xml", Action::PINGPONG, 0.15f);
	LoadAction(path, "WALK.xml", Action::LOOP);
	LoadAction(path, "RUN.xml", Action::LOOP);

	// 정면 총알발사모션.
	LoadAction(path, "FIRSTSHOT.xml", Action::END);
	LoadAction(path, "UPCOMBOSHOT.xml", Action::END);
	LoadAction(path, "LASTSHOT.xml", Action::END, 0.07);
	LoadAction(path, "FINISHMOTION.xml", Action::END);

	// 아래쪽 총알발사모션.
	LoadAction(path, "DOWNCOMBOSHOT.xml", Action::END);
	LoadAction(path, "DOWNLASTSHOT.xml", Action::END, 0.07);
	LoadAction(path, "DOWNFINISHMOTION.xml", Action::END);


	LoadAction(path, "ONDAMAGE.xml", Action::END);
	LoadAction(path, "ONDAMAGE1.xml", Action::END);
	LoadAction(path, "Die.xml", Action::END);


	actions[FIRSTSHOT]->SetEndEvent(bind(&Gunner::FirstFire, this));
	actions[UPCOMBOSHOT]->SetEndEvent(bind(&Gunner::ComboShotEnd, this));
	actions[DOWNCOMBOSHOT]->SetEndEvent(bind(&Gunner::ComboShotEnd, this));

	actions[LASTSHOT]->SetEndEvent(bind(&Gunner::SecondFire, this));
	actions[DOWNLASTSHOT]->SetEndEvent(bind(&Gunner::SecondFire, this));

	actions[FINISHMOTION]->SetEndEvent(bind(&Gunner::SetIdle, this));
	actions[DOWNFINISHMOTION]->SetEndEvent(bind(&Gunner::SetIdle, this));




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


void Gunner::OnDamage(float damage, bool _onDamageDir) 
{
	if (isDie) return;

	//UM->Change_MonsterHPbar(hpBar);

	onDamageStateCheckTime = Timer::Get()->GetRunTime() + hitRecovery;
	onDamageDir = _onDamageDir;

	if (onDamageDir) isRight = false;
	else isRight = true;
	//hpBar->UpdateHPbar(hp, hp - damage);

	currentHP -= damage;

	if (currentHP <= 0)
	{
		currentHP = 0;
		Die();
	}
}


void Gunner::CheckOnDamage() // onDamageDir이 false면 왼쪽으로 밀려나야함
{
	if (Timer::Get()->GetRunTime() < onDamageStateCheckTime) // 아직 피격중이면.
	{
		isOnDamage = true;
		SetAction(ONDAMAGE);
		trigger_AfterOnDamage = true;

		if (onDamageDir)
		{
			pos.x += 100 * DELTA;
		}
		else
		{
			pos.x -= 100 * DELTA;
		}
	}

	else if(trigger_AfterOnDamage)
	{
		isOnDamage = false;
		trigger_AfterOnDamage = false;
		SetAction(IDLE);
	}
}

void Gunner::Die()
{
	if (!isDie)
	{
		isDie = true;
		deadTime = Timer::Get()->GetRunTime() + 2.0f;
		collider->isActive = false;
		//hpBar->SetMonsterDead();
	}
}

void Gunner::CheckDead()
{
	if (!isDie) return;

	if (Timer::Get()->GetRunTime() < deadTime)
	{
		SetAction(DIE);
	}

	else
	{
		isActive = false;
		//hpBar->SetHPbarDead();
	}
}

void Gunner::Reactivation()
{
	currentHP = maxHP;
	currentMP = maxMP;
	//hpBar->Reactivation();
	isActive = true;
	collider->isActive = true;
	//trigger_CheckPlayerDeath = true;
	isDie = false;
	SetAction(IDLE);
}

void Gunner::Move()
{
	if (isDie) return;
	if (isJump) return;
	if (isAttack) return;
	if (!trigger_Move) return;
	if (isOnDamage) return;

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
	if (isDie) return;
	if (isJump) return;
	if (isAttack) return;
	if (trigger_Move) return;
	if (isOnDamage) return;

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




void Gunner::Jump()
{


}

void Gunner::SetIdle()
{
	SetAction(IDLE);
	isAttack = false;
}




void Gunner::SetAction(ActionType type)
{
	if (type == UPCOMBOSHOT || type == DOWNCOMBOSHOT)
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
		sprintf_s(buff, " UPCOMBOSHOT \n");
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


