#pragma once

class ComputeShader : public Shader
{
	friend class ShaderManager;
private:
	ID3D11ComputeShader* shader;

	ComputeShader(wstring file);
	~ComputeShader();
public:
	void Set() override;
};