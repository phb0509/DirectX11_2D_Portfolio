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

	void Update();
	void Update(Monster1* monster1);
	void Render();
	void Fire(Vector2 gunner_position, bool gunner_isRight);
	void LoadAction(string path, string file, Action::Type type, float speed = 0.1f);

	void SetAction(ActionType type);


private:

	Sprite* sprite;
	vector<Action*> actions;
	ActionType curAction;
	Collider* bulletCollider;


	bool isRight;
	double speed;

};

