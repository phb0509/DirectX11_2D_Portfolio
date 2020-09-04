#include "Framework.h"

AStar::AStar(Map* map)
{
    nodes = map->GetNodes();

    UINT width = map->GetWidth();

    for (size_t i = 0; i < nodes.size(); i++)
    {
        if (i % width != width - 1)
        {
            nodes[i]->AddEdge(nodes[i + 1]);
            nodes[i + 1]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width)
        {
            nodes[i]->AddEdge(nodes[i + width]);
            nodes[i + width]->AddEdge(nodes[i]);
        }

        if (i % width != width - 1 && i < nodes.size() - width)
        {
            nodes[i]->AddEdge(nodes[i + width + 1]);
            nodes[i + width + 1]->AddEdge(nodes[i]);
        }

        if (i % width != 0 && i < nodes.size() - width)
        {
            nodes[i]->AddEdge(nodes[i + width - 1]);
            nodes[i + width - 1]->AddEdge(nodes[i]);
        }
    }

    heap = new Heap();
}

AStar::~AStar()
{
    for (Node* node : nodes)
        delete node;

    delete heap;
}

void AStar::Update()
{
    for (Node* node : nodes)
        node->Update();
}

void AStar::Render()
{
    for (Node* node : nodes)
        node->Render();
}

void AStar::Reset()
{
    for (Node* node : nodes)
    {
        if (node->state != Node::OBSTACLE)
            node->state = Node::NONE;
    }
}

int AStar::FindCloseNode(Vector2 pos)
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

vector<Vector2> AStar::FindPath(int start, int end)
{
    vector<Vector2> order;
    if (nodes[end]->state == Node::OBSTACLE)
        return order;
    //1. ���� ��带 �ʱ�ȭ �ϰ� ���³��� �����
    float G = 0.0f;
    float H = GetDistance(start, end);
        
    nodes[start]->g = G;
    nodes[start]->h = H;
    nodes[start]->f = G + H;
    nodes[start]->via = start;
    nodes[start]->state = Node::OPEN;
    //openNodes.emplace_back(start);
    heap->Insert(nodes[start]);

    while (nodes[end]->state != Node::CLOSED)
    {
        int curIndex = GetMinNode();//2. ���� ��� �߿��� F���� ���� ���� ��带 ã�´�.
        Extend(curIndex, end);//3. ���õ� ����� ���� ������ ������ ����, ���� ���� �����.
        nodes[curIndex]->state = Node::CLOSED;//4. Ȯ���� ���� ���� Ŭ���� �Ѵ�.
    }

    //5. ������ ��忡�� ���� ���̾ �̿��� ��Ʈ��ŷ �Ѵ�.
    int curIndex = end;
    while (curIndex != start)
    {
        nodes[curIndex]->state = Node::USING;
        order.emplace_back(nodes[curIndex]->pos);
        curIndex = nodes[curIndex]->via;
    }

    heap->Clear();

    return order;
}

float AStar::GetManhattanDistance(int curIndex, int end)
{
    Vector2 curPos = nodes[curIndex]->pos;
    Vector2 endPos = nodes[end]->pos;

    Vector2 result = endPos - curPos;
    
    return abs(result.x) + abs(result.y);
}

float AStar::GetDistance(int curIndex, int end)
{
    Vector2 curPos = nodes[curIndex]->pos;
    Vector2 endPos = nodes[end]->pos;

    Vector2 result = endPos - curPos;

    return result.Length();

    float x = abs(result.x);
    float y = abs(result.y);

    float min = min(x, y);
    float max = max(x, y);

    return sqrt(min*min*2) + (max - min);
}

int AStar::GetMinNode()
{
    return heap->DeleteRoot()->index;

    /*
    int openIndex = 0;
    int nodeIndex = openNodes[openIndex];
    float minF = nodes[nodeIndex]->f;

    for (size_t i = 1; i < openNodes.size(); i++)
    {
        nodeIndex = openNodes[i];
        if (nodes[nodeIndex]->f < minF)
        {
            minF = nodes[nodeIndex]->f;
            openIndex = i;
        }
    }

    nodeIndex = openNodes[openIndex];

    openNodes.erase(openNodes.begin() + openIndex);

    return nodeIndex;
    */
}

void AStar::Extend(int center, int end)
{
    vector<Node::Edge*> edges = nodes[center]->edges;

    for (Node::Edge* edge : edges)
    {
        int index = edge->index;

        if (nodes[index]->state == Node::CLOSED)
            continue;
        if (nodes[index]->state == Node::OBSTACLE)
            continue;

        float G = nodes[center]->g + edge->cost;
        float H = GetDistance(index, end);
        float F = G + H;

        if (nodes[index]->state == Node::OPEN)
        {
            if (F < nodes[index]->f)
            {
                nodes[index]->g = G;
                nodes[index]->f = F;
                nodes[index]->via = center;
            }
        }
        else if (nodes[index]->state == Node::NONE)
        {
            nodes[index]->g = G;
            nodes[index]->h = H;
            nodes[index]->f = F;
            nodes[index]->via = center;
            nodes[index]->state = Node::OPEN;
            //openNodes.emplace_back(index);
            heap->Insert(nodes[index]);
        }
    }
}
