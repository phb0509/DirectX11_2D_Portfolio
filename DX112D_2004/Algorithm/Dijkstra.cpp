#include "Framework.h"

Dijkstra::Dijkstra()
{
    CreateNode();
}

Dijkstra::~Dijkstra()
{
    for (DNode* node : nodes)
        delete node;
}

void Dijkstra::Update()
{
    for (DNode* node : nodes)
        node->Update();
}

void Dijkstra::Render()
{
    for (DNode* node : nodes)
        node->Render();
}

void Dijkstra::ResetNodes()
{
    for (DNode* node : nodes)
    {
        node->isClosed = false;
        node->cost = FLT_MAX;
        node->via = -1;
        node->colorBuffer->data.color = { 1, 1, 1, 1 };
    }
}

int Dijkstra::FindCloseNode(Vector2 pos)
{
    float minDist = FLT_MAX;
    int index = -1;

    for (size_t i = 0; i < nodes.size(); i++)
    {
        float dist = Vector2::Distance(pos, nodes[i]->pos);
        if (minDist > dist)
        {
            minDist = dist;
            index = i;
        }
    }

    return index;
}

void Dijkstra::SetEdgeInfo(int curIndex)
{
    if (curIndex == -1)
        return;

    nodes[curIndex]->isClosed = true;

    float cost = nodes[curIndex]->cost;

    for (DNode::Edge* edge : nodes[curIndex]->edges)
    {
        if (edge->node->cost > cost + edge->cost)
        {
            edge->node->cost = cost + edge->cost;
            edge->node->via = curIndex;
        }
    }
}

int Dijkstra::FindMinCostNode()
{
    float minCost = FLT_MAX;
    int index = -1;

    for (size_t i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->isClosed)
            continue;

        if (nodes[i]->cost < minCost)
        {
            minCost = nodes[i]->cost;
            index = i;
        }
    }

    return index;
}

vector<Vector2> Dijkstra::GetOrder(int start, int end)
{
    int curIndex = start;
    nodes[curIndex]->cost = 0;
    nodes[curIndex]->via = start;

    for (DNode* node : nodes)
    {
        SetEdgeInfo(curIndex);
        curIndex = FindMinCostNode();
    }

    curIndex = end;

    vector<Vector2> order;
    while (curIndex != start)
    {
        nodes[curIndex]->colorBuffer->data.color = { 1, 0, 0, 1 };
        order.emplace_back(nodes[curIndex]->pos);
        curIndex = nodes[curIndex]->via;
    }

    return order;
}

void Dijkstra::CreateNode()
{
    nodes.emplace_back(new DNode({ 100, 100 }));
    nodes.emplace_back(new DNode({ 300, 200 }));
    nodes.emplace_back(new DNode({ 500, 500 }));
    nodes.emplace_back(new DNode({ 100, 600 }));
    nodes.emplace_back(new DNode({ 400, 100 }));
    nodes.emplace_back(new DNode({ 200, 100 }));
    nodes.emplace_back(new DNode({ 400, 600 }));
    nodes.emplace_back(new DNode({ 700, 400 }));
    nodes.emplace_back(new DNode({ 1000, 700 }));

    nodes[0]->AddEdge(nodes[1]);
    nodes[0]->AddEdge(nodes[3]);
    nodes[0]->AddEdge(nodes[5]);

    nodes[1]->AddEdge(nodes[0]);
    nodes[1]->AddEdge(nodes[2]);
    nodes[1]->AddEdge(nodes[3]);
    nodes[1]->AddEdge(nodes[4]);
    nodes[1]->AddEdge(nodes[5]);
    nodes[1]->AddEdge(nodes[6]);

    nodes[2]->AddEdge(nodes[1]);
    nodes[2]->AddEdge(nodes[4]);
    nodes[2]->AddEdge(nodes[6]);
    nodes[2]->AddEdge(nodes[7]);
    nodes[2]->AddEdge(nodes[8]);

    nodes[3]->AddEdge(nodes[0]);    
    nodes[3]->AddEdge(nodes[1]);
    nodes[3]->AddEdge(nodes[6]);

    nodes[4]->AddEdge(nodes[1]);
    nodes[4]->AddEdge(nodes[2]);
    nodes[4]->AddEdge(nodes[5]);
    nodes[4]->AddEdge(nodes[7]);    
    
    nodes[5]->AddEdge(nodes[0]);
    nodes[5]->AddEdge(nodes[1]);
    nodes[5]->AddEdge(nodes[4]);

    nodes[6]->AddEdge(nodes[1]);
    nodes[6]->AddEdge(nodes[2]);
    nodes[6]->AddEdge(nodes[3]);
    nodes[6]->AddEdge(nodes[8]);

    nodes[7]->AddEdge(nodes[2]);
    nodes[7]->AddEdge(nodes[4]);
    nodes[7]->AddEdge(nodes[8]);

    nodes[8]->AddEdge(nodes[2]);
    nodes[8]->AddEdge(nodes[6]);
    nodes[8]->AddEdge(nodes[7]);
}
