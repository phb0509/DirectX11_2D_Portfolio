#pragma once

class Vector2;

class Texture
{
private:	
	wstring file;
	ScratchImage image;

	ID3D11ShaderResourceView* srv;	

	static map<wstring, Texture*> textures;

	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	~Texture();
public:
	static Texture* Add(wstring file);
	static Texture* Add(wstring key, ID3D11ShaderResourceView* srv);
	static void Delete();

	void Set(UINT slot);

	Vector2 GetSize();	
};