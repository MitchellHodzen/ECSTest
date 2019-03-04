#pragma once

class Time
{
public:
	static void CalculateDeltaTime(int lastFrameTime, int currentFrameTime)
	{
		Time::deltaTime = (float)(currentFrameTime - lastFrameTime) / 1000;
	}
	static float GetDeltaTime()
	{
		return Time::deltaTime;
	}
private:
	Time() {}
	static inline float deltaTime = 0.0f;
};