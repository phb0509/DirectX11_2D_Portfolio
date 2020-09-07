#pragma once

class Gunner : public Transform
{

public:
	enum ActionType
	{
		IDLE = 0,
		WALK,
		RUN,
		FIRSTSHOT,
		COMBOSHOT,
		LASTSHOT,
		FINISHMOTION,
	};


	Gunner();
	~Gunner();

	void Update();
	void Render();

	void Move();
	void Attack();
	void Jump();

	void LoadAction(string path, string file, Action::Type type, float speed = 0.1f);

	void SetAction(ActionType type);

	void Fire();
	void FirstFire();
	void SecondFire();
	void ComboShotEnd();

	void SetIdle();
	bool CheckAttackInterval();
	void Shot();

	void Test();
private:


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

	bool isFirstAttack;
	int comboAttackCount;

	double maxAttackTime;
	int count = 0;

	bool isComboShotEndTrigger;

	Vector2 attackOffset;

	Effect* effect;

	IntBuffer* intBuffer;
	ColorBuffer* colorBuffer;

};