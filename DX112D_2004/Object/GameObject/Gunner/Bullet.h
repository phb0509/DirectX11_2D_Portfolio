#pragma once

class Bullet : public Transform
{

public:
	enum ActionType
	{
		IDLE,
	};



	Bullet();
	~Bullet();


	void Update(vector<Monster*> monsters);
	void Render();

	void Fire(Vector2 gunner_position, bool gunner_isRight, bool isUpShot);
	void CheckDisabledTime();

	void LoadAction(string path, string file, Action::Type type, float speed = 0.1f);
	void SetAction(ActionType type);

	Collider* collider;
private:

	Sprite* sprite;
	vector<Action*> actions;
	ActionType curAction;

	Vector2 rightDownVector;
	Vector2 leftDownVector;
	


	float damage;
	float disabledDistance;
	bool isRight;
	double speed;
	bool isUpShot;

};

