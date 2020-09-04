#include "Framework.h"
#include "InstanceScene.h"

InstanceScene::InstanceScene()
{
	material = new Material(L"TextureShader", L"InstancingShader");
	material->SetTexture(L"Textures/sample.png");

	for (UINT i = 0; i < COUNT; i++)
	{
		Float2 pos;
		pos.x = Math::Random(0, WIN_WIDTH);
		pos.y = Math::Random(0, WIN_HEIGHT);

		worlds[i] = XMMatrixTranslation(pos.x, pos.y, 0.0f);
		worlds[i] = XMMatrixTranspose(worlds[i]);
	}

	instanceBuffer = new VertexBuffer(worlds, sizeof(Matrix), COUNT);

	CreateData();

	worldBuffer = new MatrixBuffer();
}

InstanceScene::~InstanceScene()
{
	delete material;
	delete vertexBuffer;
	delete indexBuffer;
	delete instanceBuffer;
	delete worldBuffer;
}

void InstanceScene::Update()
{
}

void InstanceScene::Render()
{
	vertexBuffer->Set();
	instanceBuffer->Set(1);
	indexBuffer->Set();
	IASetPT();

	material->Set();

	DC->DrawIndexedInstanced(indices.size(), COUNT, 0, 0, 0);
	
	/*
	for (UINT i = 0; i < COUNT; i++)
	{
		worldBuffer->Set(worlds[i]);
		worldBuffer->SetVSBuffer(0);

		DC->DrawIndexed(6, 0, 0);
	}*/
}

void InstanceScene::PostRender()
{
}

void InstanceScene::CreateData()
{
	float width = 30;
	float height = 30;

	vertices.emplace_back(-width, height, 0, 0);
	vertices.emplace_back(width, height, 1, 0);
	vertices.emplace_back(-width, -height, 0, 1);
	vertices.emplace_back(width, -height, 1, 1);

	indices.emplace_back(0);
	indices.emplace_back(1);
	indices.emplace_back(2);

	indices.emplace_back(2);
	indices.emplace_back(1);
	indices.emplace_back(3);

	vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexUV), vertices.size());
	indexBuffer = new IndexBuffer(indices.data(), indices.size());
}
