#include "Framework.h"

Mario::Mario()
	: curAction(RUN)
{
	sprite = new Sprite();
	sprite->pos = { 500, 500 };

	Texture* texture = Texture::Add(L"Textures/mario.png");

	vector<Action::Clip> clips;
	clips.emplace_back(64, 82, 64, 82, texture);
	clips.emplace_back(128, 82, 64, 82, texture);
	clips.emplace_back(192, 82, 64, 82, texture);

	actions.emplace_back(new Action(clips));
}

Mario::~Mario()
{
	for (Action* action : actions)
		delete action;
}

void Mario::Update()
{
	actions[curAction]->Update();
	sprite->SetAction(actions[curAction]->GetCurClip());

	sprite->Update();	
}

void Mario::Render()
{
	sprite->Render();
}
