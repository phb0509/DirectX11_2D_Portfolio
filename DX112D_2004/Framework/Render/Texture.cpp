#include "Framework.h"

map<wstring, Texture*> Texture::textures;

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
    : srv(srv), image(move(image))
{
}

Texture::~Texture()
{
    srv->Release();
}

Texture* Texture::Add(wstring file)
{
    if (textures.count(file) > 0)
        return textures[file];

    ScratchImage image;

    V(LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image));

    ID3D11ShaderResourceView* srv;

    V(CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(),
        image.GetMetadata(), &srv));

    Texture* texture = new Texture(srv, image);
    texture->file = file;

    textures[file] = texture;

    return textures[file];
}

Texture* Texture::Add(wstring key, ID3D11ShaderResourceView* srv)
{
    ScratchImage image;

    Texture* texture = new Texture(srv, image);
    textures[key] = texture;

    return textures[key];
}

void Texture::Delete()
{
    for (auto texture : textures)
        delete texture.second;
}

void Texture::Set(UINT slot)
{
    SAMPLER_STATE->SetState();
    DC->PSSetShaderResources(slot, 1, &srv);
}

Vector2 Texture::GetSize()
{
    return Vector2(image.GetMetadata().width,
        image.GetMetadata().height);
}
