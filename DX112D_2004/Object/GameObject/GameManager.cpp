#include "Framework.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
	gunner = new Gunner();
	SetMirkWoodScene();
}

GameManager::~GameManager()
{
	delete gunner;

}

void GameManager::SetMirkWoodScene()
{
	//for (int y = 0; y < 2; y++)
	//{
	//	for (int x = 0; x < 2; x++)
	//	{
	//		gnoll = new Gnoll_Mirkwood({ 700.0f + x * 150.0f,100.0f + y * 150.0f });
	//		monsters_MirkwoodScene.emplace_back(gnoll);
	//	}
	//}


	gnoll = new Gnoll_Mirkwood({ 700.0f,100.0f});
	monsters_MirkwoodScene.push_back(gnoll);
}
