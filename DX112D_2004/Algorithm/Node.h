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

	float f;//최종 비용 f(n) = g(n) + h(n)
	float g;//출발점 부터 n까지의 비용 g(n)
	float h;//n부터 목적지 까지의 추정 비용 h(n)

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