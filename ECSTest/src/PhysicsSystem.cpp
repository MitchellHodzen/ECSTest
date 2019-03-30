#include "PhysicsSystem.h"
#include "kecs/KECS.h"
#include "Components/c_position.h"
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

void PhysicsSystem::HandleHorizontalCollisions()
{
	while (MessageManager::NotEmpty<CollisionMessage>())
	{
		CollisionMessage message = MessageManager::PopMessage<CollisionMessage>();
		Rect& rect1 = EntityManager::GetComponent<Rect>(message.entityOneIndex);
		Position& pos1 = EntityManager::GetComponent<Position>(message.entityOneIndex);
		Rect& rect2 = EntityManager::GetComponent<Rect>(message.entityTwoIndex);
		Position& pos2 = EntityManager::GetComponent<Position>(message.entityTwoIndex);

		Position rectPos1;
		Position rectPos2;
		rectPos1.x = pos1.x + rect1.offsetX;
		rectPos2.x = pos2.x + rect2.offsetX;

		//Handle horizontal collisions
		if (rectPos1.x < rectPos2.x && rectPos1.x + rect1.width > rectPos2.x)
		{
			pos1.x = rectPos2.x - rect1.width - rect1.offsetX;
		}
		else if (rectPos1.x  < rectPos2.x + rect2.width && rectPos1.x + rect1.width > rectPos2.x + rect2.width)
		{
			pos1.x = rectPos2.x + rect2.width - rect1.offsetX;
		}

	}
}

void PhysicsSystem::HandleVerticalCollisions()
{
	while (MessageManager::NotEmpty<CollisionMessage>())
	{
		CollisionMessage message = MessageManager::PopMessage<CollisionMessage>();
		Rect& rect1 = EntityManager::GetComponent<Rect>(message.entityOneIndex);
		Position& pos1 = EntityManager::GetComponent<Position>(message.entityOneIndex);
		Rect& rect2 = EntityManager::GetComponent<Rect>(message.entityTwoIndex);
		Position& pos2 = EntityManager::GetComponent<Position>(message.entityTwoIndex);

		Position rectPos1;
		Position rectPos2;
		rectPos1.y = pos1.y + rect1.offsetY;
		rectPos2.y = pos2.y + rect2.offsetY;

		//Handle vertical collisions
		if (rectPos1.y < rectPos2.y && rectPos1.y + rect1.height > rectPos2.y)
		{
			pos1.y = rectPos2.y - rect1.height - rect1.offsetY;
		}
		else if (rectPos1.y  < rectPos2.y + rect2.height && rectPos1.y + rect1.height > rectPos2.y + rect2.height)
		{
			pos1.y = rectPos2.y + rect2.height - rect1.offsetY;
		}
	}
}

void PhysicsSystem::ApplyHorizontalPhysics()
{
	std::vector<int> entities = EntityManager::GetEntitiesWithComponent<Position, Physics>();
	for (int entityIndex : entities)
	{
		Position& pos = EntityManager::GetComponent<Position>(entityIndex);
		Physics& phys = EntityManager::GetComponent<Physics>(entityIndex);

		phys.velocity.SetX(phys.velocity.GetX() * phys.maxSpeed);

		pos.x += phys.velocity.GetX() * Time::GetDeltaTime();
	}
}

void PhysicsSystem::ApplyVerticalPhysics()
{
	std::vector<int> entities = EntityManager::GetEntitiesWithComponent<Position, UserInput>();
	for (int entityIndex : entities)
	{
		Position& pos = EntityManager::GetComponent<Position>(entityIndex);
		Physics& phys = EntityManager::GetComponent<Physics>(entityIndex);


		phys.velocity.SetY(phys.velocity.GetY() * phys.maxSpeed);

		pos.y += phys.velocity.GetY() * Time::GetDeltaTime();
	}
}