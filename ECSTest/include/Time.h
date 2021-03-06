#pragma once
#include <SDL.h>

class Time
{
public:
	static void CalculateDeltaTime()
	{
		//If this is the first time calculating deltatime, set our initial currentFrameTime to now
		if (timerStarted == false)
		{
			Uint32 currentFrameTime = SDL_GetTicks();
			timerStarted = true;
		}

		//Calculate the time between the current frame and the last frame. Convert to seconds.
		lastFrameTime = currentFrameTime;
		currentFrameTime = SDL_GetTicks();
		Time::deltaTime = (float)(currentFrameTime - lastFrameTime) / 1000;
	}

	//Get the time between the last frame and the current frame in seconds 
	static float GetDeltaTime()
	{
		return Time::deltaTime;
	}
private:
	Time() {}
	static inline float deltaTime = 0.0f;
	static inline Uint32 lastFrameTime = 0;
	static inline Uint32 currentFrameTime = 0;
	static inline bool timerStarted = false;

};