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
	std::vector<Entity> entities = EntityManager::GetEntitiesWithComponent<Physics, UserInput>();

	for (Entity entity : entities)
	{
		Physics& phys = EntityManager::GetComponent<Physics>(entity);
		UserInput& uin = EntityManager::GetComponent<UserInput>(entity);
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

		phys.velocity *= phys.maxSpeed;
	}
}

void PhysicsSystem::HandleCollisions()
{
	while (MessageManager::NotEmpty<CollisionMessage>())
	{
		CollisionMessage message = MessageManager::PopMessage<CollisionMessage>();
		Rect& rect1 = EntityManager::GetComponent<Rect>(message.entityOne);
		Rect& rect2 = EntityManager::GetComponent<Rect>(message.entityTwo);

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
	std::vector<Entity> entities = EntityManager::GetEntitiesWithComponent<Transform, Physics>();
	for (Entity entity : entities)
	{
		Transform& trans = EntityManager::GetComponent<Transform>(entity);
		Physics& phys = EntityManager::GetComponent<Physics>(entity);

		//Apply delta time to velocity and assign the resulting vector to the movement vector
		Vector2 movementVector = phys.velocity * Time::GetDeltaTime();

		//Clamping speed to max speed
		if (movementVector.GetMagnitude() > phys.maxSpeed)
		{
			movementVector.SetMagnitude(phys.maxSpeed);
		}
		
		//Delta time has already been applied
		trans.position += movementVector;// *Time::GetDeltaTime();
	}
}