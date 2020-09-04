#pragma once

class Map;

class AStar
{
private:
	vector<Node*> nodes;
	//vector<int> openNodes;
	Heap* heap;

public:
	AStar(Map* map);
	~AStar();

	void Update();
	void Render();

	void Reset();
	int FindCloseNode(Vector2 pos);
	vector<Vector2> FindPath(int start, int end);
	float GetManhattanDistance(int curIndex, int end);
	float GetDistance(int curIndex, int end);
	int GetMinNode();
	void Extend(int center, int end);
};
