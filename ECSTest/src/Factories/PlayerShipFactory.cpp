#include "Factories/PlayerShipFactory.h"
#include "kecs/KECS.h"
#include "Components/c_transform.h"
#include "Components/c_rect.h"
#include "Components/c_input.h"
#include "Components/c_physics.h"
#include "Components/c_sprite.h"
#include "Tags.h"
#include "ResourceManager.h"


int PlayerShipFactory::ConstructPlayerShip(int posX, int posY)
{
	int playerShip = EntityManager::CreateEntity();
	EntityManager::AddTag<Player>(playerShip);
	EntityManager::AddComponent<UserInput>(playerShip);

	Transform trans;
	trans.position.SetValues(posX, posY);
	EntityManager::SetComponent<Transform>(playerShip, trans);

	Rect rect;
	rect.width = 50;
	rect.height = 50;
	rect.offsetX = -rect.width / 2;
	rect.offsetY = -rect.height / 2;
	EntityManager::SetComponent<Rect>(playerShip, rect);

	Sprite sprite;
	sprite.texture = ResourceManager::GetInstance().GetTexture(ResourceManager::SpriteKey::Player);
	EntityManager::SetComponent<Sprite>(playerShip, sprite);

	Physics physics;
	physics.maxSpeed = 200;
	EntityManager::SetComponent<Physics>(playerShip, physics);

	return playerShip;
}
