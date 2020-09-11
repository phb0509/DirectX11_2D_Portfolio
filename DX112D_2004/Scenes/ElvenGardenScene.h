#pragma once

class ElvenGardenScene : public Scene
{
public:
	ElvenGardenScene();
	~ElvenGardenScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void SetGunner();
	void SetMonsters();


private:
	Gunner* gunner;

	Quad* bg;
	Quad* tile;





	//Transform* bgTransform;

};