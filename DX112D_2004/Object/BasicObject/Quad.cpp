#include "Framework.h"

Quad::Quad(wstring pixelFile)
{
	material = new Material(pixelFile);
	mesh = new QuadMesh();
}

Quad::Quad(wstring textureFile, wstring pixelFile)
{
	material = new Material(pixelFile);
	material->SetTexture(textureFile);
	mesh = new QuadMesh(material->GetTexture()->GetSize());
}

Quad::~Quad()
{
	delete material;
	delete mesh;

}

void Quad::Update()
{
	UpdateWorld();
}

void Quad::Render()
{	
	SetWorldBuffer();

	material->Set();
	mesh->Render();
}