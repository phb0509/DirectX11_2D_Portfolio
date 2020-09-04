#pragma once

class EffectScene : public Scene
{
private:
	
public:
	EffectScene();
	~EffectScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};