#pragma once

class Monster : public Transform
{

public:
	Monster();
	virtual ~Monster();

	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void Move() = 0;
	virtual void Attack() = 0;
	virtual void OnDamage(float damage) = 0;
	virtual void CheckOnDamage() = 0;
	virtual void CheckDead() = 0;
	virtual void DetectPlayer() = 0;
	virtual void Die() = 0;
	virtual void Reactivation() = 0;


	//Get
	Collider* GetCollider() { return collider; }
	bool GetColliderIsActive() { return collider->isActive; }

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

	bool isRight;
	bool isDie;
	bool isAttack;
	bool isDetectedPlayer;
	bool isOnDamage;

	Collider* collider;
	Vector2 detectRange;
	Vector2 playerPos;


};