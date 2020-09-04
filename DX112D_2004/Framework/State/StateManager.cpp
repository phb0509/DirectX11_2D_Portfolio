#include "Framework.h"

StateManager* StateManager::instance = nullptr;

StateManager::StateManager()
{
	samplerState = new SamplerState();
	alphaState = new BlendState();
	alphaState->Alpha();
	additiveState = new BlendState();
	additiveState->Additive();
	blendState = new BlendState();	
	cullState = new RasterizerState();
}

StateManager::~StateManager()
{
	delete samplerState;
	delete alphaState;
	delete additiveState;
	delete cullState;
}
