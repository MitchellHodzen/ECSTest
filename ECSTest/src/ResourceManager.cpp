#include "ResourceManager.h"
#include "Texture.h"
#include "Renderer.h"

ResourceManager::ResourceManager(Renderer* renderer)
{
	LoadSprites(renderer);
}


ResourceManager::~ResourceManager()
{
	UnloadSprites();
}

bool ResourceManager::LoadSprites(Renderer* renderer)
{

	return LoadSprite("./Resources/Sprites/ship1.png", "Ship1", renderer);
}

bool ResourceManager::LoadSprite(std::string path, std::string key, Renderer* renderer)
{
	Texture* texture = new Texture();
	bool success = texture->LoadTexture(path, renderer);
	if (success)
	{
		texturePointerMap->insert_or_assign(key, texture);
	}
	return success;
}

Texture* ResourceManager::GetTexture(std::string key)
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
