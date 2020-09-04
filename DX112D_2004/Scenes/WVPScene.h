#pragma once

class WVPScene : public Scene
{
private:
	MatrixBuffer* worldBuffer;
	MatrixBuffer* viewBuffer;
	MatrixBuffer* projectionBuffer;

	MatrixBuffer* worldBuffer2;

	Texture* texture;	

	Float2 pos;
	Float2 pos2;
	Float2 camPos;

	float angle;
	Float2 size;

	Float2 pivot;

	Matrix world2;
public:
	WVPScene();
	~WVPScene();
	
	virtual void Update() override;
	virtual void Render() override;
};