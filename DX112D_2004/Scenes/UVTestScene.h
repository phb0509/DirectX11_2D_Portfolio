#pragma once

class UVTestScene : public Scene
{
private:
	Gunner* gunner;
	//Quad* bg;
	//Transform* bgTransform;
public:
	UVTestScene();
	~UVTestScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};