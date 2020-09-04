#pragma once

class Material
{
private:
	Texture* mainTexture;

	VertexShader* vertexShader;
	PixelShader* pixelShader;

public:
	Material(wstring pixelFile,	wstring vertexFile = L"VertexUVShader");
	~Material();

	void Set();

	void SetTexture(wstring textureFile);
	void SetTexture(Texture* texture) { mainTexture = texture; }
	Texture* GetTexture() { return mainTexture; }
};