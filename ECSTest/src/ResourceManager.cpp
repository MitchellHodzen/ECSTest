#include "ResourceManager.h"
#include "Texture.h"

ResourceManager::ResourceManager()
{
	//LoadSprites();
}


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

bool ResourceManager::Initialize() {
	return LoadSprites();
}

bool ResourceManager::LoadSprites()
{
	Texture* shipTexture = new Texture();
	return shipTexture->LoadTexture("./Resources/Sprites/ship1.png");
}

bool ResourceManager::LoadSprite(std::string path, std::string key) 
{
	Texture* texture = new Texture();
	bool success = texture->LoadTexture(path);
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
