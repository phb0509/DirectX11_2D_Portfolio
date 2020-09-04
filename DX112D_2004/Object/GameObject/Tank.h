#pragma once

class Tank : public Transform
{
private:
	Sprite* sprite;
	Action* action;

	float speed;

	vector<Vector2> order;
public:
	Tank();
	~Tank();

	void Update();
	void Render();

	void Move();

	void SetOrder(vector<Vector2> value) { order = value; }
};