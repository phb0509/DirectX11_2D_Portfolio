#pragma once

class TriangleCollisionScene : public Scene
{
private:
	Collider* collider;
	Collider* collider2;

public:
	TriangleCollisionScene();
	~TriangleCollisionScene();
		
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};