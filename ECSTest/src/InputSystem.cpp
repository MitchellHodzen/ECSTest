#include "InputSystem.h"
#include "kecs/KECS.h"
#include "Components/c_input.h"

InputSystem::InputSystem()
{
}


InputSystem::~InputSystem()
{
}

void InputSystem::GetUserInput()
{

	while (SDL_PollEvent(&inputEvent) != 0)
	{
		if (inputEvent.type == SDL_QUIT)
		{
			//quit = true;
		}
	}

	std::vector<int> entities = EntityManager::GetEntitiesWithComponent<UserInput>();

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	//For every entity which captures user input, record user input
	for (int entityIndex : entities)
	{
		UserInput& uin = EntityManager::GetComponent<UserInput>(entityIndex);

		uin.keyStates[UserInput::InputType::UP] = currentKeyStates[SDL_SCANCODE_UP];
		uin.keyStates[UserInput::InputType::DOWN] = currentKeyStates[SDL_SCANCODE_DOWN];
		uin.keyStates[UserInput::InputType::LEFT] = currentKeyStates[SDL_SCANCODE_LEFT];
		uin.keyStates[UserInput::InputType::RIGHT] = currentKeyStates[SDL_SCANCODE_RIGHT];
		uin.keyStates[UserInput::InputType::SPACE] = currentKeyStates[SDL_SCANCODE_SPACE];

	}
}
