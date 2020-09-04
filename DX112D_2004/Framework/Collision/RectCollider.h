#pragma once

class RectCollider : public Collider
{
public:
	struct ObbDesc
	{
		Vector2 position;
		Vector2 direction[2];
		float length[2];
	};

private:
	Vector2 size;
	
	bool isObb;
public:
	RectCollider(Vector2 size);
	RectCollider(Vector2 size, Transform* target);
	~RectCollider();
	
	virtual void Update() override;

	virtual void CreateData() override;

	virtual bool IsCollision(Vector2 position) override;	
		
	virtual bool IsCollision(IN RectCollider* rect, OUT Vector2* overlap = nullptr) override;
	virtual bool IsCollision(class CircleCollider* circle) override;

	bool AABB(IN RectCollider* rect, OUT Vector2* overlap);
	bool OBB(RectCollider* rect);

	float SeparateAxis(Vector2 separate, Vector2 e1, Vector2 e2);

	ObbDesc GetObb();	

	float Left() { return pos.x - size.x * 0.5f + offset.x; }
	float Right() { return pos.x + size.x * 0.5f + offset.x; }
	float Top() { return pos.y + size.y * 0.5f + offset.y; }
	float Bottom() { return pos.y - size.y * 0.5f + offset.y; }
};