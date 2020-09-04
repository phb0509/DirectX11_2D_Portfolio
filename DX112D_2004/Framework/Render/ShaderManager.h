#pragma once

class ShaderManager
{
private:
	map<wstring, Shader*> shaders;

	static ShaderManager* instance;

	ShaderManager();
	~ShaderManager();
public:
	static ShaderManager* Get() { return instance; }
	static void Create() { instance = new ShaderManager(); }
	static void Delete() { delete instance; }

	VertexShader* AddVS(wstring file);
	PixelShader* AddPS(wstring file);
	GeometryShader* AddGS(wstring file);
	ComputeShader* AddCS(wstring file);
};