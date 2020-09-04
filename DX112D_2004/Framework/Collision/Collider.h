#pragma once

class Collider : public Transform
{
protected:	
	enum class Type
	{
		RECT,
		CIRCLE,
		POLYGON
	}type;

	Transform* target;

	ColorBuffer* colorBuffer;

	VertexShader* vertexShader;
	PixelShader* pixelShader;

	VertexBuffer* vertexBuffer;	

	Vector2 offset;
	vector<Vertex> vertices;

public:
	CallBack HitEvent;

	Collider();
	Collider(Transform* target);
	virtual ~Collider();

	virtual void Update();
	virtual void Render();

	virtual void CreateData();
	
	bool IsCollision(IN Collider* collider, OUT Vector2* overlap = nullptr);

	virtual bool IsCollision(Vector2 position) = 0;
	virtual bool IsCollision(IN class RectCollider* rect, OUT Vector2* overlap = nullptr) = 0;
	virtual bool IsCollision(class CircleCollider* circle) = 0;
	virtual bool IsCollision(class PolygonCollider* polygon) { return false; }

	void SetOffset(Vector2 value) { offset = value; }
	void SetHitEvent(CallBack Event) { HitEvent = Event; }
	void SetColor(Float4 color) { colorBuffer->data.color = color; }
};