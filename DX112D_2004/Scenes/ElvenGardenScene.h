#pragma once

class ElvenGardenScene : public Scene
{
public:
	ElvenGardenScene();
	~ElvenGardenScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Start() override;
	virtual void End() override;

	void SetGunner();
	void SetMonsters();


private:
	Gunner* gunner;

	Quad* bg;
	Quad* tile;
	Quad* sign;
	Brazier* brazier;





	//Transform* bgTransform;

};