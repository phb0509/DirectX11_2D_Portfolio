#include "Framework.h"

Effect::Effect(wstring textureFile, UINT maxFrameX, UINT maxFrameY, float speed)
	: isAdditive(false)
{
	isActive = false;

	sprite = new Sprite(L"EffectShader");

	vector<Action::Clip> clips;

	Texture* texture = Texture::Add(textureFile);

	float w = texture->GetSize().x / maxFrameX;
	float h = texture->GetSize().y / maxFrameY;

	scale.x = w;
	scale.y = h;

	for (int y = 0; y < maxFrameY; y++)
	{
		for (int x = 0; x < maxFrameX; x++)
		{	
			float startX = w * x;
			float startY = h * y;

			clips.emplace_back(startX, startY, w, h, texture);
		}		
	}

	action = new Action(clips, Action::END, speed);
	action->SetEndEvent(bind(&Effect::End, this));

	colorBuffer = new ColorBuffer();	
}

Effect::~Effect()
{
	delete sprite;
	delete action;
	delete colorBuffer;
}

void Effect::Update()
{
	if (!isActive) return;

	action->Update();		

	UpdateWorld();
}

void Effect::Render()
{
	if (!isActive) return;	

	sprite->SetAction(action->GetCurClip());

	if (isAdditive)
		ADDITIVE_BLEND_STATE->SetState();	

	SetWorldBuffer();
	colorBuffer->SetPSBuffer(1);

	sprite->Render();		
}

void Effect::Play(Vector2 pos)
{
	isActive = true;
	this->pos = pos;

	action->Play();
}

void Effect::End()
{
	isActive = false;
}
