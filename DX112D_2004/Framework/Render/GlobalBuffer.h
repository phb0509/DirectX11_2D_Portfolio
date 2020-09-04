#pragma once
#include "Framework.h"

inline void IASetPT(D3D_PRIMITIVE_TOPOLOGY type = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	DC->IASetPrimitiveTopology(type);
}

class MatrixBuffer : public ConstBuffer
{
private:
	struct Data
	{
		Matrix mat;
	}data;

public:
	MatrixBuffer() : ConstBuffer(&data, sizeof(Data))
	{
		data.mat = XMMatrixIdentity();
	}

	void Set(Matrix value)
	{
		data.mat = XMMatrixTranspose(value);		
	}
};

class ColorBuffer : public ConstBuffer
{
public:
	struct Data
	{
		Float4 color;
	}data;

	ColorBuffer() : ConstBuffer(&data, sizeof(Data))
	{
		data.color = { 1, 1, 1, 1 };
	}
};

class FrameBuffer : public ConstBuffer
{
public:
	struct Data
	{
		Float2 maxFrame;
		Float2 curFrame;
	}data;

	FrameBuffer() : ConstBuffer(&data, sizeof(Data))
	{
		data.maxFrame = { 1, 1 };
		data.curFrame = { 1, 1 };
	}
};

class ActionBuffer : public ConstBuffer
{
public:
	struct Data
	{
		Float2 startPos;
		Float2 size;
		Float2 maxSize;		

		float padding[2];
	}data;

	ActionBuffer() : ConstBuffer(&data, sizeof(Data))
	{
		data.startPos = { 0, 0 };
		data.size = { 0, 0 };
		data.maxSize = { 0, 0 };
	}
};

class IntBuffer : public ConstBuffer
{
public:
	struct Data
	{
		int index[4];
	}data;

	IntBuffer() : ConstBuffer(&data, sizeof(Data))
	{
		for (int& i : data.index)
			i = 0;
	}
};

class FloatBuffer : public ConstBuffer
{
public:
	struct Data
	{
		float value[4];
	}data;

	FloatBuffer() : ConstBuffer(&data, sizeof(Data))
	{
		for (float& i : data.value)
			i = 0.0f;
	}
};