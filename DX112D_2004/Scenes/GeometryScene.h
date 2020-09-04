#pragma once

class GeometryScene : public Scene
{
private:
	//vector<Node*> nodes;
	vector<VertexSizeFrame> vertices;
	VertexShader* vertexShader;
	GeometryShader* geometryShader;
	PixelShader* pixelShader;

	VertexBuffer* vertexBuffer;
	FrameBuffer* frameBuffer;

	Texture* texture;
public:
	GeometryScene();
	~GeometryScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};