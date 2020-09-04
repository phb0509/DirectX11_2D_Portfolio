#pragma once

class Plane
{
private:	
	Quad* quad;
	Collider* collider;

	float speed;
	
public:
	Plane();
	~Plane();

	void Update();
	void Render();

	Collider* GetCollider() { return collider; }
};