#pragma once

class GeometryShader : public Shader
{
	friend class ShaderManager;
private:
	ID3D11GeometryShader* shader;

	GeometryShader(wstring file);
	~GeometryShader();
public:
	void Set() override;
};