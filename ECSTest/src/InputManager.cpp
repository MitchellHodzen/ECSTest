#include "InputManager.h"
#include "kecs/KECS.h"
#include "Components/c_input.h"

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

InputManager& InputManager::GetInstance()
{
	//No need to check if the instance exists, C++ won't create another static instance
	//Also thread safe by default, C++ automatically locks on instance creation
	static InputManager instance;
	return instance;
}

void InputManager::GetUserInput()
{

	while (SDL_PollEvent(&inputEvent) != 0)
	{
		if (inputEvent.type == SDL_QUIT)
		{
			//quit = true;
		}
	}

	std::vector<int> entities = EntityManager::GetEntitiesWithComponent<UserInput>();

	//For every entity which captures user input, record user input
	for (int entityIndex : entities)
	{
		UserInput& uin = EntityManager::GetComponent<UserInput>(entityIndex);

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_UP])
		{
			uin.keyStates[UserInput::InputType::UP] = true;
		}
		else
		{
			uin.keyStates[UserInput::InputType::UP] = false;
		}
		if (currentKeyStates[SDL_SCANCODE_DOWN])
		{
			uin.keyStates[UserInput::InputType::DOWN] = true;
		}
		else
		{
			uin.keyStates[UserInput::InputType::DOWN] = false;
		}
		if (currentKeyStates[SDL_SCANCODE_LEFT])
		{
			uin.keyStates[UserInput::InputType::LEFT] = true;
		}
		else
		{
			uin.keyStates[UserInput::InputType::LEFT] = false;
		}
		if (currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			uin.keyStates[UserInput::InputType::RIGHT] = true;
		}
		else
		{
			uin.keyStates[UserInput::InputType::RIGHT] = false;
		}
	}
}
