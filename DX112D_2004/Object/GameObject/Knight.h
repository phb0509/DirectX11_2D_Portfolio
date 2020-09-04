#pragma once

class Knight : public Transform
{	
private:
	enum ActionType
	{
		IDLE,
		WALK,
		ATTACK,
		JUMP
	};

	Sprite* sprite;
	vector<Action*> actions;
	Collider* attackCollider;

	ActionType curAction;

	float speed;
	float jumpPower;
	float gravity;

	bool isRight;
	bool isAttack;
	bool isJump;

	Vector2 attackOffset;

	Effect* effect;

	IntBuffer* intBuffer;
	ColorBuffer* colorBuffer;
public:
	Knight();
	~Knight();

	void Update();
	void Render();

	void Move();
	void Attack();
	void Jump();

	void LoadAction(string path, string file, Action::Type type, float speed = 0.1f);

	void SetAction(ActionType type);
	void AttackEnd();
};