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
		ONDAMAGE,
		ONDAMAGE1,
		DIE,
	};


	Gunner();
	~Gunner();

	void Update();
	void Render();

	void Move();
	void Run();
	void Attack();
	void Jump();
	void Fire();
	void FirstFire();
	void SecondFire();
	void ComboShotEnd();
	void InitMotion();
	void OnDamage(float damage, bool onDamageDir);
	void Die();
	void CheckDead();
	void Reactivation();

	bool CheckAttackInterval();
	void CheckOnDamage();
	void Shot();


	void SetPosition(Vector2 _pos) { pos = _pos; };
	void SetIdle();
	
	Collider* GetGunnerCollider() { return collider; }
	bool GetIsDie() { return isDie; }

	void Test();
	void LoadAction(string path, string file, Action::Type type, float speed = 0.1f);
	void SetAction(ActionType type);

private:
	
	Sprite* sprite;
	vector<Action*> actions;
	ActionType curAction;
	Collider* collider;

	vector<Bullet*> gunner_bullets;
	Bullet* bullet;

	double currentTime;

	float maxHP;
	float currentHP;
	
	float maxMP;
	float currentMP;

	float walkSpeed; // WALK 애니메이션 실행 시 이동속도.
	float runSpeed; // RUN 애니메이션 실행 시 이동속도.
	float jumpPower;
	float gravity;
	float hitRecovery;

	bool isRight; 
	bool isRightRun; // 오른쪽대쉬 상태인가?
	bool isLeftRun; // 왼쪽대쉬 상태인가?
	bool onDamageDir;
	bool trigger_Move;
	bool isOnDamage;
	bool trigger_AfterOnDamage;

	float rightRunCheckTime; // 오른쪽대쉬상태인지를 체크하기위한 시간체크. 
	float leftRunCheckTime;  // 왼쪽대쉬상태인지를 체크하기위한 시간체크.
	float onDamageStateCheckTime;
	float deadTime;

	bool isDie;
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