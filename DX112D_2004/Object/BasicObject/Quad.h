#pragma once

class Quad : public Transform
{
protected:
	Material* material;
	QuadMesh* mesh;
public:
	Quad(wstring pixelFile);
	Quad(wstring textureFile, wstring pixelFile);
	virtual ~Quad();

	virtual void Update();
	virtual void Render();

	Vector2 GetSize() { return material->GetTexture()->GetSize(); }
	void SetTexture(Texture* texture) { material->SetTexture(texture); }
};