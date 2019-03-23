#pragma once
#include <SDL.h>
class InputManager
{
public:
	InputManager();
	~InputManager();
	void GetUserInput();

private:
	SDL_Event inputEvent;
};