#include "Framework.h"

PolygonCollider::PolygonCollider(vector<Vector2> edges)
    : edges(edges)
{
    CreateData();
}

PolygonCollider::~PolygonCollider()
{
}

void PolygonCollider::Update()
{
    Collider::Update();
}

void PolygonCollider::CreateData()
{
    type = Type::POLYGON;

    for (Vector2 edge : edges)
        vertices.emplace_back(edge.x, edge.y);
    vertices.emplace_back(edges.front().x, edges.front().y);

    Collider::CreateData();
}

bool PolygonCollider::IsCollision(Vector2 position)
{
    vector<Vector2> P;
    for (Vector2 edge : edges)
        P.emplace_back(Vector2::TransformCoord(edge, matrix));    

    vector<Vector2> line;
    for (UINT i = 0 ; i < P.size() - 1 ; i++)
    {
        line.emplace_back(P[i + 1] - P[i]);
    }
    line.emplace_back(P[0] - P[P.size() - 1]);

    vector<Vector2> D;
    for (UINT i = 0; i < P.size(); i++)
    {
        D.emplace_back(position - P[i]);
    }

    bool result = true;

    for (UINT i = 0; i < P.size(); i++)
    {
        result &= line[i].Cross(D[i]) > 0 ? true : false;
    }    

    return result;
}

bool PolygonCollider::IsCollision(IN RectCollider* rect, OUT Vector2* overlap)
{
    return false;
}

bool PolygonCollider::IsCollision(CircleCollider* circle)
{
    vector<Line> lines = GetLines();

    for (Line line : lines)
    {
        if (circle->IsCollision(line))
            return true;
    }

    return false;
}

bool PolygonCollider::IsCollision(PolygonCollider* triangle)
{
    vector<Line> lines1 = GetLines();
    vector<Line> lines2 = triangle->GetLines();

    for (Line line1 : lines1)
    {
        for (Line line2 : lines2)
        {
            if (line1.IsCollision(line2))
                return true;
        }
    }

    return false;
}

vector<Line> PolygonCollider::GetLines()
{
    vector<Line> lines;
    for (UINT i = 0 ; i < edges.size() - 1 ; i++)
    {
        Vector2 a = Vector2::TransformCoord(edges[i], matrix);
        Vector2 b = Vector2::TransformCoord(edges[i + 1], matrix);
        lines.emplace_back(a, b);
    }
    Vector2 a = Vector2::TransformCoord(edges.back(), matrix);
    Vector2 b = Vector2::TransformCoord(edges.front(), matrix);
    lines.emplace_back(a, b);

    return lines;
}
