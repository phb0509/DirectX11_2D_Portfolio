#pragma once

class MapToolScene : public Scene
{
private:
	Tile::Type selectType;

	Map* map;
	vector<Button*> samples;

	Button* selectButton;
public:
	MapToolScene();
	~MapToolScene();
	
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	void CreateSamples();
	void SelectSample(void* param);	
};