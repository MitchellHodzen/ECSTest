#include "CollisionSystem.h"
#include "kecs/KECS.h"
#include "Components/c_transform.h"
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

bool CollisionSystem::RectsColliding(Rect& rect1, Vector2& pos1, Rect& rect2, Vector2& pos2)
{

	Vector2 rectPos1(pos1.GetX() + rect1.offsetX, pos1.GetY() + rect1.offsetY);
	Vector2 rectPos2(pos2.GetX() + rect2.offsetX, pos2.GetY() + rect2.offsetY);

	if ((rectPos1.GetX() < rectPos2.GetX() + rect2.width) &&
		(rectPos1.GetX() + rect1.width > rectPos2.GetX()) &&
		(rectPos1.GetY() < rectPos2.GetY() + rect2.height) &&
		(rectPos1.GetY() + rect1.height > rectPos2.GetY()))
	{
		return true;
	}
	return false;
}

void CollisionSystem::CheckCollisions()
{
	std::vector<int> entities = EntityManager::GetEntitiesWithComponent<Transform, Physics, Rect>(); //Only entities with physics will collide
	std::vector<int> collidableEntities = EntityManager::GetEntitiesWithComponent<Transform, Rect>();
	for (int entityIndex : entities)
	{
		for (int otherEntityIndex : collidableEntities)
		{
			if (entityIndex != otherEntityIndex)
			{
				Rect& rect1 = EntityManager::GetComponent<Rect>(entityIndex);
				Transform& trans1 = EntityManager::GetComponent<Transform>(entityIndex);
				Rect& rect2 = EntityManager::GetComponent<Rect>(otherEntityIndex);
				Transform& trans2 = EntityManager::GetComponent<Transform>(otherEntityIndex);

				if (RectsColliding(rect1, trans1.position, rect2, trans2.position))
				{
					CollisionMessage message(entityIndex, otherEntityIndex);
					MessageManager::PushMessage<CollisionMessage>(message);
				}

			}
		}
	}
}