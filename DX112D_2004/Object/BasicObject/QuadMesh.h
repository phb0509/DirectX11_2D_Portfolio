#pragma once

class QuadMesh
{
protected:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	vector<VertexUV> vertices;
	vector<UINT> indices;
public:
	QuadMesh(Vector2 size = Vector2(1, 1));		
	virtual ~QuadMesh();
	
	virtual void Render();
	virtual void UpdateSize(Vector2 size);
private:
	void CreateData(Vector2 size);
};