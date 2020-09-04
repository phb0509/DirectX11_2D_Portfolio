#pragma once

class PolygonCollider : public Collider
{
private:
	vector<Vector2> edges;

public:
	PolygonCollider(vector<Vector2> edges);
	~PolygonCollider();
	
	virtual void Update() override;

	virtual void CreateData() override;

	virtual bool IsCollision(Vector2 position) override;
	virtual bool IsCollision(IN RectCollider* rect, OUT Vector2* overlap = nullptr) override;
	virtual bool IsCollision(CircleCollider* circle) override;
	virtual bool IsCollision(PolygonCollider* triangle);	

	vector<Line> GetLines();
};