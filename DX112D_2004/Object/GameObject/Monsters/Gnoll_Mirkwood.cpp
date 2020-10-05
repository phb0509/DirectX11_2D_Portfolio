#include "Framework.h"



Gnoll_Mirkwood::Gnoll_Mirkwood(Vector2 _pos) : moveCheckTimeafterPlayerDeath(0.0f), trigger_CheckPlayerDeath(true), trigger_MoveAfterPlayerDeath(false)
{
	sprite = new Sprite();
	collider = new RectCollider({ 118, 108 }, this);



	attackCollider = new RectCollider({ 50,90 });
	attackCollider->isActive = false;

	hp = 10000;
	hpBar = new HPbar_Monster(hp);
	pos = _pos;
	damage = 1000.0f;

	InitMotion();
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

	gunner = GM->GetGunner();

	if (isRight) { attackCollider->pos = pos + Vector2(90, -20); }
	else { attackCollider->pos = pos + Vector2(-90, -20); }

	colliderBottom = pos.y - 54;


	CheckIsPossibleHitState();
	CheckPlayerDeath();
	MoveAfterPlayerDeath();
	CheckDead(); // 안죽었으면 X
	CheckOnDamage(); // 죽으면 X
	DetectPlayer(); // 죽으면 X
	CheckAttackRange();
	Move(); // 죽거나,공격받는중이면 X  
	Attack(); // 미구현.

	Action::Clip curClip = actions[curAction]->GetCurClip();
	sprite->SetAction(curClip);
	actions[curAction]->Update();

	scale.x = isRight ? curClip.size.x : -curClip.size.x;
	scale.y = curClip.size.y;

	collider->Update();
	attackCollider->Update();
	hpBar->Update();

	UpdateWorld();

	/*char buff[100];
	sprintf_s(buff, "gunner pos.y : %f\n monster pos.y : %f\n", gunner->pos.y, pos.y);
	OutputDebugStringA(buff);*/

	//effect->Update();
}

void Gnoll_Mirkwood::Render()
{
	if (!isActive) return;

	if (attackCollider->isActive)
	{
		attackCollider->Render();
	}

	SetWorldBuffer();
	sprite->Render();

	collider->Render();
}

void Gnoll_Mirkwood::Attack()
{
	if (!isAttack) return;
	if (isOnDamage) return;
	if (isDie) return;

	SetAction(SMASHATTACK);

	if (curAction == SMASHATTACK)
	{
		if (actions[curAction]->GetCurClipNum() == 2)
		{
			if (isAttackColliderTrigger)
			{
				attackCollider->isActive = true;
				isAttackColliderTrigger = false;

				if (attackCollider->IsCollision(gunner->GetGunnerCollider()))
				{
					if (gunner->pos.x <= pos.x)
					{
						gunner->OnDamage(damage, false);
					}
					else if (gunner->pos.x > pos.x)
					{
						gunner->OnDamage(damage, true);
					}
				}
			}
		}

		else
		{
			if (actions[curAction]->GetCurClipNum() == 3)
			{
				attackCollider->isActive = false;
				isAttackColliderTrigger = true;
			}
		}
	}
}



void Gnoll_Mirkwood::Move()
{
	if (isDie) return;
	if (isAttack) return;
	if (isOnDamage) return;
	if (gunner->GetIsDie()) return;

	if (isDetectedPlayerInAttackRange)
	{
		SetAction(Walk);

		if (gunner->pos.y > pos.y)
		{
			pos.y += speed * DELTA;
		}

		else
		{
			pos.y -= speed * DELTA;
		}

		if (isPossibleHitState)
		{
			isAttack = true;
		}
	}

	else if (isDetectedPlayer)
	{
		SetAction(Walk);

		if (gunner->pos == pos)
		{
			pos.x -= 0.5f;
		}

		Vector2 dir = (gunner->pos - pos).Normal();
		pos += dir * speed * DELTA;
	}

	else SetAction(Idle);
}



