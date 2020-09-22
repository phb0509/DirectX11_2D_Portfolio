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
	void Change_MonsterHPbar(HPbar_Monster* _hpBar_Monster);
	void set_IsRender_MonsterHPbar(bool isRender);

private:
	HPbar_Monster* current_HPbar_Monster;
	bool isRender_MonsterHPbar;

};