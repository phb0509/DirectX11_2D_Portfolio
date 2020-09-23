#include "Framework.h"

Brazier::Brazier() : curAction(IDLE), isRight(true)
{
	pos = { 0, 0 };
	sprite = new Sprite();

	string path = "Textures/ElvenGarden/";
	LoadAction(path, "Brazier.xml", Action::PINGPONG);
}

Brazier::~Brazier()
{
	delete sprite;

	for (Action* action : actions)
		delete action;
}

void Brazier::Update()
{
	if(!isActive) return;
	Action::Clip curClip = actions[curAction]->GetCurClip();
	sprite->SetAction(curClip);

	actions[curAction]->Update();
	scale.x = isRight ? curClip.size.x : -curClip.size.x;
	scale.y = curClip.size.y;

	UpdateWorld();
}

void Brazier::Render()
{
	if(!isActive) return;
	SetWorldBuffer();
	sprite->Render();
}

void Brazier::LoadAction(string path, string file, Action::Type type, float speed)
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

void Brazier::SetAction(ActionType type)
{
	if (curAction != type)
	{
		curAction = type;
		actions[curAction]->Play();
	}
}
