#include "Framework.h"

Transform::Transform(string tag)
	: tag(tag), pos(0, 0), rot(0, 0, 0), scale(1, 1), pivot(0, 0),
	parent(nullptr), isActive(true)
{
	matrix = XMMatrixIdentity();
	worldBuffer = new MatrixBuffer();
}

Transform::~Transform()
{
	delete worldBuffer;
}

void Transform::UpdateWorld()
{
	if (!isActive) return;

	S = XMMatrixScaling(scale.x, scale.y, 1);
	R = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	T = XMMatrixTranslation(pos.x, pos.y, 0.0f);
	P = XMMatrixTranslation(pivot.x, pivot.y, 0.0f);
	IP = XMMatrixInverse(nullptr, P);

	matrix = IP * S * R * T * P;

	if (parent != nullptr)
		matrix *= *parent;

	XMStoreFloat4x4(&matWorld, matrix);
	right = { matWorld._11, matWorld._12 };
	up = { matWorld._21, matWorld._22 };

	worldBuffer->Set(matrix);	
}

void Transform::SetWorldBuffer(UINT slot)
{
	worldBuffer->SetVSBuffer(slot);
}

Vector2 Transform::WorldPos()
{
	return Vector2::TransformCoord(pos, matrix);

	//Float4x4 temp;
	//XMStoreFloat4x4(&temp, matrix);
	//return Vector2(temp._41, temp._42);
}
