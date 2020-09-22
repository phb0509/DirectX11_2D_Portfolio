#include "Framework.h"


UIManager* UIManager::instance = nullptr;

UIManager::UIManager() : current_HPbar_Monster(nullptr) , isRender_MonsterHPbar(false)
{
}

UIManager::~UIManager()
{
}

void UIManager::Update()
{
	//if (current_HPbar_Monster != nullptr) // 몬스터 체력바
	//{
	//	current_HPbar_Monster->Update();
	//}
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

}

void UIManager::Change_MonsterHPbar(HPbar_Monster* _hpBar_Monster)
{
	current_HPbar_Monster = _hpBar_Monster;
}

void UIManager::set_IsRender_MonsterHPbar(bool isRender)
{
	isRender_MonsterHPbar = isRender;
}
