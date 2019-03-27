#pragma once
#include <SDL.h>
class InputSystem
{
public:
	InputSystem();
	~InputSystem();
	void GetUserInput();

private:
	SDL_Event inputEvent;
};