#pragma once

class MirkWoodScene : public Scene
{
private:
	Gunner* gunner;
	vector<Bullet*> gunner_bullets;
	Monster1* monster1;


	Quad* bg;
	Quad* tile;
	//Transform* bgTransform;
public:
	MirkWoodScene();
	~MirkWoodScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};