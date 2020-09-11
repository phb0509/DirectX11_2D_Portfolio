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
	virtual void DetectPlayer() = 0;
	virtual void Die() = 0;


	//Get
	Collider* GetCollider() { return collider; }

protected:

	int hp;
	float speed;
	float gravity;
	bool isRight;
	bool isDie;
	bool isAttack;
	bool isDetectedPlayer;
	Collider* collider;
	Vector2 detectRange;
	Vector2 playerPos;
	

};