#include "Framework.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
	: selectButton(nullptr), selectType(Tile::BG)
{
	map = new Map(30, 30);

	CreateSamples();
}

MapToolScene::~MapToolScene()
{
	delete map;

	for (Button* sample : samples)
		delete sample;
}

void MapToolScene::Update()
{	
	if (KEY_PRESS(VK_LBUTTON))
	{		
		if (selectButton != nullptr)
		{
			Vector2 frame = selectButton->GetFrame()->data.curFrame;
			map->ClickMap(frame, selectType);
		}
	}	

	map->Update();
	for (Button* sample : samples)
		sample->Update();
}

void MapToolScene::Render()
{
	map->Render();
	for (Button* sample : samples)
		sample->Render();
}

void MapToolScene::PostRender()
{
	ImGui::SliderInt("SelectType", (int*)&selectType, 0, 1);

	if(ImGui::Button("Save", ImVec2(100, 50)))
		map->Save();
	if (ImGui::Button("Load", ImVec2(100, 50)))
		map->Load();
}

void MapToolScene::CreateSamples()
{
	Texture* texture = Texture::Add(L"Textures/Tile/tilemap.png");

	UINT width = 27;
	UINT height = 18;

	Vector2 maxFrame(width, height);

	Vector2 size = texture->GetSize() / maxFrame;
	Vector2 startPos(600, 500);

	for (UINT y = 0; y < height; y++)
	{
		for (UINT x = 0; x < width; x++)
		{
			Vector2 curFrame(x, y);
			Button* button = new Button(texture, maxFrame, curFrame);
			button->pos.x = startPos.x + (x * size.x);
			button->pos.y = startPos.y - (y * size.y);

			button->SetEvent(bind(&MapToolScene::SelectSample,
				this, placeholders::_1), button);

			samples.emplace_back(button);
		}
	}
}

void MapToolScene::SelectSample(void* param)
{
	selectButton = (Button*)param;
}
