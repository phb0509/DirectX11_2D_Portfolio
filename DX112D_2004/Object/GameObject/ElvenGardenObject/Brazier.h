#pragma once

class Brazier : Transform
{
public:
	enum ActionType
	{
		IDLE = 0,
	};


	Brazier();
	~Brazier();

	void Update();
	void Render();

	void LoadAction(string path, string file, Action::Type type, float speed = 0.1f);
	void SetAction(ActionType type);

private:
	Sprite* sprite;
	vector<Action*> actions;
	ActionType curAction;
	
	bool isRight;
};
