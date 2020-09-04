#pragma once

class RasterizerState
{
private:
	ID3D11RasterizerState* state;
	D3D11_RASTERIZER_DESC desc;

public:
	RasterizerState();
	~RasterizerState();

	void SetState();
};