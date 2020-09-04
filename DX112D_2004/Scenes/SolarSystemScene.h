#pragma once

class SolarSystemScene : public Scene
{
private:
	Quad* sun;
	Quad* earth;
	Quad* moon;
public:
	SolarSystemScene();
	~SolarSystemScene();
	
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};