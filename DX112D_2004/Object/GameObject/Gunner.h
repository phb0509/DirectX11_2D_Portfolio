#pragma once

class Gunner : public Transform
{
private:
	enum ActionType
	{
		IDLE,
		WALK,
		RUN,
	};

	Sprite* sprite;
	vector<Action*> actions;
	Collider* attackCollider;

	ActionType curAction;

	float walkSpeed;
	float runSpeed;

	float jumpPower;
	float gravity;

	bool isRight;

	bool isRightRun;
	bool isLeftRun;

	double rightRunCheckTime;
	double leftRunCheckTime;
	double verticalCheckTime;

	bool isAttack;
	bool isJump;

	Vector2 attackOffset;

	Effect* effect;

	IntBuffer* intBuffer;
	ColorBuffer* colorBuffer;

	// 

public:
	Gunner();
	~Gunner();

	void Update();
	void Render();

	void Move();
	void Attack();
	void Jump();

	void LoadAction(string path, string file, Action::Type type, float speed = 0.1f);

	void SetAction(ActionType type);
	void AttackEnd();
};