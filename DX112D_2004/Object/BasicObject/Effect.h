#pragma once

class Effect : public Transform
{
private:
	Sprite* sprite;
	Action* action;

	bool isAdditive;

	ColorBuffer* colorBuffer;

public:
	Effect(wstring textureFile, UINT maxFrameX, UINT maxFrameY, float speed = 0.1f);
	~Effect();

	void Update();
	void Render();

	void Play(Vector2 pos);
	void End();

	void SetAdditive(bool value) { isAdditive = value; }
	void SetColor(Float4 color) { colorBuffer->data.color = color; }
};