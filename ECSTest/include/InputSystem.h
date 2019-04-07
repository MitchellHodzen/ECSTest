#pragma once
#include <SDL.h>
class InputSystem
{
public:
	InputSystem();
	~InputSystem();
	void GetUserInput();
	void HandleUserInput();


private:
	SDL_Event inputEvent;
};