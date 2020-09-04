#include "Framework.h"

ComputeShader::ComputeShader(wstring file)
{
    this->file = file;
    wstring path = L"Shaders/" + file + L".hlsl";

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    D3DCompileFromFile(path.c_str(), nullptr, nullptr, "CS",
        "cs_5_0", flags, 0, &blob, nullptr);

    DEVICE->CreateComputeShader(blob->GetBufferPointer(),
        blob->GetBufferSize(), nullptr, &shader);
}

ComputeShader::~ComputeShader()
{
    shader->Release();
    blob->Release();
}

void ComputeShader::Set()
{
    DC->CSSetShader(shader, nullptr, 0);
}
