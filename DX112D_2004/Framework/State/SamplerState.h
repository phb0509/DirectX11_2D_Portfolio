#pragma once

class SamplerState
{
private:
	ID3D11SamplerState* state;
	D3D11_SAMPLER_DESC desc;

public:
	SamplerState();
	~SamplerState();

	void SetState(UINT slot = 0);
};