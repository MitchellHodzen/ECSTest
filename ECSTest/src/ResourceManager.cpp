#include "ResourceManager.h"
#include "Texture.h"
#include "RenderSystem.h"

ResourceManager::ResourceManager(RenderSystem* renderSystem)
{
	LoadSprites(renderSystem);
}


ResourceManager::~ResourceManager()
{
	UnloadSprites();
}

bool ResourceManager::LoadSprites(RenderSystem* renderSystem)
{

	return LoadSprite("./Resources/Sprites/ship1.png", SpriteKey::Player, renderSystem);
}

bool ResourceManager::LoadSprite(std::string path, SpriteKey key, RenderSystem* renderSystem)
{
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
