#pragma once

class RectCollider;

class CircleCollider : public Collider
{
private:
	float radius;
	static const UINT sliceCount = 36;

public:
	CircleCollider(float radius);
	CircleCollider(float radius, Transform* target);

	virtual void Update() override;	
	
	virtual void CreateData() override;

	virtual bool IsCollision(Vector2 position) override;
	virtual bool IsCollision(IN RectCollider* rect, OUT Vector2* overlap = nullptr) override;
	virtual bool IsCollision(CircleCollider* circle) override;

	bool IsCollision(Line line);
};