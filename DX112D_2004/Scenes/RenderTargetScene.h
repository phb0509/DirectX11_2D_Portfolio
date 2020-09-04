#pragma once

class RenderTargetScene : public Scene
{
private:
	RenderTarget* renderTarget;	

	Quad* bg;
	Quad* plane;
	Knight* knight;

	Quad* targetTexture;
	Quad* targetTexture2;

	MatrixBuffer* viewBuffer;

	IntBuffer* intBuffer;
	FloatBuffer* floatBuffer;
	ColorBuffer* colorBuffer;
public:
	RenderTargetScene();
	~RenderTargetScene();
		
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
};