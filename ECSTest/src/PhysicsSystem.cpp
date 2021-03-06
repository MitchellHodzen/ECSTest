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

void PhysicsSystem::HandleCollisions()
{
	while (MessageManager::NotEmpty<CollisionMessage>())
	{
		CollisionMessage message = MessageManager::PopMessage<CollisionMessage>();
		Rect* rect1 = EntityManager::GetComponent<Rect>(message.entityOne);
		Rect* rect2 = EntityManager::GetComponent<Rect>(message.entityTwo);

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
		Transform* trans = EntityManager::GetComponent<Transform>(entity);
		Physics* phys = EntityManager::GetComponent<Physics>(entity);

		//Clamping speed to max speed
		if (phys->velocity.GetMagnitude() > phys->maxSpeed)
		{
			phys->velocity.SetMagnitude(phys->maxSpeed);
		}

		//Apply delta time to velocity and assign the resulting vector to the movement vector
		Vector2 movementVector = phys->velocity * Time::GetDeltaTime();

		//Delta time has already been applied
		trans->position += movementVector;// *Time::GetDeltaTime();
	}
}