#pragma once

class UIManager
{
private:
	static UIManager* instance;

public:

	UIManager();
	~UIManager();

	static UIManager* Get() { return instance; }
	static void Create() { instance = new UIManager(); }
	static void Delete() { delete instance; }

	void Update();
	void Render();
	


private:
	HPbar_Monster* hpBar_Monster;

};