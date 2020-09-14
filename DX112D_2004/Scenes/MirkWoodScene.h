#pragma once

class MirkWoodScene : public Scene
{
public:
	MirkWoodScene();
	~MirkWoodScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Start() override;
	virtual void End() override;


private:
	Gunner* gunner;
	Monster* gnoll;


	Quad* bg;
	Quad* tile;
	
	vector<Monster*> monsters;
	Transform* bgTransform;

};