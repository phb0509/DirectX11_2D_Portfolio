#include "Framework.h"

RasterizerState::RasterizerState() : desc{}
{
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_SOLID;

	DEVICE->CreateRasterizerState(&desc, &state);
}

RasterizerState::~RasterizerState()
{
	state->Release();
}

void RasterizerState::SetState()
{
	DC->RSSetState(state);
}
