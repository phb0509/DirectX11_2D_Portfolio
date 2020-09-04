#include "Framework.h"

RectCollider::RectCollider(Vector2 size) : size(size), isObb(true)
{
	CreateData();	
}

RectCollider::RectCollider(Vector2 size, Transform* target)
	: size(size), Collider(target), isObb(true)
{
	CreateData();
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
	if (isObb && target != nullptr)
		rot = target->rot;

	Collider::Update();
}

void RectCollider::CreateData()
{
	type = Type::RECT;

	float width = size.x * 0.5f;
	float height = size.y * 0.5f;

	vertices.emplace_back(-width, -height);
	vertices.emplace_back(width, -height);
	vertices.emplace_back(width, height);
	vertices.emplace_back(-width, height);
	vertices.emplace_back(-width, -height);

	Collider::CreateData();
}
/*
bool RectCollider::IsCollision(Vector2 position)
{
	Vector2 LB(-size.x * 0.5f, -size.y * 0.5f);
	LB = Vector2::TransformCoord(LB, matrix);

	Vector2 fromLB = (position - LB).Normal();
	float crossRight = fromLB.Cross(RightDir());
	float crossUp = fromLB.Cross(UpDir());

	bool isBetweenRightUp = crossRight * crossUp < 0;

	Vector2 RT(size.x * 0.5f, size.y * 0.5f);
	RT = Vector2::TransformCoord(RT, matrix);

	Vector2 fromRT = (position - RT).Normal();
	float crossLeft = fromRT.Cross(LeftDir());
	float crossDown = fromRT.Cross(DownDir());

	bool isBetweenLeftDown = crossLeft * crossDown < 0;

	return isBetweenRightUp && isBetweenLeftDown;
}*/

bool RectCollider::IsCollision(Vector2 position)
{
	Matrix invWorld = XMMatrixInverse(nullptr, matrix);

	Vector2 tempPos = Vector2::TransformCoord(position, invWorld);

	float width = size.x * 0.5f;
	float height = size.y * 0.5f;

	if (abs(tempPos.x) < width && abs(tempPos.y) < height)
		return true;

	return false;
}

bool RectCollider::IsCollision(IN RectCollider* rect, OUT Vector2* overlap)
{
	if (overlap == nullptr)
		return OBB(rect);
	else
		return AABB(rect, overlap);	
}

bool RectCollider::IsCollision(CircleCollider* circle)
{
	return circle->IsCollision(this);
}

bool RectCollider::AABB(IN RectCollider* rect, OUT Vector2* overlap)
{
	isObb = false;

	float minX = max(Left(), rect->Left());
	float maxX = min(Right(), rect->Right());

	float minY = max(Bottom(), rect->Bottom());
	float maxY = min(Top(), rect->Top());

	overlap->x = maxX - minX;
	overlap->y = maxY - minY;

	if (overlap->x > 0 && overlap->y > 0)
		return true;

	return false;
}

bool RectCollider::OBB(RectCollider* rect)
{
	isObb = true;

	ObbDesc obbA = GetObb();
	ObbDesc obbB = rect->GetObb();

	Vector2 nea1 = obbA.direction[0];
	Vector2 ea1 = nea1 * obbA.length[0];
	Vector2 nea2 = obbA.direction[1];
	Vector2 ea2 = nea2 * obbA.length[1];

	Vector2 neb1 = obbB.direction[0];
	Vector2 eb1 = neb1 * obbB.length[0];
	Vector2 neb2 = obbB.direction[1];
	Vector2 eb2 = neb2 * obbB.length[1];

	Vector2 distance = obbA.position - obbB.position;

	float lengthA = ea1.Length();
	float lengthB = SeparateAxis(nea1, eb1, eb2);
	float length = abs(distance.Dot(nea1));
	if (length > lengthA + lengthB)
		return false;

	lengthA = ea2.Length();
	lengthB = SeparateAxis(nea2, eb1, eb2);
	length = abs(distance.Dot(nea2));
	if (length > lengthA + lengthB)
		return false;

	lengthA = eb1.Length();
	lengthB = SeparateAxis(neb1, ea1, ea2);
	length = abs(distance.Dot(neb1));
	if (length > lengthA + lengthB)
		return false;

	lengthA = eb2.Length();
	lengthB = SeparateAxis(neb2, ea1, ea2);
	length = abs(distance.Dot(neb2));
	if (length > lengthA + lengthB)
		return false;

	return true;
}

float RectCollider::SeparateAxis(Vector2 separate, Vector2 e1, Vector2 e2)
{
	float r1 = abs(separate.Dot(e1));
	float r2 = abs(separate.Dot(e2));

	return r1 + r2;
}

RectCollider::ObbDesc RectCollider::GetObb()
{
	ObbDesc obbDesc;	

	obbDesc.position = pos;

	obbDesc.length[0] = size.x * 0.5f * scale.x;
	obbDesc.length[1] = size.y * 0.5f * scale.y;		

	Float4x4 world;
	XMStoreFloat4x4(&world, matrix);

	obbDesc.direction[0] = { world._11, world._12 };
	obbDesc.direction[1] = { world._21, world._22 };

	obbDesc.direction[0].Normalize();
	obbDesc.direction[1].Normalize();

	return obbDesc;
}
