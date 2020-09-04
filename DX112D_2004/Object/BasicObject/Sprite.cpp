#include "Framework.h"

Sprite::Sprite()
{
	material = new Material(L"ActionShader");
	mesh = new QuadMesh();

	actionBuffer = new ActionBuffer();		
}

Sprite::Sprite(wstring pixelShaderFile)
{
	material = new Material(pixelShaderFile);
	mesh = new QuadMesh();

	actionBuffer = new ActionBuffer();
}

Sprite::~Sprite()
{
	delete actionBuffer;
}

void Sprite::Update()
{
}

void Sprite::Render()
{	
	actionBuffer->SetPSBuffer(0);

	material->Set();
	mesh->Render();
}

void Sprite::PostRender()
{	
	ImGui::SliderFloat2("StartPos", (float*)&actionBuffer->data.startPos, 0, 1000);
	ImGui::SliderFloat2("Size", (float*)&actionBuffer->data.size, 0, 1000);
}

void Sprite::SetAction(Action::Clip clip)
{
	actionBuffer->data.startPos = clip.startPos;
	actionBuffer->data.size = clip.size;
	actionBuffer->data.maxSize = clip.texture->GetSize();
	material->SetTexture(clip.texture);
}
