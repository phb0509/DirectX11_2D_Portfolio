#pragma once

class Monster1 : public Transform
{
public:
	enum ActionType
	{
		IDLE = 0,
		WALK,
	};

	Monster1();
	Monster1(Vector2 pos);
	~Monster1();


	void Update();
	void Render();

	void Move();
	void Attack();

	void OnDamage(float damage);
	void Die();


	//Get
	Collider* GetCollider() { return collider; }
	

	void LoadAction(string path, string file, Action::Type type, float speed = 0.1f);
	void SetAction(ActionType type);
	void SetIdle();
	void Test();

private:
	Sprite* sprite;
	vector<Action*> actions;
	ActionType curAction;

	Collider* collider;

	float walkSpeed;


	float jumpPower;
	float gravity;

	bool isRight;
	bool isDie;
	bool isAttack;
	int hp;

};

