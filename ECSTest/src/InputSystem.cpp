#include "InputSystem.h"
#include "kecs/KECS.h"
#include "Components/c_input.h"
#include "Components/c_physics.h"
#include "Components/c_cannon.h"
#include "MessageManager.h"
#include "Messages/m_bulletFired.h"

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

	std::vector<Entity> entities = EntityManager::GetEntitiesWithComponent<UserInput>();

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	//For every entity which captures user input, record user input
	for (Entity entity : entities)
	{
		UserInput* uin = EntityManager::GetComponent<UserInput>(entity);

		uin->keyStates[UserInput::InputType::UP] = currentKeyStates[SDL_SCANCODE_UP];
		uin->keyStates[UserInput::InputType::DOWN] = currentKeyStates[SDL_SCANCODE_DOWN];
		uin->keyStates[UserInput::InputType::LEFT] = currentKeyStates[SDL_SCANCODE_LEFT];
		uin->keyStates[UserInput::InputType::RIGHT] = currentKeyStates[SDL_SCANCODE_RIGHT];
		uin->keyStates[UserInput::InputType::SPACE] = currentKeyStates[SDL_SCANCODE_SPACE];

	}
}

void InputSystem::HandleUserInput()
{
	std::vector<Entity> entities = EntityManager::GetEntitiesWithComponent<Physics, UserInput>();

	for (Entity entity : entities)
	{
		Physics* phys = EntityManager::GetComponent<Physics>(entity);
		UserInput* uin = EntityManager::GetComponent<UserInput>(entity);
		if (uin->keyStates[UserInput::InputType::UP])
		{
			phys->velocity.SetY(-1);
		}
		else if (uin->keyStates[UserInput::InputType::DOWN])
		{
			phys->velocity.SetY(1);
		}
		else
		{
			phys->velocity.SetY(0);
		}
		if (uin->keyStates[UserInput::InputType::LEFT])
		{
			phys->velocity.SetX(-1);
		}
		else if (uin->keyStates[UserInput::InputType::RIGHT])
		{
			phys->velocity.SetX(1);
		}
		else
		{
			phys->velocity.SetX(0);
		}

		phys->velocity *= phys->maxSpeed;

		if (uin->keyStates[UserInput::InputType::SPACE] && EntityManager::HasComponent<Cannon>(entity))
		{
			BulletFiredMessage message(entity);
			MessageManager::PushMessage<BulletFiredMessage>(message);
		}
	}
}