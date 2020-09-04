#pragma once

class Transform
{
public:
	string tag;

	Vector2 pos;
	Float3 rot;
	Vector2 scale;

	bool isActive;
protected:
	Matrix matrix;

	Vector2 pivot;
	Matrix* parent;

	MatrixBuffer* worldBuffer;

	Matrix S, R, T, P, IP;

	Vector2 right;
	Vector2 up;

	Float4x4 matWorld;
public:
	Transform(string tag = "Untagged");
	virtual ~Transform();

	void UpdateWorld();

	void SetParent(Matrix* matrix) { parent = matrix; }

	void SetWorldBuffer(UINT slot = 0);

	Matrix* GetMatrix() { return &matrix; }

	Vector2 WorldPos();

	Vector2 RightDir() { return right.Normal(); }
	Vector2 UpDir() { return up.Normal(); }
	Vector2 LeftDir() { return right.Normal() * -1.0f; }
	Vector2 DownDir() { return up.Normal() * -1.0f; }
};