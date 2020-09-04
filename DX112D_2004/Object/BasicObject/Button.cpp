#include "Framework.h"

Button::Button(Texture* texture, Vector2 maxFrame, Vector2 curFrame)
	: state(NONE), Event(nullptr), ParamEvent(nullptr), param(nullptr)
{	
	material = new Material(L"ButtonShader");
	material->SetTexture(texture);

	Vector2 size = texture->GetSize() / maxFrame;
	mesh = new QuadMesh(size);

	frameBuffer = new FrameBuffer();
	frameBuffer->data.maxFrame = maxFrame;
	frameBuffer->data.curFrame = curFrame;

	colorBuffer = new ColorBuffer();

	collider = new RectCollider(size, this);
}

Button::~Button()
{
	delete mesh;
	delete material;
	delete frameBuffer;
	delete colorBuffer;
	delete collider;
}

void Button::Update()
{
	if (collider->IsCollision(mousePos))
	{
		if (KEY_PRESS(VK_LBUTTON))
			state = DOWN;		

		if (KEY_UP(VK_LBUTTON))
		{
			if (state == DOWN)
			{
				if (Event != nullptr)
					Event();
				if (ParamEvent != nullptr)
					ParamEvent(param);
			}

			state = NONE;
		}

		switch (state)
		{
		case Button::NONE:
			colorBuffer->data.color = Float4(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		case Button::DOWN:
			colorBuffer->data.color = Float4(0.7f, 0.7f, 0.7f, 1.0f);
			break;			
		default:
			break;
		}
	}
	else
	{
		colorBuffer->data.color = Float4(1.0f, 1.0f, 1.0f, 1.0f);

		if (KEY_UP(VK_LBUTTON))
			state = NONE;
	}
	collider->scale = scale;
	collider->Update();
	UpdateWorld();
}

void Button::Render()
{
	SetWorldBuffer();
	frameBuffer->SetPSBuffer(0);
	colorBuffer->SetPSBuffer(1);

	material->Set();
	mesh->Render();

	collider->Render();
}
