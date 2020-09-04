#pragma once

class CollisionScene : public Scene
{
private:
	Collider* rect;
	Collider* rect2;

	Collider* circle;
	Collider* circle2;

	vector<Collider*> colliders;
public:
	CollisionScene();
	~CollisionScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Move();
	void Collision();
};