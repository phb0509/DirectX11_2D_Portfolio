#pragma once

class PixelShader : public Shader
{
	friend class ShaderManager;
private:
	ID3D11PixelShader* shader;	

	PixelShader(wstring file);
	~PixelShader();
public:	
	void Set() override;
};