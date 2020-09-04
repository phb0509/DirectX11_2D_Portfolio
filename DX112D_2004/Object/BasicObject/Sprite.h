#pragma once

class Sprite
{
private:	
	Material* material;
	QuadMesh* mesh;

	ActionBuffer* actionBuffer;

public:
	Sprite();	
	Sprite(wstring pixelShaderFile);
	~Sprite();	

	void Update();
	void Render();

	void PostRender();

	void SetAction(Action::Clip clip);

	Vector2 GetSize() { return material->GetTexture()->GetSize(); }
};