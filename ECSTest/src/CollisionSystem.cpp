#include "CollisionSystem.h"
#include "kecs/KECS.h"
#include "Components/c_position.h"
#include "Components/c_rect.h"
#include "Components/c_physics.h"
#include "MessageManager.h"
#include "Messages/m_collision.h"

CollisionSystem::CollisionSystem()
{
}


CollisionSystem::~CollisionSystem()
{
}

bool CollisionSystem::RectsColliding(Rect rect1, Position pos1, Rect rect2, Position pos2)
{

	Position rectPos1;
	Position rectPos2;
	rectPos1.x = pos1.x + rect1.offsetX;
	rectPos1.y = pos1.y + rect1.offsetY;
	rectPos2.x = pos2.x + rect2.offsetX;
	rectPos2.y = pos2.y + rect2.offsetY;

	if ((rectPos1.x < rectPos2.x + rect2.width) &&
		(rectPos1.x + rect1.width > rectPos2.x) &&
		(rectPos1.y < rectPos2.y + rect2.height) &&
		(rectPos1.y + rect1.height > rectPos2.y))
	{
		return true;
	}
	return false;
}

void CollisionSystem::CheckCollisions()
{
	std::vector<int> entities = EntityManager::GetEntitiesWithComponent<Position, Physics, Rect>(); //Only entities with physics will collide
	std::vector<int> collidableEntities = EntityManager::GetEntitiesWithComponent<Position, Rect>();
	for (int entityIndex : entities)
	{
		for (int otherEntityIndex : collidableEntities)
		{
			if (entityIndex != otherEntityIndex)
			{
				Rect& rect1 = EntityManager::GetComponent<Rect>(entityIndex);
				Position& pos1 = EntityManager::GetComponent<Position>(entityIndex);
				Rect& rect2 = EntityManager::GetComponent<Rect>(otherEntityIndex);
				Position& pos2 = EntityManager::GetComponent<Position>(otherEntityIndex);

				if (RectsColliding(rect1, pos1, rect2, pos2))
				{
					CollisionMessage message(entityIndex, otherEntityIndex);
					MessageManager::PushMessage<CollisionMessage>(message);
				}

			}
		}
	}
}