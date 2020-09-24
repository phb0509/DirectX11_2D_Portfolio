#include "Framework.h"

Linus::Linus() : isRight(true), curAction(IDLE)
{
	sprite = new Sprite();
	collider = new RectCollider({ 118, 116 }, this);

	string path = "Textures/ElvenGarden/";

	LoadAction(path, "Linus.xml", Action::LOOP);
}

Linus::~Linus()
{
	delete sprite;
	delete collider;

	for (Action* action : actions)
		delete action;
}

void Linus::Update()
{
	Action::Clip curClip = actions[curAction]->GetCurClip();
	sprite->SetAction(curClip);
	actions[curAction]->Update();

	scale.x = isRight ? curClip.size.x : -curClip.size.x;
	scale.y = curClip.size.y;

	collider->Update();

	UpdateWorld();
}

void Linus::Render()
{
	SetWorldBuffer();
	sprite->Render();
}

void Linus::LoadAction(string path, string file, Action::Type type, float speed)
{
	XmlDocument* document = new XmlDocument();
	document->LoadFile((path + file).c_str());

	XmlElement* atlas = document->FirstChildElement();
	string fileName = atlas->Attribute("imagePath");
	fileName = path + fileName;
	wstring imagePath;
	imagePath.assign(fileName.begin(), fileName.end());

	Texture* texture = Texture::Add(imagePath);

	vector<Action::Clip> clips;
	XmlElement* sprite = atlas->FirstChildElement();

	while (sprite != nullptr)
	{
		float x, y, w, h;

		x = sprite->FloatAttribute("x");
		y = sprite->FloatAttribute("y");
		w = sprite->FloatAttribute("w");
		h = sprite->FloatAttribute("h");

		clips.emplace_back(x, y, w, h, texture);

		sprite = sprite->NextSiblingElement();
	}

	actions.emplace_back(new Action(clips, type, speed));

	delete document;
}

void Linus::SetAction(ActionType type)
{
	if (curAction != type)
	{
		curAction = type;
		actions[curAction]->Play();
	}
}
