#include "Framework.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
	for (int i = 0; i < 500; i++)
	{
		bullet = new Bullet();
		gunner_bullets.emplace_back(bullet);
	}

	gunner = new Gunner();
}

GameManager::~GameManager()
{
	delete gunner;
	for (int i = 0; i < gunner_bullets.size(); i++)
	{
		delete gunner_bullets[i];
	}
}

void GameManager::SetMirkWoodScene()
{
}
