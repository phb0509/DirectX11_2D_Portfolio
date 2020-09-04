#include "Framework.h"

GeometryShader::GeometryShader(wstring file)
{
    this->file = file;
    wstring path = L"Shaders/" + file + L".hlsl";

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    D3DCompileFromFile(path.c_str(), nullptr, nullptr, "GS",
        "gs_5_0", flags, 0, &blob, nullptr);

    DEVICE->CreateGeometryShader(blob->GetBufferPointer(),
        blob->GetBufferSize(), nullptr, &shader);
}

GeometryShader::~GeometryShader()
{
    shader->Release();
}

void GeometryShader::Set()
{
    DC->GSSetShader(shader, nullptr, 0);
}
