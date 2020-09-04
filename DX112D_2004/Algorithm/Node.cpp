#include "Framework.h"

Node::Node(Vector2 pos, int index)
	: pos(pos), index(index), via(-1), f(0), g(0), h(0), state(NONE)
{
	quad = new Quad(L"NodeShader");
	quad->pos = pos;
	quad->scale = { 5, 5 };
	colorBuffer = new ColorBuffer();
}

Node::~Node()
{
	for (Edge* edge : edges)
		delete edge;

	delete quad;
	delete colorBuffer;
}

void Node::Update()
{
	switch (state)
	{
	case Node::NONE:
		colorBuffer->data.color = { 1, 1, 1, 1 };
		break;
	case Node::OPEN:
		colorBuffer->data.color = { 0, 1, 0, 1 };
		break;
	case Node::CLOSED:
		colorBuffer->data.color = { 0, 0, 0, 1 };
		break;
	case Node::USING:
		colorBuffer->data.color = { 0, 0, 1, 1 };
		break;
	case Node::OBSTACLE:
		colorBuffer->data.color = { 1, 0, 0, 1 };
		break;
	default:
		break;
	}

	quad->Update();
}

void Node::Render()
{
	colorBuffer->SetPSBuffer(0);
	quad->Render();
}

void Node::AddEdge(Node* node)
{
	Edge* edge = new Edge();
	edge->index = node->index;
	edge->cost = (node->pos - pos).Length();
	edges.emplace_back(edge);
}
