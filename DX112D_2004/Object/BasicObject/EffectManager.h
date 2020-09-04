#pragma once

class EffectManager
{
private:
	map<string, vector<Effect*>> totalEffect;

	static EffectManager* instance;

	EffectManager();
	~EffectManager();
public:
	static EffectManager* Get() { return instance; }
	static void Create() { instance = new EffectManager(); }
	static void Delete() { delete instance; }

	void Update();
	void Render();

	void Add(string key, UINT poolCount, wstring textureFile,
		UINT maxFrameX, UINT maxFrameY, float speed = 0.1f, bool isAdditive = false);

	void Play(string key, Vector2 pos, Float4 color = Float4(1, 1, 1, 1));
};