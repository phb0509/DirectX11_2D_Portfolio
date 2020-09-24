#pragma once

class Linus : public Transform
{
public:
	enum ActionType
	{
		IDLE,
	};


	Linus();
	~Linus();

	void Update();
	void Render();

	void LoadAction(string path, string file, Action::Type type, float speed = 0.1f);
	void SetAction(ActionType type);

private:
	Sprite* sprite;
	vector<Action*> actions;
	ActionType curAction;
	Collider* collider;

	bool isRight;

};

