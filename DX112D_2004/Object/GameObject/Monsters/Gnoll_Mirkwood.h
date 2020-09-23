#pragma once

class Gunner;

class Gnoll_Mirkwood : public Monster
{
public:
	enum ActionType
	{
		Idle,
		Walk,
		StandOnDamage,
		DIE,
		SMASHATTACK,
	};

	Gnoll_Mirkwood(Vector2 pos);
	~Gnoll_Mirkwood();

	virtual void Update() override;
	virtual void Render() override;

	virtual void InitMotion() override;
	virtual void Move() override;
	virtual void Attack() override;
	virtual void OnDamage(float damage) override;
	virtual void CheckOnDamage() override;
	virtual void CheckDead() override;
	virtual void DetectPlayer() override;
	virtual void Die() override;
	virtual void Reactivation() override;
	virtual void CheckAttackRange() override;
	virtual void AttackEnd() override;

	void CheckPlayerDeath();
	void MoveAfterPlayerDeath();

	////Get
	//Collider* GetCollider() { return collider; }
	

	void LoadAction(string path, string file, Action::Type type, float speed = 0.1f);
	void SetAction(ActionType type);
	void SetIdle();
	void Test();

private:
	Gunner* gunner;

	Sprite* sprite;
	vector<Action*> actions;
	ActionType curAction;
	HPbar_Monster* hpBar;

	Vector2 dir;
	float moveCheckTimeafterPlayerDeath;
	bool trigger_CheckPlayerDeath;
	bool trigger_MoveAfterPlayerDeath;

};

