#pragma once

class Quad;

class Node
{
private:
	friend class AStar;
	friend class Map;
	friend class Heap;

	enum State
	{
		NONE,
		OPEN,
		CLOSED,
		USING,
		OBSTACLE
	};

	struct Edge
	{
		int index;
		float cost;
	};

	Vector2 pos;
	
	int index;
	int via;

	float f;//���� ��� f(n) = g(n) + h(n)
	float g;//����� ���� n������ ��� g(n)
	float h;//n���� ������ ������ ���� ��� h(n)

	State state;

	vector<Edge*> edges;

	Quad* quad;
	ColorBuffer* colorBuffer;
public:
	Node(Vector2 pos, int index);
	~Node();

	void Update();
	void Render();

	void AddEdge(Node* node);
};