#include "Framework.h"

DNode::DNode(Vector2 pos)
	: pos(pos), isClosed(false), via(-1), cost(FLT_MAX)
{
	quad = new Quad(L"NodeShader");
	quad->scale = { 30, 30 };
	colorBuffer = new ColorBuffer();
	quad->pos = pos;
}

DNode::~DNode()
{
	delete quad;
	delete colorBuffer;
}

void DNode::Update()
{
	quad->Update();
}

void DNode::Render()
{
	colorBuffer->SetPSBuffer(0);
	quad->Render();
}

void DNode::AddEdge(DNode* node)
{
	Edge* edge = new Edge();
	edge->node = node;
	edge->cost = (node->pos - pos).Length();
	edges.emplace_back(edge);
}
