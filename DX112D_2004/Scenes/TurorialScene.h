#pragma once

class TutorialScene : public Scene
{
private:
	Texture* texture;

public:
	TutorialScene();
	~TutorialScene();

	virtual void Update() override;
	virtual void Render() override;
};