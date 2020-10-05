#include "Framework.h"


UIManager* UIManager::instance = nullptr;

UIManager::UIManager() : current_HPbar_Monster(nullptr), isRender_MonsterHPbar(false)
{
	character_Interface = new Character_Interface();
}

UIManager::~UIManager()
{
	delete character_Interface;
}

void UIManager::Update()
{
	character_Interface->Update();
}

void UIManager::Render()
{
	if (isRender_MonsterHPbar)
	{
		if (current_HPbar_Monster != nullptr)// 몬스터 체력바
		{
			current_HPbar_Monster->Render();
		}
	}

	character_Interface->Render();
}

void UIManager::Change_MonsterHPbar(HPbar_Monster* _hpBar_Monster)
{
	current_HPbar_Monster = _hpBar_Monster;
}

void UIManager::set_IsRender_MonsterHPbar(bool isRender)
{
	isRender_MonsterHPbar = isRender;
}