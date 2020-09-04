#pragma once

class Map
{
private:
	struct TileData
	{
		Vector2 frame;
		Vector2 pos;
	};

	Texture* texture;

	UINT width, height;

	Vector2 maxFrame;
	Vector2 tileSize;
	Vector2 mapSize;

	vector<Tile*> bgTile;
	vector<Tile*> objTile;

	Vector2 startPos;	

	RenderTarget* renderTarget;
	Quad* targetTexture;

	bool isEdit;
public:
	Map(UINT width, UINT height);
	~Map();

	void Update();
	void Render();

	void ClickMap(Vector2 frame, Tile::Type type);

	void Save();
	void Load();

	vector<Node*> GetNodes();

	UINT GetWidth() { return width; }
	UINT GetHeight() { return height; }
private:
	void CreateTile();

	void SetBgTile(Vector2 frame);
	void SetObjTile(Vector2 frame);

	void CreateObjTile(Vector2 pos, Vector2 frame);
	void DeleteObjTile();	

	void CreateRenderTarget(UINT width, UINT height);
	void RenderTile();
};