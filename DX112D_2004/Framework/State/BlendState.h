#pragma once

class BlendState
{
private:
	ID3D11BlendState* state;
	D3D11_BLEND_DESC desc;

public:
	BlendState();
	~BlendState();

	void SetState();

	void Alpha();
	void Additive();

	void Changed();
};