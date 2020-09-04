#include "Framework.h"

Tile::Tile() : type(BG), collider(nullptr)
{
	material = new Material(L"SpriteShader");
	mesh = new QuadMesh();
	frameBuffer = new FrameBuffer();	
}

Tile::~Tile()
{
	delete material;
	delete mesh;
	delete frameBuffer;
	delete collider;
}

void Tile::Update()
{
	collider->Update();
	UpdateWorld();
}

void Tile::Render()
{
	frameBuffer->SetPSBuffer(0);
	SetWorldBuffer();
	material->Set();
	mesh->Render();

	//collider->Render();
}

void Tile::CreateCollider(Vector2 size)
{
	collider = new RectCollider(size, this);
}
