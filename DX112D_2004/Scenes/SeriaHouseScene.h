#pragma once

class SeriaHouseScene : public Scene
{
public:
	SeriaHouseScene();
	~SeriaHouseScene();


	virtual void Update();
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

	virtual void Start();
	virtual void End();

private:

	Gunner* gunner;
	Quad* backGround;
	Collider* gateCollider;


	Vector2 bgLeftBottom;
	Vector2 bgRightTop;

	

};


