#pragma once

class PixelShaderScene : public Scene
{
private:
	Quad* quad;
	ColorBuffer* colorBuffer;
	IntBuffer* intBuffer;
	FloatBuffer* floatBuffer;

	Texture* texture;
public:
	PixelShaderScene();
	~PixelShaderScene();
	
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};