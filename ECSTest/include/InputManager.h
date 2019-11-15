#pragma once
#include <SDL.h>

class InputManager
{
public:

	enum class KeyboardKey{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE};

	static InputManager& GetInstance()
	{
		//No need to check if the instance exists, C++ won't create another static instance
		//Also thread safe by default, C++ automatically locks on instance creation
		static InputManager instance;
		return instance;
	}
	//bool Initialize();

	void UpdateInput()
	{
		while (SDL_PollEvent(&inputEvent) != 0)
		{
			if (inputEvent.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}

	bool GetKeyDown(KeyboardKey key)
	{
		switch(key)
		{
			case KeyboardKey::KEY_UP:
				return currentKeyStates[SDL_SCANCODE_UP];
			case KeyboardKey::KEY_DOWN:
				return currentKeyStates[SDL_SCANCODE_DOWN];
			case KeyboardKey::KEY_LEFT:
				return currentKeyStates[SDL_SCANCODE_LEFT];
			case KeyboardKey::KEY_RIGHT:
				return currentKeyStates[SDL_SCANCODE_RIGHT];
			case KeyboardKey::KEY_SPACE:
				return currentKeyStates[SDL_SCANCODE_SPACE];
			default:
				return false;
		}
	}

	bool ShouldQuit()
	{
		return quit;
	}
private:
	InputManager() {}
	static InputManager instance;
	SDL_Event inputEvent;

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	bool quit = false;

};