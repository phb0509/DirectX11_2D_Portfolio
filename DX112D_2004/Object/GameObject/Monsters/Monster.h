#pragma once

class Monster : public Transform
{

public:
	Monster();
	virtual ~Monster();

	
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void InitMotion() = 0;
	virtual void Move() = 0;
	virtual void Attack() = 0;
	virtual void OnDamage(float damage) = 0;
	virtual void CheckOnDamage() = 0;
	virtual void CheckDead() = 0;
	virtual void DetectPlayer() = 0;
	virtual void Die() = 0;
	virtual void Reactivation() = 0;
	virtual void CheckAttackRange() = 0;
	virtual void AttackEnd() = 0;
	


	//Get
	Collider* GetCollider() { return collider; }
	bool GetColliderIsActive() { return collider->isActive; }
	bool GetIsDie() { return isDie; }

	//Set
	void SetIsDie(bool _isDie) { isDie = _isDie; }


protected:
	int hp;
	float speed;
	float gravity;
	float onDamageStateCheckTime;
	float maxSlipMove;
	float hitRecovery;
	float deadTime;
	float damage;

	bool isRight;
	bool isDie;
	bool isAttack;
	bool isDetectedPlayer;
	bool isDetectedPlayerInAttackRange;
	bool isOnDamage;
	bool isAttackColliderTrigger;

	Collider* collider;
	Collider* attackCollider;
	Vector2 detectRange;
	Vector2 attackRange;
	Vector2 playerPos;


};