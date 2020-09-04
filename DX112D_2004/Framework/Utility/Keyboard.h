#pragma once

#define KEYMAX 255

class Keyboard
{
private:
	enum {
		NONE,
		DOWN,
		UP,
		PRESS
	};

	Keyboard();
	~Keyboard();

public:
	static Keyboard* Get()
	{
		static Keyboard instance;
		return &instance;
	}

	void Update();

	bool Down(UINT key) { return mapState[key] == DOWN; }
	bool Up(UINT key) { return mapState[key] == UP; }
	bool Press(UINT key) { return mapState[key] == PRESS; }

private:
	byte curState[KEYMAX];
	byte oldState[KEYMAX];
	byte mapState[KEYMAX];
};