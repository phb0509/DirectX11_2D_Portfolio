#pragma once

class Action
{
public:
	struct Clip
	{
		Vector2 startPos;
		Vector2 size;
		Texture* texture;

		Clip(float x, float y, float w, float h, Texture* texture)
			: startPos(x, y), size(w, h), texture(texture)
		{
		}
	};

	enum Type
	{
		END,
		LOOP,
		PINGPONG
	};

private:
	vector<Clip> clips;

	Type repeatType;
	bool isPlay;
	
	UINT curClipNum;

	float time;
	float speed;

	bool isReverse;

	CallBack EndEvent;
	CallBackParam EndFireEvent;

public:
	Action(vector<Clip> clips, Type type = LOOP, float speed = 0.1f);
	~Action();

	void Update();

	void Play();
	void Pause();
	void Stop();

	void SetEndEvent(CallBack Event) { EndEvent = Event; }
	void SetFireEndEvent(CallBackParam Event) { EndFireEvent = Event; }

	Clip GetCurClip() { return clips[curClipNum]; }
	UINT GetCurClipNum() { return curClipNum; }
};