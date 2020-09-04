#include "Framework.h"

Action::Action(vector<Clip> clips, Type type, float speed)
	: clips(clips), repeatType(type), speed(speed), curClipNum(0),
	isPlay(true), isReverse(false), time(0.0f), EndEvent(nullptr)
{
}

Action::~Action()
{
}
int a = 0;
int b = 0;
void Action::Update()
{
	if (!isPlay) return;

	time += DELTA;

	if (time > speed)
	{
		switch (repeatType)
		{
		case Action::END:
			curClipNum++;
			if (curClipNum >= clips.size())
				Stop();
			break;
		case Action::LOOP:
			curClipNum++;
			curClipNum %= clips.size();
			break;
		case Action::PINGPONG:
			if (isReverse)
			{
				curClipNum--;
				if (curClipNum <= 0)
					isReverse = false;
			}
			else
			{
				curClipNum++;
				if (curClipNum >= clips.size() - 1)
					isReverse = true;
			}
			break;
		default:
			break;
		}

		time = 0.0f;
	}
}

void Action::Play()
{
	isPlay = true;
	isReverse = false;
	time = 0.0f;
	curClipNum = 0;
}

void Action::Pause()
{
	isPlay = false;
}

void Action::Stop()
{
	isPlay = false;

	if (EndEvent)
	{
		curClipNum = 0;
		EndEvent();
	}
	else
	{
		curClipNum--;
	}
}