void Gnoll_Mirkwood::OnDamage(float damage)
{
	if (isDie) return;

	UM->Change_MonsterHPbar(hpBar);

	onDamageStateCheckTime = Timer::Get()->GetRunTime() + hitRecovery;

	hpBar->UpdateHPbar(hp, hp - damage);

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

		if (isRight) pos.x -= 200 * DELTA;
		else pos.x += 200 * DELTA;
	}

	else
	{
		isOnDamage = false;
	}
}

void Gnoll_Mirkwood::CheckDead()
{
	if (!isDie) return;

	if (Timer::Get()->GetRunTime() < deadTime)
	{
		SetAction(DIE);
	}

	else
	{
		isActive = false;
		hpBar->SetHPbarDead();
	}
}


void Gnoll_Mirkwood::DetectPlayer()
{
	if (isDie) return;
	if (gunner->GetIsDie()) return;


	playerPos = gunner->pos;

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
		hpBar->SetMonsterDead();
	}
}

void Gnoll_Mirkwood::Reactivation()
{
	hp = 10000.0f;
	hpBar->Reactivation();
	isActive = true;
	collider->isActive = true;
	trigger_CheckPlayerDeath = true;
	isDie = false;
}

void Gnoll_Mirkwood::CheckAttackRange() // SMASHATTACK 체크.
{
	if (isDie) return;
	if (gunner->GetIsDie()) return;

	playerPos = gunner->pos;

	if (
		playerPos.x > pos.x - attackRange.x &&
		playerPos.x < pos.x + attackRange.x &&
		playerPos.y < pos.y + attackRange.y &&
		playerPos.y > pos.y - attackRange.y
		)
		isDetectedPlayerInAttackRange = true;
	else
	{
		isDetectedPlayerInAttackRange = false;
	}


	if (playerPos.x >= pos.x) isRight = true;
	else isRight = false;
}

void Gnoll_Mirkwood::AttackEnd()
{
	isAttack = false;
}

void Gnoll_Mirkwood::CheckIsPossibleHitState() // GetGunnerHitCheckColliderSize()는 13임.. 규격크기.
{
	if (colliderBottom <= gunner->GetGunnerBottom() + gunner->GetGunnerHitCheckColliderSize() &&
		colliderBottom > gunner->GetGunnerBottom() - gunner->GetGunnerHitCheckColliderSize())
	{
		isPossibleHitState = true;
	}
	else
	{
		isPossibleHitState = false;
	}
}

void Gnoll_Mirkwood::CheckPlayerDeath()
{
	if (trigger_CheckPlayerDeath)
	{
		if (gunner->GetIsDie())
		{
			trigger_CheckPlayerDeath = false;
			trigger_MoveAfterPlayerDeath = true;

			dir = { Math::Random(-1.0f, 1.0f), Math::Random(-1.0f, 1.0f) };
			moveCheckTimeafterPlayerDeath = Timer::Get()->GetRunTime() + 2.0f;
			isAttack = false;
		}
	}
}

void Gnoll_Mirkwood::MoveAfterPlayerDeath()
{
	if (trigger_MoveAfterPlayerDeath)
	{
		if (Timer::Get()->GetRunTime() <= moveCheckTimeafterPlayerDeath)
		{
			SetAction(Walk);
			pos += dir * speed * DELTA;
		}
		else if (Timer::Get()->GetRunTime() > moveCheckTimeafterPlayerDeath)
		{
			trigger_MoveAfterPlayerDeath = false;
			SetAction(Idle);
		}
	}

}


void Gnoll_Mirkwood::InitMotion()
{
	string path = "Textures/Monster1/";

	LoadAction(path, "IDLE.xml", Action::END);
	LoadAction(path, "WALK.xml", Action::PINGPONG);
	LoadAction(path, "StandOnDamage.xml", Action::END, 0.1f);
	LoadAction(path, "DIE.xml", Action::END, 0.1f);
	LoadAction(path, "SMASHATTACK.xml", Action::END, 0.2f);

	actions[SMASHATTACK]->SetEndEvent(bind(&Gnoll_Mirkwood::AttackEnd, this));
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
