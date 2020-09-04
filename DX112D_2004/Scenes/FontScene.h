#pragma once

class FontScene : public Scene
{
public:
	FontScene();
	~FontScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};