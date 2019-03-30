#include "PhysicsSystem.h"
#include "kecs/KECS.h"
#include "Components/c_transform.h"
#include "Components/c_physics.h"
#include "Components/c_rect.h"
#include "Components/c_input.h"
#include "Time.h"
#include "MessageManager.h"
#include "Messages/m_collision.h"



PhysicsSystem::PhysicsSystem()
{
}


PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::HandleUserInput()
{
	std::vector<int> entities = EntityManager::GetEntitiesWithComponent<Physics, UserInput>();

	for (int entityIndex : entities)
	{
		Physics& phys = EntityManager::GetComponent<Physics>(entityIndex);
		UserInput& uin = EntityManager::GetComponent<UserInput>(entityIndex);
		if (uin.keyStates[UserInput::InputType::UP])
		{
			phys.velocity.SetY(-1);
		}
		else if (uin.keyStates[UserInput::InputType::DOWN])
		{
			phys.velocity.SetY(1);
		}
		else
		{
			phys.velocity.SetY(0);
		}
		if (uin.keyStates[UserInput::InputType::LEFT])
		{
			phys.velocity.SetX(-1);
		}
		else if (uin.keyStates[UserInput::InputType::RIGHT])
		{
			phys.velocity.SetX(1);
		}
		else
		{
			phys.velocity.SetX(0);
		}
	}
}

void PhysicsSystem::HandleCollisions()
{
	while (MessageManager::NotEmpty<CollisionMessage>())
	{
		CollisionMessage message = MessageManager::PopMessage<CollisionMessage>();
		Rect& rect1 = EntityManager::GetComponent<Rect>(message.entityOneIndex);
		Rect& rect2 = EntityManager::GetComponent<Rect>(message.entityTwoIndex);

		//Do collision handling here
		/*
		//Handle horizontal collisions
		if (rectPos1.x < rectPos2.x && rectPos1.x + rect1.width > rectPos2.x)
		{
			pos1.x = rectPos2.x - rect1.width - rect1.offsetX;
		}
		else if (rectPos1.x  < rectPos2.x + rect2.width && rectPos1.x + rect1.width > rectPos2.x + rect2.width)
		{
			pos1.x = rectPos2.x + rect2.width - rect1.offsetX;
		}
		*/

	}
}

void PhysicsSystem::ApplyPhysics()
{
	std::vector<int> entities = EntityManager::GetEntitiesWithComponent<Transform, Physics>();
	for (int entityIndex : entities)
	{
		Transform& trans = EntityManager::GetComponent<Transform>(entityIndex);
		Physics& phys = EntityManager::GetComponent<Physics>(entityIndex);

		phys.velocity *= phys.maxSpeed;

		trans.position += phys.velocity * Time::GetDeltaTime();
	}
}