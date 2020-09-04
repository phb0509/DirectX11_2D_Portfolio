#include "Framework.h"
#include "GeometryScene.h"

GeometryScene::GeometryScene()
{
	for (float y = 0; y <= 30; y++)
	{
		for (float x = 0; x <= 30; x++)
		{
			VertexSizeFrame vertex;
			vertex.pos = { x * 20, y * 20, 0};
			vertex.size = { 15, 15 };
			vertex.frame.x = Math::Random(0, 27);
			vertex.frame.y = Math::Random(0, 18);
			vertices.emplace_back(vertex);
		}
	}

	vertexBuffer = new VertexBuffer(vertices.data(),
		sizeof(VertexSizeFrame), vertices.size());

	vertexShader = SHADER->AddVS(L"VertexSizeFrameShader");
	geometryShader = SHADER->AddGS(L"GeometryFrameShader");
	pixelShader = SHADER->AddPS(L"SpriteFrameShader");

	texture = Texture::Add(L"Textures/Tile/tilemap.png");
	frameBuffer = new FrameBuffer();
	frameBuffer->data.maxFrame = { 27, 18 };
}

GeometryScene::~GeometryScene()
{
	delete vertexBuffer;
	delete frameBuffer;
}

void GeometryScene::Update()
{
	
}

void GeometryScene::Render()
{
	vertexBuffer->Set();
	IASetPT(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);

	frameBuffer->SetPSBuffer(0);
	texture->Set(0);

	vertexShader->Set();
	geometryShader->Set();
	pixelShader->Set();

	DC->Draw(vertices.size(), 0);

	DC->GSSetShader(nullptr, nullptr, 0);
}

void GeometryScene::PostRender()
{
}
