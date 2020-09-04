#include "Framework.h"
#include "AStarScene.h"

AStarScene::AStarScene()
{
	map = new Map(30, 30);	
	tank = new Tank();
	aStar = new AStar(map);
}

AStarScene::~AStarScene()
{
	delete map;
	delete tank;
	delete aStar;
}

void AStarScene::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		int start = aStar->FindCloseNode(tank->pos);
		int end = aStar->FindCloseNode(mousePos);

		aStar->Reset();
		tank->SetOrder(aStar->FindPath(start, end));

		aStar->Update();
	}

	map->Update();
	tank->Update();	
}

void AStarScene::Render()
{
	map->Render();
	tank->Render();
	//aStar->Render();
}

void AStarScene::PostRender()
{
}
