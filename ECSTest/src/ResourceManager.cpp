#include "ResourceManager.h"
#include "Texture.h"
#include "RenderSystem.h"

ResourceManager::~ResourceManager()
{
	UnloadSprites();
}

ResourceManager& ResourceManager::GetInstance()
{
	//No need to check if the instance exists, C++ won't create another static instance
	//Also thread safe by default, C++ automatically locks on instance creation
	static ResourceManager instance;
	return instance;
}

bool ResourceManager::Initialize(RenderSystem* renderSystem) {
	return LoadSprites(renderSystem);
}

bool ResourceManager::LoadSprites(RenderSystem* renderSystem)
{

	return LoadSprite("./Resources/Sprites/ship1.png", SpriteKey::Player, renderSystem)
	&& LoadSprite("./Resources/Sprites/bullet1.png", SpriteKey::Bullet, renderSystem)
	&& LoadSprite("./Resources/Sprites/enemy1.png", SpriteKey::Enemy, renderSystem);

}

bool ResourceManager::LoadSprite(std::string path, SpriteKey key, RenderSystem* renderSystem)
{
	std::cout << "Loading Sprite at " << path << std::endl;
	Texture* texture = new Texture();
	bool success = texture->LoadTexture(path, renderSystem);
	if (success)
	{
		texturePointerMap->insert_or_assign(key, texture);
	}
	return success;
}

Texture* ResourceManager::GetTexture(SpriteKey key)
{
	if (texturePointerMap->count(key))
	{
		return texturePointerMap->at(key);
	}
	return nullptr;
}

void ResourceManager::UnloadSprites()
{
	texturePointerMap->clear();
}
