#pragma once

class OffsetTestScene : public Scene
{
private:
	Plane* plane;
	Collider* test;

public:
	OffsetTestScene();
	~OffsetTestScene();
	
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};