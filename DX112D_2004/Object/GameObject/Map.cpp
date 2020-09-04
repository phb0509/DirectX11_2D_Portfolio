#include "Framework.h"

Map::Map(UINT width, UINT height)
	: width(width), height(height),	maxFrame(27, 18), isEdit(false)
{
	texture = Texture::Add(L"Textures/Tile/tilemap.png");
	tileSize = texture->GetSize() / maxFrame;
	CreateTile();
	Load();
}

Map::~Map()
{
	for (Tile* tile : bgTile)
		delete tile;

	for (Tile* tile : objTile)
		delete tile;
}

void Map::Update()
{
	for (Tile* tile : objTile)
		tile->Update();

	if (isEdit)
	{
		for (Tile* tile : bgTile)
			tile->Update();	
	}
	else
		targetTexture->Update();
}

void Map::Render()
{
	if (isEdit)
	{
		for (Tile* tile : bgTile)
			tile->Render();

		for (Tile* tile : objTile)
			tile->Render();
	}
	else
		targetTexture->Render();

	//for (Tile* tile : objTile)
		//tile->GetCollider()->Render();
}

void Map::ClickMap(Vector2 frame, Tile::Type type)
{
	switch (type)
	{
	case Tile::BG:
		SetBgTile(frame);
		break;
	case Tile::OBJ:
		SetObjTile(frame);
		break;
	default:
		break;
	}	
}

void Map::Save()
{
	BinaryWriter writer(L"TextData/TileMap.map");

	vector<TileData> data;

	for (Tile* tile : bgTile)
	{
		TileData tileData;
		tileData.frame = tile->GetFrame()->data.curFrame;

		data.emplace_back(tileData);
	}

	writer.UInt(data.size());
	writer.Byte(data.data(), sizeof(TileData) * data.size());

	data.clear();
	for (Tile* tile : objTile)
	{
		TileData tileData;
		tileData.frame = tile->GetFrame()->data.curFrame;
		tileData.pos = tile->pos;

		data.emplace_back(tileData);
	}

	writer.UInt(data.size());
	writer.Byte(data.data(), sizeof(TileData) * data.size());
}

void Map::Load()
{
	BinaryReader reader(L"TextData/TileMap.map");

	UINT size = reader.UInt();

	vector<TileData> data;
	data.resize(size);

	void* ptr = (void*)data.data();
	reader.Byte(&ptr, sizeof(TileData) * size);

	for (UINT i = 0; i < size; i++)
	{
		bgTile[i]->GetFrame()->data.curFrame = data[i].frame;
	}

	for (Tile* tile : objTile)
		delete tile;

	objTile.clear();

	size = reader.UInt();
		
	data.resize(size);

	ptr = (void*)data.data();
	reader.Byte(&ptr, sizeof(TileData) * size);

	for (UINT i = 0; i < size; i++)
	{
		CreateObjTile(data[i].pos, data[i].frame);
	}

	mapSize = { tileSize.x * width, tileSize.y * height };
	startPos = mapSize * 0.5f;
	startPos.x += 50;
	startPos.y += 50;
	CreateRenderTarget(mapSize.x, mapSize.y);
}

vector<Node*> Map::GetNodes()
{
	vector<Node*> nodes;

	int count = 0;
	for (Tile* tile : bgTile)
	{
		Vector2 tilePos = tile->pos + Vector2(50, 50);
		Node* node = new Node(tilePos, count++);

		for (Tile* obj : objTile)
		{
			Vector2 objPos = obj->pos + Vector2(50, 50);
			if (tilePos == objPos)
			{
				node->state = Node::OBSTACLE;
			}
		}

		nodes.emplace_back(node);
	}

	return nodes;
}

void Map::CreateTile()
{	
	for (UINT y = 0; y < height; y++)
	{
		for (UINT x = 0; x < width; x++)
		{
			Tile* tile = new Tile();			
			tile->SetTexture(texture);
			tile->GetFrame()->data.maxFrame = maxFrame;
			tile->GetFrame()->data.curFrame = { 1.0f, 1.0f };
			tile->pos = Vector2(tileSize.x * x, tileSize.y * y) + tileSize * 0.5f;
			tile->scale = tileSize;
			tile->CreateCollider(tileSize);

			bgTile.emplace_back(tile);
		}
	}
}

void Map::SetBgTile(Vector2 frame)
{
	for (Tile* tile : bgTile)
	{
		if (tile->GetCollider()->IsCollision(mousePos))
		{
			tile->GetFrame()->data.curFrame = frame;
		}
	}
}

void Map::SetObjTile(Vector2 frame)
{
	DeleteObjTile();

	for (Tile* tile : bgTile)
	{
		if (tile->GetCollider()->IsCollision(mousePos))
		{
			CreateObjTile(tile->pos, frame);
		}
	}
}

void Map::CreateObjTile(Vector2 pos, Vector2 frame)
{
	Tile* obj = new Tile();
	obj->SetTexture(texture);
	obj->GetFrame()->data.maxFrame = maxFrame;
	obj->GetFrame()->data.curFrame = frame;
	obj->pos = pos;
	obj->scale = tileSize;
	obj->CreateCollider(tileSize);

	objTile.emplace_back(obj);
}

void Map::DeleteObjTile()
{
	vector<Tile*>::iterator iter = objTile.begin();

	for (; iter != objTile.end(); iter++)
	{
		if ((*iter)->GetCollider()->IsCollision(mousePos))
		{
			objTile.erase(iter);
			return;
		}
	}
}

void Map::CreateRenderTarget(UINT width, UINT height)
{
	renderTarget = new RenderTarget(width, height);	

	ALPHA_BLEND_STATE->SetState();

	renderTarget->Set();

	RenderTile();

	targetTexture = new Quad(L"TextureShader");
	Texture* texture = Texture::Add(L"Map", renderTarget->GetSRV());
	targetTexture->SetTexture(texture);
	targetTexture->scale = Vector2(width, height);	
	targetTexture->pos = startPos;

	for (Tile* tile : objTile)
		tile->GetCollider()->SetOffset(startPos - mapSize *0.5f);
}

void Map::RenderTile()
{
	for (Tile* tile : bgTile)
		tile->Update();

	for (Tile* tile : objTile)
		tile->Update();

	for (Tile* tile : bgTile)
		tile->Render();

	for (Tile* tile : objTile)
		tile->Render();
}
