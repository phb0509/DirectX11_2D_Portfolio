#pragma once

struct Vertex
{
	Float3 pos;	

	Vertex() : pos(0, 0, 0)
	{
	}

	Vertex(float x, float y)
		: pos(x, y, 0)
	{
	}
};

struct VertexUV
{
	Float3 pos;
	Float2 uv;

	VertexUV() : pos(0, 0, 0), uv(0, 0)
	{
	}

	VertexUV(float x, float y, float u, float v)
		: pos(x, y, 0), uv(u, v)
	{
	}
};

struct VertexSize
{
	Float3 pos;
	Float2 size;

	VertexSize() : pos(0, 0, 0), size(0, 0)
	{
	}

	VertexSize(float x, float y, float w, float h)
		: pos(x, y, 0), size(w, h)
	{
	}
};

struct VertexSizeFrame
{
	Float3 pos;
	Float2 size;
	Float2 frame;

	VertexSizeFrame() : pos(0, 0, 0), size(0, 0), frame(0, 0)
	{
	}
};

struct VertexColor
{
	Float3 pos;
	Float4 color;

	VertexColor() : pos(0, 0, 0), color(1, 1, 1, 1)
	{
	}

	VertexColor(float x, float y, Float4 color)
		: pos(x, y, 0), color(color)
	{
	}
};