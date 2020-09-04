#pragma once

class Timer
{
private:
	Timer();
	~Timer();
public:
	static Timer* Get()
	{
		static Timer instance;
		return&instance;
	}	

	void Update();

	void SetLockFPS(double value) { lockFPS = value; }

	int GetFPS() { return frameRate; }
	double GetElapsedTime() { return timeElapsed; }
	double GetRunTime() { return runTime; }

private:
	double timeScale;
	double timeElapsed;

	__int64 curTime;
	__int64 lastTime;
	__int64 periodFrequency;

	int frameRate;
	int frameCount;

	double oneSecCount;
	double runTime;

	double lockFPS;
};