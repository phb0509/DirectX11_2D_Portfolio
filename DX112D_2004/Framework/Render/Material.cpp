#include "Framework.h"

Material::Material(wstring pixelFile, wstring vertexFile)
	: mainTexture(nullptr)
{
	vertexShader = SHADER->AddVS(vertexFile);
	pixelShader = SHADER->AddPS(pixelFile);
}

Material::~Material()
{
}

void Material::Set()
{
	if(mainTexture != nullptr)
		mainTexture->Set(0);

	vertexShader->Set();
	pixelShader->Set();
}

void Material::SetTexture(wstring textureFile)
{
	mainTexture = Texture::Add(textureFile);
}
