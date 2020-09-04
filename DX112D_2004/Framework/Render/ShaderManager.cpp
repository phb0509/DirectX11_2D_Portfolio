#include "Framework.h"

ShaderManager* ShaderManager::instance = nullptr;

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
    for (auto shader : shaders)
    {
        delete shader.second;
    }
}

VertexShader* ShaderManager::AddVS(wstring file)
{
    if (shaders.count(file) > 0)
        return dynamic_cast<VertexShader*>(shaders[file]);

    VertexShader* vs = new VertexShader(file);

    shaders[file] = vs;

    return vs;
}

PixelShader* ShaderManager::AddPS(wstring file)
{
    if (shaders.count(file) > 0)
        return dynamic_cast<PixelShader*>(shaders[file]);

    PixelShader* ps = new PixelShader(file);

    shaders[file] = ps;

    return ps;
}

GeometryShader* ShaderManager::AddGS(wstring file)
{
    if (shaders.count(file) > 0)
        return dynamic_cast<GeometryShader*>(shaders[file]);

    GeometryShader* gs = new GeometryShader(file);

    shaders[file] = gs;

    return gs;
}

ComputeShader* ShaderManager::AddCS(wstring file)
{
    if (shaders.count(file) > 0)
        return dynamic_cast<ComputeShader*>(shaders[file]);

    ComputeShader* cs = new ComputeShader(file);

    shaders[file] = cs;

    return cs;
}
