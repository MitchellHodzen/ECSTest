#pragma once
#include <SDL.h>
class InputManager
{
public:
	static InputManager& GetInstance();
	~InputManager();
	void GetUserInput();

private:
	static InputManager instance;
	SDL_Event inputEvent;

	InputManager();
};