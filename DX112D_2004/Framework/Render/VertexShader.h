#pragma once

class VertexShader : public Shader
{
	friend class ShaderManager;
private:
	ID3D11VertexShader* shader;
	ID3D11InputLayout* inputLayout;

	ID3D11ShaderReflection* reflection;

	VertexShader(wstring file);
	~VertexShader();
public:
	void Set() override;

	void CreateInputLayout();
};