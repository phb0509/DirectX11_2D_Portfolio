#pragma once

class Quad;

class DNode
{
private:
	friend class Dijkstra;

	struct Edge
	{
		DNode* node;
		float cost;
	};

	Vector2 pos;
	bool isClosed;
	int via;
	float cost;

	vector<Edge*> edges;

	Quad* quad;
	ColorBuffer* colorBuffer;
public:
	DNode(Vector2 pos);
	~DNode();

	void Update();
	void Render();

	void AddEdge(DNode* node);
};