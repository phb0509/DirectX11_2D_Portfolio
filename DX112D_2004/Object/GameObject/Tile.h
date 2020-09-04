#pragma once

class Tile : public Transform
{
public:
	enum Type
	{
		BG,
		OBJ
	};
private:		
	Material* material;
	QuadMesh* mesh;

	Collider* collider;

	Type type;
	
	FrameBuffer* frameBuffer;

public:
	Tile();
	~Tile();

	void Update();
	void Render();	

	void CreateCollider(Vector2 size);

	void SetTexture(Texture* texture) { material->SetTexture(texture); }
	FrameBuffer* GetFrame() { return frameBuffer; }	
	Collider* GetCollider() { return collider; }
};