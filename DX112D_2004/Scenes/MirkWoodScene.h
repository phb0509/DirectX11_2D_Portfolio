#pragma once

class MirkWoodScene : public Scene
{
public:
	MirkWoodScene();
	~MirkWoodScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void SetGunner();
	void SetMonsters();


private:
	Gunner* gunner;
	vector<Bullet*> gunner_bullets;
	Gnoll_Mirkwood* gnoll;

	Quad* bg;
	Quad* tile;
	
	vector<Monster*> monsters;
	Transform* bgTransform;

};