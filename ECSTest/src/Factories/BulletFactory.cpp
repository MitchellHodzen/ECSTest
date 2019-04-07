#include "Factories/BulletFactory.h"
#include "kecs/KECS.h"
#include "Components/c_transform.h"
#include "Components/c_physics.h"
#include "Components/c_sprite.h"
#include "ResourceManager.h"


Entity BulletFactory::ConstructBullet(int posX, int posY)
{

	Entity bullet = EntityManager::CreateEntity();

	Transform bulletTransform;
	bulletTransform.position.SetValues(posX, posY);
	EntityManager::SetComponent<Transform>(bullet, bulletTransform);

	Sprite bulletSprite;
	bulletSprite.texture = ResourceManager::GetInstance().GetTexture(ResourceManager::SpriteKey::Bullet);
	EntityManager::SetComponent<Sprite>(bullet, bulletSprite);

	Physics bulletPhysics;
	bulletPhysics.velocity.SetValues(0, -500);
	bulletPhysics.maxSpeed = 500;
	EntityManager::SetComponent<Physics>(bullet, bulletPhysics);

	return bullet;
}
