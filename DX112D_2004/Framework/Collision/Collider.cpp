#include "Framework.h"

Collider::Collider()
    : target(nullptr), offset(0, 0), HitEvent(nullptr)
{    
}

Collider::Collider(Transform* target)
    : target(target), offset(0, 0), HitEvent(nullptr)
{   
}

Collider::~Collider()
{
    delete vertexBuffer;
}

void Collider::Update()
{
    if (!isActive) return;

    if (target != nullptr)
    {
        Matrix R = XMMatrixRotationZ(target->rot.z);
        Vector2 tempOffset = Vector2::TransformCoord(offset, R);
        pos = target->pos + tempOffset;
        //pos = target->WorldPos() + tempOffset;
    }

    UpdateWorld();
}

void Collider::Render()
{
    if (!isActive) return;

    SetWorldBuffer();
    vertexBuffer->Set();
    IASetPT(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);

    colorBuffer->SetPSBuffer(0);

    vertexShader->Set();
    pixelShader->Set();

    DC->Draw(vertices.size(), 0);
}

void Collider::CreateData()
{
    vertexShader = SHADER->AddVS(L"VertexShader");
    pixelShader = SHADER->AddPS(L"ColorShader");

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());

    colorBuffer = new ColorBuffer();
    colorBuffer->data.color = { 0, 1, 0, 1 };      
}

bool Collider::IsCollision(IN Collider* collider, OUT Vector2* overlap)
{
    if (!isActive) return false;

    switch (collider->type)
    {
    case Collider::Type::RECT:
    {
        RectCollider* rect = dynamic_cast<RectCollider*>(collider);
        return IsCollision(rect, overlap);
    }
        break;
    case Collider::Type::CIRCLE:
    {
        CircleCollider* circle = dynamic_cast<CircleCollider*>(collider);
        return IsCollision(circle);
    }
        break;
    case Collider::Type::POLYGON:
    {
        PolygonCollider* polygon = dynamic_cast<PolygonCollider*>(collider);
        return IsCollision(polygon);
    }
    break;
    default:
        break;
    }
}


