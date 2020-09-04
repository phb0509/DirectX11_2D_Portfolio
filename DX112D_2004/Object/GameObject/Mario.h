#pragma once

class Mario
{
public:
	enum Type{		
		RUN,
	};

private:
	Sprite* sprite;
	vector<Action*> actions;

	Type curAction;
public:
	Mario();
	~Mario();

	void Update();
	void Render();
};