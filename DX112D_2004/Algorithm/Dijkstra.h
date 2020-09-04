#pragma once

class Dijkstra
{
private:
	vector<DNode*> nodes;

public:
	Dijkstra();
	~Dijkstra();

	void Update();
	void Render();

	void ResetNodes();
	int FindCloseNode(Vector2 pos);
	void SetEdgeInfo(int curIndex);
	int FindMinCostNode();

	vector<Vector2> GetOrder(int start, int end);

private:
	void CreateNode();
};