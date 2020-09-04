#include "Framework.h"

CircleCollider::CircleCollider(float radius)
    : radius(radius)
{    
    CreateData();
}

CircleCollider::CircleCollider(float radius, Transform* target)
    : Collider(target), radius(radius)
{
    CreateData();
}

void CircleCollider::Update()
{
    Collider::Update();
}

void CircleCollider::CreateData()
{
    type = Type::CIRCLE;

    float theta = 2.0f * PI / sliceCount;    

    for (UINT i = 0; i <= sliceCount; i++)
    {
        float x = cos(theta * i) * radius;
        float y = sin(theta * i) * radius;

        vertices.emplace_back(x, y);
    }

    Collider::CreateData();
}

bool CircleCollider::IsCollision(Vector2 position)
{
    float distance = Vector2::Distance(position, pos);

    return distance < radius;
}

bool CircleCollider::IsCollision(IN RectCollider* rect, OUT Vector2* overlap)
{
    RectCollider::ObbDesc obb = rect->GetObb();

    Vector2 nea1 = obb.direction[0];
    Vector2 ea1 = nea1 * obb.length[0];
    Vector2 nea2 = obb.direction[1];
    Vector2 ea2 = nea2 * obb.length[1];

    float distance1 = abs((pos - obb.position).Dot(nea1));
    float distance2 = abs((pos - obb.position).Dot(nea2));

    if (distance1 > obb.length[0] + radius) { return false; }    
    if (distance2 > obb.length[1] + radius) { return false; }
        
    if (distance1 < obb.length[0]) { return true; }
    if (distance2 < obb.length[1]) { return true; }

    float x = distance1 - obb.length[0];
    float y = distance2 - obb.length[1];

    float edgeToCircle = x * x + y * y;

    return edgeToCircle < radius* radius;
}

bool CircleCollider::IsCollision(CircleCollider* circle)
{
    float distance = Vector2::Distance(circle->pos, pos);

    return distance < radius + circle->radius;
}

bool CircleCollider::IsCollision(Line line)
{
    Vector2 A = (line.End() - line.Start());
    Vector2 B = pos - line.Start();

    float dotAB = A.Normal().Dot(B);

    if (abs(dotAB) > A.Length())
        return false;

    Vector2 contect = A.Normal() * dotAB + line.Start();
    
    return radius > Vector2::Distance(contect, pos);
}
