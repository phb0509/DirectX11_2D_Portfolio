#pragma once

class Button : public Transform
{
protected:
	enum State
	{
		NONE,
		DOWN,
		OVER
	}state;

	Material* material;
	QuadMesh* mesh;

	FrameBuffer* frameBuffer;
	ColorBuffer* colorBuffer;

	Collider* collider;

	CallBack Event;
	CallBackParam ParamEvent;

	void* param;
public:
	Button(Texture* texture, Vector2 maxFrame = Vector2(1, 1),
		Vector2 curFrame = Vector2(1, 1));
	~Button();

	void Update();
	void Render();

	void SetEvent(CallBack value) { Event = value; }
	void SetEvent(CallBackParam value, void* param) 
	{ 
		ParamEvent = value; 
		this->param = param;
	}

	FrameBuffer* GetFrame() { return frameBuffer; }
};