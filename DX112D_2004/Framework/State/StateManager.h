#pragma once

class StateManager
{
private:
	SamplerState* samplerState;
	BlendState* alphaState;
	BlendState* additiveState;
	BlendState* blendState;
	RasterizerState* cullState;

	static StateManager* instance;

	StateManager();
	~StateManager();
public:
	static StateManager* Get() { return instance; }
	static void Create() { instance = new StateManager(); }
	static void Delete() { delete instance; }

	SamplerState* GetSampler() { return samplerState; }
	BlendState* GetAlphaBlend() { return alphaState; }
	BlendState* GetAdditiveBlend() { return additiveState; }
	BlendState* GetBlend() { return blendState; }
	RasterizerState* GetCullMode() { return cullState; }
};