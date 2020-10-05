#pragma once

class Character_Interface
{
public:
	Character_Interface();
	~Character_Interface();

	void Update();
	void Render();

private:
	Quad* character_Interface;
	Quad* hpBar;
	Quad* mpBar;

	float testValue;
	FloatBuffer* floatBuffer;
	MatrixBuffer* viewBuffer;
};