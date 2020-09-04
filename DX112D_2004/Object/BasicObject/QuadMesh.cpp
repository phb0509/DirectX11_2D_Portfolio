#include "Framework.h"

QuadMesh::QuadMesh(Vector2 size)
{
	CreateData(size);

	vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexUV), vertices.size());
	indexBuffer = new IndexBuffer(indices.data(), indices.size());
}

QuadMesh::~QuadMesh()
{
	delete vertexBuffer;
	delete indexBuffer;
}

void QuadMesh::Render()
{
	CULL_MODE_STATE->SetState();

	vertexBuffer->Set();
	indexBuffer->Set();
	IASetPT();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void QuadMesh::UpdateSize(Vector2 size)
{
	float width = size.x * 0.5f;
	float height = size.y * 0.5f;

	vertices[0] = VertexUV(-width, height, 0, 0);
	vertices[1] = VertexUV(width, height, 1, 0);
	vertices[2] = VertexUV(-width, -height, 0, 1);
	vertices[3] = VertexUV(width, -height, 1, 1);

	vertexBuffer->Update(vertices.data(), vertices.size());
}

void QuadMesh::CreateData(Vector2 size)
{	
	float width = size.x * 0.5f;
	float height = size.y * 0.5f;

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
}
