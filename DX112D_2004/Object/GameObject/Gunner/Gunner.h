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
	void Run();
	void Attack();
	void Jump();
	void Fire();
	void FirstFire();
	void SecondFire();
	void ComboShotEnd();
	void InitMotion();
	void OnDamage(float damage);

	bool CheckAttackInterval();
	void CheckIdle_AfterRun();
	void Shot();


	void SetPosition(Vector2 _pos) { pos = _pos; };
	void SetIdle();
	
	Collider* GetGunnerCollider() { return collider; }

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



	float hp;
	float mp;
	float walkSpeed; // WALK �ִϸ��̼� ���� �� �̵��ӵ�.
	float runSpeed; // RUN �ִϸ��̼� ���� �� �̵��ӵ�.
	float jumpPower;
	float gravity;

	bool isRight; 
	bool isRightRun; // �����ʴ뽬 �����ΰ�?
	bool isLeftRun; // ���ʴ뽬 �����ΰ�?
	bool trigger_Move;

	float rightRunCheckTime; // �����ʴ뽬���������� üũ�ϱ����� �ð�üũ. 
	float leftRunCheckTime;  // ���ʴ뽬���������� üũ�ϱ����� �ð�üũ.

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