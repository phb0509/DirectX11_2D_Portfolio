#pragma once

class AStarScene : public Scene
{
private:
	Map* map;
	Tank* tank;
	AStar* aStar;
public:
	AStarScene();
	~AStarScene();
		
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

};