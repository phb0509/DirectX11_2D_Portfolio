#pragma once

class Scene;

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

public:
	static SceneManager* Get()
	{
		static SceneManager instance;
		return &instance;
	}

	void Update();
	void Render();
	void PreRender();
	void PostRender();

	Scene* Add(string key, Scene* scene);

	void ChangeScene(string key);

private:
	map<string, Scene*> scenes;
	Scene* curScene;
};